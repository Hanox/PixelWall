//
//  DragPoint.cpp
//  PixelCam
//
//  Created by Hannes Devillé on 18/03/14.
//
//

#include "DragPoint.h"

DragPoint::DragPoint()
{
    
}

void DragPoint::Setup(ofVec2f startPos)
{
    position = startPos;
    radius = 5;
    _isDragging = false;
}

void DragPoint::MousePressed(int x, int y, int button)
{
    ofVec2f mouseVect;
    mouseVect.set(x,y);
    ofVec2f dir = position - mouseVect;
    float distance = dir.length();
    if(distance < radius)
    {
        _isDragging = true;
    }
}

void DragPoint::MouseDragged(int x, int y, int button)
{
    if(_isDragging)
    {
        ofVec2f mouseVect;
        mouseVect.set(x,y);
        position = mouseVect;
    }
}

void DragPoint::MouseReleased(int x, int y, int button)
{
    _isDragging = false;
}

void DragPoint::Update()
{
    
}

void DragPoint::Draw()
{
    if(_isDragging) ofSetColor(255, 255, 0);
    else ofSetColor(255, 0, 255);
    ofCircle(position, radius);
}