#include <iostream>
#include "opencv2/opencv.hpp"
 using namespace cv;
 using namespace std;
int backGroundKNN();
int minContourArea=5000;
int main() {
backGroundKNN();
}

int backGroundKNN()
{
    Mat frame;
    Mat background;
    Mat foreground;
    bool finish=false;
    int history=500;
    double dist2threshold=400.0;
    bool detectShadows=false;
    vector<vector<Point>> contours;
    namedWindow("Frame");
    namedWindow("Background");
    VideoCapture capture;
    capture.open(0);

    if(!capture.isOpened())
        return 1;

    Ptr<BackgroundSubtractorKNN>bgKNN=createBackgroundSubtractorKNN(history,dist2threshold,detectShadows);
    while(!finish)
    {
        if(!capture.read(frame))
            return 1;
        bgKNN->apply(frame,foreground);
        imshow("Foreground",foreground);
        bgKNN->getBackgroundImage(background);
        imshow("Background",background);
        erode(foreground,foreground,Mat());
        dilate(foreground,foreground,Mat());
        findContours(foreground,contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);
        if(contours.size() == 0)
        {
            //TODO: add code to notify the app
            return -1;
        }
        // Start checking each contour area and identify if breach was detected or not

        double cArea = 0.0;
        int largestContour = -1,i=0;
        Rect box;
        for(i=0;i<contours.size();i++)
        {


            const vector<Point>& c = contours[i];
            cArea = fabs(contourArea(Mat(c)));
            cout<<"the contour area is"<<cArea<<endl;
            if(cArea < minContourArea )
            {
                continue;
            }
            else
            {
                largestContour = i;
                box=boundingRect(contours[i]);

            }
        }
        if(-1 != largestContour && largestContour !=0)
        {
            const char * text="present";
//			if()
            // Draw the largest contour
            // Scalar color( 0, 0, 255 );
            // drawContours( retFrame, contours, largestContour, color,1,LINE_8, hierarchy );

            rectangle( frame, box,Scalar(255,255,0) );
            cout<<"the box area is\n"<<box.area();
            // imshow("retFrame",frameIn);
            char path[80]="/home/rob/Downloads/Breach/";
            std::cout<<"largest Contour = "<<largestContour<<"\n";

            cerr<<"Breachdetected"<<endl;
            sprintf(path,"%s%d%s",path,i++,".jpg");
            cout<<"Th path is \n"<<path;
            imwrite(path,frame);

        }
        //drawContours(frame,contours,-1,Scalar(0,255,255),2);
        imshow("original",frame);
        waitKey(1);
    }
}