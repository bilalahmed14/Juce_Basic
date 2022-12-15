#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class ourLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderpos, float rotaryStartangle,
        float rotaryEndangle, Slider& slider) override {

        float diameter = jmin(width, height);
        float radius = diameter / 2;
        float centerX = x + width / 2;
        float centerY = y + height / 2;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartangle + (sliderpos * (rotaryEndangle - rotaryStartangle));

        Rectangle<float> dialArea(rx, ry, diameter, diameter);

        g.setColour(Colours::red);
        g.fillEllipse(dialArea);

        g.setColour(Colours::black);

        Path dialTick;
        dialTick.addRectangle(0, -radius, 10.0f, radius * 0.33);

        g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));



        g.setColour(Colours::black);
        g.drawEllipse(rx, ry, diameter, diameter, 5.0f);

    }


};



class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    juce::Slider dial1;
    ourLookAndFeel ourlookandfeel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
