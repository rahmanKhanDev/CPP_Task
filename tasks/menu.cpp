#include <iostream> 
#include <vector> 
#include <string> 
 
class Menu { 
public: 
    std::string title; 
    std::vector<Menu> submenus; 
 
    Menu(const std::string& title) : title(title) {} 
 
    void addSubmenu(const Menu& submenu) { 
        submenus.push_back(submenu); 
    } 
}; 
 
void displayMenu(const Menu& menu, int currentOption) { 
    std::cout << "=== " << menu.title << " ===\n"; 
    for (size_t i = 0; i < menu.submenus.size(); ++i) { 
        std::cout << (i == currentOption ? "> " : "  ") << menu.submenus[i].title << "\n"; 
    } 
} 
 
void navigateMenu(Menu& root) { 
    Menu* currentMenu = &root; 
    int currentOption = 0; 
 
    while (true) { 
        displayMenu(*currentMenu, currentOption); 
 
        std::cout << "\nCommands: 1-Down, 2-Up, 3-Enter, 4-Back, 5-Exit\n"; 
        int command; 
        std::cin >> command; 
 
        if (command == 1) { // Down 
            currentOption = (currentOption + 1) % currentMenu->submenus.size(); 
        }  

else if (command == 2) { // Up 
            currentOption = (currentOption - 1 + currentMenu->submenus.size()) % currentMenu->submenus.size(); 
        }  

else if (command == 3) { // Enter 
            

 if (!currentMenu->submenus.empty()) { 
                currentMenu = &currentMenu->submenus[currentOption]; 
                currentOption = 0; 
            } 
        } else if (command == 4) { // Back 
            // Assuming root has no parent 
            break; 
        } else if (command == 5) { // Exit 
            break; 
        } 
    } 
} 
 
int main() { 
    Menu root("Main Menu"); 
    Menu settings("Settings"); 
    settings.addSubmenu(Menu("Display Settings")); 
    settings.addSubmenu(Menu("Audio Settings")); 
    Menu media("Media"); 
    media.addSubmenu(Menu("Radio")); 
    media.addSubmenu(Menu("Bluetooth Audio")); 
 
    root.addSubmenu(settings); 
    root.addSubmenu(media); 
 
    navigateMenu(root); 
    return 0; 
} 