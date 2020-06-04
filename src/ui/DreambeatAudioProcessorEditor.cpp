
#include "DreambeatAudioProcessorEditor.h"
#include "../ui/Colors.h"

int NUM_TRACKS = 16;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ), _app( p.getApp() ), _sequencerTabs( juce::TabbedButtonBar::TabsAtTop )
{
    addAndMakeVisible( _sequencerTabs );
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
    addAndMakeVisible( _playButton );
    _playButton.onClick = [this]() {
        _app.play();
        _playhead.setVisible( _app.isPlaying() );
    };
    addAndMakeVisible( _tempoSlider );
    _tempoSlider.setRange( 90, 180, 1 );
    _tempoSlider.onValueChange = [&p, this]() { p.getApp().updateTempo( _tempoSlider.getValue() ); };
    addAndMakeVisible( _playhead );
    _playhead.setColour( juce::Label::backgroundColourId, colors::transparentWhite );
    _playhead.setInterceptsMouseClicks( false, false );
    setSize( 400, 300 );
    startTimer( 50 );
}

void DreambeatAudioProcessorEditor::timerCallback()
{
    _playhead.setVisible( _app.isPlaying() );
    if ( _app.isPlaying() )
    {
        auto seq = _app.getCurrentSequence();
        auto* grid = _grids[_sequencerTabs.getCurrentTabIndex()];
        grid->setScene( seq / 8 );
        auto div = grid->getHeight() / 8.0;
        _playhead.setBounds( 0, grid->getY() + ( seq % 8 ) * div, getWidth(), div );
    }
}

void DreambeatAudioProcessorEditor::resized()
{
    auto div = getWidth() / NUM_TRACKS;
    _sequencerTabs.setBounds( 0, 0, getWidth(), getHeight() - div * 2 );
    _playButton.setBounds( 0, getHeight() - div * 2, getWidth(), div );
    _tempoSlider.setBounds( 0, getHeight() - div, getWidth(), div );
}
