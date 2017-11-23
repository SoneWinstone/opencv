#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static const string strImg = imgPath + "corner3.jpg";

Mat g_src;
Mat g_temp;
Mat g_dst;
int g_nKSize = 3;
int g_nBlockSize = 3;
int g_lfHarrisK = 3;
int g_lfThresh = 20;
int g_lfMaxVal = 100;
int g_nThreshType = 0;

void on_change(int, void*);

int main() {
    g_src = imread(strImg);
    cvtColor(g_src, g_src, COLOR_BGR2GRAY);
    imshow("原始图", g_src);

    createTrackbar("邻域大小", "原始图", &g_nBlockSize, 20, on_change);
    createTrackbar("Sobel孔径", "原始图", &g_nKSize, 20, on_change);
    createTrackbar("Harris", "原始图", &g_lfHarrisK, 20, on_change);
    createTrackbar("阈值", "原始图", &g_lfThresh, 20, on_change);
    createTrackbar("最大阈值", "原始图", &g_lfMaxVal, 255, on_change);
    createTrackbar("阈值类型", "原始图", &g_nThreshType, 9, on_change);

    waitKey();
    return 0;
}

void on_change(int, void*) {
    /***
     * Harris 角点检测函数
     * void cornerHarris( InputArray src,   // CV_8UC1 or CV_32F
     *                          OutputArray dst, // CV_32FC1 size as src
     *                          int blockSize,  // Neighborhood size
     *                          int ksize,  // Aperture(孔径) parameter for the Sobel operator
     *                          double k, // Harris detector free parameter
     *                          int borderType = BORDER_DEFAULT );
     */
    g_lfHarrisK /= 10;
    if (g_nKSize%2 == 0)    g_nKSize += 1;
    if (g_nKSize > 31)      g_nKSize = 31;
    cornerHarris(g_src, g_temp, g_nBlockSize, g_nKSize, g_lfHarrisK);
    imshow("角点检测图", g_temp);
    /***
     * 对单通道数组应用固定阈值操作
     * 典型应用是对灰度图像进行阈值操作得到二值图像(compare( )函数也可以达到此目的)，或者是去掉噪声。例如过滤很小或很大象素值的图像点。
     * double threshold( InputArray src, OutputArray dst,
     *                         double thresh,
     *                         double maxval, // 当type为CV_THRESH_BINARY 或CV_THRESH_BINARY_INV 时的最大值
     *                         int type ); // cv::ThresholdTypes
     */
    if (g_nThreshType > 8) g_nThreshType = 16;
    if (g_nThreshType == 5) g_nThreshType = 4;
    if (g_nThreshType == 6) g_nThreshType = 7;
    threshold(g_temp, g_dst, g_lfThresh, g_lfMaxVal, g_nThreshType);
    imshow("效果图", g_dst);
}