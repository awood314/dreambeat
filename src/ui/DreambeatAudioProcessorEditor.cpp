
#include "DreambeatAudioProcessorEditor.h"
#include <ui/Colors.h>

int NUM_TRACKS = 16;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ), _app( p.getApp() ), _sequencerTabs( juce::TabbedButtonBar::TabsAtTop ),
  _nav( p.getApp().getArrangement() ), _playControls( p.getApp().getArrangement() )
{
    // tabs
    addAndMakeVisible( _sequencerTabs );

    // playhead
    addAndMakeVisible( _playhead );
    _playhead.setColour( juce::Label::backgroundColourId, colors::transparentWhite );
    _playhead.setInterceptsMouseClicks( false, false );
    p.getApp().getArrangement().newSequence.connect( [this]( int s ) {
        auto* grid = _grids[_sequencerTabs.getCurrentTabIndex()];
        grid->setScene( s / 8 );
        auto div = grid->getHeight() / 8.0;
        _playhead.setBounds( 0, grid->getY() + _sequencerTabs.getY() + ( s % 8 ) * div, getWidth(), div );
    } );

    // nav
    addAndMakeVisible( _nav );

    // play controls
    addAndMakeVisible( _playControls );

    // tempo
    addAndMakeVisible( _tempoSlider );
    _tempoSlider.setRange( 90, 180, 1 );
    _tempoSlider.onValueChange = [&p, this]() { p.getApp().updateTempo( _tempoSlider.getValue() ); };

    // slicing a sample
    _app.loadSample();
    for ( int i = 0; i < NUM_TRACKS; i++ )
    {
        // every 8 tracks gets a tab
        int grid = i / 8;
        if ( grid >= _grids.size() )
        {
            auto* sg = new SequenceGrid();
            _grids.add( sg );
            _sequencerTabs.addTab( juce::String( grid ), colors::grey, sg, grid );
        }
        _grids[grid]->addSequence( _app.getTrack( i ) );
    }

    setSize( 360, 640 );
}

void DreambeatAudioProcessorEditor::paint( juce::Graphics& g )
{
    g.setColour( colors::grey );
    g.fillRect( getLocalBounds() );
}

void DreambeatAudioProcessorEditor::resized()
{
    _tempoSlider.setSize( getWidth(), 40 );
    _sequencerTabs.setBounds( 0, _tempoSlider.getHeight(), getWidth(), getWidth() );
    _nav.setBounds( 0, _sequencerTabs.getBottom(), getWidth(), 150 );
    _playControls.setBounds( 0, _nav.getBottom(), getWidth(), getHeight() - _nav.getBottom() );
}
