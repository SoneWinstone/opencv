/***
 * 腐蚀和膨胀指的是高亮度区域(白色)
 *  erode()和dilate()支持就地(in-place)运算：可以直接输出到输入上
 */
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static const string strImg = imgPath + "dota_logo.png";

int g_nKernelErode = 3;
int g_nKernelDilate = 3;
int g_nIterErode = 1;
int g_nIterDilate = 1;
Mat g_outImgErode;
Mat g_outImgDilate;
Mat g_srcImg;

void on_kernel_erode(int, void*);
void on_kernel_dilate(int, void*);
void on_iter_erode(int, void*);
void on_iter_dilate(int, void*);

int main() {
    g_srcImg = imread(strImg);
    /***
     * 获取自定义核
     * Mat getStructuringElement(int shape, // 形状 cv::MorphShapes
     *                           Size ksize, // 大小
     *                           Point anchor = Point(-1,-1)); // 锚点
     */
    /***
     * 膨胀
     * void dilate(
     *      InputArray src,
     *      OutputArray dst,
     *      InputArray kernel,
     *      Point anchor=Point(-1,-1),
     *      int iterations=1, // 迭代的次数
     *      int borderType=BORDER_CONSTANT, // 用于推断图像外部像素的某种边界模式
     *      int borderType=BORDER_CONSTANT, // 用于推断图像外部像素的某种边界模式
     *      const Scalar& borderValue=morphologyDefaultBorderValue()
     *  );
     */
    on_kernel_dilate(0, nullptr);
    createTrackbar("核", "膨胀效果图", &g_nKernelDilate, 10, on_kernel_dilate);
    createTrackbar("迭代次数", "膨胀效果图", &g_nIterDilate, 10, on_iter_dilate);
    /***
     * 腐蚀
     * void erode(
     *      InputArray src,
     *      OutputArray dst,
     *      InputArray kernel,
     *      Point anchor=Point(-1,-1),
     *      int iterations=1,
     *      int borderType=BORDER_CONSTANT,
     *      const Scalar& borderValue=morphologyDefaultBorderValue()
     *   );
     */
    on_kernel_erode(0, nullptr);
    createTrackbar("核", "腐蚀效果图", &g_nKernelErode, 10, on_kernel_erode);
    createTrackbar("迭代次数", "腐蚀效果图", &g_nIterErode, 10, on_iter_erode);

    waitKey();
    return 0;
}

void on_kernel_erode(int, void*) {
    /***
     * 核的大小要大于1 不然程序会挂掉
     */
    if (g_nKernelErode < 1)
        g_nKernelErode = 1;
    erode(g_srcImg, g_outImgErode
            , getStructuringElement(MORPH_RECT, Size(g_nKernelErode, g_nKernelErode), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterErode);
    imshow("腐蚀效果图" , g_outImgErode);
}

void on_iter_erode(int, void*) {
    erode(g_srcImg, g_outImgErode
            , getStructuringElement(MORPH_RECT, Size(g_nKernelErode, g_nKernelErode), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterErode);
    imshow("腐蚀效果图" , g_outImgErode);
}

void on_kernel_dilate(int, void*) {
    if (g_nKernelDilate < 1)
        g_nKernelDilate = 1;

    dilate(g_srcImg, g_outImgDilate
            , getStructuringElement(MORPH_RECT, Size(g_nKernelDilate, g_nKernelDilate), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterDilate);
    imshow("膨胀效果图" , g_outImgDilate);
}

void on_iter_dilate(int, void*) {
    dilate(g_srcImg, g_outImgDilate
            , getStructuringElement(MORPH_RECT, Size(g_nKernelDilate, g_nKernelDilate), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterDilate);
    imshow("膨胀效果图" , g_outImgDilate);
}
