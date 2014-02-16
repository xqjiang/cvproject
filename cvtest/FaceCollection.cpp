//
//  FaceCollection.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "FaceCollection.h"

    FaceCollection::FaceCollection (vector<string> folders, vector<int> counters, string r) {
        FaceFolders = folders;
        FaceCounters = counters;
        root = r;
    }
    
    FaceCollection::FaceCollection (string r) {
        root = r;
    }
    
    static void update_collection(IplImage* img, CvSeq* faces, FaceCollection& collection) {
        
    }
    
vector<string> FaceCollection::get_folders() {
        return FaceFolders;
    }
    
    vector<int> FaceCollection::get_counters() {
        return FaceCounters;
    }
    
    string FaceCollection::get_root() {
        return root;
    }