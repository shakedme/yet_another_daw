//
// Created by Shaked Melman on 10/09/2024.
//

#include "FileManager.h"

FileManager::FileManager()
{
    formatManager.registerBasicFormats();
    addAndMakeVisible (openButton);
    openButton.setButtonText ("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible (playButton);
    playButton.setButtonText ("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setEnabled (false);

    addAndMakeVisible (stopButton);
    stopButton.setButtonText ("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setEnabled (false);

    addAndMakeVisible (openButton);
    addAndMakeVisible (playButton);
    addAndMakeVisible (stopButton);

    transportSource.addChangeListener (this);
    state = Stopped;

    setSize(300, 100);
}

void FileManager::resized()
{
    openButton.setBounds (10, 10, getWidth() - 20, 20);
    playButton.setBounds (10, 40, getWidth() - 20, 20);
    stopButton.setBounds (10, 70, getWidth() - 20, 20);
}

void FileManager::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState (Playing);
        else
            changeState (Stopped);
    }
}

void FileManager::cleanUp()
{
    transportSource.releaseResources();
}

void FileManager::changeState (TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
            case Stopped: // [3]
                stopButton.setEnabled (false);
                playButton.setEnabled (true);
                transportSource.setPosition (0.0);
                break;

            case Starting: // [4]
                playButton.setEnabled (false);
                transportSource.start();
                break;

            case Playing: // [5]
                stopButton.setEnabled (true);
                break;

            case Stopping: // [6]
                transportSource.stop();
                break;
        }
    }
}

void FileManager::stopButtonClicked()
{
    changeState (Stopping);
}

void FileManager::playButtonClicked()
{
    changeState (Starting);
}

void FileManager::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser> ("Select a file to play...",
        juce::File {},
        "*.wav, *.mp3");
    auto chooserFlags = juce::FileBrowserComponent::openMode
                        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc) {
        auto file = fc.getResult();

        if (file != juce::File {})
        {
            auto* reader = formatManager.createReaderFor (file);

            if (reader != nullptr)
            {
                auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
                transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                readerSource.reset (newSource.release());
            }
        }
    });
}
