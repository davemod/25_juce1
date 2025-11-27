//
// Created by hannes on 11/21/25.
//


#pragma once

#include <JuceHeader.h>

class PresetMenuComponent : public Component
{
public:
    PresetMenuComponent ();
    ~PresetMenuComponent () override;

    void resized () override; // This is important!
private:

    TextButton loadButton { "Load" };
    TextButton saveButton { "Save" };
    //TextButton nextButton { "➡️" };
    //TextButton previousButton { "⬅️" };
    TextButton nextButton { ">" };
    TextButton previousButton { "<" };

};

