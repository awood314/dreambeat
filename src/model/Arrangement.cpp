
#include "Arrangement.h"

Arrangement::Arrangement()
{
    startTimer( 50 );
}

void Arrangement::timerCallback()
{
    if ( _transport != nullptr )
    {
        int sequence = _transport->getCurrentPosition() * 16.0 / _transport->getLoopRange().getEnd();
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
