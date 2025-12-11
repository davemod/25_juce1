#include <iostream>
using namespace std;

// Vertausche zwei Integer-Werte mit Referenzen
void swap(int &a, int &b) {
    // TODO: Implementiere das Vertauschen
}

// Verdopple den Wert über einen Pointer
void doubleValue(int *ptr) {
    // TODO: Implementiere die Verdopplung
}

int main() {
    int x = 5;
    int y = 10;

    cout << "Vor dem Swap: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "Nach dem Swap: x=" << x << ", y=" << y << endl;

    int *p = &x;
    doubleValue(p);
    cout << "Nach doubleValue: x=" << x << endl;

    return 0;
}
