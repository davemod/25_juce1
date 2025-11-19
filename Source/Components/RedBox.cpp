/*
  ==============================================================================

    RedBox.cpp
    Created: 14 Nov 2025 10:00:37am
    Author:  David Hill

  ==============================================================================
*/

#include "RedBox.h"

// Definition der Funktion RedBox::paint. Deklariert wird sie in der RedBox.h. Wichtig: hier wird kein override benötigt.
void RedBox::paint (Graphics& g)
{
    g.fillAll(Colours::red);
}
