//
//  ofxTapMachine.h
//
//  Created by shugohirao on 2018/12/31.
//

#pragma once
#include "ofMain.h"

class ofxTapMachine {
private:
    int tapCount, lastTime, avgBarMillis;
    float BPM;
    vector<int> intervals;
    bool bStart;

    struct BeatInfo{
        BeatInfo():count(0),normalized(0),lastNormalized(0){}
        virtual ~BeatInfo(){}
        int count;
        float normalized, lastNormalized;
        ofEvent<int> event;
    };

protected:
    void updateBeatInfo(int time, BeatInfo &info, float beats){
        float millis = avgBarMillis / beats;
        info.normalized = fmod(time,millis) / (float)millis;
        if(info.normalized < info.lastNormalized){
            info.count++;
            ofNotifyEvent(info.event, info.count);
        }
        info.lastNormalized = info.normalized;
    }

public:
    BeatInfo bar,minim,crochet,quaver;
    BeatInfo twoBar,fourBar;

    ofxTapMachine():BPM(100),tapCount(0),avgBarMillis(1000),bStart(false){
        ofAddListener(ofEvents().update, this, &ofxTapMachine::update);
        tapCount=0;
        intervals.clear();
    }
    virtual ~ofxTapMachine(){
        ofRemoveListener(ofEvents().update, this, &ofxTapMachine::update);
    }

    void update(ofEventArgs &e){
        if(!bStart) return;

        int time = ofGetElapsedTimeMillis();
        if(intervals.size()>0 && ofGetElapsedTimeMillis() - lastTime > 3000){
            ofLogVerbose("ofxTapMachine")<<"clear tap logs";
            intervals.clear();
            tapCount = 0;
        }

        updateBeatInfo(time, fourBar, 1/4.f);
        updateBeatInfo(time, twoBar, 1/2.f);
        updateBeatInfo(time, bar, 1);
        updateBeatInfo(time, minim, 2);
        updateBeatInfo(time, crochet, 4);
        updateBeatInfo(time, quaver, 8);

    }

    void tap(){
        int time = ofGetElapsedTimeMillis();
        tapCount++;
        intervals.push_back(time - lastTime);
        lastTime = time;
        if(tapCount>3){
            intervals.erase(intervals.begin());
            avgBarMillis = accumulate(intervals.begin(), intervals.end(), 0) / intervals.size();
            BPM = 60 * 1000 / (float)avgBarMillis;
            bStart = true;
            ofLogNotice("ofxTapMachine")<<"new BPM : "<<BPM;
            bar.count = minim.count = crochet.count = quaver.count = 0;
        }

    }

    int getAverageIntervalMillis(){ return avgBarMillis; }
    float getBPM(){ return BPM; }
    bool isStart(){ return bStart; }
    void toggleStart(){ bStart=!bStart; }
};

