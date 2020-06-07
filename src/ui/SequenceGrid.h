
#pragma once

#include <model/Arrangement.h>
#include <model/TrackSequence.h>
#include "SequenceComponent.h"
#include <JuceHeader.h>

class SequenceGrid : public juce::Component
{
public:
    SequenceGrid( Arrangement& arrangement );
    
    void resized() override;
    void visibilityChanged() override;
    
    void refresh();
    
    void addSequence( TrackSequence* track );

private:
    juce::OwnedArray<SequenceComponent> _sequences;
    Arrangement& _arrangement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceGrid )
};
