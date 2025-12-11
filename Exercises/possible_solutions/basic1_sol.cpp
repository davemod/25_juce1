#include <iostream>
using namespace std;

// Vertausche zwei Integer-Werte mit Referenzen
void swap(int &a, int &b) {
    // TODO: Implementiere das Vertauschen
    int temp = a; // Wert von a speichern
    a = b;        // Wert von b in a kopieren
    b = temp;     // alten Wert von a in b kopieren
}

// Verdopple den Wert über einen Pointer
void doubleValue(int *ptr) {
    // TODO: Implementiere die Verdopplung
    *ptr = *ptr * 2;  // Wert, auf den der Pointer zeigt, verdoppeln
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
