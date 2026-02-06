
#pragma once

#include <JuceHeader.h>

namespace ProjectConstants
{
// Use constexpr for the number of bands.
// This is much safer and faster than a global int.
constexpr int numBands = 4;
} // namespace ProjectConstants

namespace EqParameterID
{
// Using a namespace instead of a struct for static methods
// is often preferred in modern C++ for "utility" collections.
inline String bandMute(int i) { return "mute_band_" + String(i); }
inline String bandSolo(int i) { return "solo_band_" + String(i); }
inline String bandGain(int i) { return "gain_band_" + String(i); }
} // namespace ParameterID
