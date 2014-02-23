//
//  FaceCollection.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "FaceCollection.h"
#include "FaceCapture.h"

FaceCollection::FaceCollection (int picNumber, CvPoint location, bool oldFrame) {
    FaceNumber = picNumber;
    FaceLocation = location;
    Processed = oldFrame;
}

FaceCollection::FaceCollection () {
    
}

int FaceCollection::get_FaceNumber() {
    return FaceNumber;
}

CvPoint FaceCollection::get_FaceLocation() {
    return FaceLocation;
}

bool FaceCollection::get_Processed() {
    return Processed;
}


/*void FaceCollection::get_N_pictures(CvSeq* capture, CvSeq* faces, IplImage* imgCamera, IplImage* imgDrawn,int scale,CvRect* r){
 int j = 0;
 
 int i;
 while (j<15) {
 FaceCapture::capture_frame(capture, imgCamera);
 
 cvCopy(imgCamera, imgDrawn);
 
 find_faces(imgCamera, storage, cascade, faces, scale);
 
 // for each face found in the image
 for( i = 0; i < (faces ? faces->total : 0); i++ ){
 r = (CvRect*)cvGetSeqElem( faces, i ); // get the rect from the sequence
 // CvRect x = resizeRect(r, scale); // and resize it
 CvRect x = cvRect(r->x/scale, r->y/scale, r->width/scale, r->height/scale);
 r = &x;
 
 draw_face_rect(r, imgDrawn); // draw the rectange around the face on the imgDrawn
 crop_and_scale_face(imgCamera, imgFace, r);
 
 
 // from here, we need to save a couple images so we can crop out the features we want.
 // then we can do the filter2D stuff
 
 j++;
 
 char *name = new char[100];
 sprintf(name,"/Users/xueqianjiang/Desktop/opencv/img%d.jpg",j);
 
 cvSaveImage(name, imgFace);
 
 cvShowImage("Window", imgDrawn);
 }
 
 }
 
 
 void FaceCollection::FaceStorage(){
 char *name = new char[100];
 sprintf(name,"/Users/xueqianjiang/Desktop/opencv/img%d.jpg",j);
 
 }
 
 */



