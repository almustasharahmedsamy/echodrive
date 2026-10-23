#include "career.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
namespace echodrive {
CareerProfile::CareerProfile() { createMissions(); }
void CareerProfile::createMissions() {
    missions_.clear();
    missions_.push_back({1,"رحلة البداية","قد السيارة لمسافة قصيرة بأمان",500,100,40,0,false});
    missions_.push_back({2,"سائق المدينة","اعبر ثلاثة شوارع دون اصطدام",1500,250,90,0,false});
    missions_.push_back({3,"موعد التسليم","أكمل مسافة طويلة في طقس متغير",3000,500,160,0,false});
    missions_.push_back({4,"الطريق الصحراوي","قد في بيئة صحراوية مع الحفاظ على الطاقة",4500,750,240,0,false});
    missions_.push_back({5,"مساعدة الطوارئ","افسح الطريق لمركبة طوارئ",6000,1000,320,0,false});
    missions_.push_back({6,"المحترف","أكمل عشر رحلات آمنة",9000,1500,450,0,false});
    missions_.push_back({7,"مستكشف مصر","زر خمس محافظات مختلفة",12000,2200,600,0,false});
    missions_.push_back({8,"السائق الاقتصادي","حافظ على الوقود فوق عشرين بالمئة",16000,2800,800,0,false});
}
void CareerProfile::setName(const std::string& name) { if (!name.empty()) stats_.driverName = name; }
void CareerProfile::beginTrip(int streetId, int vehicleId) { street_ = streetId; vehicle_ = vehicleId; tripMeters_ = 0; stats_.trips++; }
void CareerProfile::drive(double speedKmh, double seconds, bool slippery, bool trafficWarning) {
    double meters = std::max(0.0, speedKmh) * seconds / 3.6;
    tripMeters_ += static_cast<int>(meters);
    stats_.safeKilometers += static_cast<int>(meters / 1000.0);
    const double engineUse = speedKmh > 120.0 ? 0.035 : 0.018;
    stats_.fuel -= meters * engineUse / 1000.0;
    stats_.oil -= meters * 0.002 / 1000.0;
    stats_.battery -= meters * 0.001 / 1000.0;
    if (slippery) stats_.fuel -= meters * 0.003 / 1000.0;
    if (trafficWarning) stats_.reputation += 1;
    addMissionDistance(static_cast<int>(meters));
    clampValues();
}
void CareerProfile::brake(bool hard) {
    if (hard) {
        stats_.oil -= 0.04;
        stats_.damage += 0.15;
    } else {
        stats_.oil -= 0.01;
    }
    clampValues();
}
void CareerProfile::collision(double severity) {
    severity = std::clamp(severity, 0.0, 100.0);
    stats_.damage += severity;
    stats_.collisions++;
    stats_.reputation -= static_cast<int>(severity / 10.0);
    clampValues();
}
void CareerProfile::refuel(int price) {
    if (price <= 0) price = static_cast<int>((100.0 - stats_.fuel) * 2.0);
    if (stats_.money < price) return;
    stats_.money -= price;
    stats_.fuel = 100.0;
}
void CareerProfile::service(int price) {
    if (price <= 0) price = 75 + static_cast<int>(stats_.damage * 2.0);
    if (stats_.money < price) return;
    stats_.money -= price;
    stats_.damage = 0.0;
    stats_.oil = 100.0;
}
void CareerProfile::charge(int price) {
    if (price <= 0) price = static_cast<int>((100.0 - stats_.battery) * 2.0);
    if (stats_.money < price) return;
    stats_.money -= price;
    stats_.battery = 100.0;
}
void CareerProfile::finishTrip() {
    if (tripMeters_ >= 100) {
        stats_.deliveries++;
        awardXp(25 + std::max(0, 10 - stats_.collisions));
        awardMoney(50 + std::max(0, stats_.reputation));
    }
    tripMeters_ = 0;
}
void CareerProfile::addMissionDistance(int meters) {
    if (currentMission_ < 0 || currentMission_ >= static_cast<int>(missions_.size())) return;
    auto& mission = missions_[currentMission_];
    if (mission.completed) return;
    mission.progressMeters += std::max(0, meters);
    if (mission.progressMeters >= mission.targetMeters) completeMission(mission.id);
}
bool CareerProfile::completeMission(int missionId) {
    for (auto& mission : missions_) {
        if (mission.id != missionId || mission.completed) continue;
        mission.completed = true;
        awardXp(mission.xp);
        awardMoney(mission.reward);
        currentMission_ = std::min(currentMission_ + 1, static_cast<int>(missions_.size()) - 1);
        return true;
    }
    return false;
}
void CareerProfile::awardXp(int points) { stats_.xp += std::max(0, points); levelUpIfNeeded(); }
void CareerProfile::awardMoney(int amount) { stats_.money = std::max(0, stats_.money + amount); }
const CareerStats& CareerProfile::stats() const { return stats_; }
const std::vector<MissionProgress>& CareerProfile::missions() const { return missions_; }
MissionProgress& CareerProfile::activeMission() { return missions_[std::clamp(currentMission_, 0, static_cast<int>(missions_.size()) - 1)]; }
void CareerProfile::levelUpIfNeeded() {
    while (stats_.xp >= stats_.level * 100) {
        stats_.xp -= stats_.level * 100;
        stats_.level++;
        stats_.money += stats_.level * 50;
        stats_.reputation += 2;
    }
}
void CareerProfile::clampValues() {
    stats_.fuel = std::clamp(stats_.fuel, 0.0, 100.0);
    stats_.oil = std::clamp(stats_.oil, 0.0, 100.0);
    stats_.battery = std::clamp(stats_.battery, 0.0, 100.0);
    stats_.damage = std::clamp(stats_.damage, 0.0, 100.0);
    stats_.reputation = std::max(0, stats_.reputation);
}
std::string CareerProfile::summary(bool ar) const {
    std::ostringstream out;
    if (ar) out << "السائق " << stats_.driverName << "، المستوى " << stats_.level << "، الخبرة " << stats_.xp << "، المال " << stats_.money << "، الرحلات " << stats_.trips << "، الاصطدامات " << stats_.collisions << "، الضرر " << static_cast<int>(stats_.damage) << "%، الوقود " << static_cast<int>(stats_.fuel) << "%، الزيت " << static_cast<int>(stats_.oil) << "%، البطارية " << static_cast<int>(stats_.battery) << "%";
    else out << "Driver " << stats_.driverName << ", level " << stats_.level << ", XP " << stats_.xp << ", money " << stats_.money << ", trips " << stats_.trips << ", collisions " << stats_.collisions << ", damage " << static_cast<int>(stats_.damage) << "%, fuel " << static_cast<int>(stats_.fuel) << "%, oil " << static_cast<int>(stats_.oil) << "%, battery " << static_cast<int>(stats_.battery) << "%";
    return out.str();
}
std::string CareerProfile::missionSummary(bool ar) const {
    const auto& m = missions_[std::clamp(currentMission_, 0, static_cast<int>(missions_.size()) - 1)];
    std::ostringstream out;
    if (ar) out << "المهمة: " << m.title << "، " << m.description << "، التقدم " << m.progressMeters << " من " << m.targetMeters << " متر، المكافأة " << m.reward;
    else out << "Mission: " << m.title << ", " << m.description << ", progress " << m.progressMeters << " of " << m.targetMeters << " meters, reward " << m.reward;
    return out.str();
}
std::string CareerProfile::achievements(bool ar) const {
    int completed = 0;
    for (const auto& mission : missions_) completed += mission.completed ? 1 : 0;
    if (ar) return "الإنجازات: " + std::to_string(completed) + " مهام مكتملة، " + std::to_string(stats_.deliveries) + " تسليمات، سمعة " + std::to_string(stats_.reputation);
    return "Achievements: " + std::to_string(completed) + " missions complete, " + std::to_string(stats_.deliveries) + " deliveries, reputation " + std::to_string(stats_.reputation);
}
bool CareerProfile::save(const std::string& path) const {
    std::ofstream out(path);
    if (!out) return false;
    out << stats_.driverName << '\n' << stats_.level << ' ' << stats_.xp << ' ' << stats_.money << ' ' << stats_.trips << ' ' << stats_.deliveries << ' ' << stats_.safeKilometers << ' ' << stats_.collisions << ' ' << stats_.reputation << '\n';
    out << stats_.fuel << ' ' << stats_.oil << ' ' << stats_.battery << ' ' << stats_.damage << '\n';
    out << street_ << ' ' << vehicle_ << ' ' << tripMeters_ << ' ' << currentMission_ << '\n';
    for (const auto& mission : missions_) out << mission.id << ' ' << mission.progressMeters << ' ' << mission.completed << '\n';
    return true;
}
bool CareerProfile::load(const std::string& path) {
    std::ifstream in(path);
    if (!in) return false;
    std::getline(in, stats_.driverName);
    in >> stats_.level >> stats_.xp >> stats_.money >> stats_.trips >> stats_.deliveries >> stats_.safeKilometers >> stats_.collisions >> stats_.reputation;
    in >> stats_.fuel >> stats_.oil >> stats_.battery >> stats_.damage;
    in >> street_ >> vehicle_ >> tripMeters_ >> currentMission_;
    for (auto& mission : missions_) in >> mission.id >> mission.progressMeters >> mission.completed;
    clampValues();
    return static_cast<bool>(in);
}
}
