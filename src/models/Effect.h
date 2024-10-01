//
// Created by Shaked Melman on 15/09/2024.
//

#ifndef YETANOTHERDAW_EFFECT_H
#define YETANOTHERDAW_EFFECT_H

#include "juce_core/juce_core.h"

class Effect
{
public:
    juce::String effectName;
    float effectValue;
    bool isEnabled;
};

#endif //YETANOTHERDAW_EFFECT_H
