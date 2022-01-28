#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        ofSoundPlayer         beat;
        static constexpr size_t nBandsToGet = 128;
        std::array<float, nBandsToGet> fftSmoothed{{0}};
    
        static const int rollingAvgSize = 75;
        float rollingAvgArr[rollingAvgSize] = { 0.0 };
        float rollingAvgArr2[rollingAvgSize] = { 0.0 };

    
    
//        void audioRequested     (float * input, int bufferSize, int nChannels); /* output method */
//        void audioReceived     (float * input, int bufferSize, int nChannels); /* input method */
////
//        int        initialBufferSize; /* buffer size */
//        int        sampleRate;


        /* stick you maximilian stuff below */
//
//        double wave,sample,outputs[2];
//        ofxMaxiMix mymix;
//        ofxMaxiOsc sine1;
//        ofxMaxiSample beats,beat;
};
