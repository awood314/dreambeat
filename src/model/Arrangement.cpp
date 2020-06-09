
#include "Arrangement.h"

std::set<int>& Arrangement::getNotes( int sequence )
{
    return _notes[sequence];
}

void Arrangement::setNote( int track, int sequence, bool value )
{
    if ( value )
    {
        _notes[sequence].insert( track );
    }
    else
    {
        _notes[sequence].erase( track );
    }
}
