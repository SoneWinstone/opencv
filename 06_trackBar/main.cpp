#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static const string strPa = imgPath + "DOTA2_pa.jpg";

int g_nBrightVal = 100; // 亮度
int g_nContrastVal = 0; // 对比度
Mat g_srcImg;
Mat g_dstImg;

/**
 * 亮度对比度 响应函数
 *
 * 亮度对比度计算公式：
 *    g(x) = f(x) + n = (x, y) * brigh * % + contrast
 */
void on_lightAndContrastChanged(int) {
    for (int x = 0; x < g_srcImg.cols; ++x) {
        for (int y = 0; y < g_srcImg.rows; ++y) {
            for (int i = 0; i < 3; ++i) {
                /**
                 * 这里必须是(y, x) 先行后列 不然程序会崩溃
                 * uchar x = saturate_cast<uchar>(n) 防止值越界 0 <= x <= UCHAR_MAX
                 */
                g_dstImg.at<Vec3b>(y, x)[i] = saturate_cast<uchar>(g_srcImg.at<Vec3b>(y, x)[i] * g_nBrightVal * 0.01 + g_nContrastVal);
            }
        }
    }

    imshow("PA_效果图", g_dstImg);
}

int main() {
    g_srcImg = imread(strPa);
    namedWindow("PA");
    imshow("PA", g_srcImg);

//    g_dstImg = Mat::zeros(g_srcImg.size(), g_srcImg.type());
    g_dstImg = g_srcImg.clone();
    namedWindow("PA_效果图", WindowFlags::WINDOW_AUTOSIZE);

    // 调用一次回调函数 显示效果图 不然效果图是灰的
    on_lightAndContrastChanged(0);

    cvCreateTrackbar("亮度", "PA_效果图", &g_nBrightVal, 300, on_lightAndContrastChanged);
    cvCreateTrackbar("对比度", "PA_效果图", &g_nContrastVal, 100, on_lightAndContrastChanged);

    // 获取当前轨迹条位置
    int b = getTrackbarPos("亮度", "PA_效果图");
    int c = getTrackbarPos("对比度", "PA_效果图");
    cout << "bright : " << b << endl;
    cout << "contrast : " << c << endl;

    waitKey();
    return 0;
}