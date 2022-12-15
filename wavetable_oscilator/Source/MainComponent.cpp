#include "MainComponent.h"



using namespace juce;
//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 100);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open

        setAudioChannels (2, 2);
    }



    //addAndMakeVisible(ampslider);
    

    frequencyslider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    frequencyslider.setRange(50, 500);
    frequencyslider.addListener(this);
    frequencyslider.setValue(100);
    frequencyslider.setTextValueSuffix("HZ");
    freqlabel.setText("frequency", dontSendNotification);
    freqlabel.attachToComponent(&frequencyslider, true);
    



    ampslider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    ampslider.setRange(0.1, 1.5);
    ampslider.addListener(this);
    ampslider.setValue(0.2);
    ampslider.setTextValueSuffix("db");
    amplabel.setText("amplitude", dontSendNotification);
    amplabel.attachToComponent(&ampslider, true);

    addAndMakeVisible(frequencyslider);
    addAndMakeVisible(ampslider);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{

    frequency = frequencyslider.getValue();
    phase = 0;
    wtSize = 1024;
    amplitude = ampslider.getValue();
    getfrequncy = sampleRate;

    for (int i = 0; i < wtSize; i++) {

        waveTable.insert(i, sin(2.0 * double_Pi * i / wtSize));
    }

    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    float* const leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

    float* const rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);


    for (int samples=0; samples < bufferToFill.numSamples; samples++) {

        leftSpeaker[samples] = waveTable[(int)phase] * amplitude;
        rightSpeaker[samples] = waveTable[(int)phase] * amplitude;

        updateFrequency();
        
    }

    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    //bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    const int labelspace = 100;

    frequencyslider.setBounds(labelspace, 20, getWidth() - 100, 20);
    ampslider.setBounds(labelspace, 60, getWidth() - 100, 20);



}


void MainComponent::sliderValueChanged(Slider* slider) {

    if (slider == &frequencyslider) {
        frequency = frequencyslider.getValue();
        

        std::cout << frequency << std::endl;
    }

    if (slider == &ampslider) {
        amplitude = ampslider.getValue();
    }

}

void MainComponent::updateFrequency()
{
    increament = frequency * wtSize / getfrequncy;
    phase = fmod((phase + increament), wtSize);
}






