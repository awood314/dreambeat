
#include "Playback.h"
#include <JuceHeader.h>
#include <sstream>

Playback::Playback()
: _tempo( "tempo", "tempo", NormalisableRange<float>( 10.0, 300.0 ), 120.0 )
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
    setSequence( getSequence() );
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
    setSequence( getSequence() );
}

int Playback::getSequence()
{
    return (int)_position / samplesPerSequence();
}

void Playback::setSequence( int sequence )
{
    if ( sequence != _sequence )
    {
        // update sequence
        _sequence = sequence;
        _position = sequence * samplesPerSequence();
        juce::MessageManager::callAsync( [this] { newSequence( _sequence ); } );

        // update window if necessary
        if ( _sequence - _window >= 8 * _resolution )
        {
            _window = _sequence - _sequence % ( 8 * _resolution );
            juce::MessageManager::callAsync( [this] { newWindow( _window ); } );
        }
    }
}

int Playback::getResolution()
{
    return _resolution;
}

int Playback::getWindow()
{
    return _window;
}

int Playback::getOffset()
{
    return _position % samplesPerSequence();
}

int Playback::samplesPerSequence()
{
    return _sampleRate * 60 * 2 / _tempo;
}

std::string Playback::getSequenceString( int sequence )
{
    std::stringstream ss;
    for ( int i = _sequencesPerType.size() - 1; i >= 0; i-- )
    {
        auto currType = sequence / _sequencesPerType[i];
        ss << currType;
        if ( i > 0 )
        {
            ss << ":";
        }
        sequence -= currType * _sequencesPerType[i];
    }
    return ss.str();
}
