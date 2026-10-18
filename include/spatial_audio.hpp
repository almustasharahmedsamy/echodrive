#pragma once
#include <string>
namespace echodrive {
struct Vec3 { double x=0; double y=0; double z=0; };
struct SpatialSample { double gain=0; double pan=0; double distance=0; double azimuth=0; };
class SpatialAudioEngine {
public:
    void setListener(Vec3 position, double headingRadians);
    SpatialSample evaluate(Vec3 source, double baseGain=1.0, double referenceDistance=1.0, double maxDistance=100.0) const;
    std::string describe(const std::string& ar, const std::string& en, const SpatialSample& sample, bool arabic) const;
private: Vec3 listener_{}; double heading_=0;
};
}
