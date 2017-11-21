/***
 * OpenCV中的霍夫线变换有如下三种：
 *  <1>标准霍夫变换（StandardHough Transform，SHT），由HoughLines函数调用。
 *  <2>多尺度霍夫变换（Multi-ScaleHough Transform，MSHT），由HoughLines函数调用。
 *  <3>累计概率霍夫变换（ProgressiveProbabilistic Hough Transform，PPHT），由HoughLinesP函数调用。
 */
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\building\)";
static const string strImg = imgPath + "line.jpg";
static const string strImgCircle = imgPath + "circle2.jpg";

int g_nThresholdLines = 100;
int g_nMinLen = 10;
Mat g_src;
Mat g_grayLines;
Mat g_dstLines;
Mat g_dstLinesP;

void on_lines_threshold(int, void*);
void on_linesP(int, void *);
void lines();

int main() {
    g_src = imread(strImg);
    if (g_src.empty()) { cout << "读取图像失败！" << endl; exit(-1); }
    Mat g_srcCircle = imread(strImgCircle);
    g_grayLines = Mat(g_src.size(), g_src.type());
    // 边缘检测
    Canny(g_src, g_grayLines, 100, 150);
    /***
     * void HoughLines( InputArray image, OutputArray lines,
     *                        double rho, // 以像素为单位的距离精度
     *                        double theta, // 以弧度为单位的角度精度
     *                        int threshold, // 阈值 超过此值的点才会被识别为线段
     *                        double srn = 0, double stn = 0, // 多尺度霍夫变换会用到
     *                        double min_theta = 0, double max_theta = CV_PI );
     */
    imshow("边缘检测图", g_grayLines);
    createTrackbar("阈值", "边缘检测图", &g_nThresholdLines, 500, on_lines_threshold);

    /***
     * void HoughLinesP( InputArray image, OutputArray lines,
     *                         double rho, double theta, int threshold,
     *                         double minLineLength = 0, // 表示最短线段的长度 低于这个值的线段不显示
     *                         double maxLineGap = 0 ); // 允许将同一行点与点之间连接起来的最大的距离
     */
    createTrackbar("最短值", "边缘检测图", &g_nMinLen, 100, on_linesP);

    /**
     * void HoughCircles( InputArray image, OutputArray circles,
     *                         int method, // cv::HoughModes 只有HOUGH_GRADIENT可用
     *                         double dp, // 用于检测圆心的累加器图像的分辨率与输入图像之比的倒数
     *                         double minDist, // 最小半径
     *                         double param1 = 100, double param2 = 100,
     *                         int minRadius = 0, int maxRadius = 0 );
     */
    vector<Vec3f> points;
    Mat dstCircle;
    cvtColor(g_srcCircle, dstCircle, COLOR_BGR2GRAY);
    GaussianBlur(dstCircle, dstCircle, Size(5, 5), 2, 2);
//    imshow("圆灰度图", dstCircle);
    HoughCircles(dstCircle, points, HOUGH_GRADIENT, 1.0, 10);
    // 在图中绘制出圆
    for( size_t i = 0; i < points.size(); i++ )
    {
        Point center(cvRound(points[i][0]), cvRound(points[i][1]));
        int radius = cvRound(points[i][2]);
        //绘制圆心
        circle(g_srcCircle, center, 3, Scalar(0, 255, 0), -1, 8, 0 );
        //绘制圆轮廓
        circle(g_srcCircle, center, radius, Scalar(0, 0, 255), 3, 8, 0 );
    }
    imshow("霍夫圆变换", g_srcCircle);

    waitKey();
    return 0;
}

void on_lines_threshold(int, void*) {
    lines();
}

void lines() {
    vector<Vec2f> lines;
    // 对灰度图进行霍夫变换
    HoughLines(g_grayLines, lines, 1, CV_PI/180, g_nThresholdLines);
    // 将灰度图转成BGR图以显示彩色线条
    cvtColor(g_grayLines, g_dstLines, COLOR_GRAY2BGR);
    // 画出线段
    for (auto i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(g_dstLines, pt1, pt2, Scalar(255, 0, 0), 1, LINE_AA); // Scalar(x, x, x) 颜色的表示
    }
    imshow("效果图", g_dstLines);
}

void on_linesP(int, void*) {
    vector<Vec4i> lines;
    // 对灰度图进行霍夫变换
    HoughLinesP(g_grayLines, lines, 1, CV_PI/180, g_nThresholdLines, g_nMinLen);
    // 将灰度图转成BGR图以显示彩色线条
    cvtColor(g_grayLines, g_dstLinesP, COLOR_GRAY2BGR);
    // 画出线段
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line(g_dstLinesP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, LINE_AA);
    }
    imshow("效果图2", g_dstLinesP);
}