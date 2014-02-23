//
//  FaceCollection.h
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__FaceCollection__
#define __cvtest__FaceCollection__

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <FaceCapture.h>


#endif /* defined(__cvtest__FaceCollection__) */

using namespace std;


// This class represents an object that contains the collection of facial rectangle pictures in the file system
// Each individual is assigned with one folder
// Each folder has one counter
// Each folder has a collection of facial pictures in a sequence, collected from a series of images
//

class FaceCollection {
    
    // Each individual's face is represented by a foloder of images, a counter and a boolean denoting whether this person's faces in the collection have been processed or not
    // For example, there may bbe 14 facial images saved in /img/021514_163432_001/ i.e. the guy came at Feb 15, 2014, 16:34:32. And the counter would be 14, i.e. he has appeared in 14 consecutive images. And the processed status would be "not processed"
    int FaceNumber;
    bool Processed;
    CvPoint FaceLocation;
    
    
public:
    FaceCollection (int picNumber, CvPoint location, bool oldFrame);
    
    FaceCollection ();
    
    /* This following function updates the collection on the following fronts:
     1) If the collection is full and no new faces, do nothing
     2) if the colleciton is not full and there are more images of the same people coming in, store them to the corresponding folders
     3) if there are new people showing up in the image, create new folders and store them
     4) update the counter list to keep track of the number of items in the folders. The fles in each folder could be named with counter at the end.
     */
    static void update_collection(IplImage* img, CvSeq* faces, FaceCollection collection);
    
    // process the folders in the collection and empty the collection - delee all and reset counters. This includes morphing and uploading info
    void get_N_pictures(CvSeq* capture, CvSeq* faces, IplImage* imgCamera, IplImage* imgDrawn,int scale,CvRect* r);
    
    vector<IplImage> static process_collection(FaceCollection collection);
    
    static void reset_collection(FaceCollection collection);
    
    int get_FaceNumber();
    
    CvPoint get_FaceLocation();
    
    bool get_Processed();
};
