#pragma once
#include <string>
namespace echodrive {
enum class Language { Arabic, English, French, Spanish, Russian, Japanese };
class VoiceGuide {
public:
 explicit VoiceGuide(Language language = Language::Arabic);
 void setLanguage(Language language);
 Language language() const { return language_; }
 void announce(const std::string& arabic, const std::string& english) const;
 void announce6(const std::string& arabic,const std::string& english,const std::string& french,const std::string& spanish,const std::string& russian,const std::string& japanese) const;
 static std::string languageName(Language language);
private: Language language_;
};
}
