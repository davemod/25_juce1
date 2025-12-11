#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
    int horsepower;
    Engine(int hp) {
        // TODO: Initialisiere horsepower
        horsepower = hp;
    }
    void printSpecs() {
        // TODO: Gib die PS aus
        cout << "HP: " << horsepower << endl;
    }
};

class Vehicle {
public:
    string brand;
    Engine engine;

    Vehicle(string b, Engine e) : engine(e) {
        // TODO: Initialisiere brand
        brand = b;
    }

    virtual void printInfo() {
        // TODO: Gib Brand und Engine Specs aus
        cout << "Brand: " << brand << endl;
        engine.printSpecs();
    }
};

class Car : public Vehicle {
public:
    Car(string b, Engine e) : Vehicle(b, e) {}
    void printInfo() override {
        cout << "Car Info:" << endl;
        Vehicle::printInfo(); // Basisinfos aus Vehicle ausgeben
        cout << "-----------------" << endl;
    }
};

int main() {
    Engine e(150);
    Car c("BMW", e);

    c.printInfo();

    Vehicle *v = &c;
    
    // TODO: Zeige Polymorphismus: v->printInfo()
    cout << "Polymorphic call via Vehicle pointer:" << endl;
    v->printInfo();

    // TODO: Ändere die Horsepower über Pointer auf Engine
    Engine *eptr = &(c.engine);
    eptr->horsepower = 200;

    cout << "After changing engine HP via pointer:" << endl;
    c.printInfo();

    return 0;
}
