#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat mat(400, 400, CV_8U, Scalar(1));
    imshow("test", mat);
    waitKey(0);
    return 0;
}