//
// Created by Sirzh on 15.04.2021.
//

#include "Player.h"
#include "Piece\Piece.h"
#include "Board.h"
#include <typeinfo>


Player::Player(Board* b, Traits::Color c)
: board(b)
, color(c)
{
    board->addPlayer(this);

    Traits::Vertical startOfPawns = (color == Traits::Color::WHITE) ? Traits::Vertical::two : Traits::Vertical::seven;
    Traits::Vertical startOfOthers = (color == Traits::Color::WHITE) ? Traits::Vertical::one : Traits::Vertical::eight;

    unsigned alongLine = 0;
    for (auto& pwn: pawn)
    {
        pwn = new Pawn{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine }, startOfPawns } };
        board->setPiece(pwn, pwn->getCoord());
    }

    alongLine = -1;
    for (unsigned i = 0, inc = 1; i < PAIR_PIECES; i++)
    {
        rook[i] = new Rook{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(rook[i], rook[i]->getCoord());

        knight[i] = new Knight{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(knight[i], knight[i]->getCoord());

        bishop[i] = new Bishop{ this, Traits::Coordinates{ Traits::Horizontal{ alongLine += inc }, startOfOthers } };
        board->setPiece(bishop[i], bishop[i]->getCoord());

        inc *= -1;
        alongLine += 6;
    }

    // Queen prefers corresponding color
    queen = new Queen{ this, Traits::Coordinates{ Traits::Horizontal::D, startOfOthers } };
    board->setPiece(queen, queen->getCoord());

    king = new King{ this, Traits::Coordinates{ Traits::Horizontal::E, startOfOthers } };
    board->setPiece(king, king->getCoord());
}

void Player::move(Traits::Coordinates from, Traits::Coordinates to)
{
    auto piece = board->getPiece(from);
    if (this == piece->getPlayer())
    {
        if (board->getPiece(to)->getPlayer() != this)
        {
            // instead of searching for pointer with corresponding address inside of Player, we use const_cast<>()
            const_cast<Piece*>(piece)->move(to);
        }
    }
}