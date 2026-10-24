#pragma once
#include "voice.hpp"
#include <string>
namespace echodrive {
struct UiText {
    std::string title;
    std::string streetPrompt;
    std::string vehiclePrompt;
    std::string controlsTitle;
    std::string statusLabel;
    std::string mapLabel;
    std::string weatherLabel;
    std::string trafficLabel;
    std::string stationsLabel;
    std::string customizeLabel;
    std::string profileLabel;
    std::string missionLabel;
    std::string accessibilityLabel;
    std::string scenarioLabel;
    std::string forwardLabel;
    std::string brakeLabel;
    std::string leftLabel;
    std::string rightLabel;
    std::string fasterLabel;
    std::string slowerLabel;
    std::string autoLabel;
    std::string manualLabel;
    std::string pauseLabel;
    std::string quitLabel;
    std::string welcome;
    std::string paused;
    std::string resumed;
    std::string unknown;
    std::string goodbye;
    std::string languageSelected;
    std::string controlsBody;
};
class Localization {
public:
    static UiText ui(Language language);
    static std::string languageCode(Language language);
    static std::string languageName(Language language);
    static std::string selectStreet(Language language, int max);
    static std::string selectVehicle(Language language, int max);
    static std::string speedSummary(Language language, int speed, int travelled, int remaining);
    static std::string selectedVehicle(Language language, const std::string& name, int topSpeed);
    static std::string startedStreet(Language language, const std::string& name, const std::string& country, int meters);
    static std::string weather(Language language, const std::string& name, const std::string& advisory);
    static std::string traffic(Language language, const std::string& alert);
};
}
