#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = "C:\\Users\\SoneWinstone\\Pictures\\opencv\\";
static const string pa = imgPath + "DOTA2_pa.jpg";
static const string strLogo = imgPath + "dota_logo.png";

int main() {
    Mat mat;
    mat = imread(pa);

    // 这里加载灰度图 等下和单通道混合就会变色
    Mat logo = imread(strLogo, 0);
    if (logo.empty()) { cout << "加载logo失败" << endl; return -1; }

    vector<Mat> channels;
    split(mat, channels);

    // 与通道做加权操作 0：blue 1：green 2：red
    Mat roi = channels.at(0)(Rect(mat.cols - logo.cols, mat.rows - logo.rows, logo.cols, logo.rows));
    addWeighted(roi, 1.0, logo, 0.5, 0.0, roi);

    // channels.at() 返回引用！
    /**
     * 直接输出都是灰度图
     */
//    imshow("blue: ", channels.at(0));
//    imshow("green: ", channels.at(1));
//    imshow("red: ", channels.at(2));

    // 混合通道
    merge(channels, mat);
    imshow("混合蓝色通道", mat);
    waitKey();
    return 0;
}