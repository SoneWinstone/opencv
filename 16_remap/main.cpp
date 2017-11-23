#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static string imgFolder = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static string strImg = imgFolder + "LOL_yaso.jpg";

int main() {
    /***
     * void remap( InputArray src,
     *                   OutputArray dst, // same size as map1 and the same type as src
     *                   InputArray map1, // ӳ�䵽(x, y) �������x �ĵ�  ���ͣ�CV_16SC2 ,CV_32FC1, or CV_32FC2.
     *                   InputArray map2, // ���map1 ��(x, y) map2Ϊ��
     *                   int interpolation, // Interpolation method (see cv::InterpolationFlags)
     *                   int borderMode = BORDER_CONSTANT,
     *                   const Scalar& borderValue = Scalar());
     */
    Mat src = imread(strImg);
    if (src.empty()) { cout << "��ȡ" << strImg << "����" << endl; return -1; }
    imshow("ԭʼͼ", src);
    Mat dst2 = Mat(src.size(), src.type());
    Mat dst3 = Mat(src.size(), src.type());
    Mat dst = Mat(src.size(), src.type());
    Mat mapX = Mat(src.size(), CV_32F); // ֻӳ��X/Y
    Mat mapY = Mat(src.size(), CV_32F);
    Mat map = Mat(src.size(), CV_32FC2); // ͬʱӳ��(x, y) ˫ͨ��
    Mat map2 = Mat(src.size(), CV_32FC2);
    vector<Mat> channels;
    vector<Mat> channels2;
    // ����ͨ��
    split(map, channels);
    split(map2, channels2);
    for (int x = 0; x < src.cols; ++x) {
        for(int y = 0; y < src.rows; ++y) {
            mapX.at<float>(y, x) = static_cast<float>(src.cols - x); // Xȡ��
            mapY.at<float>(y, x) = static_cast<float>(src.rows - y); // Yȡ��

            channels[0].at<float>(y, x) = static_cast<float>(src.cols - x); // Xȡ��
            channels[1].at<float>(y, x) = static_cast<float>(y);

            channels2[0].at<float>(y, x) = static_cast<float>(x);
            channels2[1].at<float>(y, x) = static_cast<float>(src.rows - y); // Yȡ��
        }
    }
    // �ϲ�ͨ��
    merge(channels, map);
    merge(channels2, map2);
    // ��ӳ��
    remap(src, dst, mapX, mapY, INTER_LINEAR);
    remap(src, dst2, map, Mat(), INTER_LINEAR);
    remap(src, dst3, map2, Mat(), INTER_LINEAR);

    imshow("ӳ��ͼ", dst);
    imshow("ӳ��ͼ2", dst2);
    imshow("ӳ��ͼ3", dst3);

    waitKey();
    return 0;
}