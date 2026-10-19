#pragma once
#include <string>
#include <vector>
namespace echodrive {
enum class TrafficState { Cruising, Following, Yielding, ChangingLane, Emergency };
struct TrafficVehicle { int id; std::string type; double distance; double lateral; double speed; bool emergency; TrafficState state=TrafficState::Cruising; int lane=0; double reaction=1.0; };
class TrafficSystem {
public:
 TrafficSystem();
 void reset(int streetId);
 void tick(double playerSpeed, bool automaticDriving);
 const std::vector<TrafficVehicle>& vehicles() const { return vehicles_; }
 std::string nearestAlert(bool arabic) const;
 std::string diagnostics(bool arabic) const;
private:
 std::vector<TrafficVehicle> vehicles_; int street_=1; unsigned tick_=0;
};
}
