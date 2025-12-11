#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    string name;

    Animal(string n) : name(n) {}

    virtual void makeSound() {
        // TODO: Leere Implementierung
    }
};

class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    void makeSound() override {
        // TODO: Ausgabe "Woof"
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}
    void makeSound() override {
        // TODO: Ausgabe "Meow"
        cout << "Meow!" << endl;
    }
};

int main() {
    Dog dog("Bello");
    Cat cat("Minka");

    Animal *a;

    // TODO: Zeige Polymorphismus durch Pointer
    a = &dog; a->makeSound();
    a = &cat; a->makeSound();

    return 0;
}
