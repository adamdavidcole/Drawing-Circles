#include <iostream>
#include "ofApp.h"

using namespace std;

void log(string s) {
    cout << s << endl;
}

//--------------------------------------------------------------
void ofApp::setup(){
    //    ofBackground(255/20.0, 128/20.0, 1);
    ofBackground(12, 6, 0);
    ofSetBackgroundAuto(true);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofHideCursor();
    
    
    /* This is stuff you always need.*/
    
    sampleRate             = 44100; /* Sampling Rate */
    initialBufferSize    = 512;    /* Buffer Size. you have to fill this buffer with sound*/
    
    
    /* Now you can put anything you would normally put in maximilian's 'setup' method in here. */
    
    
    beat.load(ofToDataPath("beat2.wav"));
    beat.getLength();
    
    
    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
    
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
    
    for (int j = 0; j < shapeCount; j++) {
        float multYShift = ofMap(j, 0, shapeCount, PI/10.0, 0);
        float multY = ofMap(sin((ofGetElapsedTimef()/9.0)+multYShift), -1.0, 1.0, 495.0, 505.0);
        
        //        float red = 255 * ((float)(shapeCount - j) / (float)shapeCount);
        float r = ofMap(j, 0.0, shapeCount, radius, -20);
        float red = ofMap(j, 0.0, shapeCount, 0.0, 160.0);
        float green = ofMap(j, 0.0, shapeCount, 0.0, 1.0);
        float blue = ofMap(j, 0.0, shapeCount, 0.0, 1.0);
        
        float alphaShift = ofMap(j, 0, shapeCount, PI/3.0, 0);
        float alpha = ofMap(j, 0.0, shapeCount, -20, 100 * abs(sin((ofGetElapsedTimef()/10.0) + multYShift)));
        
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
}


//--------------------------------------------------------------
void ofApp::audioRequested     (float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        /* Stick your maximilian 'play()' code in here ! Declare your objects in testApp.h.
         
         For information on how maximilian works, take a look at the example code at
         
         http://www.maximilian.strangeloop.co.uk
         
         under 'Tutorials'.
         
         */
        
        
        
        sample=beat.play(0.25, 0, beat.length);
        wave=sine1.sinebuf(abs(mouseX));/* mouse controls sinewave pitch. we get abs value to stop it dropping
                                         //                                         delow zero and killing the soundcard*/
        
        mymix.stereo(sample + wave, outputs, 0.5);
        
        
        output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
        output[i*nChannels + 1] = outputs[1];
    }
    
}

//--------------------------------------------------------------
void ofApp::audioReceived     (float * input, int bufferSize, int nChannels){
    
    
    /* You can just grab this input and stick it in a double, then use it above to create output*/
    
    for (int i = 0; i < bufferSize; i++){
        
        /* you can also grab the data out of the arrays*/
        
        
    }
    
}

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
