#pragma once
#include "content.hpp"
#include "audio_runtime.hpp"
#include "audio_assets.hpp"
#include "settings.hpp"
#include "spatial_audio.hpp"
#include "voice.hpp"
#include "traffic.hpp"
#include "weather.hpp"
#include "route.hpp"
#include "vehicle_system.hpp"
#include "regions.hpp"
#include "career.hpp"
#include "accessibility.hpp"
#include "scenarios.hpp"
#include "economy.hpp"
#include "telemetry.hpp"
#include <string>
namespace echodrive {
enum class Command { Forward, Brake, Left, Right, Faster, Slower, Auto, Manual, Repeat, Reset, ListStreets, ListVehicles, WeatherCycle, Traffic, Map, Controls, Horn, Pause, Engine, Stations, Customize, Language, RegionMap, NewVehicle, Profile, Mission, Accessibility, Quit, Unknown };
class Game {
public:
    Game();
    void run();
private:
    Settings settings_;
    VoiceGuide voice_;
    SpatialAudioEngine audio_;
    AudioRuntime runtime_;
    TrafficSystem traffic_;
    WeatherSystem weather_;
    RouteMap route_;
    VehicleSystem vehicleSystem_;
    CareerProfile career_;
    AccessibilityProfile accessibility_;
    ScenarioBook scenarios_;
    EconomySystem economy_;
    TelemetryRecorder telemetry_;
    double speed_ = 0;
    int heading_ = 0;
    int vehicle_ = 1;
    int region_ = 1;
    bool paused_ = false;
    bool engineOn_ = true;
    Command parse(const std::string&) const;
    std::string readInput() const;
    void selectStreet();
    void selectVehicle();
    void handle(Command);
    void status() const;
    void menu() const;
    void listContent() const;
    void showControls() const;
};
}
