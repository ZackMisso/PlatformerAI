#include <pai/game.h>
#include <pai/ground.h>
#include <pai/player.h>

Game::Game(int width,
           int height,
           std::string title)
           : nanogui::Screen(nanogui::Vector2i(width, height), title)
{
    entities = std::vector<Entity*>();
    initializeBoard();
}

void Game::clearScreen(NVGcontext* ctx)
{
    // clear the screen
    nvgBeginPath(ctx);
    nvgRect(ctx, 0, 0, 1024, 1024);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgFill(ctx);
}

void Game::initializeBoard()
{
    for (int i = 0; i < 20; ++i)
    {
        Ground* ground = new Ground();
        ground->setPos(i * 32.f, 320.f);
        entities.push_back(ground);
    }

    Player* player = new Player();
    player->setPos(320.f, 288.f);
    entities.push_back(player);
}

void Game::draw(NVGcontext* ctx)
{
    clearScreen(ctx);

    for (int i = 0; i < entities.size(); ++i)
    {
        entities[i]->draw(ctx);
    }
}
