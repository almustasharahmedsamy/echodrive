#include "voice.hpp"
#include <iostream>
#ifdef ECHODRIVE_WINDOWS
#include <windows.h>
#include <sapi.h>
#endif
namespace echodrive {
VoiceGuide::VoiceGuide(Language language):language_(language){}
void VoiceGuide::setLanguage(Language language){language_=language;}
std::string VoiceGuide::languageName(Language l){switch(l){case Language::Arabic:return "العربية";case Language::English:return "English";case Language::French:return "Français";case Language::Spanish:return "Español";case Language::Russian:return "Русский";case Language::Japanese:return "日本語";}return "العربية";}
#ifdef ECHODRIVE_WINDOWS
static void speakWindows(const std::string& text){if(SUCCEEDED(CoInitializeEx(nullptr,COINIT_APARTMENTTHREADED))){ISpVoice* sapi=nullptr;if(SUCCEEDED(CoCreateInstance(CLSID_SpVoice,nullptr,CLSCTX_ALL,IID_ISpVoice,reinterpret_cast<void**>(&sapi)))){int size=MultiByteToWideChar(CP_UTF8,0,text.data(),static_cast<int>(text.size()),nullptr,0);std::wstring w(size,L' ');MultiByteToWideChar(CP_UTF8,0,text.data(),static_cast<int>(text.size()),w.data(),size);sapi->Speak(w.c_str(),SPF_ASYNC,nullptr);sapi->Release();}CoUninitialize();}}
#endif
void VoiceGuide::announce(const std::string& ar,const std::string& en)const{const std::string& text=language_==Language::Arabic?ar:en;std::cout<<"[VOICE] "<<text<<'\n';
#ifdef ECHODRIVE_WINDOWS
speakWindows(text);
#endif
}
void VoiceGuide::announce6(const std::string& ar,const std::string& en,const std::string& fr,const std::string& es,const std::string& ru,const std::string& ja)const{const std::string* text=&ar;switch(language_){case Language::Arabic:text=&ar;break;case Language::English:text=&en;break;case Language::French:text=&fr;break;case Language::Spanish:text=&es;break;case Language::Russian:text=&ru;break;case Language::Japanese:text=&ja;break;}std::cout<<"[VOICE] "<<*text<<'\n';
#ifdef ECHODRIVE_WINDOWS
speakWindows(*text);
#endif
}
}
