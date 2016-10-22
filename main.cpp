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
    /// Draw contours
    //Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    //Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    double mydata[1];
    Mat drawing = Mat(1,1, CV_64F, mydata);
    drawing = Mat::zeros(canny_output.size(),CV_8UC3);
    for( int i = 0; i< contours.size(); i++ )
    {
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        Scalar color = Scalar(0,0,255);
       // drawContours( inv, contours, i,color , 2, 8, hierarchy, 0, Point() );
        //drawContours(inv,contours,i,color,3);
        drawContours(drawing, contours, i,color , 1, 1, hierarchy, 0, Point() );
    }
    //drawContours(inv,contours,,);

    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );



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
