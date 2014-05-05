#include "testApp.h"

void testApp::setup()
{
    ofRegisterURLNotification(this);
    
    camWidth = 320;
    camHeight = 240;
    deviation = 25.0f;
    
    vidGrabber.listDevices();
    vidGrabber.setVerbose(true);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    int numPixels = camWidth * camHeight / 100;
    
    ofVec2f topLeft;
    topLeft.set(10, 10);
    
    ofVec2f bottomRight;
    bottomRight.set(310, 230);
    
    dragGridTopLeft.Setup(topLeft);
    dragGridBottomRight.Setup(bottomRight);
    
    int gridPixels = 30*20;
    wallData = vector<int>(gridPixels);
    colorData = vector<ofColor>(gridPixels);
    compareHues = vector<float>(3);
    
    //comment to manually sample hues
    compareHues[0] = 0.0f; //R
    compareHues[1] = 115.0f * 255.0f / 360.0f; //G
    compareHues[2] = 250.0f * 255.0f / 360.0f; //B
    
    colorSelectX = 0;
    colorSelectY = 0;
    
    //set to 0 to manually sample hues
    selectColorIndex = 3;
    
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
                compareHues[selectColorIndex] = getAverageHueAtPos(colorSelectX, colorSelectY, camWidth, pixels);
                cout << "hue " << selectColorIndex << ": " << compareHues[selectColorIndex] << " ";
                registerColor = false;
                ++selectColorIndex;
            }
        }
        else
        {
            bool isImageValid = true;
            for (int gridIndex = 0; gridIndex < skewGrid.grid.size(); ++gridIndex)
            {
                float camHue = getAverageHueAtPos(skewGrid.grid[gridIndex].x, skewGrid.grid[gridIndex].y, camWidth, pixels);
                bool isColorValid = false;
                for (int compareIndex = 0; compareIndex < compareHues.size(); ++compareIndex)
                {
                    if (isHueSimilar(camHue, compareHues[compareIndex]))
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
                    isImageValid = false;
                    //break;
                }
            }
            
            if(isImageValid)
            {
                string sData = "";
                for (int i = 0; i < wallData.size(); ++i)
                {
                    ostringstream ss;
                    ss << wallData[i];
                    sData = sData + ss.str();
                }
                
                if( sData.compare(lastData) != 0)
                {
                    lastData = sData;
                    
                    //fetch current local time
                    time_t rawtime;
                    struct tm * timeinfo;
                    time (&rawtime);
                    timeinfo = localtime (&rawtime);
                    string sTime = url_encode(asctime(timeinfo));
                    
                    sData = "curl \"http://hannesdeville.be/dev/pixelwall/webservice.php?id=thesecretid&data=" + sData + "&time=" + sTime + "\"";
                    system( (char*)sData.c_str());
                    cout << "system call: " << sData;
                }
            }
        }
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
    for (int i = 0; i < compareHues.size(); ++i)
    {
        ofColor clr;
        clr.setHsb(compareHues[i], 255.0f, 255.0f);
        ofSetColor(clr);
        ofRect(320, i * 22, 20, 20);
    }
    
    int drawPixelSize = 10;
    
    //draw the result
    for (int i = 0; i < wallData.size(); ++i)
    {
        ofColor clr;
        clr.setHsb(compareHues[wallData[i]], 255.0f, 255.0f);
        if(wallData[i] >= 0) ofSetColor(clr);
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

float testApp::getAverageHueAtPos(int x, int y, int width, unsigned char * pixels)
{
    float hueSum = 0;
    
    hueSum += getHueAtPos(x-1, y-1, width, pixels);
    hueSum += getHueAtPos(x  , y-1, width, pixels);
    hueSum += getHueAtPos(x+1, y-1, width, pixels);
    
    hueSum += getHueAtPos(x-1, y  , width, pixels);
    hueSum += getHueAtPos(x  , y  , width, pixels);
    hueSum += getHueAtPos(x+1, y  , width, pixels);
    
    hueSum += getHueAtPos(x-1, y-1, width, pixels);
    hueSum += getHueAtPos(x  , y-1, width, pixels);
    hueSum += getHueAtPos(x+1, y-1, width, pixels);
    
    //TODO: eliminate extreme values? : sort, drop first and last, divide by 7
    
    return hueSum / 9.0f;
}

float testApp::getHueAtPos(int x, int y, int width, unsigned char * pixels)
{
    return getColorAtPos(x  , y  , width, pixels).getHue();
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

bool testApp::isHueSimilar(float source, float target)
{
    //TODO: fix wrap around errors!
    float low = target - deviation;
    float high = target + deviation;
    return  (source >= low && source <= high) ||
            (source - 255.0f >= low && source - 255.0f <= high) ||
            (source + 255.0f >= low && source + 255.0f <= high);
}

string testApp::url_encode(const string &value)
{
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;
    
    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        }
        else if (c == ' ')  {
            escaped << '+';
        }
        else {
            escaped << '%' << setw(2) << ((int) c) << setw(0);
        }
    }
    
    return escaped.str();
}

