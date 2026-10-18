#include "spatial_audio.hpp"
#include <algorithm>
#include <cmath>
#include <sstream>
namespace echodrive {
void SpatialAudioEngine::setListener(Vec3 p,double h){listener_=p;heading_=h;}
SpatialSample SpatialAudioEngine::evaluate(Vec3 s,double base,double ref,double max)const{double dx=s.x-listener_.x, dz=s.z-listener_.z;double d=std::sqrt(dx*dx+dz*dz);double relative=std::atan2(dx,dz)-heading_;while(relative>3.141592653589793)relative-=6.283185307179586;while(relative<-3.141592653589793)relative+=6.283185307179586;double gain=base*std::clamp(ref/std::max(ref,d),0.0,1.0)*std::clamp(1.0-d/max,0.0,1.0);return {gain,std::sin(relative),d,relative};}
std::string SpatialAudioEngine::describe(const std::string& ar,const std::string& en,const SpatialSample&s,bool arabic)const{std::ostringstream o;o<<(arabic?ar:en)<<" | "<<(arabic?"المسافة ":"distance ")<<(int)s.distance<<(arabic?" متر، الاتجاه الجانبي ":" meters, side ")<<(int)(s.pan*100)<<(arabic?" بالمئة":" percent");return o.str();}
}
