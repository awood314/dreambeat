/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 24 Aug 2019 6:07:59pm
    Author:  Alex

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/BinaryData.h"

class KnobLookAndFeel : public LookAndFeel_V4
{
public:
    KnobLookAndFeel()
    {
        _knobImage = ImageFileFormat::loadFrom(BinaryData::knob_png, BinaryData::knob_pngSize);
    }
    
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, const float rotaryStartAngle, const float rotaryEndAngle, Slider &slider)
    {
        AffineTransform rotator;
        //rotator = rotator.rotated(rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle), _knobImage.getWidth() / 2, _knobImage.getHeight() / 2);
        g.drawImageTransformed(_knobImage, rotator, false);
    }

    void setImageSize(int size)
    {
        _knobImage = _knobImage.rescaled(size, size);
    }
private:
    Image _knobImage;
};
