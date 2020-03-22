#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <array>
#include <string>

#include "fmt/format.h"

static constexpr auto USAGE =
R"(C++ Weekly Game.
    Usage:
          game [options]
  Options:
          -h --help         Show this screen.
          --width=WIDTH     Screen width in pixels [default: 1024].
          --height=HEIGHT   Screen height in pixels [default: 768].
          --scale=SCALE     Scaling factor [default: 2].
)";

int main(int argc, const char** argv)
{
    double width = 1024;
    double height = 768;
    double scale = 3;

     sf::RenderWindow window(
        sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    const auto scale_factor = static_cast<float>(scale);
    ImGui::GetStyle().ScaleAllSizes(scale_factor);
    ImGui::GetIO().FontGlobalScale = scale_factor;
    

    std::array<std::string, 13> steps = { "The Plan",
      "Getting Started",
      "Finding Errors As Soon As Possible",
      "Handling Command Line Parameters",
      "C++ 20 So Far",
      "Reading SFML Input States",
      "Managing Game State",
      "Making Our Game Testable",
      "Making Game State Allocator Aware",
      "Add Logging To Game Engine",
      "Draw A Game Map",
      "Dialog Trees",
      "Porting From SFML To SDL" };

    std::array<bool, steps.size()> states{};

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) { window.close(); }
        }

        ImGui::SFML::Update(window, deltaClock.restart());


        ImGui::Begin("The Plan");

        for (std::size_t index = 0; index < steps.size(); ++index) {
            ImGui::Checkbox(fmt::format("{} : {}", index, steps.at(index)).c_str(), &states.at(index));
        }


        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}