#include "telemetry.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
namespace echodrive {
TelemetryRecorder::TelemetryRecorder() = default;
void TelemetryRecorder::start(int street,int vehicle,int region){street_=street;vehicle_=vehicle;region_=region;firstFuel_=100;lastSpeed_=0;samples_.clear();report_=DrivingReport{};sample(0,100,0,region_,TelemetryEvent::Start,"trip started");}
void TelemetryRecorder::sample(double speed,double fuel,double damage,int region,TelemetryEvent event,const std::string& note){int second=samples_.empty()?0:samples_.back().second+1;samples_.push_back({second,speed,fuel,damage,region,event,note});lastSpeed_=speed;recalculate();}
void TelemetryRecorder::addWarning(){report_.warnings++;}
void TelemetryRecorder::addCollision(){report_.collisions++;}
void TelemetryRecorder::addAccessibilityPrompt(){report_.accessibilityPrompts++;}
void TelemetryRecorder::finish(){sample(lastSpeed_,samples_.empty()?firstFuel_:samples_.back().fuel,samples_.empty()?0:samples_.back().damage,region_,TelemetryEvent::Finish,"trip finished");}
const std::vector<TelemetrySample>& TelemetryRecorder::samples()const{return samples_;}
const DrivingReport& TelemetryRecorder::report()const{return report_;}
void TelemetryRecorder::recalculate(){if(samples_.empty())return;double totalSpeed=0;report_.maximumSpeed=0;report_.fuelUsed=std::max(0.0,firstFuel_-samples_.back().fuel);report_.damageTaken=samples_.back().damage;for(const auto&s:samples_){totalSpeed+=s.speed;report_.maximumSpeed=std::max(report_.maximumSpeed,s.speed);}report_.elapsedSeconds=samples_.back().second;report_.averageSpeed=totalSpeed/samples_.size();}
std::string TelemetryRecorder::reportText(bool ar)const{std::ostringstream out;if(ar)out<<"تقرير الرحلة: الزمن "<<report_.elapsedSeconds<<" ثانية، متوسط السرعة "<<static_cast<int>(report_.averageSpeed)<<"، أعلى سرعة "<<static_cast<int>(report_.maximumSpeed)<<"، وقود مستهلك "<<static_cast<int>(report_.fuelUsed)<<"، ضرر "<<static_cast<int>(report_.damageTaken)<<"، تحذيرات "<<report_.warnings<<"، اصطدامات "<<report_.collisions<<"، تنبيهات إتاحة "<<report_.accessibilityPrompts;else out<<"Trip report: "<<report_.elapsedSeconds<<" seconds, average speed "<<static_cast<int>(report_.averageSpeed)<<", maximum speed "<<static_cast<int>(report_.maximumSpeed)<<", fuel used "<<static_cast<int>(report_.fuelUsed)<<", damage "<<static_cast<int>(report_.damageTaken)<<", warnings "<<report_.warnings<<", collisions "<<report_.collisions<<", accessibility prompts "<<report_.accessibilityPrompts;return out.str();}
std::string TelemetryRecorder::timeline(bool ar)const{std::ostringstream out;out<<(ar?"خط زمني: ":"Timeline: ");int shown=0;for(const auto&s:samples_){if(shown++>=8)break;out<<"["<<s.second<<"] "<<s.note<<"؛ ";}return out.str();}
std::string TelemetryRecorder::eventName(TelemetryEvent event,bool ar)const{
    switch(event){
    case TelemetryEvent::Start:return ar?"بداية":"start";
    case TelemetryEvent::SpeedChange:return ar?"سرعة":"speed";
    case TelemetryEvent::Brake:return ar?"فرامل":"brake";
    case TelemetryEvent::Turn:return ar?"توجيه":"turn";
    case TelemetryEvent::Weather:return ar?"طقس":"weather";
    case TelemetryEvent::Traffic:return ar?"مرور":"traffic";
    case TelemetryEvent::Refuel:return ar?"وقود":"refuel";
    case TelemetryEvent::Repair:return ar?"صيانة":"repair";
    case TelemetryEvent::Mission:return ar?"مهمة":"mission";
    case TelemetryEvent::Collision:return ar?"اصطدام":"collision";
    case TelemetryEvent::Finish:return ar?"نهاية":"finish";
    }
    return ar?"غير معروف":"unknown";
}
std::string TelemetryRecorder::safetyGrade(bool ar)const{
    int risk=riskScore();
    std::string grade=risk<10?"A":risk<25?"B":risk<50?"C":risk<75?"D":"F";
    return ar?"تقييم السلامة: "+grade+"، نقاط المخاطرة "+std::to_string(risk):"Safety grade: "+grade+", risk points "+std::to_string(risk);
}
int TelemetryRecorder::riskScore()const{
    return report_.collisions*25+report_.warnings*5+static_cast<int>(report_.damageTaken/5.0);
}
int TelemetryRecorder::sampleCount()const{
    return static_cast<int>(samples_.size());
}
bool TelemetryRecorder::exportCsv(const std::string& path)const{
    std::ofstream out(path);
    if(!out)return false;
    out<<"second,speed,fuel,damage,region,event,note\n";
    for(const auto& sample:samples_)
        out<<sample.second<<','<<sample.speed<<','<<sample.fuel<<','<<sample.damage<<','<<sample.region<<','<<eventName(sample.event,false)<<","<<sample.note<<"\"\n";
    return true;
}
void TelemetryRecorder::clear(){samples_.clear();report_=DrivingReport{};firstFuel_=0;lastSpeed_=0;}
bool TelemetryRecorder::save(const std::string& path)const{std::ofstream out(path);if(!out)return false;out<<street_<<' '<<vehicle_<<' '<<region_<<' '<<firstFuel_<<'\n';out<<report_.elapsedSeconds<<' '<<report_.averageSpeed<<' '<<report_.maximumSpeed<<' '<<report_.fuelUsed<<' '<<report_.damageTaken<<' '<<report_.warnings<<' '<<report_.collisions<<' '<<report_.accessibilityPrompts<<'\n';for(const auto&s:samples_)out<<s.second<<' '<<s.speed<<' '<<s.fuel<<' '<<s.damage<<' '<<s.region<<' '<<static_cast<int>(s.event)<<' '<<s.note<<'\n';return true;}
bool TelemetryRecorder::load(const std::string& path){std::ifstream in(path);if(!in)return false;in>>street_>>vehicle_>>region_>>firstFuel_;in>>report_.elapsedSeconds>>report_.averageSpeed>>report_.maximumSpeed>>report_.fuelUsed>>report_.damageTaken>>report_.warnings>>report_.collisions>>report_.accessibilityPrompts;samples_.clear();int second,region,event;double speed,fuel,damage;std::string note;std::string rest;while(in>>second>>speed>>fuel>>damage>>region>>event){std::getline(in,rest);if(!rest.empty()&&rest.front()==' ')rest.erase(0,1);samples_.push_back({second,speed,fuel,damage,region,static_cast<TelemetryEvent>(event),rest});}return true;}
}
