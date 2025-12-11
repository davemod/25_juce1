#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
    int horsepower;
    Engine(int hp) {
        // TODO: Initialisiere horsepower
    }
    void printSpecs() {
        // TODO: Gib die PS aus
    }
};

class Vehicle {
public:
    string brand;
    Engine engine;

    Vehicle(string b, Engine e) : engine(e) {
        // TODO: Initialisiere brand
    }

    virtual void printInfo() {
        // TODO: Gib Brand und Engine Specs aus
    }
};

class Car : public Vehicle {
public:
    Car(string b, Engine e) : Vehicle(b, e) {}
    void printInfo() override {
        // TODO: Gib Car-spezifische Infos aus
        // Tipp: Verwende Vehicle::printInfo() als Basis
    }
};

int main() {
    Engine e(150);
    Car c("BMW", e);

    c.printInfo();

    Vehicle *v = &c;
    // TODO: Zeige Polymorphismus: v->printInfo();

    // TODO: Ändere die Horsepower über Pointer auf Engine

    return 0;
}
