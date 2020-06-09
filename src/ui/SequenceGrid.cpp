
#include "SequenceGrid.h"
#include <ui/Colors.h>

int GRID_SIZE = 8;
int PADDING = 5;

SequenceGrid::SequenceGrid( Arrangement& arrangement ) : _arrangement( arrangement )
{
    //    arrangement.newSequence.connect( [this] ( int sequence ) {
    //        refresh();
    //    } );
}

void SequenceGrid::visibilityChanged()
{
    refresh();
}

void SequenceGrid::refresh()
{
    for ( int i = 0; i < _sequences.size(); i++ )
    {
        for ( int j = 0; j < _sequences[i]->size(); j++ )
        {
            _sequences[i]->getUnchecked( j )->setToggleState( _arrangement.getNotes( j ).count( i ),
                                                              juce::sendNotification );
        }
    }
}

void SequenceGrid::resized()
{
    auto width = getWidth() / GRID_SIZE;
    auto height = getHeight() / GRID_SIZE;
    for ( int i = 0; i < _sequences.size(); i++ )
    {
        auto* sequence = _sequences[i];
        for ( int j = 0; j < sequence->size(); j++ )
        {
            sequence->getUnchecked( j )->setBounds( i * width + PADDING, j * height + PADDING,
                                                    width - PADDING * 2, height - PADDING * 2 );
        }
    }
}

void SequenceGrid::addSequence()
{
    int i = _sequences.size();
    auto sequence = _sequences.add( new juce::OwnedArray<SequenceItem>() );
    for ( int j = 0; j < GRID_SIZE; j++ )
    {
        auto* item = sequence->add( new SequenceItem( colors::black ) );
        item->onClick = [this, i, j, item]() {
            _arrangement.setNote( i, j, item->getToggleState() );
        };
        addAndMakeVisible( item );
    }
}
