#pragma once

#include <string>

#include "../JuceLibraryCode/JuceHeader.h"

//#include "KnobLookAndFeel.h"

class FreqKnob : public Component
{
public:
    FreqKnob()
    {
        // slider
        addAndMakeVisible(_knobSlider);
        _knobSlider.setSliderStyle(Slider::RotaryVerticalDrag);
        _knobSlider.setRange(1.0, 5000.0);
        _knobSlider.setTextValueSuffix(" Hz");
        _knobSlider.setTextBoxStyle(Slider::TextBoxBelow, true, _knobSlider.getTextBoxWidth(), _knobSlider.getTextBoxHeight());
        _knobSlider.setSkewFactorFromMidPoint(500);
        _knobSlider.setNumDecimalPlacesToDisplay(2);
        //_knobSlider.addListener(this);
        //_knobSlider.setLookAndFeel(&_knobLookAndFeel);
        
        // label
        addAndMakeVisible(_knobLabel);
        _knobLabel.setText("Freq", dontSendNotification);
        _knobLabel.setJustificationType(Justification(Justification::Flags::centred));
        _knobLabel.attachToComponent(&_knobSlider, false);
    }

    ~FreqKnob()
    {
    }

    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        size_t knobWidth = getWidth();
        size_t knobHeight = getHeight() / 2;
        _knobSlider.setBounds(0, 0, knobWidth, knobHeight);
    }

    double getFrequency()
    {
        return _knobSlider.getValue();
    }

private:
    Slider _knobSlider;
    Label _knobLabel;
    //KnobLookAndFeel _knobLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreqKnob)
};
