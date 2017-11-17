#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static const string strPa = imgPath + "DOTA2_pa.jpg";

int g_nBrightVal = 100; // ����
int g_nContrastVal = 0; // �Աȶ�
Mat g_srcImg;
Mat g_dstImg;

/**
 * ���ȶԱȶ� ��Ӧ����
 *
 * ���ȶԱȶȼ��㹫ʽ��
 *    g(x) = f(x) + n = (x, y) * brigh * % + contrast
 */
void on_lightAndContrastChanged(int) {
    for (int x = 0; x < g_srcImg.cols; ++x) {
        for (int y = 0; y < g_srcImg.rows; ++y) {
            for (int i = 0; i < 3; ++i) {
                /**
                 * ���������(y, x) ���к��� ��Ȼ��������
                 * uchar x = saturate_cast<uchar>(n) ��ֵֹԽ�� 0 <= x <= UCHAR_MAX
                 */
                g_dstImg.at<Vec3b>(y, x)[i] = saturate_cast<uchar>(g_srcImg.at<Vec3b>(y, x)[i] * g_nBrightVal * 0.01 + g_nContrastVal);
            }
        }
    }

    imshow("PA_Ч��ͼ", g_dstImg);
}

int main() {
    g_srcImg = imread(strPa);
    namedWindow("PA");
    imshow("PA", g_srcImg);

//    g_dstImg = Mat::zeros(g_srcImg.size(), g_srcImg.type());
    g_dstImg = g_srcImg.clone();
    namedWindow("PA_Ч��ͼ", WindowFlags::WINDOW_AUTOSIZE);

    // ����һ�λص����� ��ʾЧ��ͼ ��ȻЧ��ͼ�ǻҵ�
    on_lightAndContrastChanged(0);

    cvCreateTrackbar("����", "PA_Ч��ͼ", &g_nBrightVal, 300, on_lightAndContrastChanged);
    cvCreateTrackbar("�Աȶ�", "PA_Ч��ͼ", &g_nContrastVal, 100, on_lightAndContrastChanged);

    // ��ȡ��ǰ�켣��λ��
    int b = getTrackbarPos("����", "PA_Ч��ͼ");
    int c = getTrackbarPos("�Աȶ�", "PA_Ч��ͼ");
    cout << "bright : " << b << endl;
    cout << "contrast : " << c << endl;

    waitKey();
    return 0;
}