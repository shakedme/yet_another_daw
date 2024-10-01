//
// Created by Shaked Melman on 15/09/2024.
//

#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
    projectsDirectory = ensureProjectDirectory();
}

std::unique_ptr<Project> ProjectManager::createNewProject (const juce::String& name)
{
    juce::String path = generateProjectPath (name);
    auto project = std::make_unique<Project> (name, path);

    if (saveProject (*project))
    {
        return project;
    }

    return nullptr;
}

bool ProjectManager::saveProject (const Project& project)
{
    juce::var jsonVar = project.toJSON();
    juce::String jsonString = juce::JSON::toString (jsonVar);

    juce::File projectFile (project.getPath());

    if (projectFile.create())
    {
        return projectFile.replaceWithText (jsonString);
    }

    return false;
}

std::unique_ptr<Project> ProjectManager::loadProject (const juce::String& path)
{
    juce::File projectFile (path);

    if (projectFile.existsAsFile())
    {
        juce::String jsonString = projectFile.loadFileAsString();
        juce::var jsonVar = juce::JSON::parse (jsonString);

        return Project::fromJSON (jsonVar);
    }

    return nullptr;
}

juce::String ProjectManager::generateProjectPath (const juce::String& name)
{
    juce::String sanitizedName = name.replaceCharacters (" ", "_").toLowerCase();
    juce::String timestamp = juce::Time::getCurrentTime().formatted ("%Y%m%d_%H%M%S");
    juce::String fileName = sanitizedName + "_" + timestamp + ".json";

    return projectsDirectory.getChildFile (fileName).getFullPathName();
}

juce::File ProjectManager::ensureProjectDirectory()
{
    juce::File directory = juce::File::getSpecialLocation (juce::File::userDocumentsDirectory)
                               .getChildFile ("YetAnotherDAW/Projects");

    directory.createDirectory();
    return directory;
}