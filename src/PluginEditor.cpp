/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

int NUM_ROWS = 2;

//==============================================================================
DreambeatAudioProcessorEditor::DreambeatAudioProcessorEditor (DreambeatAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), _tc(TabbedButtonBar::TabsAtTop)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // initialize rows
//    for (int i = 0; i < NUM_ROWS; i++)
//    {
//        // add components
//        auto* row = _rows.add(new RowComponent(i));
//        addAndMakeVisible(row);
//
//        // prepare oscillators
//        _modAngles.add(new double(0.0));
//    }
    
    addAndMakeVisible(_tc);
    _tc.addTab("test1", juce::Colours::black, nullptr, false);
    _tc.addTab("test2", juce::Colours::grey, nullptr, false);
    setSize (400, 300);
}

DreambeatAudioProcessorEditor::~DreambeatAudioProcessorEditor()
{
}

//==============================================================================
void DreambeatAudioProcessorEditor::paint (Graphics& g)
{
    // background
    g.fillAll(Colours::transparentBlack);

    // draw an outline around the component
    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 5);
}

void DreambeatAudioProcessorEditor::resized()
{
    _tc.setSize(getWidth(), getHeight());

//    auto rowHeight = getHeight() / NUM_ROWS;
//    auto rowWidth = getWidth();
//    for (int i = 0; i < NUM_ROWS; i++)
//    {
//        _rows[i]->setBounds(0, rowHeight * i, rowWidth, rowHeight);
//    }
}
