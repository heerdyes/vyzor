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

    // visual density from the processing-video ascii video example
    asc = string(" .`-_':,;^=+/\"|)\\<>)iv%xclrs{*}I?!][1taeo7zjLunT#JCwfy325Fp6mqSghVd4EgXPGZbYkOA&8U$@KHDBWNMR0Q");
    xsc = string(" .`-_':,;^=+/\"|)\\<>)iv%xclrs{*}I?!][1taeo7zjLunT#JCwfy325Fp6mqSghVd4EgXPGZbYkOA&8U$@KHDBWNMR0Q");
    sym = string("<^>v<^>v _ _ _ _ -\\|/--\\|/- lliivveeccoodde..bbllrr -/|\\-/|\\-");
    txt = string("");
    
    for(int i=0;i<GN;i++)
    {
        gx[i].y=ofRandom(ofGetHeight());
        gx[i].vx=ofRandom(222,255);
    }
    
    isglitch=true;
    isneo=false;
    isares=false;

    host+="<>";
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

void ofApp::rstr(ofTrueTypeFont ttf, string lcb, float fsz, float x, float y, float xd, float yd)
{
    int lsz=lcb.length();
    if(lsz==0) return;

    int xr=round(ofRandom(lsz+.5));
    xr=xr>=lsz?lsz-1:xr;
    float ayd=abs(yd);
    float axd=abs(xd);
    float dy=ofRandom(-ayd, ayd);
    float dx=ofRandom(-axd, axd);

    for(int i=0;i<lsz;i++)
    {
        float xx=ofGetWidth()-fsz*(lsz-i) - x + (i==xr?dx:0);
        float yy=y + (i==xr?dy:0);
        ttf.drawString(ofToString(lcb.at(i)), xx, yy);
    }
}

void ofApp::lstr(ofTrueTypeFont ttf, string lcb, float fsz, float x, float y, float xd, float yd)
{
    int lsz=lcb.length();
    if(lsz==0) return;

    int xr=round(ofRandom(lsz+.5));
    xr=xr>=lsz?lsz-1:xr;
    float ayd=abs(yd);
    float axd=abs(xd);
    float dy=ofRandom(-ayd, ayd);
    float dx=ofRandom(-axd, axd);

    for(int i=0;i<lsz;i++)
    {
        float xx=x + fsz*i + (i==xr?dx:0);
        float yy=y + (i==xr?dy:0);
        ttf.drawString(ofToString(lcb.at(i)), xx, yy);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    float xoff=(ofGetWidth()-camw)/2;
    float yoff=(ofGetHeight()-camh)/2;

    if(isneo)
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
    else if(isares)
    {
        ofPixelsRef pixelsRef = vg.getPixels();
        ofSetColor(255,88,11);
        for (int i = 0; i < camw; i+= 7)
        {
            for (int j = 0; j < camh; j+= 9)
            {
                float lightness = pixelsRef.getColor(i,j).getLightness();
                int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * xsc.size();
                fnt.drawString(ofToString(xsc[character]), xoff+i, yoff+8+j);
            }
        }
    }
    else
    {
        ofSetColor(255,255,255);
        vg.draw(xoff, yoff);
    }
    
    float dh=yoff+camh+33;
    string prmpt("|"+ofToString(sym[symctr]));
    prmpt+="|";
    lstr(f2, prmpt, 22, xoff, dh, 3, 1);
    lstr(f2, txt, 22, xoff+78, dh, 1, 1);
    
    float fsz=12;
    float rgap=20;

    // date and time
    string dt;
    dt+=ofToString(ofGetYear())+"_";
    dt+=ofToString(ofGetMonth(),2,'0')+"_";
    dt+=ofToString(ofGetDay(),2,'0');
    dt+=" ";
    dt+=ofToString(ofGetHours(),2,'0')+":";
    dt+=ofToString(ofGetMinutes(),2,'0')+":";
    dt+=ofToString(ofGetSeconds(),2,'0');
    dt+=" IST";
    lstr(f1, dt, fsz, 30, 30, 4, 4);

    // host
    string shost="HOST :: "+host;
    rstr(f1, shost, fsz, rgap, 30, 4, 4);

    // locator
    string loc="?/OU0/MWG0/SS0/EARTH0/IND0/BLR0/"+host+"0";
    lstr(f1, loc, fsz, 30, ofGetHeight()-20, 4, 4);

    // livecode.blr
    rstr(f1, "livecode.blr", fsz, rgap, ofGetHeight()-20, 4, 8);
    
    // glitching
    if(isglitch) for(int i=0;i<GN;i++) gx[i].rndr();
}

//////// shell! /////////
void ofApp::cmdproc(string ln)
{
    txt.clear();
    if(ln.size()==0) return;
    if(ln.size()>=2) if(ln.substr(0,2).compare("//")==0) return;

    size_t spi=ln.find(' ');
    string cmd;

    if(spi==string::npos)
    {
        // cmd with no params
        cmd=ln;
        if(cmd.compare("host")==0)
        {
            txt+="// host = "+host;
        }
        else
        {
            txt+="// define \""+cmd+"\"";
        }
    }
    else
    {
        // params present
        string cmd=ln.substr(0, spi);
        string par=ln.substr(spi+1);
        if(cmd.compare("host")==0)
        {
            txt+="// setting host to "+par+" ...";
            host=par;
        }
        else
        {
            txt+="// define \""+cmd+"\"";
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    cout<<key<<endl;

    if(key==3680) return;
    if(key==3681) return;
    if(key==1) return;

    // modes
    if(key==57345)
    {
        isglitch=!isglitch;
        return;
    }
    if(key==57344)
    {
        isneo=!isneo;
        if(isneo) isares=false;
        return;
    }
    if(key==57346)
    {
        isares=!isares;
        if(isares) isneo=false;
        return;
    }

    // text
    if(key==13) // enter
    {
        cmdproc(txt);
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
