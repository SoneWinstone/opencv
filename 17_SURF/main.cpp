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
//----------------------------------------------------��һ���� SURF���ƹؼ���---------------------------------------------------
    g_src = imread(strImg);
    if (g_src.empty()) { cout << "��ȡ" << strImg << "ʧ�ܣ�" << endl; return -1; }
    imshow("ԭʼͼ", g_src);
    /***
     *  Ptr<SURF> create(double hessianThreshold=100, // Threshold for hessian keypoint detector
     *                        int nOctaves = 4, // Number of pyramid octaves(���������Ƶ��) the keypoint detector
     *                        int nOctaveLayers = 3, // Number of octave layers within each octave
     *                        bool extended = false,
     *                        bool upright = false);
     */
    // OpenCV3.x ����SURF�ķ�ʽ��֮ǰ2.x��ʱ��ͬ
    Ptr<SURF> surf;
    surf = SURF::create(1500);
    /***
     * ���ؼ��㣬�浽keypoints��
     * void detect( InputArray image,
     *                 CV_OUT std::vector<KeyPoint>& keypoints,
     *                 InputArray mask=noArray() );
     */
    vector<KeyPoint> points;
    surf->detect(g_src, points);
    // ���ƹؼ���
    drawKeypoints(g_src, points, g_dst/*, Scalar(255, 0, 0)*/);

    imshow("Ч��ͼ", g_dst);
//--------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------�ڶ����� ����warpAffine��ñ��κ��ͼ��-------------------------------------------
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
    // �õ�����任����
    warpMat = getAffineTransform(srcTriAngle, dstTriAngle);
    warpAffine(img2, img2, warpMat, g_src.size());

//    Point2f center = Point(g_src.cols / 2, g_src.rows / 2);
//    rotMat = getRotationMatrix2D(center, 30, 1.0);
//    warpAffine(g_src, img2, rotMat, g_src.size());

    imshow("�ڶ���ͼ", img2);
//--------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------�������� ������ƥ�� -------------------------------------------------------------
    /***
     * ����������(��������)
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
     * OpenCV 3.x ��һ��detect��compute�ϲ��汾�ĺ���: detectAndCompute()
     * void detectAndCompute( InputArray image, InputArray mask,
     *                             CV_OUT std::vector<KeyPoint>& keypoints,
     *                             OutputArray descriptors,
     *                             bool useProvidedKeypoints=false );
     */

    // ʹ��BruteForce ����ƥ��
    // ����һ��3.x ��2.x ����ͬ����
    // ���ƥ����
    Ptr<BFMatcher> matcher = BFMatcher::create();
    vector<DMatch> matches;
    /***
     * ƥ������ͼ������
     * void match( InputArray queryDescriptors, InputArray trainDescriptors,
     *          CV_OUT std::vector<DMatch>& matches, InputArray mask=noArray() ) const;
     */
    matcher->match(description1, description2, matches, noArray());
    /***
     * ����ƥ������
     *  ����һ�����ذ汾�� ���� KNN �㷨
     * void drawMatches( InputArray img1,
     *                      const std::vector<KeyPoint>& keypoints1, // ����img1�õ��Ĺؼ���
     *                      InputArray img2,
     *                      const std::vector<KeyPoint>& keypoints2, // ����img2�õ��Ĺؼ���
     *                      const std::vector<DMatch>& matches1to2, // img1��img2��ƥ��㣬 ��ʾÿһ��img1�е���������img2�еĶ�Ӧ
     *                      InputOutputArray outImg, // ���ͼ�� ����ȡ����flags
     *                      const Scalar& matchColor=Scalar::all(-1), // ƥ���ߵ���ɫ Ĭ���������
     *                      const Scalar& singlePointColor=Scalar::all(-1), // ��һ���������ɫ
     *                      const std::vector<char>& matchesMask=std::vector<char>(),
     *                      int flags=DrawMatchesFlags::DEFAULT );
     */
    Mat dst;
    drawMatches(g_src, points1, img2, points2, matches, dst);
    imshow("����ƥ��", dst);
//--------------------------------------------------------------------------------------------------------------------------------------
    waitKey();
    return 0;
}