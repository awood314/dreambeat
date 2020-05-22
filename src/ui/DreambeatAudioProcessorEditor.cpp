
#include "DreambeatAudioProcessorEditor.h"
#include "../model/DreambeatAudioProcessor.h"

DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p )
: AudioProcessorEditor( &p ), _tc( TabbedButtonBar::TabsAtTop )
{
    addAndMakeVisible( _tc );
    _tc.addTab( "test1", juce::Colours::black, &_button, false );
    _tc.addTab( "test2", juce::Colours::grey, nullptr, false );
    _button.onClick = [this, &p]() { p.getApp().play(); };
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
