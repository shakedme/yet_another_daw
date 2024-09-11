//
// Created by Shaked Melman on 10/09/2024.
//

#ifndef YETANOTHERDAW_FILEMANAGER_H
#define YETANOTHERDAW_FILEMANAGER_H

#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_audio_utils/juce_audio_utils.h"
#include "juce_gui_basics/juce_gui_basics.h"


enum TransportState {
    Stopped,
    Starting,
    Playing,
    Stopping
};

class FileManager : public juce::Component, juce::ChangeListener
{

public:
    FileManager();

    void resized() override;
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    void cleanUp();

    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
private:

    void changeState(TransportState newState);

    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    std::unique_ptr<juce::FileChooser> chooser;

    juce::AudioFormatManager formatManager;
    TransportState state;
};

#endif //YETANOTHERDAW_FILEMANAGER_H
