#pragma once

#include <string>

#include "../JuceLibraryCode/JuceHeader.h"

//#include "KnobLookAndFeel.h"

class AmountKnob : public Component
{
public:
    AmountKnob()
    {
        // slider
        addAndMakeVisible(_knobSlider);
        _knobSlider.setSliderStyle(Slider::RotaryVerticalDrag);
        _knobSlider.setRange(0.0, 10.0);
        _knobSlider.setTextBoxStyle(Slider::TextBoxBelow, true, _knobSlider.getTextBoxWidth(), _knobSlider.getTextBoxHeight());
        _knobSlider.setNumDecimalPlacesToDisplay(2);
        //_knobSlider.addListener(this);
        //slider->setLookAndFeel(&_knobLookAndFeel);
        
        // label
        addAndMakeVisible(_knobLabel);
        _knobLabel.setText("Amount", dontSendNotification);
        _knobLabel.setJustificationType(Justification(Justification::Flags::centred));
        _knobLabel.attachToComponent(&_knobSlider, false);
    }

    ~AmountKnob()
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

    double getAmount()
    {
        return _knobSlider.getValue() / 10.0;
    }

private:
    Slider _knobSlider;
    Label _knobLabel;
    //KnobLookAndFeel _knobLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmountKnob)
};
