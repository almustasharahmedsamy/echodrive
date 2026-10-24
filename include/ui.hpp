#pragma once
#include "localization.hpp"
#include <string>
namespace echodrive {
struct UiTheme { bool highContrast=true; bool compact=false; bool unicode=true; };
class DesktopUi {
public:
    DesktopUi();
    void setTheme(const UiTheme& theme);
    const UiTheme& theme() const;
    std::string frame(const std::string& content) const;
    std::string header(Language language, const std::string& subtitle) const;
    std::string menu(Language language) const;
    std::string controls(Language language) const;
    std::string prompt(Language language, const std::string& label) const;
    std::string divider() const;
private:
    UiTheme theme_;
    std::string border() const;
};
}
