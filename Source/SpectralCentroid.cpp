/*
  ==============================================================================

    SpectralCentroid.cpp
    Created: 29 May 2019 12:00:51am
    Author:  Carmelo Fascella

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectralCentroid.h"
#include "PluginProcessor.h"

//==============================================================================
SpectralCentroid::SpectralCentroid(PluginDajeAudioProcessor& p)
:Thread("SpectralCentroidThread"), processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	centersGrativtyFunction();
 
}

SpectralCentroid::~SpectralCentroid()
{
}

void SpectralCentroid::paint (Graphics& g)
{
   
}

void SpectralCentroid::resized()
{

}

void SpectralCentroid::run()
{

    spectralCentroidFunction();
    
}

void SpectralCentroid::spectralCentroidFunction()
{
    float numL = 0;
    float numR = 0;
    float denL = 0;
    float denR = 0;
    
    powerSpectrumFunction();
    

    for(int i = 0; i <= PluginDajeAudioProcessor::fftSize / 2 - 1; i++)
    {
        numL +=  log2(centersFreq[i] / 1000 ) * powerSpectrumL[i + 1];
        numR +=  log2(centersFreq[i] / 1000 ) * powerSpectrumR[i + 1];
        
        denL += powerSpectrumL[i + 1];
        denR += powerSpectrumR[i + 1];
    }
    
	if (denL == 0)
		centroidL = 0;
	else
		centroidL = numL / denL;

	if (denR == 0)
		centroidR = 0;
	else
		centroidR = numR / denR;

	centroidMid = (centroidL + centroidR) / 2;
    
    //printf("\ndiff: %.5f", numL - numR);
    
    /*
    if(centroidL > maxL)
    {
        maxL = centroidL;
        printf("\n maxL = %.3f", maxL );
    }
    
    if(centroidR > maxR)
    {
        maxR = centroidR;
        printf("\n maxR = %.3f", maxR );
    }
    
    
    if(centroidL < minL)
    {
        minL = centroidL;
        printf("\n minL = %.3f", minL );
    }
    
    if(centroidR < minR)
    {
        minR = centroidR;
        printf("\n minR = %.3f", minR );
    }
    */
    
    
    
    //printf("\nleft:%.3f   mid:%.3f   right: %.3f", centroidL, centroidMid, centroidR);
    //sendChangeMessage();
    
    
}

//calculation of P(k)
void SpectralCentroid::powerSpectrumFunction()
{
    //printf("\n");
    for(int i = 0; i < PluginDajeAudioProcessor::fftSize; i++)
    {
        powerSpectrumL[i] = processor.fftDataL[i] * processor.fftDataL[i];
        powerSpectrumR[i] = processor.fftDataR[i] * processor.fftDataR[i];
        
        //printf("%.4f ", processor.fftDataL[i]);

    }
    
    //modify the spectrum, it starts from 1, the value i = 0 is discarded
    powerSpectrumL[1] = powerSpectrumL[0] + powerSpectrumL[1];
    powerSpectrumR[1] = powerSpectrumR[0] + powerSpectrumR[1];
    //printf("\n");
    
}

void SpectralCentroid::centersGrativtyFunction()
{
	centersFreq[0] = rangeFreq;

    for(int i = 1; i < PluginDajeAudioProcessor::fftSize; i++)
    {
        centersFreq[i] = rangeFreq * (i + 1);
    }
}
