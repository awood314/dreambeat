
#include "Arrangement.h"
#include <iostream>

Arrangement::Arrangement()
{
}


void Arrangement::play()
{
}

int Arrangement::getSequence( Arrangement::SequenceType type )
{
    if ( type == Arrangement::SequenceType::Beat || type == Arrangement::SequenceType::Bar )
    {
        return _sequence / _sequencesPerType[type] % ( _sequencesPerType[type + 1] / _sequencesPerType[type] );
    }
    if ( type == Arrangement::SequenceType::Phrase )
    {
        return _sequence / _sequencesPerType[type];
    }
    return 0;
}

void Arrangement::incrementSequence( Arrangement::SequenceType type )
{
    if ( type != Arrangement::SequenceType::Section )
    {

        updateSequence( _sequence + _sequencesPerType[type] - _sequence % _sequencesPerType[type] );
    }
}

void Arrangement::decrementSequence( Arrangement::SequenceType type )
{
    if ( type != Arrangement::SequenceType::Section )
    {
        if ( _sequence > 0 )
        {
            int diff = _sequence % _sequencesPerType[type];
            if ( diff )
            {
                updateSequence( _sequence - diff );
            }
            else
            {
                updateSequence( _sequence - _sequencesPerType[type] );
            }
        }
    }
}

bool Arrangement::canDecrementSequence( Arrangement::SequenceType type )
{
    if ( type != Arrangement::SequenceType::Section )
    {
        return _sequence > 0;
    }
    return false;
}

void Arrangement::updateSequence( int sequence )
{
    _sequence = sequence;
    newSequence( _sequence );
}
