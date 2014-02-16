//
//  draw.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "draw.h"
#include <Recognition.h>


// Function to detect and draw any faces that is present in an image
IplImage* detect_and_draw( IplImage* img, CvSeq* faces, int scale)
{
    // Create two points to represent the face locations
    CvPoint pt1, pt2;
        // Loop the number of faces found.
        for( int i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            
            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }
    
    return img;
}

