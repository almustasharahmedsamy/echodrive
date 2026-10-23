#include "scenarios.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
namespace echodrive {
ScenarioBook::ScenarioBook() { reset(); }
void ScenarioBook::reset() { scenarios_ = {
 {1,ScenarioType::Delivery,"التسليم الآمن","قد 800 متر دون اصطدام",150,0,true,false},
 {2,ScenarioType::Emergency,"ممر الطوارئ","افسح الطريق لسيارة الطوارئ",250,0,false,false},
 {3,ScenarioType::FuelSaving,"اقتصاد الوقود","أكمل المهمة مع وقود فوق 30 بالمئة",300,0,false,false},
 {4,ScenarioType::WeatherChallenge,"اختبار الطقس","قد في مطر أو عاصفة",350,0,false,false},
 {5,ScenarioType::AccessibilityTraining,"التدريب الصوتي","استعمل الخريطة والحالة الصوتية",200,0,false,false},
 {6,ScenarioType::NightDrive,"رحلة الليل","أكمل طريقًا طويلًا دون ضرر كبير",450,0,false,false},
 {7,ScenarioType::RegionalTour,"جولة مصرية","زر ثلاث مناطق مصرية",700,0,false,false}
}; activeId_ = 1; }
void ScenarioBook::update(double speed,double distance,bool emergencyYielded,bool lowFuel,int weatherIndex,int region) { auto& s=scenarios_[std::clamp(activeId_-1,0,static_cast<int>(scenarios_.size())-1)]; if (!s.unlocked||s.completed) return; bool done=false; switch(s.type){case ScenarioType::Delivery:done=distance>=800;break;case ScenarioType::Emergency:done=emergencyYielded;break;case ScenarioType::FuelSaving:done=lowFuel;break;case ScenarioType::WeatherChallenge:done=weatherIndex>0;break;case ScenarioType::AccessibilityTraining:done=speed>=0&&region>=1;break;case ScenarioType::NightDrive:done=distance>=2000;break;case ScenarioType::RegionalTour:done=region>=3;break;} if(done)complete(s.id); }
void ScenarioBook::unlock(int id){for(auto& s:scenarios_)if(s.id==id)s.unlocked=true;}
void ScenarioBook::complete(int id){for(auto& s:scenarios_)if(s.id==id&&s.unlocked){s.completed=true;unlock(id+1);activeId_=std::min(id+1,static_cast<int>(scenarios_.size()));}}
const std::vector<Scenario>& ScenarioBook::all()const{return scenarios_;}
std::string ScenarioBook::active(bool ar)const{const auto&s=scenarios_[std::clamp(activeId_-1,0,static_cast<int>(scenarios_.size())-1)];return ar?"السيناريو: "+s.title+"، الهدف: "+s.objective:"Scenario: "+s.title+", objective: "+s.objective;}
std::string ScenarioBook::summary(bool ar)const{int completed=0,unlocked=0;for(const auto&s:scenarios_){completed+=s.completed;unlocked+=s.unlocked;}return ar?"السيناريوهات: "+std::to_string(completed)+" مكتملة من "+std::to_string(unlocked)+" مفتوحة":"Scenarios: "+std::to_string(completed)+" complete of "+std::to_string(unlocked)+" unlocked";}
bool ScenarioBook::save(const std::string& path)const{std::ofstream out(path);if(!out)return false;out<<activeId_<<'\n';for(const auto&s:scenarios_)out<<s.id<<' '<<s.unlocked<<' '<<s.completed<<'\n';return true;}
bool ScenarioBook::load(const std::string& path){std::ifstream in(path);if(!in)return false;in>>activeId_;for(auto&s:scenarios_)in>>s.id>>s.unlocked>>s.completed;return static_cast<bool>(in);}
}
