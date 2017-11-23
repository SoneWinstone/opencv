#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

static string imgFolder = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static string strImg = imgFolder + "LOL_yaso.jpg";

Mat g_src;
Mat g_temp;
Mat g_dst;

int main() {
//----------------------------------------------------第一部分 SURF绘制关键点---------------------------------------------------
    g_src = imread(strImg);
    if (g_src.empty()) { cout << "读取" << strImg << "失败！" << endl; return -1; }
    imshow("原始图", g_src);
    /***
     *  Ptr<SURF> create(double hessianThreshold=100, // Threshold for hessian keypoint detector
     *                        int nOctaves = 4, // Number of pyramid octaves(金字塔振幅频率) the keypoint detector
     *                        int nOctaveLayers = 3, // Number of octave layers within each octave
     *                        bool extended = false,
     *                        bool upright = false);
     */
    // OpenCV3.x 创建SURF的方式跟之前2.x的时候不同
    Ptr<SURF> surf;
    surf = SURF::create(1500);
    /***
     * 检测关键点，存到keypoints中
     * void detect( InputArray image,
     *                 CV_OUT std::vector<KeyPoint>& keypoints,
     *                 InputArray mask=noArray() );
     */
    vector<KeyPoint> points;
    surf->detect(g_src, points);
    // 绘制关键点
    drawKeypoints(g_src, points, g_dst/*, Scalar(255, 0, 0)*/);

    imshow("效果图", g_dst);
//--------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------第二部分 利用warpAffine获得变形后的图像-------------------------------------------
//    Mat img2 = Mat::zeros(g_src.size(), g_src.type());
    Mat img2 = imread(imgFolder + "SURF.jpg");

    Point2f srcTriAngle[3];
    Point2f dstTriAngle[3];

    Mat rotMat(2, 3, CV_32F);
    Mat warpMat(2, 3, CV_32F);

    srcTriAngle[0] = Point2f(0, 0);
    srcTriAngle[1] = Point2f(static_cast<float>(g_src.cols - 1), 0);
    srcTriAngle[2] = Point2f(0, static_cast<float>(g_src.rows - 1));

    dstTriAngle[0] = Point2f(static_cast<float>(g_src.cols * .0), static_cast<float>(g_src.rows * .25));
    dstTriAngle[1] = Point2f(static_cast<float>(g_src.cols * .8), static_cast<float>(g_src.rows * .3));
    dstTriAngle[2] = Point2f(static_cast<float>(g_src.cols * .2), static_cast<float>(g_src.rows * .85));
    // 得到仿射变换矩阵
    warpMat = getAffineTransform(srcTriAngle, dstTriAngle);
    warpAffine(img2, img2, warpMat, g_src.size());

//    Point2f center = Point(g_src.cols / 2, g_src.rows / 2);
//    rotMat = getRotationMatrix2D(center, 30, 1.0);
//    warpAffine(g_src, img2, rotMat, g_src.size());

    imshow("第二幅图", img2);
//--------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------第三部分 特征点匹配 -------------------------------------------------------------
    /***
     * 计算描述子(特征向量)
     * void compute( InputArray image,
     *                   CV_OUT CV_IN_OUT std::vector<KeyPoint>& keypoints,
     *                   OutputArray descriptors );
     */
    vector<KeyPoint> points1;
    vector<KeyPoint> points2;

    surf->detect(g_src, points1);
    surf->detect(img2, points2);

    Mat description1, description2;

    surf->compute(g_src, points1, description1);
    surf->compute(img2, points2, description2);
    /***
     * OpenCV 3.x 有一个detect和compute合并版本的函数: detectAndCompute()
     * void detectAndCompute( InputArray image, InputArray mask,
     *                             CV_OUT std::vector<KeyPoint>& keypoints,
     *                             OutputArray descriptors,
     *                             bool useProvidedKeypoints=false );
     */

    // 使用BruteForce 进行匹配
    // 又是一个3.x 与2.x 大不相同的类
    // 获得匹配器
    Ptr<BFMatcher> matcher = BFMatcher::create();
    vector<DMatch> matches;
    /***
     * 匹配两幅图的算子
     * void match( InputArray queryDescriptors, InputArray trainDescriptors,
     *          CV_OUT std::vector<DMatch>& matches, InputArray mask=noArray() ) const;
     */
    matcher->match(description1, description2, matches, noArray());
    /***
     * 绘制匹配向量
     *  还有一个重载版本的 用于 KNN 算法
     * void drawMatches( InputArray img1,
     *                      const std::vector<KeyPoint>& keypoints1, // 根据img1得到的关键点
     *                      InputArray img2,
     *                      const std::vector<KeyPoint>& keypoints2, // 根据img2得到的关键点
     *                      const std::vector<DMatch>& matches1to2, // img1到img2的匹配点， 表示每一个img1中的特征点在img2中的对应
     *                      InputOutputArray outImg, // 输出图像 内容取决于flags
     *                      const Scalar& matchColor=Scalar::all(-1), // 匹配线的颜色 默认是随机的
     *                      const Scalar& singlePointColor=Scalar::all(-1), // 单一特征点的颜色
     *                      const std::vector<char>& matchesMask=std::vector<char>(),
     *                      int flags=DrawMatchesFlags::DEFAULT );
     */
    Mat dst;
    drawMatches(g_src, points1, img2, points2, matches, dst);
    imshow("特征匹配", dst);
//--------------------------------------------------------------------------------------------------------------------------------------
    waitKey();
    return 0;
}