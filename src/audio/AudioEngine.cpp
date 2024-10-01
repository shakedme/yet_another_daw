//
// Created by Shaked Melman on 29/09/2024.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine() : gain (1.0f)
{
    formatManager.registerBasicFormats();
    setAudioChannels (0, 2); // no inputs, 2 outputs
}

AudioEngine::~AudioEngine()
{
    shutdownAudio();
}

void AudioEngine::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void AudioEngine::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock (bufferToFill);

    // Apply gain
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        bufferToFill.buffer->applyGain (channel, bufferToFill.startSample, bufferToFill.numSamples, gain);
    }
}

void AudioEngine::releaseResources()
{
    transportSource.releaseResources();
}

void AudioEngine::loadFile (const juce::File& file)
{
    auto* reader = formatManager.createReaderFor (file);
    if (reader != nullptr)
    {
        auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
}

void AudioEngine::play()
{
    transportSource.start();
}

void AudioEngine::stop()
{
    transportSource.stop();
}

void AudioEngine::setGain (float newGain)
{
    gain = newGain;
}