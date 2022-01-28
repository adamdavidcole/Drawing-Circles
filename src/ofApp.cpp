#include <iostream>
#include "ofApp.h"

using namespace std;

void log(string s) {
    cout << s << endl;
}

void logFloatArr(float arr[], int arrSize) {
    cout << "[ ";
    for (int i = 0; i < arrSize; i++) {
        cout << to_string(arr[i]);
        
        if (i != arrSize - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

//--------------------------------------------------------------
void ofApp::setup(){
    //    ofBackground(255/20.0, 128/20.0, 1);
    ofBackground(12, 6, 0);
    ofSetBackgroundAuto(true);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofHideCursor();
    
    
    beat.load("circles.mp3");
    beat.play();
    
    /* This is stuff you always need.*/
    
//    sampleRate             = 44100; /* Sampling Rate */
//    initialBufferSize    = 512;    /* Buffer Size. you have to fill this buffer with sound*/
//
    
    /* Now you can put anything you would normally put in maximilian's 'setup' method in here. */
    
//
//    beat.load(ofToDataPath("beat2.wav"));
//    beat.getLength();
//
//    beat.load(ofToDataPath("circles.mp3"));
//    beat.getLength();
    
//    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
//
//    beat.setVolume(1);
//

    // (5) grab the fft, and put in into a "smoothed" array,
    //        by taking maximums, as peaks and then smoothing downward
    float * val = ofSoundGetSpectrum(nBandsToGet);        // request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){

        // let the smoothed value sink to zero:
        fftSmoothed[i] *= 0.96f;

        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

    }

    for (int i = 0; i <= rollingAvgSize - 2; i++)
    {
        rollingAvgArr[i] = rollingAvgArr[i + 1]; //move all element to the right except last one
        
       
    }
    
    float fftVal = CLAMP(fftSmoothed[1], 0, 1.0);
    rollingAvgArr[rollingAvgSize - 1] = fftVal;
    
    float fftVal2Total = 0; //CLAMP(fftSmoothed[1], 0, 1.0);
    int rangeStart = 10;
    int rangeEnd = 18;
    for (int i = 10; i < 18; i++) {
        fftVal2Total += fftSmoothed[i];
    }
    float fftVal2Avg = fftVal2Total / (rangeEnd - rangeStart);
    rollingAvgArr2[rollingAvgSize - 1] = fftVal2Avg;

    
//    logFloatArr(rollingAvgArr, rollingAvgSize);
}

//--------------------------------------------------------------
void ofApp::draw(){
    //    ofFill();
    //    ofSetColor(30, 100);
    //    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    
    int segments = 2000;
    int radius = 300;
    int shapeCount = 10;
    
    float gapX = ofMap(ofGetMouseX(), 0, ofGetWidth(), ofGetWidth() / 20, -ofGetWidth() / 20);
    float gapY = ofMap(ofGetMouseY(), 0, ofGetHeight(), ofGetHeight() / 20, -ofGetHeight() / 20);
    //    float multY = ofMap(ofGetMouseY(), 0, ofGetHeight(), 495.0, 505.0);
    
    float shift = 0.75;
    
    float xCenter = ofGetWidth() / 2;
    float yCenter = 4.0 * (ofGetHeight() / 9.0);
    
    ofNoFill();
    ofSetColor(255,0,0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    
    float sum = 0;
    float sum2 = 0;
    for (int i = 0; i < rollingAvgSize; i++) {
        sum += rollingAvgArr[i];
        sum2 += rollingAvgArr2[i];
    }
    float fftAvg = sum / rollingAvgSize;
    float fftAvg2 = sum2 / rollingAvgSize;

    
    
    for (int j = 0; j < shapeCount; j++) {
        float multYShift = ofMap(j, 0, shapeCount, PI/10.0, 0);
        float multY = ofMap(sin((ofGetElapsedTimef()/9.0)+multYShift), -1.0, 1.0, 495.0, 505.0);
        
        //        float red = 255 * ((float)(shapeCount - j) / (float)shapeCount);
        float fftAvgClamped2 = CLAMP(fftAvg2, 0, 0.003);

        float rWave = 10 * sin((ofGetElapsedTimef() * 1.5) + multYShift);
        
        float rFacotr = ofMap(fftAvgClamped2, 0.0, 0.003, 0.0, 225.0);
        if (ofGetElapsedTimef() < 9.500) rFacotr = 0;
//        if (rFacotr < 30) rFacotr = 0;
        log(to_string(rFacotr));

        float r = ofMap(j, 0.0, shapeCount, radius + rWave, - 20);
        float red = ofMap(j, 0.0, shapeCount, 0.0, 160.0);
        float green = ofMap(j, 0.0, shapeCount, 0.0, 1.0) + rFacotr;
        float blue = ofMap(j, 0.0, shapeCount, 0.0, 1.0) + + rFacotr/2;
        
        float maxAlpha = 100 * abs(sin((ofGetElapsedTimef()/10.0) + multYShift));
       
        float fftAvgClamped = CLAMP(fftAvg, 0, 1.0);

        float maxAlpha2 = ofMap(fftAvgClamped, 0, 1.0, 0, 150);
        float alphaShift = ofMap(j, 0, shapeCount, PI/3.0, 0);
        float alpha = ofMap(j, 0.0, shapeCount, -20, maxAlpha2);
        
        if (j == shapeCount - 1) {
            // increase background color brightness based on alpha of "closest" cirlce
            float redBackground = MAX(ofMap(alpha, 0, 100.0, 0, 10.0), 0.0);
            float greenBackground = MAX(ofMap(alpha, 0, 100.0, 0, 5.0), 0.0);
            ofSetBackgroundColor(redBackground, greenBackground, 0);
        }
        //
        
        ofSetColor(red, green, blue, alpha);
        
        ofBeginShape();
        
        for (int i = 0; i < segments; i++) {
            float theta = (2 * PI) * ((float)i / (float)segments);
            //            log("Theta: " + to_string(theta));
            
            float x = xCenter - gapX * j +
            cos(theta + PI / 2.0) * r *
            (shift * cos(500 * theta + PI) + PI / 2.0);
            float y = yCenter - gapY * j +
            sin(theta + PI / 2.0) * r *
            (sin(multY * theta + PI) + PI / 2.0);
            //            log("x: " + to_string(x) + " ', y: " + to_string(y));
            ofVertex(x, y);
        }
        
        ofEndShape(true);
    }
    
    
    //        log("Gap: " + to_string(gap));
    
    //        image.draw(ofGetWidth() / 2 - image.getWidth() / 2, ofGetHeight() / 2 - image.getHeight() / 2);
    //        image.resize(100, 100);
    
//    ofSetColor(255, 255, 255,255);
//    ofRect(600, 300, sample*150, sample*150); /* audio sigs go between -1 and 1. See?*/
//    ofCircle(200, 300, wave*150);
    ofEnableAlphaBlending();
        ofSetColor(255,255,255,100);
        ofDrawRectangle(100,ofGetHeight()-300,5*128,200);
    ofDisableAlphaBlending();
    
    // draw the fft resutls:
    ofSetColor(255,255,255,255);
    
    float width = (float)(5*128) / nBandsToGet;
    for (int i = 0;i < nBandsToGet; i++){
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofDrawRectangle(100+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
    }
}


//--------------------------------------------------------------
//void ofApp::audioRequested     (float * output, int bufferSize, int nChannels){
//
//    for (int i = 0; i < bufferSize; i++){
//
//        /* Stick your maximilian 'play()' code in here ! Declare your objects in testApp.h.
//
//         For information on how maximilian works, take a look at the example code at
//
//         http://www.maximilian.strangeloop.co.uk
//
//         under 'Tutorials'.
//
//         */
//
//
//
////        sample=beat.play(0.25, 0, beat.length);
//        wave=sine1.sinebuf(abs(mouseX));/* mouse controls sinewave pitch. we get abs value to stop it dropping
//                                         //                                         delow zero and killing the soundcard*/
//
//        mymix.stereo(sample + wave, outputs, 0.5);
//
//
//        output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
//        output[i*nChannels + 1] = outputs[1];
//    }
//
//}
//
////--------------------------------------------------------------
//void ofApp::audioReceived     (float * input, int bufferSize, int nChannels){
//
//
//    /* You can just grab this input and stick it in a double, then use it above to create output*/
//
//    for (int i = 0; i < bufferSize; i++){
//
//        /* you can also grab the data out of the arrays*/
//
//
//    }
//
//}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        ofDisableBlendMode();
    } else if (key == '2') {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
