#pragma once
#include <string>
namespace echodrive {
struct AudioAssetSet { std::string ambience; std::string engine; };
AudioAssetSet assetsForStreet(int streetId);
}
