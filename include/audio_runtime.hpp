#pragma once
#include "spatial_audio.hpp"
#include <memory>
#include <string>
#include <vector>
struct ma_engine;
struct ma_sound;
namespace echodrive {
class AudioRuntime {
public:
    AudioRuntime();
    ~AudioRuntime();
    AudioRuntime(const AudioRuntime&) = delete;
    bool start();
    void stop();
    bool ready() const { return ready_; }
    bool playLoop(const std::string& path, Vec3 position, float volume=1.0f);
    bool playOneShot(const std::string& path, Vec3 position, float volume=1.0f);
    void setListener(Vec3 position, double headingRadians);
    SpatialSample lastSample() const { return lastSample_; }
private:
    ma_engine* engine_ = nullptr;
    std::vector<ma_sound*> sounds_;
    Vec3 listener_{};
    double heading_=0;
    bool ready_=false;
    SpatialSample lastSample_{};
    void applySpatial(ma_sound* sound, Vec3 position, float volume);
};
}
