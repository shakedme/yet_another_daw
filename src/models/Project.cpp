
#include "Project.h"

#include <utility>

Project::Project (juce::String name, juce::String path)
    : projectName (std::move (name)), projectPath (std::move ((path)))
{
}

void Project::addTrack (std::unique_ptr<Track> track)
{
    tracks.add (track.release());
}

void Project::removeTrack (const juce::String& trackId)
{
    for (int i = tracks.size() - 1; i >= 0; --i)
    {
        if (tracks[i]->getUniqueID() == trackId)
        {
            tracks.remove (i);
            break;
        }
    }
}

Track* Project::getTrack (const juce::String& trackId)
{
    for (auto track : tracks)
    {
        if (track->getUniqueID() == trackId)
            return track;
    }
    return nullptr;
}

juce::var Project::toJSON() const
{
    auto* jsonObject = new juce::DynamicObject();

    jsonObject->setProperty ("name", projectName);
    jsonObject->setProperty ("path", projectPath);

    juce::Array<juce::var> tracksArray;
    for (auto track : tracks)
    {
        tracksArray.add (track->toJSON());
    }
    jsonObject->setProperty ("tracks", tracksArray);

    return jsonObject;
}

std::unique_ptr<Project> Project::fromJSON (const juce::var& json)
{
    if (!json.isObject())
        return nullptr;

    auto project = std::make_unique<Project> (json["name"], json["path"]);

    if (auto* tracksArray = json["tracks"].getArray())
    {
        for (auto& trackVar : *tracksArray)
        {
            if (auto track = Track::fromJSON (trackVar))
            {
                project->addTrack (std::move (track));
            }
        }
    }

    return project;
}