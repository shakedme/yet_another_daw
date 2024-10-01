#include "Track.h"
#include <juce_audio_formats/juce_audio_formats.h>

Track::Track (juce::String name, juce::String filePath)
    : trackName (std::move (name)), audioFilePath (std::move (filePath)), volume (1.0f), pan (0.0f), isMuted (false), isSolo (false)
{
    uniqueID = juce::Uuid().toString();
}

void Track::loadAudioData()
{
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    std::unique_ptr<juce::AudioFormatReader> reader (formatManager.createReaderFor (juce::File (audioFilePath)));

    if (reader != nullptr)
    {
        auto numChannels = static_cast<int> (reader->numChannels);
        auto numSamples = static_cast<int> (reader->lengthInSamples);

        juce::AudioBuffer<float> tempBuffer (numChannels, numSamples);
        reader->read (&tempBuffer, 0, numSamples, 0, true, true);

        generateWaveform (tempBuffer);
    }
}

void Track::generateWaveform (const juce::AudioBuffer<float>& audioBuffer)
{
    auto numChannels = audioBuffer.getNumChannels();
    auto numSamples = audioBuffer.getNumSamples();

    waveformData.setSize (1, WAVEFORM_RESOLUTION);
    waveformData.clear();

    int samplesPerThumbnailPoint = juce::jmax (1, numSamples / WAVEFORM_RESOLUTION);

    int sample = 0;
    for (int i = 0; i < WAVEFORM_RESOLUTION; ++i)
    {
        float lowValue = 0.0f;
        float highValue = 0.0f;

        for (int j = 0; j < samplesPerThumbnailPoint && sample < numSamples; ++j, ++sample)
        {
            for (int channel = 0; channel < numChannels; ++channel)
            {
                float sampleValue = audioBuffer.getSample (channel, sample);
                lowValue = juce::jmin (lowValue, sampleValue);
                highValue = juce::jmax (highValue, sampleValue);
            }
        }

        waveformData.setSample (0, i, (highValue - lowValue) * 0.5f);
    }

    waveformReady = true;
}

juce::var Track::toJSON() const
{
    auto* json = new juce::DynamicObject();
    json->setProperty ("name", trackName);
    json->setProperty ("filePath", audioFilePath);
    json->setProperty ("volume", volume);
    json->setProperty ("pan", pan);
    json->setProperty ("muted", isMuted);
    json->setProperty ("solo", isSolo);
    json->setProperty ("id", uniqueID);
    return json;
}

std::unique_ptr<Track> Track::fromJSON (const juce::var& json)
{
    if (!json.isObject())
        return nullptr;

    auto track = std::make_unique<Track> (json["name"], json["filePath"]);
    track->setVolume (json["volume"]);
    track->setPan (json["pan"]);
    track->setMuted (json["muted"]);
    track->setSolo (json["solo"]);
    track->uniqueID = json["id"];
    return track;
}