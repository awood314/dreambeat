
#include "Playback.h"
#include <JuceHeader.h>
#include <iostream>

Playback::Playback() : _tempo( "tempo", "tempo", NormalisableRange<float>( 10.0, 300.0 ), 120.0 )
{
}

void Playback::setSampleRate( double rate )
{
    auto currSequence = getSequence();
    auto currOffset = getOffset();
    _sampleRate = rate;
    _position = samplesPerSequence() * currSequence + currOffset;
    // shouldn't need to fire signal
}

double Playback::getSampleRate()
{
    return _sampleRate;
}

void Playback::setTempo( float tempo )
{
    auto currSequence = getSequence();
    auto currOffset = getOffset();
    _tempo = tempo;
    _position = samplesPerSequence() * currSequence + currOffset;
    // shouldn't need to fire signal
}

float Playback::getTempo()
{
    return _tempo;
}

void Playback::play()
{
    _position = 0;
    updateSequence( getSequence() );
    _playing = !_playing;
}

bool Playback::isPlaying()
{
    return _playing;
}

void Playback::incrementPosition( int samples )
{
    _position += samples;
    // if following playhead
    updateSequence( getSequence() );
}

int Playback::getSequence()
{
    return (int)_position / samplesPerSequence();
}

int Playback::getOffset()
{
    return _position % samplesPerSequence();
}

int Playback::getSequence( Playback::SequenceType type )
{
    if ( type == Playback::SequenceType::Beat || type == Playback::SequenceType::Bar )
    {
        return getSequence() / _sequencesPerType[type] %
               ( _sequencesPerType[type + 1] / _sequencesPerType[type] );
    }
    if ( type == Playback::SequenceType::Phrase )
    {
        return getSequence() / _sequencesPerType[type];
    }
    return 0;
}


void Playback::incrementSequence( Playback::SequenceType type )
{
    if ( type != Playback::SequenceType::Section )
    {
        updateSequence( _sequence + _sequencesPerType[type] - _sequence % _sequencesPerType[type] );
    }
}

void Playback::decrementSequence( Playback::SequenceType type )
{
    if ( type != Playback::SequenceType::Section )
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

bool Playback::canDecrementSequence( Playback::SequenceType type )
{
    if ( type != Playback::SequenceType::Section )
    {
        return _sequence > 0;
    }
    return false;
}

void Playback::updateSequence( unsigned sequence )
{
    if ( sequence != _sequence )
    {
        _sequence = sequence;
        _position = sequence * samplesPerSequence();
        juce::MessageManager::callAsync( [this] { newSequence( _sequence ); } );
    }
}

int Playback::samplesPerSequence()
{
    return _sampleRate * 60 * 2 / _tempo;
}
