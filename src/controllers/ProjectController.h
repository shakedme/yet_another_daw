//
// Created by Shaked Melman on 01/10/2024.
//

#ifndef YETANOTHERDAW_PROJECTCONTROLLER_H
#define YETANOTHERDAW_PROJECTCONTROLLER_H

#include "../components/NavBar.h"
#include "../managers/ProjectManager.h"
#include "../models/Project.h"
#include "juce_audio_utils/juce_audio_utils.h"

class ProjectController : public juce::ChangeBroadcaster
{
public:
    ProjectController();
    ~ProjectController() override = default;

    void handleUserInput (NavBar::FileMenuOption option);

    void createNewProject();
    void openProject();
    void saveProject();

    Project* getCurrentProject() const { return currentProject.get(); }

private:
    ProjectManager projectManager;
    std::unique_ptr<Project> currentProject;

    void updateListeners();
};

#endif //YETANOTHERDAW_PROJECTCONTROLLER_H
