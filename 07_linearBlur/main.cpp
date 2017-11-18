#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\person\)";
static const string strImg = imgPath + "girl001.jpg";

int g_nSize = 3;
Mat g_outImgGaussian;
Mat g_outImgBox;
Mat g_srcImg;

void on_chgBoxKSize() {
    // 高斯的卷积必须是奇数 也可以单独在高斯滤波里改变
    if (g_nSize%2 == 0) {
        ++g_nSize;
        return;
    }

    boxFilter(g_srcImg, g_outImgBox, -1, Size(g_nSize, g_nSize));
    imshow("[1]方框滤波效果图", g_outImgBox);
}

void on_chgGuassianKSize() {
    GaussianBlur(g_srcImg, g_outImgGaussian, Size(g_nSize, g_nSize), 0, 0);
    imshow("[2]高斯滤波效果图", g_outImgGaussian);
}

/**
 * 一个trackBar控制两张图像
 */
void on_changed(int, void*) {
    on_chgBoxKSize();
    on_chgGuassianKSize();
}

int main() {
    /**
     * 方框滤波
     */
    Mat girl = imread(strImg);
    g_srcImg = girl.clone();
    // Mat outImg = Mat(girl.size(), girl.type());
    /***
     * void boxFilter( InputArray src, OutputArray dst,
     *                       int ddepth, 图像深度， -1时为src的深度
     *                       Size ksize, 卷积的大小
     *                       Point anchor = Point(-1,-1), 锚点（即被平滑的那个点）
     *                       bool normalize = true, 是否归一化
     *                       int borderType = BORDER_DEFAULT 一般不用管
     *                       );
     */
    imshow("原图", girl);
    // boxFilter(girl, g_outImg, -1, Size(3, 3), Point(-1, -1), false);
    // imshow("[1]方框滤波效果图", g_outImg);
    on_chgBoxKSize();
    createTrackbar("kSize", "原图", &g_nSize, 50, on_changed);

    /***
     * 均值滤波
     * void blur( InputArray src, OutputArray dst, Size ksize, Point anchor = Point(-1,-1), int borderType = BORDER_DEFAULT );
     * 在函数内部调用方框滤波
     *      boxFilter( src, dst, -1, ksize, anchor, true, borderType );
     * 没什么好说的
     */

    /***
     * 高斯滤波
     *  高斯低通滤波是模糊 这里的高斯滤波就是低通滤波
     *  高斯高通滤波是锐化
     *
     * 高斯模糊会比方框滤波平滑一些
     * void GaussianBlur( InputArray src, OutputArray dst, Size ksize,
     *                          double sigmaX,  核函数在X方向的的标准偏差
     *                          double sigmaY = 0,  核函数在Y方向的的标准偏差。若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。
     *                          int borderType = BORDER_DEFAULT );
     */
    on_chgGuassianKSize();

    waitKey();
    return 0;
}
