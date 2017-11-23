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
    imshow("ԭʼͼ", g_src);

    createTrackbar("�����С", "ԭʼͼ", &g_nBlockSize, 20, on_change);
    createTrackbar("Sobel�׾�", "ԭʼͼ", &g_nKSize, 20, on_change);
    createTrackbar("Harris", "ԭʼͼ", &g_lfHarrisK, 20, on_change);
    createTrackbar("��ֵ", "ԭʼͼ", &g_lfThresh, 20, on_change);
    createTrackbar("�����ֵ", "ԭʼͼ", &g_lfMaxVal, 255, on_change);
    createTrackbar("��ֵ����", "ԭʼͼ", &g_nThreshType, 9, on_change);

    waitKey();
    return 0;
}

void on_change(int, void*) {
    /***
     * Harris �ǵ��⺯��
     * void cornerHarris( InputArray src,   // CV_8UC1 or CV_32F
     *                          OutputArray dst, // CV_32FC1 size as src
     *                          int blockSize,  // Neighborhood size
     *                          int ksize,  // Aperture(�׾�) parameter for the Sobel operator
     *                          double k, // Harris detector free parameter
     *                          int borderType = BORDER_DEFAULT );
     */
    g_lfHarrisK /= 10;
    if (g_nKSize%2 == 0)    g_nKSize += 1;
    if (g_nKSize > 31)      g_nKSize = 31;
    cornerHarris(g_src, g_temp, g_nBlockSize, g_nKSize, g_lfHarrisK);
    imshow("�ǵ���ͼ", g_temp);
    /***
     * �Ե�ͨ������Ӧ�ù̶���ֵ����
     * ����Ӧ���ǶԻҶ�ͼ�������ֵ�����õ���ֵͼ��(compare( )����Ҳ���Դﵽ��Ŀ��)��������ȥ��������������˺�С��ܴ�����ֵ��ͼ��㡣
     * double threshold( InputArray src, OutputArray dst,
     *                         double thresh,
     *                         double maxval, // ��typeΪCV_THRESH_BINARY ��CV_THRESH_BINARY_INV ʱ�����ֵ
     *                         int type ); // cv::ThresholdTypes
     */
    if (g_nThreshType > 8) g_nThreshType = 16;
    if (g_nThreshType == 5) g_nThreshType = 4;
    if (g_nThreshType == 6) g_nThreshType = 7;
    threshold(g_temp, g_dst, g_lfThresh, g_lfMaxVal, g_nThreshType);
    imshow("Ч��ͼ", g_dst);
}