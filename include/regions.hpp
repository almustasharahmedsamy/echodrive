#pragma once
#include <string>
#include <vector>
namespace echodrive {
struct Region { int id; std::string governorate; std::string city; std::string route; double latitude; double longitude; };
const std::vector<Region>& egyptRegions();
std::string regionMapSummary(int id,bool arabic);
}
