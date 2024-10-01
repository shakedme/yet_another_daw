//
// Created by Shaked Melman on 15/09/2024.
//

#ifndef YETANOTHERDAW_NAVBAR_H
#define YETANOTHERDAW_NAVBAR_H

#include "FileManager.h"
#include "juce_gui_basics/juce_gui_basics.h"

class NavBar : public juce::Component
{
public:
    enum class FileMenuOption {
        New,
        Open,
        Save,
        SaveAs,
    };

    NavBar();
    void resized() override;
    void paint (juce::Graphics& g) override;
    std::function<void (FileMenuOption)> onFileMenuClicked;

private:
    juce::TextButton fileButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavBar)
};

#endif //YETANOTHERDAW_NAVBAR_H
