#pragma once

//==============================================================================

#include "../controllers/ProjectController.h"
#include "../managers/ProjectManager.h"
#include "../models/Project.h"
#include "FileManager.h"
#include "NavBar.h"
#include "juce_audio_utils/juce_audio_utils.h"
#include "tracks/TracksContainer.h"

class MainComponent : public juce::Component,
                      public juce::ChangeListener
{
public:
    MainComponent();
    ~MainComponent() override;
    void paint (juce::Graphics& g) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    NavBar navBar;
    TracksContainer tracksContainer;
    ProjectController projectController;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
