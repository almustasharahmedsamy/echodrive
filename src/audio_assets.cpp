#include "audio_assets.hpp"
#include <algorithm>
#include <string>
namespace echodrive {
AudioAssetSet assetsForStreet(int id){
    id=std::clamp(id,1,15);
    const std::string prefix = id < 10 ? "0" : "";
    const std::string engine = id % 2 ? "assets/audio/vehicles/Car_Engine_Loop.ogg" : "assets/audio/vehicles/Car_Engine_Loop_2.ogg";
    return {"assets/audio/ambience/street_" + prefix + std::to_string(id) + ".ogg", engine};
}
}
