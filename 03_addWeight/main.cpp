#include <iostream>
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

static std::string imgPath = "C:\\Users\\SoneWinstone\\Pictures\\opencv\\";

int main() {
    Mat mat = imread(imgPath + "DOTA2_pa.jpg");
//    if (mat.empty()) { return 1; }
//    namedWindow("[1]pa");
//    imshow("[1]pa", mat);

    Mat logo = imread(imgPath + "dota_logo.png");
//    namedWindow("[2]logo");
//    imshow("[2]logo", logo);

    Mat roi;
    roi = mat(Rect(mat.cols - logo.cols, mat.rows - logo.rows, logo.cols, logo.rows));
//    roi = mat(Range(200, 200 + logo.cols), Range(200, 200 + logo.rows));

    addWeighted(roi, 0.5, logo, 0.3, 0., roi);
    namedWindow("[3]pa+logo");
    imshow("[3]pa+logo", mat);

    waitKey();
    return 0;
}