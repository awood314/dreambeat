
#include "DreambeatAudioProcessorEditor.h"
#include "../model/DreambeatAudioProcessor.h"

int NUM_TRACKS = 16;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ), _sequencerTabs( juce::TabbedButtonBar::TabsAtTop )
{
    addAndMakeVisible( _sequencerTabs );
    for ( int i = 0; i < NUM_TRACKS; i++ )
    {
        // every 8 tracks gets a tab
        int grid = i / 8;
        if ( grid >= _grids.size() )
        {
            auto* sg = new SequenceGrid();
            _grids.add( sg );
            _sequencerTabs.addTab( juce::String( grid ), juce::Colours::grey, sg, grid );
        }
        _grids[grid]->addSequence( p.getApp(), i );
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
    _sequencerTabs.setBounds( 0, 0, getWidth(), getHeight() - div * 2 );
    for ( auto* grid : _grids )
    {
        grid->setBounds( 0, 0, getWidth(), getHeight() );
    }
    _playButton.setBounds( 0, getHeight() - div * 2, getWidth(), div );
    _tempoSlider.setBounds( 0, getHeight() - div, getWidth(), div );
}
