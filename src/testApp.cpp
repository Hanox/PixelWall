#include "testApp.h"

void testApp::setup()
{
    ofRegisterURLNotification(this);
    
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
    
    int gridPixels = 30*20;
    wallData = vector<int>(gridPixels);
    colorData = vector<ofColor>(gridPixels);
    compareColors = vector<ofColor>(3);
    
    colorSelectX = 0;
    colorSelectY = 0;
    selectColorIndex = 0;
    registerColor = false;
}

void testApp::update()
{
	ofBackground(100,100,100);
    
    skewGrid.UpdateGrid(dragGridTopLeft.position, dragGridBottomRight.position, 30, 20);
    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
	if (bNewFrame)
    {
        //get the pixels from current video frame
        unsigned char * pixels = vidGrabber.getPixels();
        
        if(selectColorIndex < 3)
        {
            if (registerColor)
            {
                compareColors[selectColorIndex] = getColorAtPos(colorSelectX, colorSelectY, camWidth, pixels);
                registerColor = false;
                ++selectColorIndex;
            }
        }
        else
        {
            bool isImageValid = false;
            for (int gridIndex = 0; gridIndex < skewGrid.grid.size(); ++gridIndex)
            {
                ofColor camColor = getColorAtPos(skewGrid.grid[gridIndex].x, skewGrid.grid[gridIndex].y, camWidth, pixels);
                bool isColorValid = false;
                for (int compareIndex = 0; compareIndex < compareColors.size(); ++compareIndex)
                {
                    if (IsColorSimilar(camColor, compareColors[compareIndex]))
                    {
                        wallData[gridIndex] = compareIndex;
                        isColorValid = true;
                        //break;
                    }
                }
                
                //if we encounter an invalid color we invalidate the entire image
                if (!isColorValid)
                {
                    wallData[gridIndex] = -1;
                    //isImageValid = false;
                    //break;
                }
            }
        }
        
        //if the image is valid we save the new image to the server!
        //one solution is to keep the file(s) locally and upload them using ofxFTP
        
        //OR using PHP
        //1. Authenticate (LOGIN) - PHP call
        
        //2. Check if login was succesfull (ASYNC?)
        
        //3. Write the updated data to the server - PHP Call
        
        //4. Check if write was succesfull (otherwise keep locally?)
    }
    
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofSetHexColor(0xffffff);
    vidGrabber.draw(0, 0);
    
    //draw grid
    dragGridTopLeft.Draw();
    dragGridBottomRight.Draw();
    skewGrid.Draw();
    
    //draw the selected colors
    for (int i = 0; i < compareColors.size(); ++i)
    {
        ofSetColor(compareColors[i]);
        ofRect(320, i * 22, 20, 20);
    }
    
    int drawPixelSize = 10;
    
    //draw the result
    for (int i = 0; i < wallData.size(); ++i)
    {
        if(wallData[i] >= 0) ofSetColor(compareColors[wallData[i]]);
        else ofSetColor(0, 255, 255);
        ofRect( (i % 30) * drawPixelSize, 240 + (19-(i/30))*drawPixelSize, drawPixelSize, drawPixelSize);
    }
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
    
    colorSelectX = x;
    colorSelectY = y;
    registerColor = true;
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

void testApp::urlResponse(ofHttpResponse & response)
{
    
}

ofColor testApp::getColorAtPos(int x, int y, int width, unsigned char * pixels)
{
    int index = y * width * 3 + x * 3;
    ofColor clr;
    clr.r = pixels[index];
    clr.g = pixels[index+1];
    clr.b = pixels[index+2];
    return clr;
}

bool testApp::IsColorSimilar(ofColor source, ofColor target)
{
    int deviation = 50;
    return  source.r > target.r - deviation && source.r < target.r + deviation &&
            source.g > target.g - deviation && source.g < target.g + deviation &&
            source.b > target.b - deviation && source.b < target.b + deviation;
}

