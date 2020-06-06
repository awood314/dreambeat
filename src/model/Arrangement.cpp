
#include "Arrangement.h"
#include <iostream>

Arrangement::Arrangement()
{
    startTimer( 50 );
}

void Arrangement::timerCallback()
{
    if ( _transport != nullptr )
    {
        double sequence = _transport->getCurrentPosition() * 16.0 / _transport->getLoopRange().getEnd();
        if ( sequence != _sequence )
        {
            _sequence = sequence;
            newSequence( _sequence );
        }
    }
}

void Arrangement::setTransport( tracktion_engine::TransportControl* transport )
{
    _transport = transport;
}

void Arrangement::play()
{
    if ( _transport != nullptr )
    {
        if ( _transport->isPlaying() )
        {
            _transport->stop( false, false );
            playPause( false );
        }
        else
        {
            _transport->setCurrentPosition( 0 );
            _transport->play( false );
            playPause( true );
        }
    }
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
        updateSequence( _sequence + _sequencesPerType[type] );
    }
}

void Arrangement::decrementSequence( Arrangement::SequenceType type )
{
    if ( type != Arrangement::SequenceType::Section )
    {
        if ( _sequence >= _sequencesPerType[type] )
        {
            updateSequence( _sequence - _sequencesPerType[type] );
        }
    }
}

bool Arrangement::canDecrementSequence( Arrangement::SequenceType type )
{
    if ( type != Arrangement::SequenceType::Section )
    {
        return _sequence >= _sequencesPerType[type];
    }
    return false;
}

void Arrangement::updateSequence( int sequence )
{
    _transport->setCurrentPosition( sequence * _transport->getLoopRange().getEnd() / 16.0 );
}
