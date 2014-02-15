//
//  main.cpp
//  opencvtest
//
//  Created by Xueqian Jiang on 1/28/14.
//  Copyright (c) 2014 Xueqian Jiang. All rights reserved.
//

// include the necessary libraries
#include <iostream>
#include <opencv2/opencv.hpp>
// Sample Application to demonstrate how Face detection can be done as a part of your source code.

// Include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <draw.h>

IplImage* crop( IplImage* src,  CvRect roi);

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
    
    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );
    
    CvCapture* capture =capture = cvCaptureFromCAM(-1); // capture from video device (Macbook iSight)
    
    // Create a sample image
    IplImage *img;
    IplImage *newImg;
    
    while(1) {
        newImg = cvQueryFrame( capture );
        if( !newImg ) break;
        // flip image
        img = cvCreateImage(cvGetSize(newImg), IPL_DEPTH_8U, 1);
        img = newImg;
        cvFlip(img, img, 1);
        
        detect_and_draw(img);
        
        char c = cvWaitKey(33); // press escape to quit
        if( c == 27 ) break;
        
    }
    
    cvReleaseCapture( &capture );
    
    // Release the image
    cvReleaseImage(&img);
    
    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");
    
    // return 0 to indicate successfull execution of the program
    return 0;
}
