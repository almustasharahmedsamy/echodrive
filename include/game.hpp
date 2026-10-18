#pragma once
#include "content.hpp"
#include "settings.hpp"
#include "spatial_audio.hpp"
#include "voice.hpp"
#include <string>
namespace echodrive {
enum class Command { Forward, Brake, Left, Right, Faster, Slower, Auto, Manual, Repeat, Reset, ListStreets, ListVehicles, Quit, Unknown };
class Game {
public: Game(); void run();
private:
 Settings settings_; VoiceGuide voice_; SpatialAudioEngine audio_; double speed_=0; int heading_=0; int vehicle_=1;
 Command parse(const std::string&) const; void selectStreet(); void selectVehicle(); void handle(Command); void status() const; void menu() const; void listContent() const;
};
}
