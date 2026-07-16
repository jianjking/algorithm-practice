#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "camera_capture.h"

using namespace std;
using namespace cv;

bool capture_frame(const string& save_path)
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Camera open failed." << endl;
        return false;
    }

    Mat frame;
    cap >> frame;

    if (frame.empty())
    {
        cout << "Frame capture failed." << endl;
        cap.release();
        return false;
    }

    bool ok = imwrite(save_path, frame);

    if (!ok)
    {
        cout << "Image save failed: " << save_path << endl;
        cap.release();
        return false;
    }

    cap.release();

    return true;
}