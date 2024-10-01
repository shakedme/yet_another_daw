//
// Created by Shaked Melman on 15/09/2024.
//

#include "NavBar.h"

NavBar::NavBar()
{
    addAndMakeVisible (fileButton);
    fileButton.setButtonText ("File");
    fileButton.setBounds (0, 5, 100, 20);

    fileButton.onClick = [this] {
        juce::PopupMenu fileMenu;
        fileMenu.addItem ("New", [this] { onFileMenuClicked (FileMenuOption::New); });
        fileMenu.addItem ("Open", [this] { onFileMenuClicked (FileMenuOption::Open); });
        fileMenu.addItem ("Save", [this] { onFileMenuClicked (FileMenuOption::Save); });
        fileMenu.addItem ("Save As", [this] { onFileMenuClicked (FileMenuOption::SaveAs); });
        fileMenu.showAt (&fileButton);
    };
}

void NavBar::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (10, 20, 50)); // Dark navy blue color
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds().removeFromBottom (1), 2);
}

void NavBar::resized()
{
}