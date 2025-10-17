#pragma once

#include "ofMain.h"

#define GN 4

class glch
{
public:
    float x,y;
    float vx,vy;
    
    glch(float _x=18,float _y=100,float _vx=8,float _vy=0)
    {
        x=_x;
        y=_y;
        vx=_vx;
        vy=_vy;
    }
    
    void rndr()
    {
        ofSetColor(0,255,128,108);
        ofDrawLine(x-5,y,x+5,y);
        ofDrawLine(x-10,y,x+10,y);
        ofDrawLine(x-15,y,x+15,y);
        ofDrawLine(x-20,y,x+20,y);
        ofDrawLine(x-25,y,x+25,y);
        ofDrawLine(x-30,y,x+30,y);
        ofDrawLine(x-35,y,x+35,y);
        ofDrawLine(x-40,y,x+40,y);
        ofDrawLine(x-45,y,x+45,y);
    }
    
    void evolve()
    {
        x+=vx;
        y+=vy;
        float ww=ofGetWidth()*4;
        float hh=ofGetHeight();
        if(x>ww)
        {
            x-=ww;
            y=ofRandom(hh);
        }
        if(y>hh) y-=hh;
    }
};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

        ofVideoGrabber vg;
        int camw;
        int camh;
        
        string asc;
        ofTrueTypeFont fnt;
        ofTrueTypeFont f2;
        ofTrueTypeFont f1;
        
        string txt;
        char mode;
        string sym;
        int symctr;
        int frmctr;
        
        glch gx[GN];
        bool isglitch;
        bool isneo;
};

