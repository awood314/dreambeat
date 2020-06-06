
#include "ArrangementNavigator.h"
#include <ui/Colors.h>

ArrangementNavigator::ArrangementNavigator( Arrangement& arrangement )
: _arrangement( arrangement ), _playButton( "play", juce::DrawableButton::ImageFitted )
{
    // navigator
    std::vector<Arrangement::SequenceType> orderedTypes{ Arrangement::SequenceType::Section,
                                                         Arrangement::SequenceType::Phrase,
                                                         Arrangement::SequenceType::Bar,
                                                         Arrangement::SequenceType::Beat };
    for ( int i = 0; i < orderedTypes.size(); i++ )
    {
        auto type = orderedTypes[i];

        // up button
        auto* upButton =
        new juce::DrawableButton( "up " + juce::String( i ), juce::DrawableButton::ImageFitted );
        _sequenceUpButtons.add( upButton );
        addAndMakeVisible( upButton );
        upButton->onClick = [this, type]() { _arrangement.decrementSequence( type ); };
        upButton->setImages( juce::Drawable::createFromImageData( BinaryData::caret_up_svg, BinaryData::caret_up_svgSize )
                             .get() );
        upButton->setEnabled( _arrangement.canDecrementSequence( type ) );

        // label
        auto* label = new juce::Label();
        label->setFont( juce::Font( 24 ) );
        label->setText( juce::String( 1 + _arrangement.getSequence( type ) ), juce::sendNotification );
        label->setJustificationType( juce::Justification::centred );
        _sequenceLabels.add( label );
        addAndMakeVisible( label );

        // down button
        auto* downButton =
        new juce::DrawableButton( "up " + juce::String( i ), juce::DrawableButton::ImageFitted );
        _sequenceDownButtons.add( downButton );
        addAndMakeVisible( downButton );
        downButton->onClick = [this, type]() { _arrangement.incrementSequence( type ); };
        downButton->setImages( juce::Drawable::createFromImageData( BinaryData::caret_down_svg, BinaryData::caret_down_svgSize )
                               .get() );
    }

    // listen to arrangement for changes
    _arrangement.newSequence.connect( [this, orderedTypes]( int ) {
        for ( int i = 0; i < orderedTypes.size(); i++ )
        {
            auto type = orderedTypes[i];
            _sequenceLabels[i]->setText( juce::String( 1 + _arrangement.getSequence( type ) ),
                                         juce::sendNotification );
            _sequenceUpButtons[i]->setEnabled( _arrangement.canDecrementSequence( type ) );
        }
    } );

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
