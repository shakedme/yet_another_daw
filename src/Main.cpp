
#include "gui/MainComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

class Main : public juce::JUCEApplication
{
public:
    //==============================================================================
    Main() {}

    const juce::String getApplicationName() override { return "YetAnotherDaw"; }
    const juce::String getApplicationVersion() override { return "0.0.1"; }
    bool moreThanOneInstanceAllowed() override { return false; }

    //==============================================================================

    void initialise (const juce::String& commandLine) override
    {
        mainWindow.reset (new MainWindow (getApplicationName()));
    }
    void shutdown() override { mainWindow = nullptr; }

    //==============================================================================
    void systemRequestedQuit() override { quit(); }

    void anotherInstanceStarted (const juce::String& commandLine) override {}

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow (const juce::String& name)
            : DocumentWindow (name,
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (Main)
