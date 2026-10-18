#include "audio_runtime.hpp"
#include "spatial_audio.hpp"
#include "miniaudio.h"
#include <cmath>
namespace echodrive {
AudioRuntime::AudioRuntime() { start(); }
AudioRuntime::~AudioRuntime() { stop(); }
bool AudioRuntime::start(){ if(ready_) return true; engine_=new ma_engine{}; ma_engine_config config=ma_engine_config_init(); if(ma_engine_init(&config,engine_)!=MA_SUCCESS){delete engine_;engine_=nullptr;return false;} ready_=true; return true; }
void AudioRuntime::stop(){ for(auto* s:sounds_){if(s){ma_sound_uninit(s);delete s;}} sounds_.clear(); if(engine_){ma_engine_uninit(engine_);delete engine_;engine_=nullptr;} ready_=false; }
void AudioRuntime::applySpatial(ma_sound* sound,Vec3 p,float volume){SpatialAudioEngine spatial;spatial.setListener(listener_,heading_);lastSample_=spatial.evaluate(p,volume,1.0,100.0);ma_sound_set_volume(sound,(float)lastSample_.gain);ma_sound_set_pan(sound,(float)lastSample_.pan);ma_sound_set_position(sound,(float)p.x,(float)p.y,(float)p.z);}
bool AudioRuntime::playLoop(const std::string& path,Vec3 p,float volume){if(!ready_)return false;auto* s=new ma_sound{};if(ma_sound_init_from_file(engine_,path.c_str(),MA_SOUND_FLAG_NO_PITCH|MA_SOUND_FLAG_STREAM,nullptr,nullptr,s)!=MA_SUCCESS){delete s;return false;}applySpatial(s,p,volume);ma_sound_set_looping(s,MA_TRUE);ma_sound_start(s);sounds_.push_back(s);return true;}
bool AudioRuntime::playOneShot(const std::string& path,Vec3 p,float volume){if(!ready_)return false;auto* s=new ma_sound{};if(ma_sound_init_from_file(engine_,path.c_str(),MA_SOUND_FLAG_NO_PITCH|MA_SOUND_FLAG_DECODE,nullptr,nullptr,s)!=MA_SUCCESS){delete s;return false;}applySpatial(s,p,volume);ma_sound_start(s);sounds_.push_back(s);return true;}
void AudioRuntime::setListener(Vec3 p,double h){listener_=p;heading_=h;}
}
