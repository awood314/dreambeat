
#include "PlayControls.h"
#include <ui/Colors.h>

PlayControls::PlayControls( Playback& playback )
: _playback( playback )
, _playButton( "play", juce::DrawableButton::ImageFitted )
{

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
    _playButton.onClick = [this]() { _playback.play(); };
}

void PlayControls::resized()
{
    _playButton.setBounds( getLocalBounds() );
    _playButton.setEdgeIndent( getHeight() );
}
