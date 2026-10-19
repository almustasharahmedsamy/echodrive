#include "vehicle_system.hpp"
#include <algorithm>
namespace echodrive {
VehicleSystem::VehicleSystem():stations_{{1,"Fuel station",true,true,false,false},{2,"Gas station",false,false,true,false},{3,"EV charging hub",false,false,false,true},{4,"Service center",true,true,true,true}}{}
std::string energyName(EnergyType t,bool ar){switch(t){case EnergyType::Petrol:return ar?"بنزين":"Petrol";case EnergyType::Diesel:return ar?"سولار":"Diesel";case EnergyType::Gas:return ar?"غاز":"Gas";case EnergyType::Electric:return ar?"كهرباء":"Electric";case EnergyType::Hybrid:return ar?"هجين":"Hybrid";}return "";}
void VehicleSystem::setColor(const std::string& c){setup_.color=c;}
void VehicleSystem::upgradeEngine(const std::string& e){setup_.engine=e;}
void VehicleSystem::upgradeBrakes(const std::string& b){setup_.brakes=b;}
void VehicleSystem::refuel(){if(setup_.energy==EnergyType::Electric)return;setup_.fuel=100;}
void VehicleSystem::changeOil(){setup_.oil=100;}
void VehicleSystem::charge(){if(setup_.energy==EnergyType::Petrol||setup_.energy==EnergyType::Diesel||setup_.energy==EnergyType::Gas)return;setup_.battery=100;}
std::string VehicleSystem::customize(bool ar)const{return ar?"التخصيص: اللون "+setup_.color+"، المحرك "+setup_.engine+"، الفرامل "+setup_.brakes+"، الطاقة "+energyName(setup_.energy,true):"Customization: color "+setup_.color+", engine "+setup_.engine+", brakes "+setup_.brakes+", energy "+energyName(setup_.energy,false);}
std::string VehicleSystem::status(bool ar)const{return ar?"الوقود "+std::to_string((int)setup_.fuel)+" بالمئة، الزيت "+std::to_string((int)setup_.oil)+" بالمئة، البطارية "+std::to_string((int)setup_.battery)+" بالمئة":"Fuel "+std::to_string((int)setup_.fuel)+" percent, oil "+std::to_string((int)setup_.oil)+" percent, battery "+std::to_string((int)setup_.battery)+" percent";}
std::string VehicleSystem::stations(bool ar)const{std::string out=ar?"المحطات: ":"Stations: ";for(const auto&s:stations_)out+=std::to_string(s.id)+" "+s.name+"; ";return out;}
}
