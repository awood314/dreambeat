
#include "ThumbnailComponent.h"

ThumbnailComponent::ThumbnailComponent( DreambeatApp& app )
: _sampleThumbnailCache( 5 ), _sampleThumbnail( 512, _formatManager, _sampleThumbnailCache )
{
    _formatManager.registerBasicFormats();
    //    _formatManager.createReaderFor( app.getSample() );
    //    _sampleThumbnail.addChangeListener( this );
    //    _sampleThumbnail.setSource( new juce::FileInputSource( app.getSample() ) );
}

void ThumbnailComponent::changeListenerCallback( juce::ChangeBroadcaster* source )
{
    if ( source == &_sampleThumbnail )
    {
        repaint();
    }
}


void ThumbnailComponent::paint( juce::Graphics& g )
{
    Rectangle<int> thumbnailBounds( 10, 100, getWidth() - 20, getHeight() - 120 );
    g.setColour( Colours::white );
    g.fillRect( thumbnailBounds );
    g.setColour( Colours::red );
    _sampleThumbnail.drawChannels( g, thumbnailBounds, 0.0, _sampleThumbnail.getTotalLength(), 1.0f );
}
