/**
 * 这部分内容设计的专业知识比较多 原理部分可以多查资料
 */
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
//static const string strImg = imgPath + "DOTA2_cm.jpg";
static const string strImg = imgPath + "LOL_yaso.jpg";

int g_nSize = 3;
int g_nThreshold1 = 3;
int g_nThreshold2 = 1;
int g_nSizeLaplace = 1;
Mat g_srcImg;
Mat g_outTemp;
Mat g_outImgCanny;
Mat g_outImgSobel;
Mat g_outImgScharr;
Mat g_outImgLaplace;
Mat g_outImgColorCanny;

void getCanny();
void on_size(int, void*);
void on_thresh1(int, void*);
void on_thresh2(int, void*);
void on_laplace_size(int, void *);

int main() {
    g_srcImg = imread(strImg);
    imshow("原图", g_srcImg);
    g_outImgCanny = Mat(g_srcImg.size(), g_srcImg.type());
    /***
     * void Canny( InputArray image,
     *              OutputArray edges,
     *              double threshold1, // 第一个滞后性阈值
     *              double threshold2, // 第二个滞后性阈值 两个阈值的比例2:1 或 3:1
     *              int apertureSize = 3, // Sobel算子的孔径大小 3-7
     *              bool L2gradient = false );
     */
    createTrackbar("阈值1", "原图", &g_nThreshold1, 200, on_thresh1);
    createTrackbar("阈值2", "原图", &g_nThreshold2, 200, on_thresh2);
    // createTrackbar("Sobel孔径", "原图", &g_nSize, 7, on_size); // 孔径不用调 设成3效果比较好

    /***
     * 因为Sobel算子结合了高斯平滑和分化（differentiation），因此结果会具有更多的抗噪性。
     * 大多数情况下，我们使用sobel函数时，取【xorder = 1，yorder = 0，ksize = 3】来计算图像X方向的导数，【xorder = 0，yorder = 1，ksize = 3】来计算图像y方向的导数。
     *
     * Sobel 不用转成灰度图 可以直接在彩色图操作
     *
     * void Sobel( InputArray src, OutputArray dst,
     *                   int ddepth, // 输出图像的深度 根据src.depth()取相应的深度
     *                   int dx, // x方向上的差分阶数
     *                   int dy,
     *                   int ksize = 3, // Sobel核的大小
     *                   double scale = 1, // 计算导数时可选的缩放因子
     *                   double delta = 0,
     *                   int borderType = BORDER_DEFAULT );
     */
    /**
     * 若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F
     * 若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F
     * 若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F
     * 若src.depth() = CV_64F, 取ddepth = -1/CV_64F
     */
    g_outImgSobel.create(g_srcImg.size(), g_srcImg.type());
    g_outImgSobel = Scalar::all(0);
    Mat g_outImgSobelx = g_outImgSobel.clone();
    Mat g_outImgSobely = g_outImgSobel.clone();
    // 计算X方向梯度
    Sobel(g_srcImg, g_outImgSobelx, -1, 1, 0, 3);
    // 不是太理解这个
    // convertScaleAbs( g_outImgSobelx, g_outImgSobelx );//计算绝对值，并将结果转换成8位
    // 计算Y方向梯度
    Sobel(g_srcImg, g_outImgSobely, -1, 0, 1, 3);
    // 合并梯度
    addWeighted(g_outImgSobelx, 0.5, g_outImgSobely, 0.5, .0, g_outImgSobel);
    imshow("Sobel效果图X", g_outImgSobelx);
    imshow("Sobel效果图Y", g_outImgSobely);
    imshow("Sobel效果图", g_outImgSobel);

    /***
     * laplacian 得到的也是灰度图
     * void Laplacian( InputArray src, OutputArray dst,
     *                       int ddepth,
     *                       int ksize = 1,
     *                       double scale = 1,
     *                       double delta = 0,
     *                       int borderType = BORDER_DEFAULT );
     */
    createTrackbar("kSize", "原图", &g_nSizeLaplace, 9, on_laplace_size);

    /***
     * void Scharr( InputArray src, OutputArray dst, int ddepth,
     *                    int dx, int dy, double scale = 1, double delta = 0,
     *                    int borderType = BORDER_DEFAULT );
     * 相当于 Sobel(src, dst, ddepth, dx, dy, CV_SCHARR, scale, delta, borderType) ： CV_SCHARR = -1
     */
    Scharr(g_srcImg, g_outImgScharr, -1, 1, 0);
    imshow("Scharr效果图", g_outImgScharr);

    waitKey();
    return 0;
}

void on_size(int, void*) { getCanny(); }

void on_thresh1(int, void*) { getCanny(); }

void on_thresh2(int, void*) { getCanny(); }

void getCanny() {
    // Sobel 大小必须是3-7之间
    if (g_nSize < 3)
        g_nSize = 3;
    if (g_nSize % 2 == 0)
        g_nSize = g_nSize - 1;
    // 得到灰度边缘图像
    Canny(g_srcImg, g_outImgCanny, g_nThreshold1, g_nThreshold2, g_nSize);
    // g_outTemp = Mat(g_srcImg.size(), g_srcImg.type());
    // 转换成灰度图
    cvtColor(g_srcImg, g_outTemp, COLOR_BGR2GRAY); // cv::ColorConversionCodes
    // 降噪
    Mat gray;
    gray.create(g_outTemp.size(), g_outTemp.type());
    blur(g_outTemp, gray, Size(3, 3));

    //** 将输出图像的所有元素设置为0 不然图像可能不会发生变化 **
    g_outImgColorCanny = Scalar::all(0);
    Canny(gray, gray, g_nThreshold1, g_nThreshold2, g_nSize);
    // 使用Canny算子输出的边缘图作为掩码，来将原图拷到目标图中
    g_srcImg.copyTo(g_outImgColorCanny, gray);
    imshow("效果图", g_outImgCanny);
    imshow("彩色效果图", g_outImgColorCanny);
}

void on_laplace_size(int, void*) {
    // ksize 必须是正奇数
    if (g_nSizeLaplace%2 == 0)
        g_nSizeLaplace = g_nSizeLaplace + 1;

    Mat temp = Mat(g_srcImg.size(), CV_8UC(1));
    blur(g_srcImg, temp, Size(3, 3));
    Laplacian(temp, g_outImgLaplace, -1, g_nSizeLaplace);
    temp = Scalar::all(0);
    g_srcImg.copyTo(temp, g_outImgLaplace);
    // laplace 的彩色图不好看 还是显示灰度图吧
    // imshow("Laplace效果图", temp);
    imshow("Laplace效果图", g_outImgLaplace);
}