
#include <JuceHeader.h>

class DreambeatEngine
{
public:
    DreambeatEngine();

    tracktion_engine::HostedAudioDeviceInterface& getAudioInterface();
    tracktion_engine::ExternalPlayheadSynchroniser& getPlayheadSynchroniser();

    void play();

private:
    class PluginEngineBehaviour : public tracktion_engine::EngineBehaviour
    {
    public:
        bool autoInitialiseDeviceManager() override
        {
            return false;
        }
    };

    tracktion_engine::AudioTrack* getOrInsertAudioTrackAt( int index );
    void setupInputs();
    void setupOutputs();

    tracktion_engine::Engine _engine;
    tracktion_engine::Edit _edit;
    tracktion_engine::ExternalPlayheadSynchroniser _playheadSynchroniser;
};
