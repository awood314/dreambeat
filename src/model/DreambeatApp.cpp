
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

tracktion_engine::StepClip::Ptr DreambeatApp::getClip()
{
    return _engine->getClip();
}


void DreambeatApp::play()
{
    _engine->play();
}

void DreambeatApp::play( int index )
{
    _engine->play( index );
}
