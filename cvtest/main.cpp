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


// Create a string that contains the exact cascade name
const char* cascade_name =
"/opt/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
/*    "haarcascade_profileface.xml";*/


// Function prototype for detecting and drawing an object from an image
void detect_and_draw( IplImage* image );


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

// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img )
{
    
    // Create memory for calculations
    static CvMemStorage* storage = 0;
    
    // Create a new Haar classifier
    static CvHaarClassifierCascade* cascade = 0;
    
    int scale = 1;
    
    // Create a new image based on the input image
    IplImage* temp = cvCreateImage( cvSize(img->width/scale,img->height/scale), 8, 3 );
    
    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;
    
    // Load the HaarClassifierCascade
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
    // Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return;
    }
    
    // Allocate the memory storage
    storage = cvCreateMemStorage(0);
    
    // Clear the memory storage which was used before
    cvClearMemStorage( storage );
    
    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {
        
        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                           1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                           cvSize(40, 40) );
        
        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
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
    }
    
    // Show the image in the window named "result"
    cvShowImage( "result", img );
    
    // Release the temp image created.
    cvReleaseImage( &temp );
}
