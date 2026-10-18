#pragma once
#include <string>
namespace echodrive {
enum class Language { Arabic, English };
class VoiceGuide {
public:
 explicit VoiceGuide(Language language = Language::Arabic);
 void setLanguage(Language language);
 void announce(const std::string& arabic, const std::string& english) const;
private: Language language_;
};
}
