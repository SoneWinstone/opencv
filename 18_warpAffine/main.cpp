#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static string imgFolder = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static string strImg = imgFolder + "LOL_yaso.jpg";

int main() {
    Mat src = imread(strImg);
    Mat dst = Mat::zeros(src.size(), src.type());
    Mat dst2 = Mat::zeros(src.size(), src.type());
    imshow("原图", src);
    /***
     * void warpAffine( InputArray src, OutputArray dst,
     *                        InputArray M, // 2*3 的变换矩阵
     *                        Size dsize, // 输出图像的尺寸
     *                        int flags = INTER_LINEAR, // 插值方法
     *                        int borderMode = BORDER_CONSTANT,
     *                        const Scalar& borderValue = Scalar());
     *
     * 类似函数对比：
     *  warpAffine() src和dst具有相同的数据类型，耗费资源更多
     *  cvGetQuadrangleSubPix() 可以精确的从8位图像中提取四边形到浮点数缓存区中，系统开销比较小
     */
    // 定义两组点 代表两个三角形
    Point2f srcTriAngle[3];
    Point2f dstTriAngle[3];

    Mat rotMat(2, 3, CV_32F);
    Mat warpMat(2, 3, CV_32F);

    srcTriAngle[0] = Point2f(0, 0);
    srcTriAngle[1] = Point2f(static_cast<float>(src.cols - 1), 0);
    srcTriAngle[2] = Point2f(0, static_cast<float>(src.rows - 1));

    dstTriAngle[0] = Point2f(static_cast<float>(src.cols * .0), static_cast<float>(src.rows * .33));
    dstTriAngle[1] = Point2f(static_cast<float>(src.cols * .65), static_cast<float>(src.rows * .35));
    dstTriAngle[2] = Point2f(static_cast<float>(src.cols * .5), static_cast<float>(src.rows * .8));
    // 得到仿射变换矩阵
    warpMat = getAffineTransform(srcTriAngle, dstTriAngle);
    warpAffine(src, dst, warpMat, Size(static_cast<int>(src.cols * 1.2), static_cast<int>(src.rows * 1.2)));

    imshow("warpAffine效果图", dst);
    /***
     * Mat getRotationMatrix2D( Point2f center, // 源图像的缩放中心
     *                                double angle, // 旋转角度 角度正值表示逆时针旋转(坐标原点是左上角)
     *                                double scale ); // 缩放系数
     */
    Point2f center = Point(dst.cols / 2, dst.rows / 2);
    // 顺时针旋转70°
    double angle = -70;
    // 缩放0.7倍
    double scale = 0.7;
    // 得到旋转缩放矩阵
    rotMat = getRotationMatrix2D(center, angle, scale);
    // 得出旋转缩放的图像
    warpAffine(dst, dst2, rotMat, dst.size());
    imshow("旋转缩放的warp", dst2);

    waitKey();
    return 0;
}