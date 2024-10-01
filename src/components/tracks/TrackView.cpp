//
// Created by Shaked Melman on 15/09/2024.
//

#include "TrackView.h"

TrackView::TrackView (Track& t) : track (t)
{
    startTimer (50);
}

void TrackView::paint (juce::Graphics& g)
{
    if (track.isWaveformReady())
    {
        g.setColour (juce::Colours::lightblue);
        const auto& waveform = track.getWaveformData();
        auto numSamples = waveform.getNumSamples();
        auto width = getWidth();
        auto height = getHeight();
        auto midHeight = height / 2;

        for (int i = 0; i < numSamples; ++i)
        {
            auto sampleValue = waveform.getSample (0, i);
            auto x = juce::jmap ((float) i, 0.0f, (float) numSamples - 1, 0.0f, (float) width);
            auto y = juce::jmap (sampleValue, -1.0f, 1.0f, (float) height, 0.0f);

            g.drawLine (x, static_cast<float> (midHeight), x, y);
        }
    }
    else
    {
        g.setColour (juce::Colours::grey);
        g.drawText ("Loading waveform...", getLocalBounds(), juce::Justification::centred);
    }
    g.fillAll (juce::Colours::black);

    // Draw track name
    g.setColour (juce::Colours::white);
    g.drawText (track.getName(), getLocalBounds().reduced (5), juce::Justification::topLeft);
}

void TrackView::timerCallback()
{
    if (track.isWaveformReady())
    {
        stopTimer();
        repaint();
    }
}
