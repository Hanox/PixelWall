//
//  SkewGrid.cpp
//  PixelCam
//
//  Created by Hannes Devillé on 17/03/14.
//
//

#include "SkewGrid.h"
SkewGrid::SkewGrid()
{
    grid = vector<ofVec2f>();
}

void SkewGrid::UpdateGrid(ofVec2f topLeft, ofVec2f topRight, ofVec2f bottomLeft, ofVec2f bottomRight, int nWidth, int nHeight)
{
    ofVec2f lefttbStep = (bottomLeft - topLeft) / nHeight;
    ofVec2f righttbStep = (bottomRight - topRight) / nHeight;
    
    //clear
    grid.clear();
    grid = vector<ofVec2f>(nWidth*nHeight);
    
    for (int xval = 0; xval<nWidth; ++xval)
    {
        for (int yval = 0; yval<nHeight; ++yval)
        {
            ofVec2f leftStart = topLeft + yval * lefttbStep;
            ofVec2f rightEnd = topRight + yval * righttbStep;
            ofVec2f vec = leftStart + (rightEnd - leftStart) * ((float)xval/(float)nWidth);
            
            int index = yval * nWidth + xval;
            grid[index] = vec;
        }
    }
}

void SkewGrid::Draw()
{
    //Draw Corners
    
    
    //Draw Grid
    for (int i=0; i<grid.size(); ++i)
    {
        ofSetColor(255, 255, 255);
        ofRect(grid[i].x, grid[i].y, 1, 1);
    }
}