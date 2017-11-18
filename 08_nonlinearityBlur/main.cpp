#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\person\)";
static const string strImg = imgPath + "girl001.jpg";

int g_nSizeMedian = 3;  // 必须是奇数
int g_nSizeBilateral = 3;
Mat g_outImgMedian;
Mat g_outImgBilateral;
Mat g_srcImg;

void on_medianBlur(int, void*);
void on_bilateralFilter(int, void*);

int main() {
    g_srcImg = imread(strImg);
    if (g_srcImg.empty()) { cout << "打开图像" << strImg << "失败！" << endl; return -1; }

    /***
     * 中值滤波
     * void medianBlur( InputArray src, OutputArray dst, int ksize );
     */
    on_medianBlur(0, nullptr);
    createTrackbar("kSize", "[3]中值滤波", &g_nSizeMedian, 50, on_medianBlur);

    /***
     * 双边滤波 有美颜效果！！！ 有美颜效果！！！ 有美颜效果！！！
     * void bilateralFilter( InputArray src, OutputArray dst,
     *                             int d, //Diameter of each pixel neighborhood that is used during filtering. If it is non-positive,it is computed from sigmaSpace.
     *                             double sigmaColor, //Filter sigma in the color space.
     *                             double sigmaSpace, //Filter sigma in the coordinate space.
     *                             int borderType = BORDER_DEFAULT );
     */
    on_bilateralFilter(0, nullptr);
    createTrackbar("kSize", "[4]双边滤波", &g_nSizeBilateral, 50, on_bilateralFilter);

    while((char)waitKey(0) != 'q');
    return 0;
}

void on_medianBlur(int, void*) {
    if (g_nSizeMedian%2 == 0)
        ++g_nSizeMedian;

    medianBlur(g_srcImg, g_outImgMedian, g_nSizeMedian);
    imshow("[3]中值滤波", g_outImgMedian);
}

void on_bilateralFilter(int, void*) {
    bilateralFilter(g_srcImg, g_outImgBilateral, g_nSizeBilateral
                            , (double)g_nSizeBilateral*g_nSizeBilateral
                            , (double)g_nSizeBilateral/2);
    imshow("[4]双边滤波", g_outImgBilateral);
}
