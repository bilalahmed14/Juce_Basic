#pragma once

#include <JuceHeader.h>
using namespace juce;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void updateFrequency();

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    Slider frequencyslider, ampslider;
    Label freqlabel, amplabel;


    Array<float> waveTable;
    double wtSize;
    double frequency;
    double phase;
    double increament;
    double amplitude;
    double getfrequncy;
    double getamplitude;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
