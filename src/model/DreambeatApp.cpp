
#include "DreambeatApp.h"
#include "../util/Threading.h"

DreambeatApp::DreambeatApp()
{
}

void DreambeatApp::createEngine( double sampleRate, int blockSize )
{
    if ( !_engine )
    {
        callFunctionOnMessageThread( [&] { _engine = std::make_unique<DreambeatEngine>(); } );
    }
    jassert( _engine );
    callFunctionOnMessageThread(
    [&] { _engine->getAudioInterface().prepareToPlay( sampleRate, blockSize ); } );
}

void DreambeatApp::synchronize( juce::AudioProcessor& proc )
{
    // Update position info first
    _engine->getPlayheadSynchroniser().synchronise( proc );
}

void DreambeatApp::processBlock( juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages )
{
    _engine->getAudioInterface().processBlock( buffer, midiMessages );
}

void DreambeatApp::loadSample()
{
    auto amen = juce::File::createTempFile( ".wav" );
    amen.replaceWithData( BinaryData::amen_wav, BinaryData::amen_wavSize );
    auto createdTracks = _engine->loadSample( amen );
    for ( auto* track : createdTracks )
    {
        _tracks.add( new TrackSequence( track ) );
    }
}

int DreambeatApp::getCurrentSequence()
{
    return _engine->getCurrentSequence();
}

bool DreambeatApp::isPlaying()
{
    return _engine->isPlaying();
}

void DreambeatApp::play()
{
    _engine->play();
}

void DreambeatApp::updateTempo( double tempo )
{
    _engine->updateTempo( tempo );
}

TrackSequence* DreambeatApp::getTrack( int i )
{
    return _tracks[i];
}
