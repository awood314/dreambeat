
#include "Playback.h"
#include <iostream>

Playback::Playback()
{
}

void Playback::setSampleRate( double rate )
{
    _sampleRate = rate;
    _samplesPerSequence = ( _sampleRate / ( 137.40 / 60.0 ) ) * 2;
}

void Playback::play()
{
    _position = 0;
    _playing = !_playing;
}

bool Playback::isPlaying()
{
    return _playing;
}

void Playback::incrementPosition( int samples )
{
    _position += samples;
}

int Playback::getSequence()
{
    //    if ( type == Playback::SequenceType::Beat || type == Playback::SequenceType::Bar )
    //    {
    //        return ( _position * _samplesPerSequence ) / _sequencesPerType[type] % ( _sequencesPerType[type + 1] / _sequencesPerType[type] );
    //    }
    //    if ( type == Playback::SequenceType::Phrase )
    //    {
    //        return _position / _sequencesPerType[type];
    //    }
    return _position / _samplesPerSequence;
}

int Playback::getOffset()
{
    return _position % _samplesPerSequence;
}

void Playback::incrementSequence( Playback::SequenceType type )
{
    //    if ( type != Playback::SequenceType::Section )
    //    {
    //
    //        updateSequence( _sequence + _sequencesPerType[type] - _sequence % _sequencesPerType[type] );
    //    }
}

void Playback::decrementSequence( Playback::SequenceType type )
{
    //    if ( type != Playback::SequenceType::Section )
    //    {
    //        if ( _sequence > 0 )
    //        {
    //            int diff = _sequence % _sequencesPerType[type];
    //            if ( diff )
    //            {
    //                updateSequence( _sequence - diff );
    //            }
    //            else
    //            {
    //                updateSequence( _sequence - _sequencesPerType[type] );
    //            }
    //        }
    //    }
}

bool Playback::canDecrementSequence( Playback::SequenceType type )
{
    //    if ( type != Playback::SequenceType::Section )
    //    {
    //        return _sequence > 0;
    //    }
    return false;
}

void Playback::updateSequence( int sequence )
{
    //    _sequence = sequence;
    //    newSequence( _sequence );
}
