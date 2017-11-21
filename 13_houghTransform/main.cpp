/***
 * OpenCV�еĻ����߱任���������֣�
 *  <1>��׼����任��StandardHough Transform��SHT������HoughLines�������á�
 *  <2>��߶Ȼ���任��Multi-ScaleHough Transform��MSHT������HoughLines�������á�
 *  <3>�ۼƸ��ʻ���任��ProgressiveProbabilistic Hough Transform��PPHT������HoughLinesP�������á�
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
    if (g_src.empty()) { cout << "��ȡͼ��ʧ�ܣ�" << endl; exit(-1); }
    Mat g_srcCircle = imread(strImgCircle);
    g_grayLines = Mat(g_src.size(), g_src.type());
    // ��Ե���
    Canny(g_src, g_grayLines, 100, 150);
    /***
     * void HoughLines( InputArray image, OutputArray lines,
     *                        double rho, // ������Ϊ��λ�ľ��뾫��
     *                        double theta, // �Ի���Ϊ��λ�ĽǶȾ���
     *                        int threshold, // ��ֵ ������ֵ�ĵ�Żᱻʶ��Ϊ�߶�
     *                        double srn = 0, double stn = 0, // ��߶Ȼ���任���õ�
     *                        double min_theta = 0, double max_theta = CV_PI );
     */
    imshow("��Ե���ͼ", g_grayLines);
    createTrackbar("��ֵ", "��Ե���ͼ", &g_nThresholdLines, 500, on_lines_threshold);

    /***
     * void HoughLinesP( InputArray image, OutputArray lines,
     *                         double rho, double theta, int threshold,
     *                         double minLineLength = 0, // ��ʾ����߶εĳ��� �������ֵ���߶β���ʾ
     *                         double maxLineGap = 0 ); // ����ͬһ�е����֮���������������ľ���
     */
    createTrackbar("���ֵ", "��Ե���ͼ", &g_nMinLen, 100, on_linesP);

    /**
     * void HoughCircles( InputArray image, OutputArray circles,
     *                         int method, // cv::HoughModes ֻ��HOUGH_GRADIENT����
     *                         double dp, // ���ڼ��Բ�ĵ��ۼ���ͼ��ķֱ���������ͼ��֮�ȵĵ���
     *                         double minDist, // ��С�뾶
     *                         double param1 = 100, double param2 = 100,
     *                         int minRadius = 0, int maxRadius = 0 );
     */
    vector<Vec3f> points;
    Mat dstCircle;
    cvtColor(g_srcCircle, dstCircle, COLOR_BGR2GRAY);
    GaussianBlur(dstCircle, dstCircle, Size(5, 5), 2, 2);
//    imshow("Բ�Ҷ�ͼ", dstCircle);
    HoughCircles(dstCircle, points, HOUGH_GRADIENT, 1.0, 10);
    // ��ͼ�л��Ƴ�Բ
    for( size_t i = 0; i < points.size(); i++ )
    {
        Point center(cvRound(points[i][0]), cvRound(points[i][1]));
        int radius = cvRound(points[i][2]);
        //����Բ��
        circle(g_srcCircle, center, 3, Scalar(0, 255, 0), -1, 8, 0 );
        //����Բ����
        circle(g_srcCircle, center, radius, Scalar(0, 0, 255), 3, 8, 0 );
    }
    imshow("����Բ�任", g_srcCircle);

    waitKey();
    return 0;
}

void on_lines_threshold(int, void*) {
    lines();
}

void lines() {
    vector<Vec2f> lines;
    // �ԻҶ�ͼ���л���任
    HoughLines(g_grayLines, lines, 1, CV_PI/180, g_nThresholdLines);
    // ���Ҷ�ͼת��BGRͼ����ʾ��ɫ����
    cvtColor(g_grayLines, g_dstLines, COLOR_GRAY2BGR);
    // �����߶�
    for (auto i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(g_dstLines, pt1, pt2, Scalar(255, 0, 0), 1, LINE_AA); // Scalar(x, x, x) ��ɫ�ı�ʾ
    }
    imshow("Ч��ͼ", g_dstLines);
}

void on_linesP(int, void*) {
    vector<Vec4i> lines;
    // �ԻҶ�ͼ���л���任
    HoughLinesP(g_grayLines, lines, 1, CV_PI/180, g_nThresholdLines, g_nMinLen);
    // ���Ҷ�ͼת��BGRͼ����ʾ��ɫ����
    cvtColor(g_grayLines, g_dstLinesP, COLOR_GRAY2BGR);
    // �����߶�
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line(g_dstLinesP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, LINE_AA);
    }
    imshow("Ч��ͼ2", g_dstLinesP);
}