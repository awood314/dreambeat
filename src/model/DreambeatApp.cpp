
#include "DreambeatApp.h"
#include "../util/Threading.h"

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
                track->getNextAudioBlock( juce::AudioSourceChannelInfo( &buffer, 0, buffer.getNumSamples() ) );
            }
        }
        _playback.incrementPosition( buffer.getNumSamples() );
    }
}

juce::OwnedArray<TrackSequence>& DreambeatApp::loadSample()
{
    _formatManager.registerBasicFormats();
    auto amen = juce::File::createTempFile( ".wav" );
    amen.replaceWithData( BinaryData::amen_wav, BinaryData::amen_wavSize );
    for ( int i = 0; i < 8; i++ )
    {
        _tracks.add( new TrackSequence( _formatManager.createReaderFor( amen ),
                                        _playback.getSampleRate(), 8, i ) );
    }
    return _tracks;
}

void DreambeatApp::setSampleRate( double rate )
{
    _playback.setSampleRate( rate );
    for ( auto* track : _tracks )
    {
        track->prepareToPlay( 512, rate );
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
