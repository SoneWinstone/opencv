/**
 * �ⲿ��������Ƶ�רҵ֪ʶ�Ƚ϶� ԭ���ֿ��Զ������
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
    imshow("ԭͼ", g_srcImg);
    g_outImgCanny = Mat(g_srcImg.size(), g_srcImg.type());
    /***
     * void Canny( InputArray image,
     *              OutputArray edges,
     *              double threshold1, // ��һ���ͺ�����ֵ
     *              double threshold2, // �ڶ����ͺ�����ֵ ������ֵ�ı���2:1 �� 3:1
     *              int apertureSize = 3, // Sobel���ӵĿ׾���С 3-7
     *              bool L2gradient = false );
     */
    createTrackbar("��ֵ1", "ԭͼ", &g_nThreshold1, 200, on_thresh1);
    createTrackbar("��ֵ2", "ԭͼ", &g_nThreshold2, 200, on_thresh2);
    // createTrackbar("Sobel�׾�", "ԭͼ", &g_nSize, 7, on_size); // �׾����õ� ���3Ч���ȽϺ�

    /***
     * ��ΪSobel���ӽ���˸�˹ƽ���ͷֻ���differentiation������˽������и���Ŀ����ԡ�
     * ���������£�����ʹ��sobel����ʱ��ȡ��xorder = 1��yorder = 0��ksize = 3��������ͼ��X����ĵ�������xorder = 0��yorder = 1��ksize = 3��������ͼ��y����ĵ�����
     *
     * Sobel ����ת�ɻҶ�ͼ ����ֱ���ڲ�ɫͼ����
     *
     * void Sobel( InputArray src, OutputArray dst,
     *                   int ddepth, // ���ͼ������ ����src.depth()ȡ��Ӧ�����
     *                   int dx, // x�����ϵĲ�ֽ���
     *                   int dy,
     *                   int ksize = 3, // Sobel�˵Ĵ�С
     *                   double scale = 1, // ���㵼��ʱ��ѡ����������
     *                   double delta = 0,
     *                   int borderType = BORDER_DEFAULT );
     */
    /**
     * ��src.depth() = CV_8U, ȡddepth =-1/CV_16S/CV_32F/CV_64F
     * ��src.depth() = CV_16U/CV_16S, ȡddepth =-1/CV_32F/CV_64F
     * ��src.depth() = CV_32F, ȡddepth =-1/CV_32F/CV_64F
     * ��src.depth() = CV_64F, ȡddepth = -1/CV_64F
     */
    g_outImgSobel.create(g_srcImg.size(), g_srcImg.type());
    g_outImgSobel = Scalar::all(0);
    Mat g_outImgSobelx = g_outImgSobel.clone();
    Mat g_outImgSobely = g_outImgSobel.clone();
    // ����X�����ݶ�
    Sobel(g_srcImg, g_outImgSobelx, -1, 1, 0, 3);
    // ����̫������
    // convertScaleAbs( g_outImgSobelx, g_outImgSobelx );//�������ֵ���������ת����8λ
    // ����Y�����ݶ�
    Sobel(g_srcImg, g_outImgSobely, -1, 0, 1, 3);
    // �ϲ��ݶ�
    addWeighted(g_outImgSobelx, 0.5, g_outImgSobely, 0.5, .0, g_outImgSobel);
    imshow("SobelЧ��ͼX", g_outImgSobelx);
    imshow("SobelЧ��ͼY", g_outImgSobely);
    imshow("SobelЧ��ͼ", g_outImgSobel);

    /***
     * laplacian �õ���Ҳ�ǻҶ�ͼ
     * void Laplacian( InputArray src, OutputArray dst,
     *                       int ddepth,
     *                       int ksize = 1,
     *                       double scale = 1,
     *                       double delta = 0,
     *                       int borderType = BORDER_DEFAULT );
     */
    createTrackbar("kSize", "ԭͼ", &g_nSizeLaplace, 9, on_laplace_size);

    /***
     * void Scharr( InputArray src, OutputArray dst, int ddepth,
     *                    int dx, int dy, double scale = 1, double delta = 0,
     *                    int borderType = BORDER_DEFAULT );
     * �൱�� Sobel(src, dst, ddepth, dx, dy, CV_SCHARR, scale, delta, borderType) �� CV_SCHARR = -1
     */
    Scharr(g_srcImg, g_outImgScharr, -1, 1, 0);
    imshow("ScharrЧ��ͼ", g_outImgScharr);

    waitKey();
    return 0;
}

void on_size(int, void*) { getCanny(); }

void on_thresh1(int, void*) { getCanny(); }

void on_thresh2(int, void*) { getCanny(); }

void getCanny() {
    // Sobel ��С������3-7֮��
    if (g_nSize < 3)
        g_nSize = 3;
    if (g_nSize % 2 == 0)
        g_nSize = g_nSize - 1;
    // �õ��Ҷȱ�Եͼ��
    Canny(g_srcImg, g_outImgCanny, g_nThreshold1, g_nThreshold2, g_nSize);
    // g_outTemp = Mat(g_srcImg.size(), g_srcImg.type());
    // ת���ɻҶ�ͼ
    cvtColor(g_srcImg, g_outTemp, COLOR_BGR2GRAY); // cv::ColorConversionCodes
    // ����
    Mat gray;
    gray.create(g_outTemp.size(), g_outTemp.type());
    blur(g_outTemp, gray, Size(3, 3));

    //** �����ͼ�������Ԫ������Ϊ0 ��Ȼͼ����ܲ��ᷢ���仯 **
    g_outImgColorCanny = Scalar::all(0);
    Canny(gray, gray, g_nThreshold1, g_nThreshold2, g_nSize);
    // ʹ��Canny��������ı�Եͼ��Ϊ���룬����ԭͼ����Ŀ��ͼ��
    g_srcImg.copyTo(g_outImgColorCanny, gray);
    imshow("Ч��ͼ", g_outImgCanny);
    imshow("��ɫЧ��ͼ", g_outImgColorCanny);
}

void on_laplace_size(int, void*) {
    // ksize ������������
    if (g_nSizeLaplace%2 == 0)
        g_nSizeLaplace = g_nSizeLaplace + 1;

    Mat temp = Mat(g_srcImg.size(), CV_8UC(1));
    blur(g_srcImg, temp, Size(3, 3));
    Laplacian(temp, g_outImgLaplace, -1, g_nSizeLaplace);
    temp = Scalar::all(0);
    g_srcImg.copyTo(temp, g_outImgLaplace);
    // laplace �Ĳ�ɫͼ���ÿ� ������ʾ�Ҷ�ͼ��
    // imshow("LaplaceЧ��ͼ", temp);
    imshow("LaplaceЧ��ͼ", g_outImgLaplace);
}