
#include "TrackSequence.h"

TrackSequence::TrackSequence( juce::AudioFormatReader* reader, int slices, int index )
{
    if ( reader != nullptr )
    {
        int slice = (int)reader->lengthInSamples / slices;
        _sampleBuffer.setSize( (int)reader->numChannels, slice );
        reader->read( &_sampleBuffer, 0, slice, slice * index, true, true );
    }
}

int TrackSequence::applyToBuffer( juce::AudioBuffer<float>& buffer, int position, int numInputChannels, int numOutputChannels )
{
    auto numSamples = juce::jmin( buffer.getNumSamples(), _sampleBuffer.getNumSamples() - position );
    for ( auto channel = 0; channel < numOutputChannels; ++channel )
    {
        buffer.copyFrom( channel, 0, _sampleBuffer, channel % numInputChannels, position, numSamples );
    }
    return numSamples;
}
