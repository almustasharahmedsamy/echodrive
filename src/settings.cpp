#include "settings.hpp"
#include <fstream>
namespace echodrive {
bool saveSettings(const Settings&s,const std::string&p){std::ofstream o(p);if(!o)return false;o<<(s.language==Language::Arabic?"ar":"en")<<'\n'<<s.automaticDriving<<'\n'<<s.repeatGuidance<<'\n'<<s.masterVolume<<'\n'<<s.street<<'\n';return true;}
Settings loadSettings(const std::string&p){Settings s;std::ifstream i(p);if(!i)return s;std::string l;int a,r;i>>l>>a>>r>>s.masterVolume>>s.street;s.language=l=="en"?Language::English:Language::Arabic;s.automaticDriving=a;s.repeatGuidance=r;return s;}
}
