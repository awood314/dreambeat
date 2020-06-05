
#include "ArrangementNavigator.h"

ArrangementNavigator::ArrangementNavigator( Arrangement& arrangement ) : _arrangement( arrangement )
{
    addAndMakeVisible( _playButton );
    _playButton.onClick = [this]() { _arrangement.play(); };
}

void ArrangementNavigator::resized()
{
    _playButton.setBounds( getLocalBounds() );
}
