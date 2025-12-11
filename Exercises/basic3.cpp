#include <iostream>
#include <string>
using namespace std;

class Address {
public:
    string street;
    string city;
    int zip;

    Address(string s, string c, int z) {
        // TODO: Initialisiere die Membervariablen
    }

    void printAddress() {
        // TODO: Gib die Adresse aus
    }
};

class Person {
public:
    string name;
    int age;
    Address addr; // Komposition

    Person(string n, int a, Address ad) : addr(ad) {
        // TODO: Initialisiere name und age
    }

    void printInfo() {
        // TODO: Gib Name, Alter und Adresse aus
    }
};

int main() {
    Address adr("Musterstr. 1", "Berlin", 10115);
    Person p("Niko", 29, adr);
    p.printInfo();

    return 0;
}
