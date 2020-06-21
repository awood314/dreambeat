
#include "SequenceItem.h"
#include <ui/Colors.h>

SequenceItem::SequenceItem( juce::Colour color )
: _color( color )
{
}

void SequenceItem::paint( juce::Graphics& g )
{
    if ( getToggleState() )
    {
        g.setColour( colors::black );
    }
    else
    {
        g.setColour( colors::white );
    }
    g.fillRoundedRectangle( getLocalBounds().toFloat(), 1.0 );
}
