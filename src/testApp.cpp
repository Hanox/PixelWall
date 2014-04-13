#include "testApp.h"

void testApp::setup()
{
    camWidth = 320;
    camHeight = 240;
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    int numPixels = camWidth * camHeight / 100;
    
    ofVec2f topLeft;
    topLeft.set(0, 0);
    
    ofVec2f bottomRight;
    bottomRight.set(100, 100);
    
    dragGridTopLeft.Setup(topLeft);
    dragGridBottomRight.Setup(bottomRight);
    
    wallData.data = vector<int>(skewGrid.grid.size());
}

void testApp::update()
{
	ofBackground(100,100,100);
    
    skewGrid.UpdateGrid(dragGridTopLeft.position, dragGridBottomRight.position, 20, 10);
    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
	if (bNewFrame)
    {
        //get the pixels from current video frame
        unsigned char * pixels = vidGrabber.getPixels();
        
        for (int i = 0; i<skewGrid.grid.size(); ++i)
        {
            colorData[i] = getColorAtPos(skewGrid.grid[i].x, skewGrid.grid[i].y, camWidth, pixels);
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw()
{
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
    vidGrabber.draw(0, 0);
    
    //draw grid
    dragGridTopLeft.Draw();
    dragGridBottomRight.Draw();
    skewGrid.Draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    dragGridTopLeft.MouseDragged(x, y, button);
    dragGridBottomRight.MouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    dragGridTopLeft.MousePressed(x, y, button);
    dragGridBottomRight.MousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    dragGridTopLeft.MouseReleased(x, y, button);
    dragGridBottomRight.MouseReleased(x, y, button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}

ofColor testApp::getColorAtPos(int x, int y, int width, unsigned char * pixels)
{
    int index = y * width * 3 + x * 3;
    ofColor clr;
    clr.r = pixels[index]/255.0f;
    clr.g = pixels[index+1]/255.0f;
    clr.b = pixels[index+2]/255.0f;
    return clr;
}
