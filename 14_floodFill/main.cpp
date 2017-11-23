#include <ctime>
#include <random>
#include <string>
#include <cstdlib>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
//static const string strImg = imgPath + "DOTA2_cm.jpg";
static const string strImg = imgPath + "LOL_yaso.jpg";

Mat g_src;
Mat g_gray;
Mat g_temp;
Mat g_mask;
Mat g_dst;
int g_nLB = 1;
int g_nUB = 1;

/**
 * C++11 random library
 */
// default_random_engine engine(static_cast<unsigned int>(time(NULL)));
// ���������
default_random_engine engine(static_cast<unsigned int>(time(NULL)));
// ��������
// engine.seed(static_cast<unsigned int>(time(NULL)));
// �����������Χ
uniform_int_distribution<unsigned int> distribution(0, 255);

/***
 * ����¼��ص�����
 * @param event // cv::MouseEventTypes
 * @param x // ����ڴ��ڵ��������
 * @param y
 * @param flags // cv::MouseEventFlags
 * @param userdata
 */
void onMouse(int event, int x, int y, int flags, void* userdata);
void on_diff_LB(int, void*);
void on_diff_UB(int, void*);
int random();

int main() {
    // ������������
    srand(static_cast<unsigned int>(time(NULL)));
    // ����mask �����汾��������һ��
    /***
     * ����mask����ı���
     * int floodFill( InputOutputArray image,
     *                    Point seedPoint, Scalar newVal, CV_OUT Rect* rect = 0,
     *                    Scalar loDiff = Scalar(), Scalar upDiff = Scalar(),
     *                    int flags = 4 );
     */
    /***
     * ��mask����汾
     * int floodFill( InputOutputArray image,
     *                      //��Ҫע����ǣ���ˮ��䲻�������Ĥmask�ķ�����������
     *                      //���磬һ����Ե������ӵ��������������Ϊ��Ĥ���Է�ֹ��䵽��Ե��ͬ���ģ�Ҳ�����ڶ�εĺ���������ʹ��ͬһ����Ĥ���Ա�֤�������򲻻��ص���
     *                      //������Ҫע����ǣ���Ĥmask���������ͼ������� mask ��������ͼ��(x,y)���ص����Ӧ�ĵ������Ϊ(x+1,y+1)��
     *                      InputOutputArray mask, // 8UC1 �����src��2�����ص�
     *                      Point seedPoint, // ��ˮ����㷨����ʼ��
     *                      Scalar newVal, // ���ص㱻Ⱦɫ��ֵ
     *                      CV_OUT Rect* rect=0, // ��������floodFill������Ҫ�ػ��������С�߽��������
     *                      Scalar loDiff = Scalar(), // ��ʾ��ǰ�۲�����ֵ���䲿����������ֵ���ߴ�����ò�������������֮������Ȼ���ɫ֮���lower brightness/color difference�������ֵ
     *                      Scalar upDiff = Scalar(), // ���upper brightness/color difference�������ֵ
     *                      int flags = 4 ); // ��Դ��ע������ϸ����
     */
    g_src = imread(strImg);
    imshow("Ч��ͼ", g_src);
    setMouseCallback("Ч��ͼ", onMouse);
//    GaussianBlur(src, temp, Size(3, 3), 0);
//    bilateralFilter(src, temp, 3, 9, 1.5);

    createTrackbar("����", "Ч��ͼ", &g_nLB, 20, on_diff_LB);
    createTrackbar("����", "Ч��ͼ", &g_nUB, 20, on_diff_UB);

    waitKey();
    return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
    // cout << "x: " << x << " - y: " << y << endl;
    if (event != EVENT_LBUTTONDOWN) {
        return ;
    }
    // ÿ�ε�����������ɫ
    floodFill(g_src, Point(x, y), Scalar(random(), random(), random()), 0, Scalar(g_nLB, g_nLB, g_nLB), Scalar(g_nUB, g_nUB, g_nUB));
    imshow("ԭʼͼ", g_src);
}

void on_diff_LB(int, void*){}
void on_diff_UB(int, void*){}

int random() {
    // return rand() % 256;
    return distribution(engine);
}