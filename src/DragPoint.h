//
//  DragPoint.h
//  PixelCam
//
//  Created by Hannes Devillé on 18/03/14.
//
//

#ifndef __PixelCam__DragPoint__
#define __PixelCam__DragPoint__

#include <iostream>
#include "ofMain.h"

class DragPoint
{
    
    bool _isDragging;
    
public:
    DragPoint();
    
    void Setup(ofVec2f startPos);
    void Update();
    void Draw();
    void MousePressed(int x, int y, int button);
    void MouseDragged(int x, int y, int button);
    void MouseReleased(int x, int y, int button);
    
    float radius;
    ofVec2f position;
};

#endif /* defined(__PixelCam__DragPoint__) */
