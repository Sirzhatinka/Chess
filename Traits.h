//
// Created by Sirzh on 09.08.2021.
//

#ifndef CHESS_TRAITS_H
#define CHESS_TRAITS_H

enum class Horizontal{ A = 1, B, C, D, E, F, G, H };
enum class Vertical { one = 1, two, three, four, five, six, seven, eight };

struct Coordinates { Horizontal h; Vertical v; };

enum class Color { BLACK, WHITE };

#endif //CHESS_TRAITS_H
