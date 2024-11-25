#include <iostream> 
#include <thread> 
#include <mutex> 
#include <random> 
#include <chrono> 
 
class VehicleData { 
public: 
    int speed; 
    int fuel; 
    int temperature; 
 
    VehicleData() : speed(0), fuel(100), temperature(80) {} 
 
    void update() { 
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> speedDist(0, 120); 
        std::uniform_int_distribution<> fuelDist(-2, 0); 
        std::uniform_int_distribution<> tempDist(-2, 2); 
 
        speed = speedDist(gen); 
        fuel += fuelDist(gen); 
        fuel = std::max(0, fuel); 
        temperature += tempDist(gen); 
    } 
}; 
 
void displayData(VehicleData& data, std::mutex& dataMutex) { 
    while (true) { 
        { 
            std::lock_guard<std::mutex> lock(dataMutex); 
            std::cout << "\033[2J\033[1;1H"; // Clear console 
            std::cout << "Speed: " << data.speed << " km/h\n"; 
            std::cout << "Fuel: " << data.fuel << "%\n"; 
            std::cout << "Temperature: " << data.temperature << "°C\n"; 
 
            if (data.fuel < 10) { 
                std::cout << "Warning: Low Fuel!\n"; 
            } 
            if (data.temperature > 100) { 
                std::cout << "Warning: High Temperature!\n"; 
            } 
        } 
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    } 
} 
 
void updateData(VehicleData& data, std::mutex& dataMutex) { 
    while (true) { 
        { 
            std::lock_guard<std::mutex> lock(dataMutex); 
            data.update(); 
        } 
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    } 
} 
 
int main() { 
    VehicleData data; 
    std::mutex dataMutex; 
 
    std::thread updateThread(updateData, std::ref(data), std::ref(dataMutex)); 
    std::thread displayThread(displayData, std::ref(data), std::ref(dataMutex)); 
 
    updateThread.join(); 
    displayThread.join(); 
 
    return 0; 
} 