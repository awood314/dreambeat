
#include "DreambeatAudioProcessorEditor.h"
#include <ui/Colors.h>

int NUM_NOTES = 8;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ), _app( p.getApp() ), _sequencerTabs( juce::TabbedButtonBar::TabsAtTop ),
  _nav( p.getApp().getPlayback() ), _playControls( p.getApp().getPlayback() )
{
    // tabs
    addAndMakeVisible( _sequencerTabs );

    /////////////////////////////////////
    // slicing a sample
    auto* sg = new SequenceGrid( _app.getArrangement() );
    _grids.add( sg );
    _sequencerTabs.addTab( juce::String( 0 ), colors::grey, sg, 0 );
    for ( auto* track : _app.loadSample() )
    {
        _grids[0]->addSequence();
    }
    /////////////////////////////////////

    // nav
    addAndMakeVisible( _nav );

    // play controls
    addAndMakeVisible( _playControls );

    // tempo
    addAndMakeVisible( _tempoSlider );
    _tempoSlider.setRange( 90, 180, 1 );
    //    _tempoSlider.onValueChange = [&p, this]() { p.getApp().updateTempo( _tempoSlider.getValue() ); };

    // playhead
    addAndMakeVisible( _playhead );
    _playhead.setColour( juce::Label::backgroundColourId, colors::transparentWhite );
    _playhead.setInterceptsMouseClicks( false, false );
    auto playheadUpdate = [this]( int s ) {
        auto top = _sequencerTabs.getY() + _sequencerTabs.getTabBarDepth();
        auto div = ( _sequencerTabs.getBottom() - top ) / NUM_NOTES;
        _playhead.setBounds( 0, top + ( s % NUM_NOTES ) * div, getWidth(), div );
    };
    p.getApp().getPlayback().newSequence.connect( playheadUpdate );

    setSize( 360, 640 );
    playheadUpdate( _app.getPlayback().getSequence() );
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
