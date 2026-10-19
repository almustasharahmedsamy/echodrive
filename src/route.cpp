#include "route.hpp"
#include <algorithm>
#include <array>
#include <cmath>
namespace echodrive {
void RouteMap::load(int id){state_.streetId=std::clamp(id,1,15);state_.lengthM=2600+state_.streetId*380;state_.speedLimit=state_.streetId%3==0?80:state_.streetId%3==1?50:110;state_.progressM=0;state_.landmark=0;}
void RouteMap::advance(double kmh,double seconds){state_.progressM=std::min(state_.lengthM,state_.progressM+std::max(0.0,kmh)*1000.0/3600.0*seconds);state_.landmark=std::min(4,(int)(state_.progressM/(state_.lengthM/5.0)));}
void RouteMap::reset(){state_.progressM=0;state_.landmark=0;}
std::string RouteMap::nextLandmark(bool ar)const{static const std::array<const char*,5>a={"بداية الطريق","تقاطع رئيسي","منطقة مزدحمة","منعطف قادم","نهاية الشارع"};static const std::array<const char*,5>e={"Route start","Main intersection","Busy district","Upcoming turn","Street finish"};return ar?a[state_.landmark]:e[state_.landmark];}
std::string RouteMap::render(bool ar)const{const int width=30;int mark=(int)std::round((state_.progressM/state_.lengthM)*(width-1));std::string line(width,'-');line[std::clamp(mark,0,width-1)]='X';return (ar?"خريطة المسار: [":"Route map: [")+line+"] "+nextLandmark(ar);}
}
