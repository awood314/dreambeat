
#include <JuceHeader.h>

template <typename Function> void callFunctionOnMessageThread( Function&& func )
{
    if ( juce::MessageManager::getInstance()->isThisTheMessageThread() )
    {
        func();
    }
    else
    {
        jassert( !juce::MessageManager::getInstance()->currentThreadHasLockedMessageManager() );
        juce::WaitableEvent finishedSignal;
        juce::MessageManager::callAsync( [&] {
            func();
            finishedSignal.signal();
        } );
        finishedSignal.wait( -1 );
    }
}
