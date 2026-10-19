#pragma once
#include <string>
#include <vector>
namespace echodrive {
enum class EnergyType { Petrol, Diesel, Gas, Electric, Hybrid };
struct CarSetup { std::string color="blue"; std::string engine="standard"; std::string brakes="standard"; EnergyType energy=EnergyType::Petrol; double fuel=70; double oil=80; double battery=85; };
struct Station { int id; std::string name; bool fuel; bool oil; bool gas; bool charger; };
class VehicleSystem {
public:
 VehicleSystem();
 void setColor(const std::string& color); void upgradeEngine(const std::string& engine); void upgradeBrakes(const std::string& brakes);
 void refuel(); void changeOil(); void charge();
 std::string customize(bool arabic) const; std::string status(bool arabic) const; std::string stations(bool arabic) const;
 const CarSetup& setup() const { return setup_; }
private: CarSetup setup_; std::vector<Station> stations_;
};
std::string energyName(EnergyType type,bool arabic);
}
