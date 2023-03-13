#pragma once

#include <Interfaces/IDrawer.hpp>

class Drawer : public IDrawer
{
    void drawBoard(const Chess::Board& board) const override;

    void showRemainingTime(const Chess::Match& m) const;
public:
    Drawer() = default;

    void drawMainMenu()     const override;
    void drawSettingsMenu() const override;
    void drawMatchEnd(Chess::Match::Winner winner) const override;
    void drawPlay(const Chess::Match& match)       const override;
};