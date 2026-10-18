#pragma once
#include <string>
namespace echodrive {
enum class Weather { Clear, Rain, Storm, Wind, HumidHeat, Cold, Snow, Ice, Desert, Mountain, Farm };
struct WeatherState { Weather type=Weather::Clear; int temperature=22; int wind=8; int humidity=45; bool slippery=false; };
class WeatherSystem {
public:
    WeatherSystem();
    void set(Weather weather);
    void cycle();
    const WeatherState& state() const { return state_; }
    std::string name(bool arabic) const;
    std::string advisory(bool arabic) const;
    std::string ambiencePath() const;
private: WeatherState state_{}; int index_=0;
};
}
