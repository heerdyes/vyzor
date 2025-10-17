#pragma once

#include "ofMain.h"

#define GN 6
#define PWMI 6
#define NCTR 8
#define MAXRND 108
#define QLEN 8

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
    
    void rndr(bool isneo, bool isares)
    {
        if(isneo) ofSetColor(0,255,128,55);
        else if(isares) ofSetColor(255,88,11,55);
        else ofSetColor(255,255,255,55);

        ofDrawLine(x-5,y,x+5,y-1);
        ofDrawLine(x-10,y,x+10,y+1);
        ofDrawLine(x-20,y,x+20,y);
        ofDrawLine(x-40,y,x+40,y);
        ofDrawLine(x-80,y,x+80,y-1);
        ofDrawLine(x-160,y,x+160,y+1);
    }
    
    void evolve()
    {
        x+=vx;
        y+=vy;
        float ww=ofGetWidth()*PWMI;
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

        void cmdproc(string ln);
        void lstr(int ix, ofTrueTypeFont ttf, string lcb, float fsz, float x, float y, float xd, float yd);
        void rstr(int ix, ofTrueTypeFont ttf, string lcb, float fsz, float x, float y, float xd, float yd);

        ofVideoGrabber vg;
        int camw;
        int camh;
        
        string asc;
        string xsc;
        string num;
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
        bool isares;
        string cln;
        string host;
        int xr[NCTR];

        string quot[QLEN]={
            "there is no spoon.",
            "what is the matrix?",
            "some programs will be thinking soon",
            "follow the white rabbit...",
            "greetings, programs!",
            "codified likeness utility",
            "biodigital jazz, man. the ISOs",
            "programs are disappearing, castor."
        };
};
