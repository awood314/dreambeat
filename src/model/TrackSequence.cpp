
#include "TrackSequence.h"

TrackSequence::TrackSequence( juce::AudioFormatReader* reader, int slices, int index )
{
    if ( reader != nullptr )
    {
        // read slice into temporary buffer for resampling
        _originalBuffer.setSize( (int)reader->numChannels, (int)reader->lengthInSamples );
        auto slice = reader->lengthInSamples / slices;
        reader->read( &_originalBuffer, 0, (int)slice, slice * index, true, true );
        _originalSampleRate = reader->sampleRate;
    }
}

void TrackSequence::render( double sampleRate )
{
    // resample the buffer
    double ratio = _originalSampleRate / sampleRate;
    _sampleBuffer.setSize( _originalBuffer.getNumChannels(), _originalBuffer.getNumSamples() / ratio );
    for ( int channel = 0; channel < _sampleBuffer.getNumChannels(); channel++ )
    {
        LagrangeInterpolator resampler;
        resampler.reset();
        resampler.process( ratio, _originalBuffer.getReadPointer( channel ),
                           _sampleBuffer.getWritePointer( channel ), _sampleBuffer.getNumSamples() );
    }
}

int TrackSequence::applyToBuffer( juce::AudioBuffer<float>& buffer, int position, int numInputChannels, int numOutputChannels )
{
    auto numSamples = juce::jmin( buffer.getNumSamples(), _sampleBuffer.getNumSamples() - position );
    if ( numSamples > 0 )
    {
        for ( auto channel = 0; channel < numOutputChannels; ++channel )
        {
            buffer.copyFrom( channel, 0, _sampleBuffer, channel % numInputChannels, position, numSamples );
        }
        return numSamples;
    }
    return 0;
}
