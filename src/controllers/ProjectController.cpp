//
// Created by Shaked Melman on 01/10/2024.
//

#include "ProjectController.h"
#include "juce_gui_basics/juce_gui_basics.h"

ProjectController::ProjectController() = default;

void ProjectController::createNewProject()
{
    auto alertWindow = std::make_unique<juce::AlertWindow> ("New Project",
        "Enter project name:",
        juce::MessageBoxIconType::QuestionIcon);

    alertWindow->addTextEditor ("projectName", "New Project");
    alertWindow->addButton ("OK", 1, juce::KeyPress (juce::KeyPress::returnKey, 0, 0));
    alertWindow->addButton ("Cancel", 0, juce::KeyPress (juce::KeyPress::escapeKey, 0, 0));

    alertWindow->enterModalState (true,
        juce::ModalCallbackFunction::create (
            [this, alertWindow = std::move (alertWindow)] (int result) mutable {
                if (result == 1)
                {
                    juce::String projectName = alertWindow->getTextEditorContents ("projectName");
                    if (projectName.isNotEmpty())
                    {
                        currentProject = projectManager.createNewProject (projectName);
                        if (currentProject)
                        {
                            updateListeners();
                        }
                        else
                        {
                            juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                "Error",
                                "Failed to create new project.");
                        }
                    }
                }
            }));
}

void ProjectController::openProject()
{
    juce::FileChooser chooser ("Select a project file to open...",
        juce::File::getSpecialLocation (juce::File::userDocumentsDirectory),
        "*.json");

    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        currentProject = ProjectManager::loadProject (file.getFullPathName());
        if (currentProject)
        {
            updateListeners();
        }
        else
        {
            juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                "Error",
                "Failed to open project.");
        }
    }
}

void ProjectController::saveProject()
{
    if (currentProject)
    {
        if (ProjectManager::saveProject (*currentProject))
        {
            //            DMSG("Project saved");
        }
        else
        {
            juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                "Error",
                "Failed to save project.");
        }
    }
}

void ProjectController::updateListeners()
{
    sendChangeMessage();
}

void ProjectController::handleUserInput (NavBar::FileMenuOption option)
{
    switch (option)
    {
        case NavBar::FileMenuOption::New:
            createNewProject();
            break;
        case NavBar::FileMenuOption::Open:
            openProject();
            break;
        case NavBar::FileMenuOption::Save:
            saveProject();
            break;
        case NavBar::FileMenuOption::SaveAs:
            break;
    }
}
