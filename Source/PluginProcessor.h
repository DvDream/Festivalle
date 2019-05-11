/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
 */
class PluginDajeAudioProcessor  : public AudioProcessor,
public ChangeBroadcaster
{
public:
    //==============================================================================
    PluginDajeAudioProcessor();
    ~PluginDajeAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    double setThreshold(double value);
    int prova = 10;
    
    enum
    {
        fftOrder = 10,           // [1]
        fftSize = 1 << fftOrder // [2]
    };
    
    void pushNextSampleIntoFifo(float sample) noexcept;
    
    
    
    float* getFFTData();
    float getFFTDataIndex(int index);
    
    bool getNextFFTBlockReady();
    void setNextFFTBlockReady(bool setup);

    
private:
    double rawVolume = 1;
    double threshold;
    int count = 0;
    
    float fifo[fftSize];           // [4]
    int fifoIndex = 0;              // [6]
    float fftData[2 * fftSize];    // [5]
    
    bool nextFFTBlockReady = false; // [7]
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginDajeAudioProcessor)
};
