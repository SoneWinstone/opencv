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
    imshow("ԭͼ", src);
    /***
     * void warpAffine( InputArray src, OutputArray dst,
     *                        InputArray M, // 2*3 �ı任����
     *                        Size dsize, // ���ͼ��ĳߴ�
     *                        int flags = INTER_LINEAR, // ��ֵ����
     *                        int borderMode = BORDER_CONSTANT,
     *                        const Scalar& borderValue = Scalar());
     *
     * ���ƺ����Աȣ�
     *  warpAffine() src��dst������ͬ���������ͣ��ķ���Դ����
     *  cvGetQuadrangleSubPix() ���Ծ�ȷ�Ĵ�8λͼ������ȡ�ı��ε��������������У�ϵͳ�����Ƚ�С
     */
    // ��������� ��������������
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
    // �õ�����任����
    warpMat = getAffineTransform(srcTriAngle, dstTriAngle);
    warpAffine(src, dst, warpMat, Size(static_cast<int>(src.cols * 1.2), static_cast<int>(src.rows * 1.2)));

    imshow("warpAffineЧ��ͼ", dst);
    /***
     * Mat getRotationMatrix2D( Point2f center, // Դͼ�����������
     *                                double angle, // ��ת�Ƕ� �Ƕ���ֵ��ʾ��ʱ����ת(����ԭ�������Ͻ�)
     *                                double scale ); // ����ϵ��
     */
    Point2f center = Point(dst.cols / 2, dst.rows / 2);
    // ˳ʱ����ת70��
    double angle = -70;
    // ����0.7��
    double scale = 0.7;
    // �õ���ת���ž���
    rotMat = getRotationMatrix2D(center, angle, scale);
    // �ó���ת���ŵ�ͼ��
    warpAffine(dst, dst2, rotMat, dst.size());
    imshow("��ת���ŵ�warp", dst2);

    waitKey();
    return 0;
}