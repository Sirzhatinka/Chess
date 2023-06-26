//
// Created by Sirzh on 09.08.2021.
//
#pragma once

#include <utility>
#include <stdexcept>
#include <optional>

namespace Chess
{
constexpr auto boardSize = 8;

enum class Horizontal { A,   B,   C,     D,    E,    F,   G,     H     };
enum class Vertical   { one, two, three, four, five, six, seven, eight };

enum class Color : bool { BLACK, WHITE };

struct Coordinates
{
    Horizontal x;
    Vertical   y;

    Coordinates() = default;
    Coordinates(int x_, int y_);
    Coordinates(Horizontal x_, Vertical y_) noexcept;

    static std::optional<Coordinates> makeCoord(int x_, int y_) noexcept;

    bool tryShiftAt(int x_, int y_);

    bool operator==(const Coordinates& c) const;
    bool operator!=(const Coordinates& c) const;
};


struct Move
{
    Coordinates from;
    Coordinates to;

    bool operator==(const Move& m) const;
    bool operator!=(const Move& m) const;
};

}
