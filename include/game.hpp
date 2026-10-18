#pragma once
#include "settings.hpp"
#include "voice.hpp"
#include <string>
#include <vector>
namespace echodrive {
enum class Command { Forward, Brake, Left, Right, Faster, Slower, Auto, Manual, Repeat, Reset, Quit, Unknown };
struct Street { int id; std::string ar; std::string en; std::string description; };
class Game {
public: Game(); void run();
private:
 Settings settings_; VoiceGuide voice_; double speed_=0; int heading_=0; std::vector<Street> streets_;
 Command parse(const std::string&) const; void selectStreet(); void handle(Command); void status() const; void menu() const;
};
}
