/***
 * ��ʴ������ָ���Ǹ���������(��ɫ)
 *  erode()��dilate()֧�־͵�(in-place)���㣺����ֱ�������������
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
     * ��ȡ�Զ����
     * Mat getStructuringElement(int shape, // ��״ cv::MorphShapes
     *                           Size ksize, // ��С
     *                           Point anchor = Point(-1,-1)); // ê��
     */
    /***
     * ����
     * void dilate(
     *      InputArray src,
     *      OutputArray dst,
     *      InputArray kernel,
     *      Point anchor=Point(-1,-1),
     *      int iterations=1, // �����Ĵ���
     *      int borderType=BORDER_CONSTANT, // �����ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ
     *      int borderType=BORDER_CONSTANT, // �����ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ
     *      const Scalar& borderValue=morphologyDefaultBorderValue()
     *  );
     */
    on_kernel_dilate(0, nullptr);
    createTrackbar("��", "����Ч��ͼ", &g_nKernelDilate, 10, on_kernel_dilate);
    createTrackbar("��������", "����Ч��ͼ", &g_nIterDilate, 10, on_iter_dilate);
    /***
     * ��ʴ
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
    createTrackbar("��", "��ʴЧ��ͼ", &g_nKernelErode, 10, on_kernel_erode);
    createTrackbar("��������", "��ʴЧ��ͼ", &g_nIterErode, 10, on_iter_erode);

    waitKey();
    return 0;
}

void on_kernel_erode(int, void*) {
    /***
     * �˵Ĵ�СҪ����1 ��Ȼ�����ҵ�
     */
    if (g_nKernelErode < 1)
        g_nKernelErode = 1;
    erode(g_srcImg, g_outImgErode
            , getStructuringElement(MORPH_RECT, Size(g_nKernelErode, g_nKernelErode), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterErode);
    imshow("��ʴЧ��ͼ" , g_outImgErode);
}

void on_iter_erode(int, void*) {
    erode(g_srcImg, g_outImgErode
            , getStructuringElement(MORPH_RECT, Size(g_nKernelErode, g_nKernelErode), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterErode);
    imshow("��ʴЧ��ͼ" , g_outImgErode);
}

void on_kernel_dilate(int, void*) {
    if (g_nKernelDilate < 1)
        g_nKernelDilate = 1;

    dilate(g_srcImg, g_outImgDilate
            , getStructuringElement(MORPH_RECT, Size(g_nKernelDilate, g_nKernelDilate), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterDilate);
    imshow("����Ч��ͼ" , g_outImgDilate);
}

void on_iter_dilate(int, void*) {
    dilate(g_srcImg, g_outImgDilate
            , getStructuringElement(MORPH_RECT, Size(g_nKernelDilate, g_nKernelDilate), Point(-1,-1))
            , Point(-1,-1)
            , g_nIterDilate);
    imshow("����Ч��ͼ" , g_outImgDilate);
}
