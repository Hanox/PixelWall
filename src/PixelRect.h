//
//  PixelRect.h
//  PixelCam
//
//  Created by Hannes Devillé on 21/03/14.
//
//

#ifndef __PixelCam__PixelRect__
#define __PixelCam__PixelRect__

#include <iostream>
#include "ofMain.h"
#include "WallData.h"

class PixelRect
{
    
public:
    PixelRect();
    
    void Setup(WallData wallData);
    void Update();
    void Draw();
};

#endif /* defined(__PixelCam__PixelRect__) */
