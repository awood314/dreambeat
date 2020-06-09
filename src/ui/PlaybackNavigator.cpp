
#include "PlaybackNavigator.h"
#include <ui/Colors.h>

PlaybackNavigator::PlaybackNavigator( Playback& playback ) : _playback( playback )
{
    // navigator
    std::vector<Playback::SequenceType> orderedTypes{ Playback::SequenceType::Section,
                                                      Playback::SequenceType::Phrase,
                                                      Playback::SequenceType::Bar,
                                                      Playback::SequenceType::Beat };
    for ( int i = 0; i < orderedTypes.size(); i++ )
    {
        auto type = orderedTypes[i];

        // up button
        auto* upButton =
        new juce::DrawableButton( "up " + juce::String( i ), juce::DrawableButton::ImageFitted );
        _sequenceUpButtons.add( upButton );
        addAndMakeVisible( upButton );
        upButton->onClick = [this, type]() { _playback.decrementSequence( type ); };
        upButton->setImages( juce::Drawable::createFromImageData( BinaryData::caret_up_svg, BinaryData::caret_up_svgSize )
                             .get() );
        upButton->setEnabled( _playback.canDecrementSequence( type ) );

        // label
        auto* label = new juce::Label();
        label->setFont( juce::Font( 24 ) );
        label->setText( juce::String( 1 + _playback.getSequence() ), juce::sendNotification );
        label->setJustificationType( juce::Justification::centred );
        _sequenceLabels.add( label );
        addAndMakeVisible( label );

        // down button
        auto* downButton =
        new juce::DrawableButton( "up " + juce::String( i ), juce::DrawableButton::ImageFitted );
        _sequenceDownButtons.add( downButton );
        addAndMakeVisible( downButton );
        downButton->onClick = [this, type]() { _playback.incrementSequence( type ); };
        downButton->setImages( juce::Drawable::createFromImageData( BinaryData::caret_down_svg, BinaryData::caret_down_svgSize )
                               .get() );
    }

    // listen to playback for changes
    _playback.newSequence.connect( [this, orderedTypes]( int ) {
        for ( int i = 0; i < orderedTypes.size(); i++ )
        {
            auto type = orderedTypes[i];
            _sequenceLabels[i]->setText( juce::String( 1 + _playback.getSequence() ), juce::sendNotification );
            _sequenceUpButtons[i]->setEnabled( _playback.canDecrementSequence( type ) );
        }
    } );
}

void PlaybackNavigator::resized()
{
    auto rowHeight = getHeight() / 3;
    auto rowWidth = getWidth() / _sequenceLabels.size();
    auto buttonInsets = juce::jmin( rowHeight, rowWidth );
    for ( int i = 0; i < _sequenceLabels.size(); i++ )
    {
        _sequenceUpButtons[i]->setEdgeIndent( buttonInsets );
        _sequenceUpButtons[i]->setBounds( i * rowWidth, 0, rowWidth, rowHeight );
        _sequenceLabels[i]->setBounds( i * rowWidth, rowHeight, rowWidth, rowHeight );
        _sequenceDownButtons[i]->setEdgeIndent( buttonInsets );
        _sequenceDownButtons[i]->setBounds( i * rowWidth, rowHeight * 2, rowWidth, rowHeight );
    }
}