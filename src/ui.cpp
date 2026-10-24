#include "ui.hpp"
#include <sstream>
namespace echodrive {
DesktopUi::DesktopUi()=default;
void DesktopUi::setTheme(const UiTheme& theme){theme_=theme;}
const UiTheme& DesktopUi::theme()const{return theme_;}
std::string DesktopUi::border()const{return theme_.highContrast?"============================================================":"------------------------------------------------------------";}
std::string DesktopUi::divider()const{return border();}
std::string DesktopUi::frame(const std::string& content)const{std::ostringstream out;out<<border()<<"\n"<<content<<"\n"<<border();return out.str();}
std::string DesktopUi::header(Language language,const std::string& subtitle)const{auto t=Localization::ui(language);std::ostringstream out;out<<frame(t.title+" | "+subtitle);return out.str();}
std::string DesktopUi::menu(Language language)const{auto t=Localization::ui(language);std::ostringstream out;out<<frame("[↑/↓] "+t.forwardLabel+" / "+t.brakeLabel+" | [←/→] "+t.leftLabel+" / "+t.rightLabel+"\n[F1] "+t.statusLabel+" | [F2] "+t.mapLabel+" | [F3] "+t.weatherLabel+" | [F4] "+t.trafficLabel+"\n[F5] "+t.stationsLabel+" | [F6] "+t.customizeLabel+" | [profile] "+t.profileLabel+" | [mission] "+t.missionLabel+"\n[access] "+t.accessibilityLabel+" | [scenario] "+t.scenarioLabel+" | [Q] "+t.quitLabel);return out.str();}
std::string DesktopUi::controls(Language language)const{auto t=Localization::ui(language);return frame(t.controlsTitle+"\n"+t.controlsBody);}
std::string DesktopUi::prompt(Language language,const std::string& label)const{return frame(Localization::ui(language).title+"\n"+label);}
}
