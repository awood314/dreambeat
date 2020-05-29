
#include "DreambeatAudioProcessorEditor.h"
#include "../model/DreambeatAudioProcessor.h"

int NUM_TRACKS = 8;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p )
{
    for ( int i = 0; i < NUM_TRACKS; i++ )
    {
        auto* sc = new SequenceComponent( p.getApp(), i );
        _sequencer.add( sc );
        addAndMakeVisible( sc );
    }
    addAndMakeVisible( _playButton );
    _playButton.onClick = [&p]() { p.getApp().play(); };
    setSize( 400, 300 );
}

void DreambeatAudioProcessorEditor::resized()
{
    auto div = getWidth() / NUM_TRACKS;
    for ( int i = 0; i < NUM_TRACKS; i++ )
    {
        _sequencer[i]->setBounds( i * div, 0, div, getHeight() - div );
    }
    _playButton.setBounds( 0, getHeight() - div, getWidth(), div );
}
