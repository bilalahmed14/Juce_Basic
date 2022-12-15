/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PlugintestAudioProcessorEditor::PlugintestAudioProcessorEditor (PlugintestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    //gainSlider.setRange(0, 1);
    //gainSlider.setValue(0.5);
    gainSlider.setRange(-48, 0); // algorthimic scale
    gainSlider.setValue(-1);                // algorthimic scale
    gainSlider.addListener(this);



    addAndMakeVisible(gainSlider);
}

PlugintestAudioProcessorEditor::~PlugintestAudioProcessorEditor()
{
}

//==============================================================================
void PlugintestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void PlugintestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


    gainSlider.setBounds(getLocalBounds());
}

void PlugintestAudioProcessorEditor::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &gainSlider) {
        //audioProcessor.rawvolume = gainSlider.getValue();
        //changing the above linear to logarthimic scale (db = 20 * log(x)) arrange equation for X
        audioProcessor.rawvolume = pow(10, gainSlider.getValue() / 20); 
    }
    
}
