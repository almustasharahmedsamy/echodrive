#pragma once
#include <string>
#include <vector>
namespace echodrive {
enum class TelemetryEvent { Start, SpeedChange, Brake, Turn, Weather, Traffic, Refuel, Repair, Mission, Collision, Finish };
struct TelemetrySample { int second; double speed; double fuel; double damage; int region; TelemetryEvent event; std::string note; };
struct DrivingReport { int elapsedSeconds=0; double averageSpeed=0; double maximumSpeed=0; double fuelUsed=0; double damageTaken=0; int warnings=0; int collisions=0; int accessibilityPrompts=0; };
class TelemetryRecorder {
public:
 TelemetryRecorder();
 void start(int street,int vehicle,int region);
 void sample(double speed,double fuel,double damage,int region,TelemetryEvent event,const std::string& note);
 void addWarning();
 void addCollision();
 void addAccessibilityPrompt();
 void finish();
 const std::vector<TelemetrySample>& samples() const;
 const DrivingReport& report() const;
 std::string reportText(bool arabic) const;
 std::string timeline(bool arabic) const;
 std::string safetyGrade(bool arabic) const;
 int riskScore() const;
 int sampleCount() const;
 std::string eventName(TelemetryEvent event, bool arabic) const;
 bool exportCsv(const std::string& path) const;
 void clear();
 bool save(const std::string& path) const;
 bool load(const std::string& path);
private:
 std::vector<TelemetrySample> samples_;
 DrivingReport report_;
 int street_=1;
 int vehicle_=1;
 int region_=1;
 double firstFuel_=0;
 double lastSpeed_=0;
 void recalculate();
};
}
