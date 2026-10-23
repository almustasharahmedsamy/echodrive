#pragma once
#include <string>
#include <vector>
namespace echodrive {
enum class StationType { Fuel, Gas, Electric, Service, Dealership, Insurance };
struct StationOffer {
    int id;
    StationType type;
    std::string name;
    std::string region;
    int price;
    int capacity;
    bool open;
};
struct Contract {
    int id;
    std::string title;
    std::string destination;
    int cargoWeight;
    int distance;
    int reward;
    int penalty;
    bool accepted;
    bool completed;
};
struct VehiclePart {
    std::string name;
    int level;
    int price;
    double efficiency;
};
class EconomySystem {
public:
    EconomySystem();
    void reset();
    void refreshMarket(int region, int weatherIndex);
    bool acceptContract(int id);
    bool completeContract(int id, int travelledMeters, double damage);
    bool buyFuel(int stationId, double amount, int& wallet, double& fuel);
    bool buyCharge(int stationId, double amount, int& wallet, double& battery);
    bool buyInsurance(int stationId, int& wallet, double& damage);
    bool buyPart(const std::string& name, int& wallet);
    int calculateFuelPrice(int region, int weatherIndex) const;
    int calculateRepairPrice(double damage, int weatherIndex) const;
    const std::vector<StationOffer>& stations() const;
    const std::vector<Contract>& contracts() const;
    const std::vector<VehiclePart>& parts() const;
    std::string stationSummary(bool arabic) const;
    std::string contractSummary(bool arabic) const;
    std::string partSummary(bool arabic) const;
    std::string ledgerSummary(bool arabic) const;
    bool save(const std::string& path) const;
    bool load(const std::string& path);
private:
    std::vector<StationOffer> stations_;
    std::vector<Contract> contracts_;
    std::vector<VehiclePart> parts_;
    int completedContracts_ = 0;
    int failedContracts_ = 0;
    int marketRegion_ = 1;
    int marketWeather_ = 0;
    void createStations();
    void createContracts();
    void createParts();
};
}
