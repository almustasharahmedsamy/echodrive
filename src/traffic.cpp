#include "traffic.hpp"
#include <algorithm>
#include <cmath>
namespace echodrive {
TrafficSystem::TrafficSystem(){reset(1);}
void TrafficSystem::reset(int streetId){street_=streetId;tick_=0;vehicles_.clear();const char* types[]={"سيدان","حافلة","شاحنة","دراجة","سيارة أجرة","شرطة"};for(int i=0;i<6;i++)vehicles_.push_back({i+1,types[(i+streetId)%6],18.0+i*13.0,(i%3-1)*1.7,35.0+(i*9)%45,i==5});}
void TrafficSystem::tick(double playerSpeed,bool automatic){++tick_;for(auto&v:vehicles_){double delta=(v.speed-playerSpeed)*0.02;v.distance-=delta;if(v.distance<4)v.distance=75+(v.id*11)%35;v.lateral+=std::sin((tick_+v.id*17)*0.025)*0.03;if(automatic&&v.distance<22)v.speed=std::max(12.0,v.speed-1.5);else v.speed=std::min(95.0,v.speed+0.4);}}
std::string TrafficSystem::nearestAlert(bool ar)const{const TrafficVehicle* n=nullptr;for(const auto&v:vehicles_)if(!n||v.distance<n->distance)n=&v;if(!n)return ar?"الطريق خالٍ":"Road is clear";if(n->distance<12)return ar?"تحذير، "+n->type+" قريبة جدًا أمامك":"Warning, a "+n->type+" is very close ahead";if(n->distance<30)return ar?"مركبة "+n->type+" أمامك على بعد "+std::to_string((int)n->distance)+" متر":"A "+n->type+" is ahead, "+std::to_string((int)n->distance)+" meters";return ar?"حركة المرور طبيعية":"Traffic is normal";}
}
