//
//  Recognition.h
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__Recognition__
#define __cvtest__Recognition__

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <genderDetection.h>
#include <Capture.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

#endif /* defined(__cvtest__Recognition__) */

// Function to detect faces in an image
//CvSeq* face_detect( IplImage* img );


void find_faces( IplImage* img, CvMemStorage* storage, CvHaarClassifierCascade* cascade, CvSeq* faces, float scale);
void report_faces(int start, int n, Ptr<FaceRecognizer> model);
bool same_face(CvRect* r, CvRect* r_last, IplImage* imgCamera, IplImage* imgCamera_last, int num, int num_last);
void show_message(int predict_result, CvRect* r, IplImage* &imgDrawn);