#include "settings.hpp"
#include <fstream>
namespace echodrive {
bool saveSettings(const Settings&s,const std::string&p){std::ofstream o(p);if(!o)return false;const char* code[]={"ar","en","fr","es","ru","ja"};o<<code[(int)s.language]<<'\n'<<s.automaticDriving<<'\n'<<s.repeatGuidance<<'\n'<<s.masterVolume<<'\n'<<s.street<<'\n';return true;}
Settings loadSettings(const std::string&p){Settings s;std::ifstream i(p);if(!i)return s;std::string l;int a,r;i>>l>>a>>r>>s.masterVolume>>s.street;if(l=="en")s.language=Language::English;else if(l=="fr")s.language=Language::French;else if(l=="es")s.language=Language::Spanish;else if(l=="ru")s.language=Language::Russian;else if(l=="ja")s.language=Language::Japanese;else s.language=Language::Arabic;s.automaticDriving=a;s.repeatGuidance=r;return s;}
}
