#pragma once

#include <pai/entity.h>
#include <nanogui/screen.h>
#include <string>
#include <vector>

class Game : public nanogui::Screen
{
public:
    Game(int width,
         int height,
         std::string title);

    void initializeBoard();
    void clearScreen(NVGcontext* ctx);
    void draw(NVGcontext* ctx);

protected:
    std::vector<Entity*> entities;
};
