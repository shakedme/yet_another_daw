
#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible (navBar);
    addAndMakeVisible (tracksContainer);
    navBar.onFileMenuClicked = [this](NavBar::FileMenuOption option) {
        projectController.handleUserInput(option);
    };
    projectController.addChangeListener (this);
}

MainComponent::~MainComponent()
{
    projectController.removeChangeListener (this);
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    navBar.setBounds (bounds.removeFromTop (30));
    tracksContainer.setBounds (bounds);
}

void MainComponent::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source == &projectController)
    {
        if (auto* project = projectController.getCurrentProject())
        {
//            tracksContainer.updateTracks (project->getTracks());
        }
        else
        {
//            tracksContainer.clearTracks();
        }
    }
}