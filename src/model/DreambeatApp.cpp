
#include "DreambeatApp.h"
#include "../util/Threading.h"

DreambeatApp::DreambeatApp()
{
    _amen = juce::File::createTempFile( ".wav" );
    _amen.replaceWithData( BinaryData::amen_wav, BinaryData::amen_wavSize );
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
    _engine->loadSample( _amen );
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

juce::File& DreambeatApp::getSample()
{
    return _amen;
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

void DreambeatApp::enableClip( int track, int clip, bool value )
{
    _engine->enableClip( track, clip, value );
}
