
#include "ArrangementNavigator.h"
#include <ui/Colors.h>

ArrangementNavigator::ArrangementNavigator( Arrangement& arrangement )
: _arrangement( arrangement ), _playButton( "play", juce::DrawableButton::ImageFitted )
{
    // navigator
    addAndMakeVisible( _beatUpButton );
    //    _beatUpButton.onClick = [this] () { arrangement.}
    addAndMakeVisible( _beatLabel );
    arrangement.newSequence.connect( [this]( int sequence ) {
        _beatLabel.setText( juce::String( sequence + 1 ), juce::sendNotification );
    } );
    addAndMakeVisible( _beatDownButton );

    // play button
    addAndMakeVisible( _playButton );
    _playButton.setImages( juce::Drawable::createFromImageData( BinaryData::play_unselected_svg,
                                                                BinaryData::play_unselected_svgSize )
                           .get(),
                           nullptr, nullptr, nullptr,
                           juce::Drawable::createFromImageData( BinaryData::play_selected_svg, BinaryData::play_selected_svgSize )
                           .get() );
    _playButton.setClickingTogglesState( true );
    _playButton.setColour( juce::DrawableButton::backgroundOnColourId, colors::transparent );
    _playButton.onClick = [this]() { _arrangement.play(); };
}

void ArrangementNavigator::resized()
{
    auto div = getHeight() / 3;
    _beatLabel.setSize( getWidth() / 2, getHeight() );
    _playButton.setBounds( getWidth() / 2, div, div, div );
}
