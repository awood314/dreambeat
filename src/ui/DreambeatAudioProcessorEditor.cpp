
#include "DreambeatAudioProcessorEditor.h"
#include "../ui/Colors.h"

int NUM_TRACKS = 16;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ), _app( p.getApp() ),
  _sequencerTabs( juce::TabbedButtonBar::TabsAtTop ), _nav( p.getApp().getArrangement() )
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
            _sequencerTabs.addTab( juce::String( grid ), juce::Colours::grey, sg, grid );
        }
        _grids[grid]->addSequence( _app.getTrack( i ) );
    }

    setSize( 360, 640 );
}

void DreambeatAudioProcessorEditor::resized()
{
    auto div = getHeight() / 4;
    _tempoSlider.setSize( getWidth(), div );
    _sequencerTabs.setBounds( 0, div, getWidth(), div * 2 );
    _nav.setBounds( 0, div * 3, getWidth(), div );
}
