
#include "SampleSlicerComponent.h"

int NUM_SLICES = 8;

SampleSlicerComponent::SampleSlicerComponent( DreambeatApp& app ) : _thumbnailComponent( app )
{
    addAndMakeVisible( _thumbnailComponent );
    for ( int i = 0; i < NUM_SLICES; i++ )
    {
        auto* tb = new TextButton( juce::String( i ) );
        tb->onClick = [&app, i]() { app.play(); };
        _slicerButtons.add( tb );
        addAndMakeVisible( tb );
    }
}

void SampleSlicerComponent::resized()
{
    _thumbnailComponent.setBounds( 0, 0, getWidth(), getHeight() / 2 );
    auto div = getWidth() / NUM_SLICES;
    for ( int i = 0; i < NUM_SLICES; i++ )
    {
        _slicerButtons[i]->setBounds( i * div, getHeight() / 2, div, getHeight() / 2 );
    }
}
