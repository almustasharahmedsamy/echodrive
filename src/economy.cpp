#include "economy.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
namespace echodrive {
EconomySystem::EconomySystem() { reset(); }
void EconomySystem::reset() {
    completedContracts_ = 0;
    failedContracts_ = 0;
    marketRegion_ = 1;
    marketWeather_ = 0;
    createStations();
    createContracts();
    createParts();
}
void EconomySystem::createStations() {
    stations_ = {
        {1, StationType::Fuel, "محطة القاهرة المركزية", "القاهرة", 3, 100, true},
        {2, StationType::Gas, "محطة الغاز السريع", "الجيزة", 2, 100, true},
        {3, StationType::Electric, "شحن النيل", "القليوبية", 4, 100, true},
        {4, StationType::Service, "مركز صيانة الدلتا", "الدقهلية", 5, 100, true},
        {5, StationType::Dealership, "معرض القناة", "الإسماعيلية", 10, 100, true},
        {6, StationType::Insurance, "تأمين الطريق", "السويس", 80, 100, true},
        {7, StationType::Fuel, "محطة الساحل", "الإسكندرية", 4, 100, true},
        {8, StationType::Service, "ورشة الصعيد", "أسيوط", 6, 100, true},
        {9, StationType::Electric, "شحن الأقصر", "الأقصر", 5, 100, true},
        {10, StationType::Fuel, "محطة الصحراء", "الوادي الجديد", 6, 100, true},
        {11, StationType::Insurance, "تأمين سيناء", "شمال سيناء", 95, 100, true},
        {12, StationType::Gas, "غاز البحر الأحمر", "البحر الأحمر", 3, 100, true}
    };
}
void EconomySystem::createContracts() {
    contracts_ = {
        {1, "رسالة الإسعاف", "الجيزة", 100, 850, 180, 70, false, false},
        {2, "قطع غيار عاجلة", "الإسكندرية", 300, 2100, 420, 150, false, false},
        {3, "أجهزة كهربائية", "الدقهلية", 500, 3200, 650, 240, false, false},
        {4, "مؤن الصحراء", "الوادي الجديد", 800, 4800, 1100, 420, false, false},
        {5, "معدات الميناء", "بورسعيد", 1200, 6200, 1500, 550, false, false},
        {6, "أدوية الأقصر", "الأقصر", 250, 7100, 1800, 700, false, false},
        {7, "بذور زراعية", "المنيا", 600, 3900, 800, 300, false, false},
        {8, "معدات الإنقاذ", "البحر الأحمر", 900, 9000, 2600, 1000, false, false},
        {9, "شحنة دولية", "الإسماعيلية", 1400, 5400, 1900, 800, false, false},
        {10, "طرد شخصي", "أسوان", 50, 11000, 3200, 1300, false, false}
    };
}
void EconomySystem::createParts() {
    parts_ = {
        {"محرك اقتصادي", 1, 400, 1.15},
        {"محرك رياضي", 2, 900, 1.35},
        {"محرك كهربائي", 2, 1100, 1.45},
        {"فرامل قياسية", 1, 250, 1.00},
        {"فرامل ABS", 2, 650, 1.25},
        {"فرامل سباق", 3, 1200, 1.60},
        {"إطارات مطر", 2, 500, 1.30},
        {"إطارات صحراوية", 2, 550, 1.28},
        {"بطارية موسعة", 2, 1000, 1.40},
        {"عازل صوتي", 1, 700, 0.80},
        {"رادار مسافة", 3, 1500, 0.65},
        {"نظام طوارئ", 3, 1800, 0.60}
    };
}
void EconomySystem::refreshMarket(int region, int weatherIndex) {
    marketRegion_ = std::max(1, region);
    marketWeather_ = std::max(0, weatherIndex);
    for (auto& station : stations_) {
        station.open = ((station.id + marketRegion_ + marketWeather_) % 11) != 0;
        station.price = std::max(1, station.price + (marketRegion_ % 4) + marketWeather_);
    }
}
bool EconomySystem::acceptContract(int id) {
    for (auto& contract : contracts_) {
        if (contract.id == id && !contract.completed && !contract.accepted) {
            contract.accepted = true;
            return true;
        }
    }
    return false;
}
bool EconomySystem::completeContract(int id, int travelledMeters, double damage) {
    for (auto& contract : contracts_) {
        if (contract.id != id || !contract.accepted || contract.completed) continue;
        if (travelledMeters < contract.distance || damage > 60.0) {
            failedContracts_++;
            contract.accepted = false;
            return false;
        }
        contract.completed = true;
        contract.accepted = false;
        completedContracts_++;
        return true;
    }
    return false;
}
bool EconomySystem::buyFuel(int stationId, double amount, int& wallet, double& fuel) {
    if (amount <= 0.0 || fuel >= 100.0) return false;
    int price = calculateFuelPrice(marketRegion_, marketWeather_);
    int total = static_cast<int>(amount * price);
    if (wallet < total) return false;
    for (const auto& station : stations_) if (station.id == stationId && station.open && (station.type == StationType::Fuel || station.type == StationType::Gas)) {
        wallet -= total;
        fuel = std::min(100.0, fuel + amount);
        return true;
    }
    return false;
}
bool EconomySystem::buyCharge(int stationId, double amount, int& wallet, double& battery) {
    if (amount <= 0.0 || battery >= 100.0) return false;
    int price = 4 + marketRegion_ % 3 + marketWeather_;
    int total = static_cast<int>(amount * price);
    if (wallet < total) return false;
    for (const auto& station : stations_) if (station.id == stationId && station.open && station.type == StationType::Electric) {
        wallet -= total;
        battery = std::min(100.0, battery + amount);
        return true;
    }
    return false;
}
bool EconomySystem::buyInsurance(int stationId, int& wallet, double& damage) {
    for (const auto& station : stations_) if (station.id == stationId && station.open && station.type == StationType::Insurance) {
        int total = station.price + static_cast<int>(damage * 2.0);
        if (wallet < total) return false;
        wallet -= total;
        damage = 0.0;
        return true;
    }
    return false;
}
bool EconomySystem::buyPart(const std::string& name, int& wallet) {
    for (const auto& part : parts_) if (part.name == name && wallet >= part.price) {
        wallet -= part.price;
        return true;
    }
    return false;
}
int EconomySystem::calculateFuelPrice(int region, int weatherIndex) const { return 2 + (region % 4) + (weatherIndex > 2 ? 2 : 0); }
int EconomySystem::calculateRepairPrice(double damage, int weatherIndex) const { return 50 + static_cast<int>(damage * 3.0) + weatherIndex * 15; }
const std::vector<StationOffer>& EconomySystem::stations() const { return stations_; }
const std::vector<Contract>& EconomySystem::contracts() const { return contracts_; }
const std::vector<VehiclePart>& EconomySystem::parts() const { return parts_; }
std::string EconomySystem::stationSummary(bool ar) const {
    int open = 0;
    for (const auto& station : stations_) open += station.open ? 1 : 0;
    if (ar) return "السوق: " + std::to_string(open) + " محطة مفتوحة، سعر الوقود " + std::to_string(calculateFuelPrice(marketRegion_, marketWeather_)) + "، المنطقة " + std::to_string(marketRegion_);
    return "Market: " + std::to_string(open) + " stations open, fuel price " + std::to_string(calculateFuelPrice(marketRegion_, marketWeather_)) + ", region " + std::to_string(marketRegion_);
}
std::string EconomySystem::contractSummary(bool ar) const {
    int open = 0;
    int accepted = 0;
    for (const auto& contract : contracts_) { open += !contract.completed; accepted += contract.accepted; }
    if (ar) return "العقود: " + std::to_string(open) + " متاحة، " + std::to_string(accepted) + " قيد التنفيذ، " + std::to_string(completedContracts_) + " مكتملة، " + std::to_string(failedContracts_) + " فاشلة";
    return "Contracts: " + std::to_string(open) + " available, " + std::to_string(accepted) + " active, " + std::to_string(completedContracts_) + " complete, " + std::to_string(failedContracts_) + " failed";
}
std::string EconomySystem::partSummary(bool ar) const {
    if (ar) return "قطع الغيار: " + std::to_string(parts_.size()) + " خيارات، من عازل الصوت إلى الرادار ونظام الطوارئ";
    return "Parts: " + std::to_string(parts_.size()) + " options, from sound insulation to radar and emergency system";
}
std::string EconomySystem::ledgerSummary(bool ar) const {
    if (ar) return "دفتر الاقتصاد: العقود المكتملة " + std::to_string(completedContracts_) + "، الفاشلة " + std::to_string(failedContracts_) + "، المنطقة السوقية " + std::to_string(marketRegion_);
    return "Economy ledger: completed contracts " + std::to_string(completedContracts_) + ", failed " + std::to_string(failedContracts_) + ", market region " + std::to_string(marketRegion_);
}
bool EconomySystem::save(const std::string& path) const {
    std::ofstream out(path);
    if (!out) return false;
    out << completedContracts_ << ' ' << failedContracts_ << ' ' << marketRegion_ << ' ' << marketWeather_ << '\n';
    for (const auto& station : stations_) out << station.id << ' ' << station.price << ' ' << station.open << '\n';
    for (const auto& contract : contracts_) out << contract.id << ' ' << contract.accepted << ' ' << contract.completed << '\n';
    return true;
}
bool EconomySystem::load(const std::string& path) {
    std::ifstream in(path);
    if (!in) return false;
    in >> completedContracts_ >> failedContracts_ >> marketRegion_ >> marketWeather_;
    for (auto& station : stations_) in >> station.id >> station.price >> station.open;
    for (auto& contract : contracts_) in >> contract.id >> contract.accepted >> contract.completed;
    return static_cast<bool>(in);
}
}
