//
// Created by Shaked Melman on 15/09/2024.
//

#ifndef YETANOTHERDAW_TRACK_H
#define YETANOTHERDAW_TRACK_H

#include "Effect.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_core/juce_core.h"

class Track
{
public:
    Track (juce::String name, juce::String filePath);
    ~Track() = default;

    static constexpr int WAVEFORM_RESOLUTION = 1000; // Number of points in the waveform
    static constexpr int SAMPLES_PER_THUMBNAIL_POINT = 128; // Number of samples per waveform point

    [[nodiscard]] const juce::String& getName() const { return trackName; }
    [[nodiscard]] const juce::String& getFilePath() const { return audioFilePath; }
    void setVolume (float newVolume) { volume = juce::jlimit (0.0f, 1.0f, newVolume); }
    [[nodiscard]] float getVolume() const { return volume; }
    void setPan (float newPan) { pan = juce::jlimit (-1.0f, 1.0f, newPan); }
    [[nodiscard]] float getPan() const { return pan; }
    void setMuted (bool shouldBeMuted) { isMuted = shouldBeMuted; }
    [[nodiscard]] bool getMuted() const { return isMuted; }
    void setSolo (bool shouldBeSolo) { isSolo = shouldBeSolo; }
    [[nodiscard]] bool getSolo() const { return isSolo; }
    [[nodiscard]] juce::String getUniqueID() const { return uniqueID; }

    void loadAudioData();
    [[nodiscard]] const juce::AudioBuffer<float>& getWaveformData() const { return waveformData; }
    [[nodiscard]] bool isWaveformReady() const { return waveformReady; }

    [[nodiscard]] juce::var toJSON() const;
    static std::unique_ptr<Track> fromJSON (const juce::var& json);

private:
    juce::String trackName;
    juce::String audioFilePath;
    juce::AudioBuffer<float> waveformData;
    bool waveformReady = false;

    float volume;
    float pan;
    bool isMuted;
    bool isSolo;

    juce::String uniqueID;

    void generateWaveform(const juce::AudioBuffer<float>& audioBuffer);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Track)
};
#endif //YETANOTHERDAW_TRACK_H
