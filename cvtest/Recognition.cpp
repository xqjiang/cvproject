//
//  Recognition.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "Recognition.h"


void find_faces( IplImage* img, CvMemStorage* storage, CvHaarClassifierCascade* cascade, CvSeq* faces, float scale){
    // this function finds the faces and returns a sequence
    
    cvClearMemStorage( storage ); // Clear the memory storage which was used before
    IplImage* tmp = cvCreateImage(cvSize(cvGetSize(img).width*scale, cvGetSize(img).height*scale), img->depth, img->nChannels);
    
    cvResize(img, tmp);
    
    if( !cascade ){
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return;
    }// Check whether the cascade has loaded successfully. Else report and error and quit
    
    if( cascade )
    {
        float faceFraction = 1.0/16; // face can be a minimum size of 1/16 the size of the image
        int w = (int)(cvGetSize(tmp).width*faceFraction);
        int h = (int)(cvGetSize(tmp).height*faceFraction);
        faces = cvHaarDetectObjects( tmp, cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(w, h)); // create sequence of images for however many faces are detected
    }
    
    // resize all of the rects
    
    cvReleaseImage(&tmp);
    
}

bool same_face(CvRect* r, CvRect* r_last, IplImage* imgCamera, IplImage* imgCamera_last, int i, int k) {
    float distance = (std::max(i,k)+1.0)/(std::min(i,k)+1.0);
    // Find the dimensions of the face,and scale it if necessary
    int curr_left = r->x;
    //cout<<"curr_left"<<curr_left<<"\n";
    int curr_right = (r->x+r->width);
    //cout<<"curr_right"<<curr_right<<"\n";
    int last_left = r_last->x;
    //cout<<"last_left"<<last_left<<"\n";
    int last_right = (r_last->x+r_last->width);
    //cout<<"curr_right"<<last_right<<"\n";
    int diff = ((curr_left - last_left) + (curr_right - last_right))/2 * distance;
    //int img_wid = imgCamera->width;
    //cout<<"diff is: "<<diff<<"vs. width of "<<r->width<<"/n";
    return diff<(r->width)/4;
}

void report_faces(int start, int n, Ptr<FaceRecognizer> model) {
    const char* folder_name ="/Users/xueqianjiang/Desktop/Images";
    std::stringstream filename;
    int result;
    for (int i = start+1; i<=start+n; i++) {
        filename<< folder_name << "/img" << i << ".jpg";
        result = detect(model, filename.str());
    }
    
    // query database on the eigenface of the images
    // save the face visit in the database
}

// this will show the image on top of each rectangular face detected and then put into the prediction result
void show_message(int predict_result, CvRect* r, IplImage* &imgDrawn)
{
    //char* actual_text = "Prediction = %d"+predict_result.str();
    const char* actual_text = "testing";
	double hscale = 1.0;
	double vscale = 0.8;
	double shear = 0.2;
	int thickness = 2;
	int line_type = 8;
    
	CvFont font1;
	cvInitFont(&font1,CV_FONT_HERSHEY_DUPLEX,hscale,vscale,shear,thickness,line_type);
    cvPutText(imgDrawn, actual_text,  cvPoint(r->x+10,r->y+10),&font1, CV_RGB(0,0,250));
    
    cvNamedWindow("Drawing_and_Text", 1);
	cvShowImage("Drawing_and_Text", imgDrawn);
}
