#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static string imgFolder = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static string strImg = imgFolder + "LOL_yaso.jpg";

int main() {
    /***
     * void remap( InputArray src,
     *                   OutputArray dst, // same size as map1 and the same type as src
     *                   InputArray map1, // 映射到(x, y) 或仅仅是x 的点  类型：CV_16SC2 ,CV_32FC1, or CV_32FC2.
     *                   InputArray map2, // 如果map1 是(x, y) map2为空
     *                   int interpolation, // Interpolation method (see cv::InterpolationFlags)
     *                   int borderMode = BORDER_CONSTANT,
     *                   const Scalar& borderValue = Scalar());
     */
    Mat src = imread(strImg);
    if (src.empty()) { cout << "读取" << strImg << "出错！" << endl; return -1; }
    imshow("原始图", src);
    Mat dst2 = Mat(src.size(), src.type());
    Mat dst3 = Mat(src.size(), src.type());
    Mat dst = Mat(src.size(), src.type());
    Mat mapX = Mat(src.size(), CV_32F); // 只映射X/Y
    Mat mapY = Mat(src.size(), CV_32F);
    Mat map = Mat(src.size(), CV_32FC2); // 同时映射(x, y) 双通道
    Mat map2 = Mat(src.size(), CV_32FC2);
    vector<Mat> channels;
    vector<Mat> channels2;
    // 分离通道
    split(map, channels);
    split(map2, channels2);
    for (int x = 0; x < src.cols; ++x) {
        for(int y = 0; y < src.rows; ++y) {
            mapX.at<float>(y, x) = static_cast<float>(src.cols - x); // X取反
            mapY.at<float>(y, x) = static_cast<float>(src.rows - y); // Y取反

            channels[0].at<float>(y, x) = static_cast<float>(src.cols - x); // X取反
            channels[1].at<float>(y, x) = static_cast<float>(y);

            channels2[0].at<float>(y, x) = static_cast<float>(x);
            channels2[1].at<float>(y, x) = static_cast<float>(src.rows - y); // Y取反
        }
    }
    // 合并通道
    merge(channels, map);
    merge(channels2, map2);
    // 做映射
    remap(src, dst, mapX, mapY, INTER_LINEAR);
    remap(src, dst2, map, Mat(), INTER_LINEAR);
    remap(src, dst3, map2, Mat(), INTER_LINEAR);

    imshow("映射图", dst);
    imshow("映射图2", dst2);
    imshow("映射图3", dst3);

    waitKey();
    return 0;
}