#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\person\)";
static const string strImg = imgPath + "girl001.jpg";

int g_nSize = 3;
Mat g_outImgGaussian;
Mat g_outImgBox;
Mat g_srcImg;

void on_chgBoxKSize() {
    // ��˹�ľ������������ Ҳ���Ե����ڸ�˹�˲���ı�
    if (g_nSize%2 == 0) {
        ++g_nSize;
        return;
    }

    boxFilter(g_srcImg, g_outImgBox, -1, Size(g_nSize, g_nSize));
    imshow("[1]�����˲�Ч��ͼ", g_outImgBox);
}

void on_chgGuassianKSize() {
    GaussianBlur(g_srcImg, g_outImgGaussian, Size(g_nSize, g_nSize), 0, 0);
    imshow("[2]��˹�˲�Ч��ͼ", g_outImgGaussian);
}

/**
 * һ��trackBar��������ͼ��
 */
void on_changed(int, void*) {
    on_chgBoxKSize();
    on_chgGuassianKSize();
}

int main() {
    /**
     * �����˲�
     */
    Mat girl = imread(strImg);
    g_srcImg = girl.clone();
    // Mat outImg = Mat(girl.size(), girl.type());
    /***
     * void boxFilter( InputArray src, OutputArray dst,
     *                       int ddepth, ͼ����ȣ� -1ʱΪsrc�����
     *                       Size ksize, ����Ĵ�С
     *                       Point anchor = Point(-1,-1), ê�㣨����ƽ�����Ǹ��㣩
     *                       bool normalize = true, �Ƿ��һ��
     *                       int borderType = BORDER_DEFAULT һ�㲻�ù�
     *                       );
     */
    imshow("ԭͼ", girl);
    // boxFilter(girl, g_outImg, -1, Size(3, 3), Point(-1, -1), false);
    // imshow("[1]�����˲�Ч��ͼ", g_outImg);
    on_chgBoxKSize();
    createTrackbar("kSize", "ԭͼ", &g_nSize, 50, on_changed);

    /***
     * ��ֵ�˲�
     * void blur( InputArray src, OutputArray dst, Size ksize, Point anchor = Point(-1,-1), int borderType = BORDER_DEFAULT );
     * �ں����ڲ����÷����˲�
     *      boxFilter( src, dst, -1, ksize, anchor, true, borderType );
     * ûʲô��˵��
     */

    /***
     * ��˹�˲�
     *  ��˹��ͨ�˲���ģ�� ����ĸ�˹�˲����ǵ�ͨ�˲�
     *  ��˹��ͨ�˲�����
     *
     * ��˹ģ����ȷ����˲�ƽ��һЩ
     * void GaussianBlur( InputArray src, OutputArray dst, Size ksize,
     *                          double sigmaX,  �˺�����X����ĵı�׼ƫ��
     *                          double sigmaY = 0,  �˺�����Y����ĵı�׼ƫ���sigmaYΪ�㣬�ͽ�����ΪsigmaX�����sigmaX��sigmaY����0����ô����ksize.width��ksize.height���������
     *                          int borderType = BORDER_DEFAULT );
     */
    on_chgGuassianKSize();

    waitKey();
    return 0;
}
