#include "game.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <conio.h>
#endif
namespace echodrive {
Game::Game() : settings_(loadSettings("echodrive.cfg")), voice_(settings_.language) {
    audio_.setListener({0, 0, 0}, 0);
    route_.load(settings_.street);
    career_.load("echodrive.profile");
    accessibility_.load("echodrive.accessibility");
    scenarios_.load("echodrive.scenarios");
    economy_.load("echodrive.economy");
    telemetry_.load("echodrive.telemetry");
    ui_.setTheme({accessibility_.settings().highContrast, false, true});
}
void Game::menu() const {
    std::cout << ui_.menu(settings_.language) << "\n> ";
}
std::string Game::readInput() const {
#ifdef _WIN32
    int c = _getch();
    if (c == 0 || c == 224) {
        int k = _getch();
        if (k == 72) return "up";
        if (k == 80) return "down";
        if (k == 75) return "left";
        if (k == 77) return "right";
        if (k >= 59 && k <= 68) return "f" + std::to_string(k - 58);
        if (k == 133) return "f11";
        if (k == 134) return "f12";
        if (k == 82) return "insert";
        if (k == 83) return "delete";
        return "";
    }
    if (c == 27) return "esc";
    if (c == 9) return "tab";
    if (c == 20) return "capslock";
    if (c == 13) return "enter";
    return std::string(1, static_cast<char>(std::tolower(c)));
#else
    std::string x;
    std::getline(std::cin, x);
    for (auto& c : x) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return x;
#endif
}
void Game::selectStreet() {
    std::cout << ui_.prompt(settings_.language, Localization::selectStreet(settings_.language, 15)) << "\n> ";
    int n = 1;
    std::cin >> n;
    std::cin.ignore(10000, '\n');
    if (n < 1 || n > 15) n = 1;
    settings_.street = n;
    route_.load(n);
    const auto& x = allStreets()[n - 1];
    auto assets = assetsForStreet(n);
    runtime_.setListener({0, 0, 0}, 0);
    runtime_.playLoop(assets.ambience, {0, 0, 8}, 0.45f);
    traffic_.reset(n);
    economy_.refreshMarket(region_, static_cast<int>(weather_.state().type));
    career_.beginTrip(n, vehicle_);
    telemetry_.start(n, vehicle_, region_);
    voice_.announce6(Localization::startedStreet(Language::Arabic, x.ar, x.country, static_cast<int>(route_.state().lengthM)), Localization::startedStreet(Language::English, x.en, x.country, static_cast<int>(route_.state().lengthM)), Localization::startedStreet(Language::French, x.en, x.country, static_cast<int>(route_.state().lengthM)), Localization::startedStreet(Language::Spanish, x.en, x.country, static_cast<int>(route_.state().lengthM)), Localization::startedStreet(Language::Russian, x.en, x.country, static_cast<int>(route_.state().lengthM)), Localization::startedStreet(Language::Japanese, x.en, x.country, static_cast<int>(route_.state().lengthM)));
}
void Game::selectVehicle() {
    std::cout << ui_.prompt(settings_.language, Localization::selectVehicle(settings_.language, 40)) << "\n> ";
    int n = 1;
    std::cin >> n;
    std::cin.ignore(10000, '\n');
    if (n < 1 || n > 40) n = 1;
    vehicle_ = n;
    auto assets = assetsForStreet(settings_.street);
    runtime_.playLoop(assets.engine, {0, 0, 1}, 0.70f);
    const auto& x = allVehicles()[n - 1];
    career_.beginTrip(settings_.street, vehicle_);
    voice_.announce6(Localization::selectedVehicle(Language::Arabic, x.ar, x.topSpeed), Localization::selectedVehicle(Language::English, x.en, x.topSpeed), Localization::selectedVehicle(Language::French, x.en, x.topSpeed), Localization::selectedVehicle(Language::Spanish, x.en, x.topSpeed), Localization::selectedVehicle(Language::Russian, x.en, x.topSpeed), Localization::selectedVehicle(Language::Japanese, x.en, x.topSpeed));
}
Command Game::parse(const std::string& r) const {
    if (r == "1" || r == "up" || r == "forward" || r == "z" || r == "e" || r == "تقدم") return Command::Forward;
    if (r == "2" || r == "down" || r == "stop" || r == "x" || r == "توقف" || r == "فرامل") return Command::Brake;
    if (r == "3" || r == "right" || r == "v" || r == "يمين") return Command::Right;
    if (r == "4" || r == "left" || r == "c" || r == "يسار") return Command::Left;
    if (r == "5" || r == "+" || r == "b" || r == "i" || r == "أسرع") return Command::Faster;
    if (r == "6" || r == "-" || r == "n" || r == "o" || r == "أبطئ") return Command::Slower;
    if (r == "a" || r == "auto" || r == "قيادة آلية") return Command::Auto;
    if (r == "m" || r == "manual" || r == "قيادة يدوية") return Command::Manual;
    if (r == "s" || r == "u" || r == "status" || r == "حالة" || r == "enter" || r == "f1") return Command::Repeat;
    if (r == "r" || r == "reset" || r == "إعادة" || r == "f11") return Command::Reset;
    if (r == "l" || r == "streets") return Command::ListStreets;
    if (r == "vehicles" || r == "listvehicles") return Command::ListVehicles;
    if (r == "w" || r == "j" || r == "weather" || r == "طقس" || r == "f3") return Command::WeatherCycle;
    if (r == "t" || r == "k" || r == "traffic" || r == "مرور" || r == "f4") return Command::Traffic;
    if (r == "d" || r == "y" || r == "map" || r == "خريطة" || r == "f2") return Command::Map;
    if (r == "f" || r == "controls" || r == "تحكم" || r == "f9") return Command::Controls;
    if (r == "g" || r == "horn") return Command::Horn;
    if (r == "p" || r == "pause" || r == "esc" || r == "f10") return Command::Pause;
    if (r == "h" || r == "engine" || r == "capslock") return Command::Engine;
    if (r == "insert" || r == "f5") return Command::Stations;
    if (r == "tab" || r == "f7") return Command::NewVehicle;
    if (r == "f6" || r == "customize") return Command::Customize;
    if (r == "f8" || r == "language") return Command::Language;
    if (r == "f12" || r == "region" || r == "f0") return Command::RegionMap;
    if (r == "profile" || r == "ملف") return Command::Profile;
    if (r == "mission" || r == "مهمة") return Command::Mission;
    if (r == "access" || r == "إتاحة") return Command::Accessibility;
    if (r == "scenario" || r == "سيناريو") return Command::Mission;
    if (r == "delete") return Command::NewVehicle;
    if (r == "q" || r == "quit" || r == "خروج") return Command::Quit;
    return Command::Unknown;
}
void Game::status() const {
    const auto& rs = route_.state();
    std::string ar = "السرعة " + std::to_string(static_cast<int>(speed_)) + "، قطعت " + std::to_string(static_cast<int>(rs.progressM)) + " متر، متبقي " + std::to_string(static_cast<int>(rs.lengthM - rs.progressM)) + " متر، " + vehicleSystem_.status(true) + "، " + vehicleSystem_.customize(true) + "، " + career_.summary(true) + "، " + career_.missionSummary(true) + "، " + economy_.stationSummary(true) + "، " + economy_.contractSummary(true) + "، " + telemetry_.reportText(true);
    std::string en = "Speed " + std::to_string(static_cast<int>(speed_)) + ", travelled " + std::to_string(static_cast<int>(rs.progressM)) + " meters, remaining " + std::to_string(static_cast<int>(rs.lengthM - rs.progressM)) + " meters, " + vehicleSystem_.status(false) + ", " + vehicleSystem_.customize(false) + ", " + career_.summary(false) + ", " + career_.missionSummary(false) + ", " + economy_.stationSummary(false) + ", " + economy_.contractSummary(false) + ", " + telemetry_.reportText(false);
    voice_.announce(ar, en);
}
void Game::showControls() const {
    std::cout << ui_.controls(settings_.language) << "\n";
    auto a = Localization::ui(Language::Arabic);
    auto e = Localization::ui(Language::English);
    auto f = Localization::ui(Language::French);
    auto s = Localization::ui(Language::Spanish);
    auto r = Localization::ui(Language::Russian);
    auto j = Localization::ui(Language::Japanese);
    voice_.announce6(a.controlsTitle, e.controlsTitle, f.controlsTitle, s.controlsTitle, r.controlsTitle, j.controlsTitle);
}
void Game::listContent() const {
    std::cout << "\n--- 15 Streets ---\n";
    for (const auto& s : allStreets()) std::cout << s.id << ". " << s.en << " — " << s.country << "\n";
    std::cout << "\n--- 40 Vehicles ---\n";
    for (const auto& v : allVehicles()) std::cout << v.id << ". " << v.en << " [" << v.category << "] max " << v.topSpeed << " km/h\n";
}
void Game::handle(Command c) {
    if (paused_ && c != Command::Pause && c != Command::Quit) {
        voice_.announce("اللعبة متوقفة، اضغط Escape أو F10", "Game paused, press Escape or F10");
        return;
    }
    switch (c) {
    case Command::Forward:
        speed_ = std::min(static_cast<double>(allVehicles()[vehicle_ - 1].topSpeed), speed_ + 8);
        route_.advance(speed_);
        traffic_.tick(speed_, settings_.automaticDriving);
        career_.drive(speed_, 1.0, weather_.state().slippery, traffic_.nearestAlert(false).find("Warning") != std::string::npos);
        telemetry_.sample(speed_, career_.stats().fuel, career_.stats().damage, region_, TelemetryEvent::SpeedChange, "forward");
        scenarios_.update(speed_, route_.state().progressM, false, career_.stats().fuel < 30, static_cast<int>(weather_.state().type), region_);
        break;
    case Command::Brake:
        speed_ = std::max(0.0, speed_ - 20);
        route_.advance(speed_ * .15);
        traffic_.tick(speed_, settings_.automaticDriving);
        career_.brake(speed_ > 30);
        break;
    case Command::Right: heading_ = 1; audio_.setListener({0, 0, 0}, 0.25); break;
    case Command::Left: heading_ = -1; audio_.setListener({0, 0, 0}, -0.25); break;
    case Command::Faster: speed_ = std::min(static_cast<double>(allVehicles()[vehicle_ - 1].topSpeed), speed_ + 15); route_.advance(speed_); career_.drive(speed_, 1.0, false, false); break;
    case Command::Slower: speed_ = std::max(0.0, speed_ - 15); break;
    case Command::Auto: settings_.automaticDriving = true; break;
    case Command::Manual: settings_.automaticDriving = false; break;
    case Command::Reset: speed_ = 0; heading_ = 0; route_.reset(); traffic_.reset(settings_.street); weather_.set(Weather::Clear); break;
    case Command::Repeat: status(); break;
    case Command::ListStreets: case Command::ListVehicles: listContent(); break;
    case Command::WeatherCycle: weather_.cycle(); runtime_.playLoop(weather_.ambiencePath(), {0, 0, 5}, 0.38f); voice_.announce6(Localization::weather(Language::Arabic, weather_.name(true), weather_.advisory(true)), Localization::weather(Language::English, weather_.name(false), weather_.advisory(false)), Localization::weather(Language::French, weather_.name(false), weather_.advisory(false)), Localization::weather(Language::Spanish, weather_.name(false), weather_.advisory(false)), Localization::weather(Language::Russian, weather_.name(false), weather_.advisory(false)), Localization::weather(Language::Japanese, weather_.name(false), weather_.advisory(false))); break;
    case Command::Traffic: traffic_.tick(speed_, settings_.automaticDriving); voice_.announce6(traffic_.nearestAlert(true), Localization::traffic(Language::English, traffic_.nearestAlert(false)), Localization::traffic(Language::French, traffic_.nearestAlert(false)), Localization::traffic(Language::Spanish, traffic_.nearestAlert(false)), Localization::traffic(Language::Russian, traffic_.nearestAlert(false)), Localization::traffic(Language::Japanese, traffic_.nearestAlert(false))); break;
    case Command::Map: voice_.announce(route_.render(true), route_.render(false)); std::cout << route_.render(true) << "\n"; break;
    case Command::Controls: showControls(); break;
    case Command::Horn: runtime_.playOneShot("assets/audio/vehicles/Car_Horn.ogg", {1, 0, 3}, 0.8f); voice_.announce("بوق", "Horn"); break;
    case Command::Pause: { paused_ = !paused_; auto a=Localization::ui(Language::Arabic); auto e=Localization::ui(Language::English); auto f=Localization::ui(Language::French); auto s=Localization::ui(Language::Spanish); auto r=Localization::ui(Language::Russian); auto j=Localization::ui(Language::Japanese); voice_.announce6(paused_?a.paused:a.resumed, paused_?e.paused:e.resumed, paused_?f.paused:f.resumed, paused_?s.paused:s.resumed, paused_?r.paused:r.resumed, paused_?j.paused:j.resumed); break; }
    case Command::Engine: engineOn_ = !engineOn_; if (!engineOn_) speed_ = 0; voice_.announce(engineOn_ ? "تم تشغيل المحرك" : "تم إيقاف المحرك", engineOn_ ? "Engine on" : "Engine off"); break;
    case Command::Stations: voice_.announce(vehicleSystem_.stations(true) + ". " + vehicleSystem_.status(true), vehicleSystem_.stations(false) + ". " + vehicleSystem_.status(false)); vehicleSystem_.refuel(); vehicleSystem_.changeOil(); vehicleSystem_.charge(); career_.refuel(); career_.service(); career_.charge(); break;
    case Command::Customize: { static const char* colors[] = {"blue", "red", "green", "black", "white", "yellow"}; static int i = 0; vehicleSystem_.setColor(colors[++i % 6]); vehicleSystem_.upgradeEngine(i % 2 ? "sport" : "standard"); vehicleSystem_.upgradeBrakes(i % 2 ? "abs-sport" : "standard"); voice_.announce(vehicleSystem_.customize(true), vehicleSystem_.customize(false)); break; }
    case Command::Language: { int n = (static_cast<int>(voice_.language()) + 1) % 6; settings_.language = static_cast<Language>(n); voice_.setLanguage(settings_.language); voice_.announce6("تم اختيار العربية", "English selected", "Français sélectionné", "Español seleccionado", "Выбран русский язык", "日本語を選択しました"); break; }
    case Command::RegionMap: region_ = region_ % 27 + 1; voice_.announce(regionMapSummary(region_, true), regionMapSummary(region_, false)); scenarios_.update(speed_, route_.state().progressM, false, career_.stats().fuel < 30, static_cast<int>(weather_.state().type), region_); break;
    case Command::NewVehicle: vehicle_ = vehicle_ % 40 + 1; selectVehicle(); break;
    case Command::Profile: voice_.announce(career_.summary(true) + ". " + career_.achievements(true), career_.summary(false) + ". " + career_.achievements(false)); break;
    case Command::Mission: voice_.announce(career_.missionSummary(true) + ". " + scenarios_.active(true), career_.missionSummary(false) + ". " + scenarios_.active(false)); break;
    case Command::Accessibility: voice_.announce(accessibility_.summary(true), accessibility_.summary(false)); break;
    case Command::Quit: career_.finishTrip(); telemetry_.finish(); career_.save("echodrive.profile"); accessibility_.save("echodrive.accessibility"); scenarios_.save("echodrive.scenarios"); economy_.save("echodrive.economy"); telemetry_.save("echodrive.telemetry"); saveSettings(settings_, "echodrive.cfg"); { auto a=Localization::ui(Language::Arabic); auto e=Localization::ui(Language::English); auto f=Localization::ui(Language::French); auto s=Localization::ui(Language::Spanish); auto r=Localization::ui(Language::Russian); auto j=Localization::ui(Language::Japanese); voice_.announce6(a.goodbye, e.goodbye, f.goodbye, s.goodbye, r.goodbye, j.goodbye); } break;
    case Command::Unknown: { auto a=Localization::ui(Language::Arabic); auto e=Localization::ui(Language::English); auto f=Localization::ui(Language::French); auto s=Localization::ui(Language::Spanish); auto r=Localization::ui(Language::Russian); auto j=Localization::ui(Language::Japanese); voice_.announce6(a.unknown, e.unknown, f.unknown, s.unknown, r.unknown, j.unknown); break; }
    }
}
void Game::run() {
    auto a=Localization::ui(Language::Arabic); auto e=Localization::ui(Language::English); auto f=Localization::ui(Language::French); auto s=Localization::ui(Language::Spanish); auto r=Localization::ui(Language::Russian); auto j=Localization::ui(Language::Japanese);
    voice_.announce6(a.welcome, e.welcome, f.welcome, s.welcome, r.welcome, j.welcome);
    selectStreet();
    selectVehicle();
    for (;;) {
        menu();
        std::string x = readInput();
        Command c = parse(x);
        handle(c);
        if (c == Command::Quit) break;
    }
}
}
