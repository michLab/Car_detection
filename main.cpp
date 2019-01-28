#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/features2d.hpp>
#include <math.h>

using namespace std;
using namespace cv;

int main()
{
    // Load an cascadeclassifier xml file:
    string car_cascade_name = "haarcascade_car.xml";
    CascadeClassifier car_cascade;
    car_cascade.load(car_cascade_name);

    // Load a video from file:
    Mat frame;
    VideoCapture cap;
    string video_name = "cars.avi";
    if (!cap.open(video_name))
    {
        cout << "Cannot open the video file " << video_name << endl;
    }

    // Do things with this video:
    Mat frame_resized; // for resized video frame
    Mat gray; // for gray, resized video
    while (cap.read(frame))
    {
        resize(frame, frame_resized, Size(0,0), 0.5, 0.5);
        //imshow("Original size", frame);
        imshow("Resized", frame_resized);
        cvtColor(frame_resized, gray, COLOR_BGR2GRAY);
        // Find cars using classifier:
        vector<Rect> cars;
        car_cascade.detectMultiScale(gray, cars, 1.4, 2);
        if (cars.empty() == true)
        {
            cout << "No cars found" << endl;
            continue;
        }
        else
        {
            cout << cars.size() << " car(s) found" << endl;
            imshow("Cars", frame_resized);
        }
        for (auto elem : cars)
        {
            Rect car_roi;
            car_roi.x = elem.x;
            car_roi.y = elem.y;
            car_roi.width = elem.width;
            car_roi.height = elem.height;

            rectangle(frame_resized, Point(car_roi.x,car_roi.y),
                      Point(car_roi.x + car_roi.width,
                            car_roi.y + car_roi.height),
                      Scalar(127,0,255),2);
            imshow("Cars", frame_resized);
        }

        int k = waitKey(1);
        if (k == 27)
        {
           break;
        }
    }

    return 0;
}
