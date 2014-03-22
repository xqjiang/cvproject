
//
//  genderDetection.cpp
//  cvtest
//
//  Created by Xueqian Jiang on 2/22/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "genderDetection.h"

void read_csv(string filename, vector<Mat>& imagess, vector<int>& labelss)
{
    ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, ';');
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            imagess.push_back(imread(path, 0));
            labelss.push_back(atoi(classlabel.c_str()));
        }
    }
}

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
        case 1:
            cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
            break;
        case 3:
            cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
            break;
        default:
            src.copyTo(dst);
            break;
    }
    return dst;
}

Ptr<FaceRecognizer> gender_detection(string fn_csv)
{
    string output_folder;
    
    //string fn_csv = string("/Users/xueqianjiang/Desktop/male.txt");
    
    // These vectors hold the images and corresponding labels.
    vector<Mat> images;
    vector<int> labels;
    
    // Read in the data. This can fail if no valid
    // input filename is given.
    try {
        read_csv(fn_csv, images, labels);
    } catch (Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    
    // this part will add in the EigenFaceRecognizer in order to in reduce the dimension further
    // int height = images[0].rows;
    //PCA model
    //Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    //train the PCA model and without loss of information
    //model->train(images, labels);
    //save the results of the train
    // model->save("eigenface.yml");
    //take out the feature values from the eigenfaces and then rank them from largest to smallest
    //Mat eigenvalues = model->getMat("eigenvalues");
    //take out the feature values from the model，eigenvectures and the eigenvalues are in the same order
    //Mat W = model->getMat("eigenvectors");
    //打算保留前121个特征向量，代码中没有体现原因，但选择121是经过斟酌的，首先，在我的实验中，"前121个特征值之和/所有特征值总和>0.97"；其次，121=11^2，可以将结果表示成一个11*11的2维图像方阵，交给fisherface去计算
    //  int xth = 121;
    //after PCA
    //vector<Mat> reduceDemensionimages;
    //choose the first xth eigenvalues and get rid of the rest
    // Mat evs = Mat(W, Range::all(), Range(0, xth));
    
    //for(int i=0;i<images.size();i++)
    //{
    //  Mat mean= model->getMat("mean");
    //subspaceProjection
    //Mat projection = subspaceProject(W, mean, images[i].reshape(1,1));
    //reduced dimensionality and save them
    //reduceDemensionimages.push_back(projection.reshape(1,sqrt(xth)));
    // }
    
    // Quit if there are not enough images for this demo.
    //     Ptr<FaceRecognizer> fishermodel = createFisherFaceRecognizer();
    //fishermodel->train(reduceDemensionimages,labels);
    
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    model->train(images, labels);
    return model;
}


int detect(Ptr<FaceRecognizer> model, string Image_filename) {
    Mat A = imread(Image_filename, 0);
    int prediction = model->predict(A);
    string result_message = format("Predicted class = %d.", prediction);
    cout << result_message<<endl;
    return prediction;
}

int detect_Id(Ptr<FaceRecognizer> model, string Image_filename) {
    Mat A = imread(Image_filename, 0);
    int prediction = model->predict(A);
    string result_message = format("Predicted Identity for id = %d.", prediction);
    cout << result_message<<endl;
    return prediction;
}

Ptr<FaceRecognizer> new_person_detection(string filename){
    Ptr<FaceRecognizer> LBPH_model = createLBPHFaceRecognizer();
    vector<Mat> images;
    vector<int> labels;
    
    try {
        read_csv(filename, images, labels);
    } catch (Exception& e) {
        cerr << "Error opening file \"" << filename << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    LBPH_model -> train(images, labels);
    return LBPH_model;
}
