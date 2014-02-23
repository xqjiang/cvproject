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

#include <Recognition.h>
#include <draw.h>
#include <FaceCollection.h>


// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
    
    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );
    
    CvCapture* capture =capture = cvCaptureFromCAM(-1); // capture from video device (Macbook iSight)
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 1000 );// set window size to 640
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 600 ); // set window size to 480
    
    // Create a sample image
    IplImage *img;
    IplImage *newImg;
    IplImage *lastimg;
    
    CvSeq* faces;
    CvSeq* lastfaces;
    
    //FaceCollection collection = FaceCollection("/Users/alexli/Documents/Academics 2014 Winter/cvtest/cvtest");
    
    while(1) {
        
        //*************************************************************************************/
        //Step 1: stream video. Video to images
        //*************************************************************************************/
        newImg = cvQueryFrame( capture );
        
        if( !newImg ) break;
        // flip image
        img = cvCreateImage(cvGetSize(newImg), IPL_DEPTH_8U, 1);
        img = newImg;
        cvFlip(img, img, 1);
        
        //*************************************************************************************/
        //Step 2: detect faces
        //*************************************************************************************/
        CvSeq* faces = face_detect(img);
        
        // When there are faces in the image, collect the image
        if (faces->total !=0) {
            //*************************************************************************************/
            //Step 3: classify faces and save them into groups
            //*************************************************************************************/
            //FaceCollection::update_collection(img, faces, collection);
         
            //**********************************************************************************/
            //Step 4: process the "full and unprocessed folders"
            //*************************************************************************************/
            //vector<IplImage> processed_images;
            //processed_images= FaceCollection::process_collection(collection);
            
            //*************************************************************************************/
            //Step 5: extraction information from processed facial images
            //*************************************************************************************/
            // vector<FaceRecord> recs = record(processed_images);
            
            //*************************************************************************************/
            //Step 6: upload the records
            //*************************************************************************************/
            // upload(recs);
            
        } else {
            //FaceCollection::reset_collection(collection);
        }
        
        // update
        lastimg = img;
        lastfaces = faces;
        
        //*************************************************************************************/
        //DEBUG and DISPLAY
        //*************************************************************************************/
        
        // Show the image in the window named "result"
        // box the faces in the image for display
        int scale = 1;
        img = detect_and_draw(img, faces, scale);
        cvShowImage( "result", img );
        
        // press escape to quit
        if( cvWaitKey(33) == 27 ) break;
    }
    
    cvReleaseCapture( &capture );
    
    // Release the image
    cvReleaseImage(&img);
    
    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");
    
    // return 0 to indicate successfull execution of the program
    return 0;
}