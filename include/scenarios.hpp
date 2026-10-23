#pragma once
#include <string>
#include <vector>
namespace echodrive {
enum class ScenarioType { Delivery, Emergency, FuelSaving, WeatherChallenge, AccessibilityTraining, NightDrive, RegionalTour };
struct Scenario { int id; ScenarioType type; std::string title; std::string objective; int reward; int timeLimit; bool unlocked; bool completed; };
class ScenarioBook {
public:
 ScenarioBook();
 void reset();
 void update(double speed, double distance, bool emergencyYielded, bool lowFuel, int weatherIndex, int region);
 void unlock(int id);
 void complete(int id);
 const std::vector<Scenario>& all() const;
 std::string active(bool arabic) const;
 std::string summary(bool arabic) const;
 bool save(const std::string& path) const;
 bool load(const std::string& path);
private:
 std::vector<Scenario> scenarios_;
 int activeId_ = 1;
};
}
