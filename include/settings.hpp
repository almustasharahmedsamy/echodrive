#pragma once
#include "voice.hpp"
#include <string>
namespace echodrive {
struct Settings { Language language=Language::Arabic; bool automaticDriving=false; bool repeatGuidance=true; int masterVolume=80; int street=1; };
bool saveSettings(const Settings&, const std::string&);
Settings loadSettings(const std::string&);
}
