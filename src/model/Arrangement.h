
#pragma once

#include <model/ResolutionTree.h>

#include <unordered_map>
#include <unordered_set>

class Arrangement
{
public:
    Arrangement() = default;

    std::unordered_set<int>& getNotes( int sequence );
    void setNote( int track, int sequence, bool value );
    bool hasFinerResolution( int track, int sequence, int resolution );

private:
    // for audio playback
    // sequence -> track notes
    std::unordered_map<int, std::unordered_set<int>> _notes;
    
    // for ui
    // track -> sequence notes
    std::unordered_map<int, ResolutionTree> _resolutionTrees;
};
