
#include "Arrangement.h"

std::unordered_set<int>& Arrangement::getNotes( int sequence )
{
    return _notes[sequence];
}

bool Arrangement::hasFinerResolution( int track, int sequence, int resolution )
{
    auto resolutionTree = _resolutionTrees.find( track );
    if ( resolutionTree == _resolutionTrees.end() )
    {
        return false;
    }
    else
    {
        return resolutionTree->second.hasFinerResolution( sequence, resolution );
    }
}

void Arrangement::setNote( int track, int sequence, bool value )
{
    auto resolutionTree = _resolutionTrees.find( track );
    if ( value )
    {
        _notes[sequence].insert( track );
        if ( resolutionTree == _resolutionTrees.end() )
        {
            resolutionTree = _resolutionTrees.emplace( track, ResolutionTree( 128 ) ).first;
        }
        resolutionTree->second.addNote( sequence );
    }
    else
    {
        _notes[sequence].erase( track );
        if ( resolutionTree != _resolutionTrees.end() )
        {
            resolutionTree->second.removeNote( sequence );
        }
    }
}
