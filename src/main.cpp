#include <pai/game.h>
#include <nanogui/glutil.h>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
    // TODO

    std::cout << "Hello World" << std::endl;

    try {
        nanogui::init();
        {
           nanogui::ref<Game> app = new Game(640, 640, "platformer ai");
           app->drawAll();
           app->setVisible(true);
           nanogui::mainloop();
        }
        nanogui::shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
        return -1;
    }

    return 0;
}
