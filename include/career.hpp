#pragma once
#include <string>
#include <vector>
namespace echodrive {
struct MissionProgress {
    int id = 1;
    std::string title;
    std::string description;
    int targetMeters = 500;
    int reward = 100;
    int xp = 50;
    int progressMeters = 0;
    bool completed = false;
};
struct CareerStats {
    std::string driverName = "Ahmed";
    int level = 1;
    int xp = 0;
    int money = 500;
    int trips = 0;
    int deliveries = 0;
    int safeKilometers = 0;
    int collisions = 0;
    int reputation = 0;
    double fuel = 70.0;
    double oil = 80.0;
    double battery = 85.0;
    double damage = 0.0;
};
class CareerProfile {
public:
    CareerProfile();
    void setName(const std::string& name);
    void beginTrip(int streetId, int vehicleId);
    void drive(double speedKmh, double seconds, bool slippery, bool trafficWarning);
    void brake(bool hard);
    void collision(double severity);
    void refuel(int price = 0);
    void service(int price = 0);
    void charge(int price = 0);
    void finishTrip();
    void addMissionDistance(int meters);
    bool completeMission(int missionId);
    void awardXp(int points);
    void awardMoney(int amount);
    const CareerStats& stats() const;
    const std::vector<MissionProgress>& missions() const;
    MissionProgress& activeMission();
    std::string summary(bool arabic) const;
    std::string missionSummary(bool arabic) const;
    std::string achievements(bool arabic) const;
    bool save(const std::string& path) const;
    bool load(const std::string& path);
private:
    CareerStats stats_;
    std::vector<MissionProgress> missions_;
    int street_ = 1;
    int vehicle_ = 1;
    int tripMeters_ = 0;
    int currentMission_ = 0;
    void createMissions();
    void levelUpIfNeeded();
    void clampValues();
};
}
