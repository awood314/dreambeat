
#include "TrackSequence.h"

TrackSequence::TrackSequence( juce::AudioFormatReader* reader, double sampleRate, int slices, int index )
: _timestretcher( sampleRate, reader->numChannels, RubberBand::RubberBandStretcher::OptionProcessRealTime )
{
    if ( reader != nullptr )
    {
        _readerSource.reset( new AudioFormatReaderSource( reader, true ) );
        setSource( _readerSource.get(), 0, nullptr, reader->sampleRate );
        _basePosition = ( getTotalLength() / slices ) * index;
        prepareToPlay( 512, sampleRate );
        start();

        _timestretcher.setTimeRatio( .5 );
    }
}

TrackSequence::~TrackSequence()
{
    setSource( nullptr );
    releaseResources();
}

void TrackSequence::reset()
{
    setNextReadPosition( _basePosition );
}

void TrackSequence::getNextAudioBlock( const juce::AudioSourceChannelInfo& info )
{
    // process buffer
    while ( _timestretcher.available() < info.numSamples )
    {
        // process more audio
        juce::AudioTransportSource::getNextAudioBlock( info );
        _timestretcher.process( info.buffer->getArrayOfReadPointers(), info.numSamples, false );
    }
    _timestretcher.retrieve( info.buffer->getArrayOfWritePointers(), info.numSamples );
}
