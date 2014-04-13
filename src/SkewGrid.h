//
//  SkewGrid.h
//  PixelCam
//
//  Created by Hannes Devillé on 17/03/14.
//
//

#ifndef __PixelCam__SkewGrid__
#define __PixelCam__SkewGrid__

#include <iostream>
#include "ofMain.h"

class SkewGrid
{
    
public:
    SkewGrid();
    
    void Draw();
    
    void UpdateGrid(ofVec2f topLeft, ofVec2f bottomRight, int nWidth, int nHeight);
    vector<ofVec2f> grid;
};

#endif /* defined(__PixelCam__SkewGrid__) */
