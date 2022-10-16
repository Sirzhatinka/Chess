#pragma once

#include <fstream>

#include "Drawer.hpp"

// can be useful for action tracking during playing or logging
class FileDrawer : public Drawer
{
    std::ofstream _drawOutput;
    std::ifstream _askInput;
public:
    FileDrawer(const Chess::Gameplay* gp);

    void drawMainMenu()     const final;
    void drawSettingsMenu() const final;
    void drawBoard()        const final;
};