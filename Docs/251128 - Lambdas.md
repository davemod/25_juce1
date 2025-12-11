# 28.11.2025

## Beispiel von Lambda Funktionen in c++

### Aufbau einer Lambda Funktion

Eine Lambda Funktion in C++ ist eine anonyme Funktion, die direkt im Code definiert werden kann. Der allgemeine Aufbau sieht so aus:

```cpp
[Capture] (Parameter) -> Rückgabetyp {
    // Funktionskörper
}
```

- **Capture**: Welche Variablen aus dem umgebenden Kontext übernommen werden.
- **Parameter**: Übergabeparameter wie bei normalen Funktionen.
- **Rückgabetyp**: Optional, kann oft weggelassen werden.
- **Funktionskörper**: Der auszuführende Code.

---

### Beispiel: Lambda Funktion in einer `std::function`

Man kann eine Lambda Funktion einer `std::function` zuweisen, um sie flexibel zu verwenden:

```cpp
#include <functional>
#include <iostream>

int main() {
    std::function<int(int, int)> addiere = [](int a, int b) {
        return a + b;
    };

    std::cout << "3 + 4 = " << addiere(3, 4) << std::endl;
    return 0;
}
```

**Erklärung:**  
Hier wird eine Lambda Funktion erstellt, die zwei Zahlen addiert. Sie wird in einer `std::function` gespeichert und wie eine normale Funktion aufgerufen.

---

### Beispiel: Lambda Funktion mit `juce::TextButton::onClick`

In JUCE kann man das `onClick`-Event eines Buttons mit einer Lambda Funktion verbinden:

```cpp
juce::TextButton myButton { "Klick mich!" };

myButton.onClick = []() {
    juce::Logger::outputDebugString("Button wurde geklickt!");
};
```

**Erklärung:**  
Hier wird dem Button eine Lambda Funktion zugewiesen, die ausgeführt wird, wenn der Button geklickt wird.  
Das ist besonders praktisch, um schnell auf Benutzerinteraktionen zu reagieren, ohne eine separate Funktion schreiben zu müssen.

---

**Zusammenfassung:**  
- Lambda Funktionen sind anonyme Funktionen, die direkt im Code definiert werden.
- Sie können Variablen aus dem Kontext übernehmen und flexibel eingesetzt werden.
- In JUCE werden sie oft für Event-Handler wie `onClick` verwendet.