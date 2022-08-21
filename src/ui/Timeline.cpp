
#include "Timeline.h"

int NUM_TICKS = 8;

Timeline::Timeline( Playback& p )
: _playback( p )
{
    for ( int i = 0; i < NUM_TICKS; i++ )
    {
        auto* timeLabel = new juce::Label();
        timeLabel->setJustificationType( juce::Justification::centredTop );
        timeLabel->setMinimumHorizontalScale( 1.0 );
        timeLabel->setFont( juce::Font( 12.0 ) );
        timeLabel->setInterceptsMouseClicks( false, false );
        _timeLabels.add( timeLabel );
        addAndMakeVisible( timeLabel );
    }
    auto labelUpdate = [this]( int window ) {
        for ( int i = 0; i < NUM_TICKS; i++ )
        {
            _timeLabels[i]->setText( _playback.getSequenceString( window + i * _playback.getResolution() ),
                                     juce::sendNotification );
        }
    };
    _playback.newWindow.connect( labelUpdate );
    labelUpdate( 0 );
}

void Timeline::mouseDown( const juce::MouseEvent &event )
{
    auto section = ( event.getMouseDownY() * NUM_TICKS ) / getHeight();
    _playback.setSequence( _playback.getWindow() + section * _playback.getResolution() );
}

void Timeline::paint( juce::Graphics& g )
{
}

void Timeline::resized()
{
    auto div = getHeight() / NUM_TICKS;
    for ( int i = 0; i < NUM_TICKS; i++ )
    {
        _timeLabels[i]->setBounds( 0, div * i, getWidth(), div );
    }
}
