#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tapMachine = make_shared<ofxTapMachine>();
    ofAddListener(tapMachine->bar.event, this, &ofApp::barFunc);
    ofAddListener(tapMachine->minim.event, this, &ofApp::minimFunc);
    ofAddListener(tapMachine->crochet.event, this, &ofApp::crochetFunc);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 0, 0);
    ofDrawCircle(50+(ofGetWidth()-100)*tapMachine->bar.normalized, 200, 10);

    ofSetColor(0, 255, 0);
    ofDrawCircle(50+(ofGetWidth()-100)*tapMachine->minim.normalized, 250, 10);

    ofSetColor( 0, 0, 255);
    ofDrawCircle(50+(ofGetWidth()-100)*tapMachine->crochet.normalized, 300, 10);


    string msg="===============[ ofxTapMachine example ]===============\n";
    msg += "press space bar more than 3 times to get average BPM.\n";
    msg += "FPS        : " + ofToString(ofGetFrameRate(), 2) + "\n";
    msg += "BPM        : " + ofToString(tapMachine->getBPM(),2) + "\n";
    msg += "bar        : " + ofToString(tapMachine->bar.count) + "\n";
    msg += "minim      : " + ofToString(tapMachine->minim.count) + "\n";
    msg += "crochet    : " + ofToString(tapMachine->crochet.count) + "\n";
    msg += "quaver     : " + ofToString(tapMachine->quaver.count) + "\n";
    
    ofDrawBitmapStringHighlight(msg, 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==' ') tapMachine->tap();
    if(key=='s') tapMachine->toggleStart();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::barFunc(int &count){
    cout<<"barCount : "<<count<<endl;
}
void ofApp::minimFunc(int &count){
    cout<<"minimCount : "<<count<<endl;
}
void ofApp::crochetFunc(int &count){
    cout<<"crochetCount : "<<count<<endl;
}
