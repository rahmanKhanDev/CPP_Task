#include <iostream> 
#include <map> 
#include <string> 
 
class Theme { 
public: 
    std::string backgroundColor; 
    std::string fontColor; 
    int fontSize; 
    std::string iconStyle; 
 
    Theme(const std::string& bg, const std::string& font, int size, const std::string& icon) 
        : backgroundColor(bg), fontColor(font), fontSize(size), iconStyle(icon) {} 
 
    void display() const { 
        std::cout << "Background Color: " << backgroundColor << "\n" 
                  << "Font Color: " << fontColor << "\n" 
                  << "Font Size: " << fontSize << "\n" 
                  << "Icon Style: " << iconStyle << "\n"; 
    } 
}; 
 
int main() { 
    std::map<std::string, Theme> themes; 
    themes["Classic"] = Theme("Black", "White", 12, "Square"); 
    themes["Sport"] = Theme("Red", "White", 14, "Bold"); 
    themes["Eco"] = Theme("Green", "Black", 10, "Minimal"); 
 
    std::string selectedTheme; 
    while (true) { 
        std::cout << "Available Themes:\n"; 
        for (const auto& [name, theme] : themes) { 
            std::cout << "- " << name << "\n"; 
        } 
        std::cout << "Enter theme name to apply (or type 'exit' to quit): "; 
        std::cin >> selectedTheme; 
 
        if (selectedTheme == "exit") break; 
 
        if (themes.find(selectedTheme) != themes.end()) { 
            std::cout << "Applying Theme: " << selectedTheme << "\n"; 
            themes[selectedTheme].display(); 
        } else { 
            std::cout << "Invalid theme. Try again.\n"; 
        } 
    } 
 
    return 0; 
} 

 