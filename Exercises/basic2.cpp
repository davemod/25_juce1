#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    int age;

    Person(string n, int a) {
        // TODO: Initialisiere die Membervariablen
    }

    void printInfo() {
        // TODO: Gib Name und Alter aus
    }
};

int main() {
    Person p("Niko", 29);
    p.printInfo();

    Person *ptr = &p;
    // TODO: Rufe printInfo() über den Pointer auf

    return 0;
}
