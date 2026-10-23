#include "accessibility.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
namespace echodrive {
AccessibilityProfile::AccessibilityProfile() { createDefaultBindings(); }
void AccessibilityProfile::createDefaultBindings() {
    bindings_ = {
        {"forward", "UP", "تقدم"}, {"brake", "DOWN", "فرامل"},
        {"steer_left", "LEFT", "يسار"}, {"steer_right", "RIGHT", "يمين"},
        {"status", "F1", "الحالة"}, {"map", "F2", "الخريطة"},
        {"weather", "F3", "الطقس"}, {"traffic", "F4", "المرور"},
        {"stations", "F5", "المحطات"}, {"customize", "F6", "التخصيص"},
        {"new_vehicle", "F7", "سيارة جديدة"}, {"language", "F8", "اللغة"},
        {"controls", "F9", "التحكم"}, {"pause", "F10", "إيقاف"},
        {"reset", "F11", "إعادة"}, {"regions", "F12", "المحافظات"},
        {"horn", "G", "البوق"}, {"engine", "CAPSLOCK", "المحرك"},
        {"next_car", "TAB", "السيارة التالية"}, {"pause_alt", "ESC", "إيقاف بديل"}
    };
}
void AccessibilityProfile::toggleContrast() { settings_.highContrast = !settings_.highContrast; }
void AccessibilityProfile::toggleMotion() { settings_.reduceMotion = !settings_.reduceMotion; }
void AccessibilityProfile::toggleRepeat() { settings_.repeatAnnouncements = !settings_.repeatAnnouncements; }
void AccessibilityProfile::toggleMouse() { settings_.mouseMode = !settings_.mouseMode; }
void AccessibilityProfile::speechFaster() { settings_.speechRate = std::min(10, settings_.speechRate + 1); }
void AccessibilityProfile::speechSlower() { settings_.speechRate = std::max(-10, settings_.speechRate - 1); }
void AccessibilityProfile::volumeUp() { settings_.speechVolume = std::min(100, settings_.speechVolume + 5); }
void AccessibilityProfile::volumeDown() { settings_.speechVolume = std::max(0, settings_.speechVolume - 5); }
void AccessibilityProfile::verbosityUp() { settings_.verbosity = std::min(4, settings_.verbosity + 1); }
void AccessibilityProfile::verbosityDown() { settings_.verbosity = std::max(0, settings_.verbosity - 1); }
void AccessibilityProfile::bind(const std::string& action, const std::string& key) { for (auto& binding : bindings_) if (binding.action == action) { binding.key = key; return; } bindings_.push_back({action, key, action}); }
const AccessibilitySettings& AccessibilityProfile::settings() const { return settings_; }
const std::vector<KeyBinding>& AccessibilityProfile::bindings() const { return bindings_; }
std::string AccessibilityProfile::summary(bool ar) const { std::ostringstream out; if (ar) out << "الإتاحة: تباين " << (settings_.highContrast ? "مرتفع" : "عادي") << "، حركة مخففة " << (settings_.reduceMotion ? "نعم" : "لا") << "، تكرار صوتي " << (settings_.repeatAnnouncements ? "نعم" : "لا") << "، ماوس " << (settings_.mouseMode ? "مفعل" : "لوحة مفاتيح") << "، سرعة صوت " << settings_.speechRate << "، مستوى التفاصيل " << settings_.verbosity; else out << "Accessibility: contrast " << (settings_.highContrast ? "high" : "normal") << ", reduced motion " << (settings_.reduceMotion ? "yes" : "no") << ", repeat " << (settings_.repeatAnnouncements ? "yes" : "no") << ", mouse " << (settings_.mouseMode ? "on" : "keyboard") << ", speech rate " << settings_.speechRate << ", verbosity " << settings_.verbosity; return out.str(); }
std::string AccessibilityProfile::bindingSummary(bool ar) const { std::ostringstream out; for (const auto& binding : bindings_) { if (ar) out << binding.arabicLabel << "=" << binding.key << "، "; else out << binding.action << "=" << binding.key << ", "; } return out.str(); }
bool AccessibilityProfile::save(const std::string& path) const { std::ofstream out(path); if (!out) return false; out << settings_.highContrast << ' ' << settings_.reduceMotion << ' ' << settings_.repeatAnnouncements << ' ' << settings_.mouseMode << ' ' << settings_.speechRate << ' ' << settings_.speechVolume << ' ' << settings_.verbosity << '\n'; for (const auto& binding : bindings_) out << binding.action << ' ' << binding.key << '\n'; return true; }
bool AccessibilityProfile::load(const std::string& path) { std::ifstream in(path); if (!in) return false; in >> settings_.highContrast >> settings_.reduceMotion >> settings_.repeatAnnouncements >> settings_.mouseMode >> settings_.speechRate >> settings_.speechVolume >> settings_.verbosity; std::string action; std::string key; while (in >> action >> key) bind(action, key); return static_cast<bool>(in) || in.eof(); }
}
