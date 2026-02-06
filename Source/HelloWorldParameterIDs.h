
#pragma once

#include <JuceHeader.h>

struct HelloWorldParameterID
{

  static String bandMute(int i) { return "mute_band_" + std::to_string(i); };

  static String bandSolo(int i) { return "solo_band_" + std::to_string(i); };

  static String bandGain(int i) { return "gain_band_" + std::to_string(i); };
};
