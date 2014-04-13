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

void SkewGrid::UpdateGrid(ofVec2f topLeft, ofVec2f bottomRight, int nWidth, int nHeight)
{
    //clear
    grid.clear();
    grid = vector<ofVec2f>(nWidth*nHeight);
    
    float stepX = (bottomRight.x - topLeft.x) / (float) (nWidth - 1);
    float stepY = (topLeft.y - bottomRight.y) / (float) (nHeight - 1);
    
    for (int xval = 0; xval<nWidth; ++xval)
    {
        for (int yval = 0; yval<nHeight; ++yval)
        {
            int index = yval * nWidth + xval;
            ofVec2f vec;
            vec.set(topLeft.x + xval * stepX, bottomRight.y + yval * stepY);
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