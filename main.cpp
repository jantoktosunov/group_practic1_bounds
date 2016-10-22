#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
Mat src, src_gray;
Mat inv;

void thresh_callback(int, void* )
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( inv, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );



}

int main(int argc, char** argv) {

    /// Load an image
    src = imread( argv[1] );

    if( !src.data )
    { return -1; }

    /// Convert it to gray

    cvtColor( src, src_gray, CV_BGR2GRAY );

    src_gray = src_gray > 128; // Tresholding – Определяем порог
    imshow("",src_gray);
    bitwise_not(src_gray,inv);
    imshow("INV",inv);
    //createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback(0,0);

    waitKey(0);
    return(0);
}