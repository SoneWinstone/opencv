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
// 随机数引擎
default_random_engine engine(static_cast<unsigned int>(time(NULL)));
// 设置种子
// engine.seed(static_cast<unsigned int>(time(NULL)));
// 设置随机数范围
uniform_int_distribution<unsigned int> distribution(0, 255);

/***
 * 鼠标事件回调函数
 * @param event // cv::MouseEventTypes
 * @param x // 相对于窗口的鼠标坐标
 * @param y
 * @param flags // cv::MouseEventFlags
 * @param userdata
 */
void onMouse(int event, int x, int y, int flags, void* userdata);
void on_diff_LB(int, void*);
void on_diff_UB(int, void*);
int random();

int main() {
    // 重新设置种子
    srand(static_cast<unsigned int>(time(NULL)));
    // 除了mask 两个版本其他参数一样
    /***
     * 不带mask掩码的变体
     * int floodFill( InputOutputArray image,
     *                    Point seedPoint, Scalar newVal, CV_OUT Rect* rect = 0,
     *                    Scalar loDiff = Scalar(), Scalar upDiff = Scalar(),
     *                    int flags = 4 );
     */
    /***
     * 带mask掩码版本
     * int floodFill( InputOutputArray image,
     *                      //需要注意的是，漫水填充不会填充掩膜mask的非零像素区域。
     *                      //例如，一个边缘检测算子的输出可以用来作为掩膜，以防止填充到边缘。同样的，也可以在多次的函数调用中使用同一个掩膜，以保证填充的区域不会重叠。
     *                      //另外需要注意的是，掩膜mask会比需填充的图像大，所以 mask 中与输入图像(x,y)像素点相对应的点的坐标为(x+1,y+1)。
     *                      InputOutputArray mask, // 8UC1 长宽比src大2个像素点
     *                      Point seedPoint, // 漫水填充算法的起始点
     *                      Scalar newVal, // 像素点被染色的值
     *                      CV_OUT Rect* rect=0, // 用于设置floodFill函数将要重绘区域的最小边界矩形区域
     *                      Scalar loDiff = Scalar(), // 表示当前观察像素值与其部件邻域像素值或者待加入该部件的种子像素之间的亮度或颜色之负差（lower brightness/color difference）的最大值
     *                      Scalar upDiff = Scalar(), // 正差（upper brightness/color difference）的最大值
     *                      int flags = 4 ); // 看源码注释有详细解释
     */
    g_src = imread(strImg);
    imshow("效果图", g_src);
    setMouseCallback("效果图", onMouse);
//    GaussianBlur(src, temp, Size(3, 3), 0);
//    bilateralFilter(src, temp, 3, 9, 1.5);

    createTrackbar("负差", "效果图", &g_nLB, 20, on_diff_LB);
    createTrackbar("正差", "效果图", &g_nUB, 20, on_diff_UB);

    waitKey();
    return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
    // cout << "x: " << x << " - y: " << y << endl;
    if (event != EVENT_LBUTTONDOWN) {
        return ;
    }
    // 每次点击都是随机颜色
    floodFill(g_src, Point(x, y), Scalar(random(), random(), random()), 0, Scalar(g_nLB, g_nLB, g_nLB), Scalar(g_nUB, g_nUB, g_nUB));
    imshow("原始图", g_src);
}

void on_diff_LB(int, void*){}
void on_diff_UB(int, void*){}

int random() {
    // return rand() % 256;
    return distribution(engine);
}