
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
    addAndMakeVisible( _tempoSlider );
    _tempoSlider.setRange( 90, 180, 1 );
    _tempoSlider.onValueChange = [&p, this]() { p.getApp().updateTempo( _tempoSlider.getValue() ); };
    setSize( 400, 300 );
}

void DreambeatAudioProcessorEditor::resized()
{
    auto div = getWidth() / NUM_TRACKS;
    for ( int i = 0; i < NUM_TRACKS; i++ )
    {
        _sequencer[i]->setBounds( i * div, 0, div, getHeight() - div * 2 );
    }
    _playButton.setBounds( 0, getHeight() - div * 2, getWidth(), div );
    _tempoSlider.setBounds( 0, getHeight() - div, getWidth(), div );
}
