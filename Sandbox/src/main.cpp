#define TIMGE_ENABLE_IMGUI
#include <iostream>
#include <TIMGE/Exception.hpp>
#include "Game.hpp"

int main()
{
    try {
        Game game;
        game.Run();
    } catch (const TIMGE::Exception& e) {
        std::cerr << e.What() << "!\n";
    } catch (...) {
        std::cerr << "An unknown exception has been thrown!\n";
    }
}


