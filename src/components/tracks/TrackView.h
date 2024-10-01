//
// Created by Shaked Melman on 15/09/2024.
//

#ifndef YETANOTHERDAW_TRACKVIEW_H
#define YETANOTHERDAW_TRACKVIEW_H
#include "../../models/Track.h"
#include "juce_audio_utils/juce_audio_utils.h"

class TrackView : public juce::Component,
                  private juce::Timer
{
public:
    TrackView (Track& t);
    void paint (juce::Graphics& g) override;

private:
    Track& track;
    void timerCallback() override;
};
#endif //YETANOTHERDAW_TRACKVIEW_H
