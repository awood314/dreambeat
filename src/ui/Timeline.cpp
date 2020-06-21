
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

void Timeline::paint( juce::Graphics& g )
{
}

void Timeline::resized()
{
    auto div = getHeight() / 8;
    for ( int i = 0; i < NUM_TICKS; i++ )
    {
        _timeLabels[i]->setBounds( 0, div * i, getWidth(), div );
    }
}
