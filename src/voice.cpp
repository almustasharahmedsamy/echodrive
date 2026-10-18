#include "voice.hpp"
#include <iostream>
#ifdef ECHODRIVE_WINDOWS
#include <windows.h>
#include <sapi.h>
#endif
namespace echodrive {
VoiceGuide::VoiceGuide(Language l):language_(l){}
void VoiceGuide::setLanguage(Language l){language_=l;}
void VoiceGuide::announce(const std::string& ar,const std::string& en) const {
 const std::string& text=language_==Language::Arabic?ar:en; std::cout<<"[VOICE] "<<text<<'\n';
#ifdef ECHODRIVE_WINDOWS
 if(SUCCEEDED(CoInitializeEx(nullptr,COINIT_APARTMENTTHREADED))){ ISpVoice* sapi=nullptr; if(SUCCEEDED(CoCreateInstance(CLSID_SpVoice,nullptr,CLSCTX_ALL,IID_ISpVoice,reinterpret_cast<void**>(&sapi)))){ std::wstring w(text.begin(),text.end()); sapi->Speak(w.c_str(),SPF_ASYNC,nullptr); sapi->Release(); } CoUninitialize(); }
#endif
}
}
