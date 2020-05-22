
#include "DreambeatAudioProcessorEditor.h"
#include "../model/DreambeatAudioProcessor.h"

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ),
processor( p ),
_tc( TabbedButtonBar::TabsAtTop )
{
    addAndMakeVisible( _tc );
    _tc.addTab( "test1", juce::Colours::black, nullptr, false );
    _tc.addTab( "test2", juce::Colours::grey, nullptr, false );
    setSize( 400, 300 );
}

DreambeatAudioProcessorEditor::~DreambeatAudioProcessorEditor()
{
}

void DreambeatAudioProcessorEditor::paint( Graphics& g )
{
    // background
    g.fillAll( Colours::transparentBlack );
}

void DreambeatAudioProcessorEditor::resized()
{
    _tc.setSize( getWidth(), getHeight() );
}
