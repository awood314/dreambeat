
#include "TrackSequence.h"

TrackSequence::TrackSequence( juce::AudioFormatReader* reader, double sampleRate, float tempo, int slices, int index )
: _slices( slices ), _index( index ), _tempo( tempo ),
  _timestretcher( sampleRate, reader->numChannels, RubberBand::RubberBandStretcher::OptionProcessRealTime )
{
    if ( reader != nullptr )
    {
        _readerSource.reset( new AudioFormatReaderSource( reader, true ) );
        _readerSource->setLooping( true );
        setSource( _readerSource.get(), 0, nullptr, reader->sampleRate );
        prepareToPlay( 512, sampleRate );
        setNextReadPosition( _basePosition );
        start();
    }
}

TrackSequence::~TrackSequence()
{
    setSource( nullptr );
    releaseResources();
}

void TrackSequence::prepareToPlay( int blockSize, double sampleRate )
{
    juce::AudioTransportSource::prepareToPlay( blockSize, sampleRate );
    _basePosition = ( getTotalLength() / (float) _slices ) * _index;
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
    _offset += info.numSamples;
}

void TrackSequence::sync( int sequence, int offset, float tempo )
{
    if ( offset != _offset || sequence != _sequence )
    {
        _sequence = sequence;
        _offset = offset;
        setNextReadPosition( _basePosition + offset );
        _timestretcher.reset();
    }
    auto newRatio = _tempo / tempo;
    if ( newRatio != _timestretcher.getTimeRatio() )
    {
        _timestretcher.setTimeRatio( _tempo / tempo );
    }
}
