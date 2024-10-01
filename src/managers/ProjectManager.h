//
// Created by Shaked Melman on 15/09/2024.
//

#ifndef YETANOTHERDAW_PROJECTMANAGER_H
#define YETANOTHERDAW_PROJECTMANAGER_H

#include "../models/Project.h"

class ProjectManager
{
public:
    ProjectManager();

    std::unique_ptr<Project> createNewProject (const juce::String& name);
    static bool saveProject (const Project& project);
    static std::unique_ptr<Project> loadProject (const juce::String& path);

private:
    juce::String generateProjectPath (const juce::String& name);
    static juce::File ensureProjectDirectory();

    juce::File projectsDirectory;
};

#endif //YETANOTHERDAW_PROJECTMANAGER_H
