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

Mat g_src;
Mat g_tempR;
Mat g_tempP;
Mat g_dstP;
Mat g_dstR;

void resize(bool b = true);
void up();
void down();

int main() {
    g_src = imread(strImg);
    g_dstP = g_src.clone();
    g_dstR = g_src.clone();
    imshow("ԭʼͼ", g_src);
    /***
     * void resize( InputArray src, OutputArray dst,
     *                    Size dsize,   // Ŀ��ͼ��Ĵ�С dsize��fx��fy֮�б�����һ����Ϊ�� ���ǿ��Ի����Ƶ�����
     *                    double fx = 0,    // X����ı������� scale factor
     *                    double fy = 0,
     *                    int interpolation = INTER_LINEAR );   // ��ֵ�� cv::InterpolationFlags ��Сͼ���Ƽ�CV_INTER_AREA���Ŵ�ͼ���Ƽ�CV_INTER_LINEAR
     */

    /***
     * void pyrUp( InputArray src, OutputArray dst,
     *                   const Size& dstsize = Size(), // Ĭ�ϳߴ� Size(src.cols*2, (src.rows*2)
     *                   int borderType = BORDER_DEFAULT );
     * void pyrDown( InputArray src, OutputArray dst,
     *                   const Size& dstsize = Size(), // Ĭ�ϳߴ� Size((src.cols+1)/2, (src.rows+1)/2)
     *                   int borderType = BORDER_DEFAULT );
     */
    while (1) {
        int key = waitKey();
        switch (key) {
            case 'q':
                exit(0);
            case 'w':
                resize();
                break;
            case 's':
                resize(false);
                break;
            case 'd':
                up();
                break;
            case 'a':
                down();
                break;
        }
    }
}

void resize(bool sizeUp) {
    g_tempR = g_dstR;
    if (sizeUp) {
        resize(g_tempR, g_dstR, Size(g_tempR.cols*2, g_tempR.rows*2));
    } else {
        resize(g_tempR, g_dstR, Size(g_tempR.cols/2, g_tempR.rows/2));
    }
    imshow("Ч��ͼ", g_dstR);
}

void up() {
    g_tempP = g_dstP;
    pyrUp(g_tempP, g_dstP);
    imshow("Ч��ͼ", g_dstP);
}

void down() {
    g_tempP = g_dstP;
    pyrDown(g_tempP, g_dstP);
    imshow("Ч��ͼ", g_dstP);
}
