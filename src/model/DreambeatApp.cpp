
#include "DreambeatApp.h"
#include "../util/Threading.h"

juce::OwnedArray<TrackSequence>& DreambeatApp::loadSample()
{
    _formatManager.registerBasicFormats();
    auto amen = juce::File::createTempFile( ".wav" );
    amen.replaceWithData( BinaryData::amen_wav, BinaryData::amen_wavSize );
    std::unique_ptr<juce::AudioFormatReader> amenReader( _formatManager.createReaderFor( amen ) );
    for ( int i = 0; i < 8; i++ )
    {
        _tracks.add( new TrackSequence( amenReader.get(), 8, i ) );
    }
    return _tracks;
}

void DreambeatApp::processBlock( juce::AudioBuffer<float>& buffer,
                                 juce::MidiBuffer& midiMessages,
                                 int numInputChannels,
                                 int numOutputChannels )
{
    if ( buffer.getNumSamples() > 0 && _playback.isPlaying() )
    {
        auto seq = _playback.getSequence();
        for ( const auto& trackIndex : _arrangement.getNotes( seq ) )
        {
            auto* track = _tracks[trackIndex];
            if ( track != nullptr )
            {
                auto offset = _playback.getOffset();
                int samplesApplied = track->applyToBuffer( buffer, offset, numInputChannels, numOutputChannels );
            }
        }
        _playback.incrementPosition( buffer.getNumSamples() );
    }
}

TrackSequence* DreambeatApp::getTrack( int i )
{
    return _tracks[i];
}

Arrangement& DreambeatApp::getArrangement()
{
    return _arrangement;
}

Playback& DreambeatApp::getPlayback()
{
    return _playback;
}
