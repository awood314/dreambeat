
#include "DreambeatAudioProcessorEditor.h"
#include <ui/Colors.h>

int NUM_NOTES = 8;

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p )
, _app( p.getApp() )
, _grid( _app.getArrangement(), _app.getPlayback() )
, _timeline( _app.getPlayback() )
, _playControls( _app.getPlayback() )
{
    // tempo
    addAndMakeVisible( _tempoSlider );
    _tempoSlider.setRange( 90, 180, 1 );
    _tempoSlider.onValueChange = [&p, this]() {
        p.getApp().getPlayback().setTempo( _tempoSlider.getValue() );
    };

    // grid
    for ( auto* track : _app.loadSample() )
    {
        _grid.addSequence();
    }
    addAndMakeVisible( _grid );

    // timeline
    addAndMakeVisible( _timeline );

    // playhead
    addAndMakeVisible( _playhead );
    _playhead.setColour( juce::Label::backgroundColourId, colors::transparentWhite );
    _playhead.setInterceptsMouseClicks( false, false );
    auto playheadUpdate = [this]( int s ) {
        auto div = _grid.getHeight() / NUM_NOTES;
        _playhead.setBounds( _grid.getX(), _grid.getY() + ( s % NUM_NOTES ) * div, _grid.getWidth(), div );
    };
    p.getApp().getPlayback().newSequence.connect( playheadUpdate );

    // play controls
    addAndMakeVisible( _playControls );

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
    auto columnWidth = getWidth() / 10;
    auto gridWidth = columnWidth * 8;

    // top to bottom
    _tempoSlider.setSize( getWidth(), 40 );

    // bottom to top
    _playControls.setBounds( columnWidth, getBottom() - columnWidth * 2, gridWidth, columnWidth * 2 );
    _grid.setBounds( columnWidth, _playControls.getY() - gridWidth, gridWidth, gridWidth );
    _timeline.setBounds( _grid.getRight(), _grid.getY(), columnWidth, gridWidth );
}
