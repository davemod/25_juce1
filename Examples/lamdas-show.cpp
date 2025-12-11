#include <iostream>
#include <vector>

/*
 * Einführung in Lambda-Funktionen:
 * 
 * Lambda-Funktionen sind anonyme Funktionen, die direkt an der Stelle definiert werden, 
 * an der sie benötigt werden. Sie werden oft für kurze Funktionen benutzt, 
 * die nur einmal oder innerhalb eines bestimmten Kontexts verwendet werden.
 *
 * Syntax:
 * [capture](parameters) -> return_type { body }
 * 
 * - capture: Welche Variablen aus dem umgebenden Scope die Lambda-Funktion sehen darf
 *   - []       : keine Variablen
 *   - [=]      : alle Variablen per Wert kopieren
 *   - [&]      : alle Variablen per Referenz binden
 *   - [x, &y]  : x per Wert, y per Referenz
 * - parameters: Funktionsparameter, wie bei normalen Funktionen
 * - return_type: optional, C++ kann ihn oft ableiten
 * - body: Codeblock, der ausgeführt wird
 */

int main(){

    int a = 4; // -> 4
    int b = 8;
    bool correct = false;

    // Einfache Lambda-Funktion, die nichts von außen braucht
    auto simpleLambda = []() 
    {
        std::cout << "Hallo von einer Lambda-Funktion!\n";
    };
    simpleLambda(); // Aufruf

    // Lambda mit Parametern
    auto lambdaWithPar = [] (int x, int y) 
    {
        //return x + y;
        int result = x + y;
        std::cout << result << std::endl;
    };
    lambdaWithPar(12, 24);

    // Lambda, das spezifische Variablen aus dem Scope benutzt
    auto captureWithCopy = [a, b]() // Werte werden kopiert
    {// Werte können nicht verändert werden, man muss neuer Variable den Wert zuweisen, wenn man etwas ändern möchte
        int c = a;
        int d = b;
        int result = a + b;
        std::cout << result << std::endl;
    };
    captureWithCopy();

    auto captureByCopyAll = [=]() 
    {
        std::cout << "Summer per Copy Capture: " << a + b << "\nBool Wert ausgeben lassen: " << correct << std::endl;
    }; 
    captureByCopyAll();

    // Capture by reference -> Werte sind veränderbar, gilt auch für den scope!
    std::cout << "A before refernced capture lambda: " << a << "\nB before lambda: " << b << std::endl;
    auto captureWithReference = [&] () 
    {
        a += 2;
        b += 3;
        int result = a + b;
        std::cout << result << std::endl;
    };
    captureWithReference();

    std::cout << "A after refernced capture lambda: " << a << "\nB after lambda: " << b << std::endl;


    std::vector<int> numbers = {5, 2, 8, 1, 9};
    std::sort(numbers.begin(), numbers.end(), [](int x, int y){
        bool correct = x < y;
        std::cout << "Is number smaller? "<< x << " vs." << y << " " << "Correct: " << correct << std::endl;
        return correct;
    });
    

    for (int n : numbers){
        std::cout << n << " ";
        std::cout << "\n";
    }

    return 0;
};