#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "SkewGrid.h"
#include "DragPoint.h"
#include "WallData.h"

class testApp : public ofBaseApp
{
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofColor getColorAtPos(int x, int y, int camWidth, unsigned char * pixels);

    ofVideoGrabber vidGrabber;
    int camHeight;
    int camWidth;
    SkewGrid skewGrid;
    DragPoint dragGridTopLeft;
    DragPoint dragGridBottomRight;
    WallData wallData;
    vector<ofColor> colorData;
    vector<ofColor> compareColors;
};
