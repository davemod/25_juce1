#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    int age;

    Person(string n, int a) {
        // TODO: Initialisiere die Membervariablen
        name = n;
        age = a;
    }

    void printInfo() {
        // TODO: Gib Name und Alter aus
        cout << "Alter: " << age << "\nName: " << name << endl;
    }
};

int main() {
    Person p("Niko", 29);
    p.printInfo();

    Person *ptr = &p;
    // TODO: Rufe printInfo() über den Pointer auf
    ptr->printInfo();

    return 0;
}
