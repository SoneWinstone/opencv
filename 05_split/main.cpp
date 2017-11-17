#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = "C:\\Users\\SoneWinstone\\Pictures\\opencv\\";
static const string pa = imgPath + "DOTA2_pa.jpg";
static const string strLogo = imgPath + "dota_logo.png";

int main() {
    Mat mat;
    mat = imread(pa);

    // ������ػҶ�ͼ ���º͵�ͨ����Ͼͻ��ɫ
    Mat logo = imread(strLogo, 0);
    if (logo.empty()) { cout << "����logoʧ��" << endl; return -1; }

    vector<Mat> channels;
    split(mat, channels);

    // ��ͨ������Ȩ���� 0��blue 1��green 2��red
    Mat roi = channels.at(0)(Rect(mat.cols - logo.cols, mat.rows - logo.rows, logo.cols, logo.rows));
    addWeighted(roi, 1.0, logo, 0.5, 0.0, roi);

    // channels.at() �������ã�
    /**
     * ֱ��������ǻҶ�ͼ
     */
//    imshow("blue: ", channels.at(0));
//    imshow("green: ", channels.at(1));
//    imshow("red: ", channels.at(2));

    // ���ͨ��
    merge(channels, mat);
    imshow("�����ɫͨ��", mat);
    waitKey();
    return 0;
}