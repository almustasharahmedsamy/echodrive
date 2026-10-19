#pragma once
#include <string>
namespace echodrive {
struct RouteState { int streetId=1; double lengthM=3000; double progressM=0; int speedLimit=60; int landmark=0; };
class RouteMap {
public:
    void load(int streetId);
    void advance(double speedKmh, double seconds=1.0);
    void reset();
    const RouteState& state() const { return state_; }
    std::string nextLandmark(bool arabic) const;
    std::string render(bool arabic) const;
private: RouteState state_{};
};
}
