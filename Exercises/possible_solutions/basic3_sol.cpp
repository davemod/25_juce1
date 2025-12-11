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
        street = s;
        city = c;
        zip = z;
    }

    void printAddress() {
        // TODO: Gib die Adresse aus
        cout << "Adresse:\n" << street << "\n" << zip << " " << city << endl;
    }
};

class Person {
public:
    string name;
    int age;
    Address addr; // Komposition

    Person(string n, int a, Address ad) : addr(ad) {
        // TODO: Initialisiere name und age
        name = n;
        age = a;
        addr = ad;
    }

    void printInfo() {
        // TODO: Gib Name, Alter und Adresse aus
        cout << "Name: " << name << "\nAlter: " << age << endl;
        addr.printAddress();
    }
};

int main() {
    Address adr("Musterstr. 1", "Berlin", 10115);
    Person p("Niko", 29, adr);
    p.printInfo();

    return 0;
}
