#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);


    addAndMakeVisible(dial1);
    dial1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    
    dial1.setLookAndFeel(&ourlookandfeel);


}

MainComponent::~MainComponent()
{
    dial1.setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::white);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.


    dial1.setBounds(getLocalBounds());
}
