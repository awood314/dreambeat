
#include "DreambeatApp.h"
#include "../util/Threading.h"

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

void DreambeatApp::play()
{
    _engine->play();
}
