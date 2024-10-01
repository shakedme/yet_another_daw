//
// Created by Shaked Melman on 15/09/2024.
//

#ifndef YETANOTHERDAW_PROJECT_H
#define YETANOTHERDAW_PROJECT_H

#include "Track.h"
#include "juce_core/juce_core.h"

class Project
{
public:
    Project (juce::String name, juce::String path);
    ~Project() = default;

    void addTrack (std::unique_ptr<Track> track);
    void removeTrack (const juce::String& trackId);
    Track* getTrack (const juce::String& trackId);
    [[nodiscard]] const juce::OwnedArray<Track>& getTracks() const { return tracks; }

    [[nodiscard]] const juce::String& getName() const { return projectName; }
    [[nodiscard]] const juce::String& getPath() const { return projectPath; }

    [[nodiscard]] juce::var toJSON() const;
    static std::unique_ptr<Project> fromJSON (const juce::var& json);

private:
    juce::String projectName;
    juce::String projectPath;
    juce::OwnedArray<Track> tracks;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project)
};
#endif //YETANOTHERDAW_PROJECT_H
