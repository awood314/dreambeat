#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "FreqKnob.h"
#include "AmountKnob.h"

class RowComponent : public Component
{
public:
    RowComponent(unsigned index)
        : _index(index), 
          _frequencyKnob(),
          _amountKnob()
    {
        addAndMakeVisible(_frequencyKnob);
        addAndMakeVisible(_amountKnob);
    }

    ~RowComponent()
    {
    }

    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        size_t knobSize = getWidth() / 2;
        _frequencyKnob.setBounds(0, 0, knobSize, knobSize);
        _amountKnob.setBounds(knobSize, 0, knobSize, knobSize);
    }

    double getFrequency()
    {
        return _frequencyKnob.getFrequency();
    }

    double getAmount()
    {
        return _amountKnob.getAmount();
    }

private:
    unsigned _index;
    FreqKnob _frequencyKnob;
    AmountKnob _amountKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RowComponent)
};
