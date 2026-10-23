#pragma once
#include <string>
#include <vector>
namespace echodrive {
struct KeyBinding { std::string action; std::string key; std::string arabicLabel; };
struct AccessibilitySettings { bool highContrast = true; bool reduceMotion = true; bool repeatAnnouncements = true; bool mouseMode = false; int speechRate = 0; int speechVolume = 100; int verbosity = 2; };
class AccessibilityProfile {
public:
 AccessibilityProfile();
 void toggleContrast(); void toggleMotion(); void toggleRepeat(); void toggleMouse();
 void speechFaster(); void speechSlower(); void volumeUp(); void volumeDown(); void verbosityUp(); void verbosityDown();
 void bind(const std::string& action, const std::string& key);
 const AccessibilitySettings& settings() const;
 const std::vector<KeyBinding>& bindings() const;
 std::string summary(bool arabic) const;
 std::string bindingSummary(bool arabic) const;
 bool save(const std::string& path) const;
 bool load(const std::string& path);
private:
 AccessibilitySettings settings_;
 std::vector<KeyBinding> bindings_;
 void createDefaultBindings();
};
}
