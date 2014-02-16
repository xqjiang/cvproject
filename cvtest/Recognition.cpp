//
//  Recognition.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "Recognition.h"

// Create a string that contains the exact cascade name
const char* cascade_name =
"/opt/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
/*    "haarcascade_profileface.xml";*/


// Function to test whether a face is detected
CvSeq* face_detect( IplImage* img )
{   CvSeq* faces = 0;
    
    // Create memory for calculations
    static CvMemStorage* storage = 0;
    
    // Create a new Haar classifier
    static CvHaarClassifierCascade* cascade = 0;
    
    // Load the HaarClassifierCascade
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
    // Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
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
        faces = cvHaarDetectObjects( img, cascade, storage,
                                           1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                           cvSize(40, 40) );
    }
    
    return faces;
    
}