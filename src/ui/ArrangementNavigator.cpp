
#include "ArrangementNavigator.h"

ArrangementNavigator::ArrangementNavigator( Arrangement& arrangement ) : _arrangement( arrangement )
{
    addAndMakeVisible( _beatUpButton );
    //    _beatUpButton.onClick = [this] () { arrangement.}
    addAndMakeVisible( _beatLabel );
    arrangement.newSequence.connect( [this]( int sequence ) {
        _beatLabel.setText( juce::String( sequence + 1 ), juce::sendNotification );
    } );
    addAndMakeVisible( _beatDownButton );

    addAndMakeVisible( _playButton );
    _playButton.onClick = [this]() { _arrangement.play(); };
}

void ArrangementNavigator::resized()
{
    auto div = getWidth() / 2;
    _beatLabel.setSize( div, getHeight() );
    _playButton.setBounds( div, 0, div, getHeight() );
}
