#pragma once

#include "ofMain.h"
#include "ofxTapMachine.h"

class ofApp : public ofBaseApp{
private:
    ofPtr<ofxTapMachine> tapMachine;

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);

    void barFunc(int &count);
    void minimFunc(int &count);
    void crochetFunc(int &count);
};
