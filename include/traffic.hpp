#pragma once
#include <string>
#include <vector>
namespace echodrive {
struct TrafficVehicle { int id; std::string type; double distance; double lateral; double speed; bool emergency; };
class TrafficSystem {
public:
    TrafficSystem();
    void reset(int streetId);
    void tick(double playerSpeed, bool automaticDriving);
    const std::vector<TrafficVehicle>& vehicles() const { return vehicles_; }
    std::string nearestAlert(bool arabic) const;
private:
    std::vector<TrafficVehicle> vehicles_;
    int street_=1;
    unsigned tick_=0;
};
}
