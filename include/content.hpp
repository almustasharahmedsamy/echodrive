#pragma once
#include <string>
#include <vector>
namespace echodrive {
struct Street { int id; std::string ar; std::string en; std::string country; std::string description; };
struct Vehicle { int id; std::string ar; std::string en; std::string category; int topSpeed; double engineTone; };
const std::vector<Street>& allStreets();
const std::vector<Vehicle>& allVehicles();
}
