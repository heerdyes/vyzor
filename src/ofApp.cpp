#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0,0,0);
    ofSetWindowTitle("vyzor");

    camw = 1280;
    camh = 720;
    mode='c'; // 'a'
    frmctr=0;

    vg.setVerbose(true);
    vg.setup(camw, camh);

    fnt.load("OCRA", 9);
    f1.load("OCRA", 12);
    f2.load("OCRA", 22);
    symctr=0;

    asc = string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
    sym = string("<^>v<^>v _ _ _ _ -\\|/--\\|/- lliivveeccoodde..bbllrr -/|\\-/|\\-");
    txt = string("");
    
    for(int i=0;i<GN;i++)
    {
        gx[i].y=ofRandom(ofGetHeight());
        gx[i].vx=ofRandom(144,216);
    }
    
    isglitch=true;
    isneo=false;
}

//--------------------------------------------------------------
void ofApp::update()
{
    vg.update();
    
    if(frmctr%10==0)
    {
        symctr=(symctr+1)%sym.size();
    }
    
    for(int i=0;i<GN;i++)
    {
        gx[i].evolve();
    }
    
    frmctr++;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    float xoff=(ofGetWidth()-camw)/2;
    float yoff=(ofGetHeight()-camh)/2;

    if(!isneo)
    {
        ofSetColor(255,255,255);
        vg.draw(xoff, yoff);
    }
    else
    {
        ofPixelsRef pixelsRef = vg.getPixels();
        ofSetColor(11,222,22);
        for (int i = 0; i < camw; i+= 7)
        {
            for (int j = 0; j < camh; j+= 9)
            {
                float lightness = pixelsRef.getColor(i,j).getLightness();
                int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asc.size();
                fnt.drawString(ofToString(asc[character]), xoff+i, yoff+8+j);
            }
        }
    }
    
    float dh=yoff+camh+33;
    f2.drawString("|", xoff, dh);
    f2.drawString(ofToString(sym[symctr]), xoff+22, dh);
    f2.drawString("|", xoff+44, dh);
    f2.drawString(txt, xoff+78, dh);
    
    // date and time
    string dt="OU0/MWG0/SS0/EARTH0/IND0/BLR0 :: ";
    dt+=ofToString(ofGetYear());
    dt+=ofToString(ofGetMonth());
    dt+=ofToString(ofGetDay());
    dt+="_";
    dt+=ofToString(ofGetHours());
    dt+=ofToString(ofGetMinutes());
    dt+=ofToString(ofGetSeconds());
    f1.drawString(dt, 20,30);
    
    // glitching
    if(isglitch) for(int i=0;i<GN;i++) gx[i].rndr();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    cout<<key<<endl;

    // modes
    if(key==57345)
    {
        isglitch=!isglitch;
        return;
    }
    if(key==57344)
    {
        isneo=!isneo;
        return;
    }

    // text
    if(key==13) // enter
    {
        txt=string("");
    }
    else if(key==8)
    {
        if(txt.length()>0) txt.pop_back();
    }
    else
    {
        txt+=(char)key;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
