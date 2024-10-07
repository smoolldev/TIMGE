#include <TIMGE/TIMGE.hpp>
#include <cstdint>
#include <cstdlib>
#include <string_view>

class Game : public TIMGE::Application
{
    public:
        Game(std::string_view title, uint32_t width, uint32_t height)
            : TIMGE::Application(title, width, height)
        {
            
        }
        ~Game();
};

int main(int argc, char **argv)
{
    Game game = Game::Game("title", 1280, 720);

    if (!game)
    { exit(-1); }

    game.Run();

    return 0;
}
