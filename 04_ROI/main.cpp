#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static std::string imgPath = "C:\\Users\\SoneWinstone\\Pictures\\opencv\\";

int main() {
    Mat mat = imread(imgPath + "DOTA2_pa.jpg");
//    if (mat.empty()) { return 1; }

    Mat logo = imread(imgPath + "dota_logo.png");

    Mat roi;
    roi = mat(Rect(mat.cols - logo.cols, mat.rows - logo.rows, logo.cols, logo.rows));

    Mat mask = imread(imgPath + "dota_logo.png", 0);
    logo.copyTo(roi, mask);

//    addWeighted(roi, 0.5, logo, 0.3, 0.0, roi);

    namedWindow("[3]pa+logo");
    imshow("[3]pa+logo", mat);

    waitKey();
    return 0;
}