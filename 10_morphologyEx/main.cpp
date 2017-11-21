/***
 * 形态学高级运算就是基于腐蚀和膨胀的组合运算
 *  开运算、闭运算、形态学梯度、“顶帽”、“黑帽”等
 */
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

static const std::string imgPath = R"(C:\Users\SoneWinstone\Pictures\opencv\)";
static const string strImg = imgPath + "dota_logo.png";

int g_nChoose = 0;
int g_nKernel = 3;
int g_nShape = 0;
int g_nIter = 1;
Mat g_outImgErode;
Mat g_outImgDilate;
Mat g_outImgOpen;
Mat g_outImgClose;
Mat g_outImgGrad;
Mat g_outImgTophat;
Mat g_outImgBlackhat;
Mat g_srcImg;

void on_kernel(int, void*);
void on_iter(int, void*);
void on_type(int, void*);
void on_shape(int, void*);
void getRst();

int main() {
    g_srcImg = imread(strImg);
    imshow("原图", g_srcImg);
    /***
     * enum MorphTypes{
     *      MORPH_ERODE    = 0, // 腐蚀
     *      MORPH_DILATE   = 1, // 膨胀
     *      MORPH_OPEN     = 2, // 开运算——先腐蚀后膨胀: dst = open(src, element) = dilate(erode(src, element))
     *      MORPH_CLOSE    = 3, // 闭运算——先膨胀后腐蚀：dst = close(src, element) = erode(dilate(src, element))
     *      MORPH_GRADIENT = 4, // 形态学梯度——膨胀图与腐蚀图之差：dst = morpho_grad(src, element) = dilate(src, element) - erode(src, element)
     *      MORPH_TOPHAT   = 5, // 顶帽——原图像与“开运算“的结果图之差：dst = tophat(src, element) = src - open(src, element)
     *      MORPH_BLACKHAT = 6, // 黑帽——“闭运算“的结果图与原图像之差：dst = blackhat(src, element) = close(src, element) - src
     *      MORPH_HITMISS  = 7  // Hit-or-Miss
     *  };
     */
    /***
     * void morphologyEx( InputArray src, OutputArray dst,
     *                          int op, // cv::MorphTypes
     *                          InputArray kernel, // getStructuringElement()
     *                          Point anchor = Point(-1,-1),
     *                          int iterations = 1,
     *                          int borderType = BORDER_CONSTANT,
     *                          const Scalar& borderValue = morphologyDefaultBorderValue() );
     */
    createTrackbar("MorphTypes", "原图", &g_nChoose, 6, on_type);
    createTrackbar("kernel", "原图", &g_nKernel, 10, on_kernel);
    createTrackbar("迭代次数", "原图", &g_nIter, 10, on_iter);
    createTrackbar("element", "原图", &g_nShape, 2, on_shape);

    waitKey();
    return 0;
}

void on_kernel(int, void*) {
    getRst();
}

void on_iter(int, void*) {
    getRst();
}

void on_shape(int, void*) {
    getRst();
}

void on_type(int, void*) {
    getRst();
}

/***
 * 抽取出来一个通用的函数
 *  优点：比只写一个响应函数 然后调用三个模块的方式效率高很多
 *  缺点：每次只对当前type起作用
 * 我之前的写法：
 *  createTrackbar("type", ..., on_chg);
 *  createTrackbar("kernel", ..., on_chg);
 *  createTrackbar("iter", ..., on_chg);
 *  on_chg(int, void*) {
 *     on_type();
 *     on_kernel();
 *     on_iter();
 *  }
 */
void getRst() {
    if (g_nKernel < 1)
        g_nKernel = 1;
    Mat element = getStructuringElement(g_nShape, Size(g_nKernel, g_nKernel));
    switch (g_nChoose) {
        // MORPH_ERODE
        case 0:
            morphologyEx(g_srcImg, g_outImgErode, MORPH_ERODE, element, Point(-1, -1), g_nIter);
            imshow("[0]腐蚀效果图", g_outImgErode);
            break;
            // MORPH_DILATE
        case 1:
            morphologyEx(g_srcImg, g_outImgDilate, MORPH_DILATE, element, Point(-1, -1), g_nIter);
            imshow("[1]膨胀效果图", g_outImgDilate);
            break;
            // MORPH_OPEN
        case 2:
            morphologyEx(g_srcImg, g_outImgOpen, MORPH_OPEN, element, Point(-1, -1), g_nIter);
            imshow("[2]开运算效果图", g_outImgOpen);
            break;
            //  MORPH_CLOSE
        case 3:
            morphologyEx(g_srcImg, g_outImgClose, MORPH_CLOSE, element, Point(-1, -1), g_nIter);
            imshow("[3]闭运算效果图", g_outImgClose);
            break;
            //  MORPH_GRADIENT
        case 4:
            morphologyEx(g_srcImg, g_outImgGrad, MORPH_GRADIENT, element, Point(-1, -1), g_nIter);
            imshow("[4]形态学梯度效果图", g_outImgGrad);
            break;
            // MORPH_TOPHAT
        case 5:
            morphologyEx(g_srcImg, g_outImgTophat, MORPH_TOPHAT, element, Point(-1, -1), g_nIter);
            imshow("[5]顶帽效果图", g_outImgTophat);
            break;
            // MORPH_BLACKHAT
        case 6:
            morphologyEx(g_srcImg, g_outImgBlackhat, MORPH_BLACKHAT, element, Point(-1, -1), g_nIter);
            imshow("[6]黑帽效果图", g_outImgBlackhat);
            break;
    }
}
#if 0
// morphologyEx 源码
void cv::morphologyEx( InputArray _src, OutputArray _dst, int op,
                       InputArray _kernel, Point anchor, int iterations,
                       int borderType, const Scalar& borderValue )
{
    CV_INSTRUMENT_REGION()

    Mat kernel = _kernel.getMat();
    if (kernel.empty())
    {
        kernel = getStructuringElement(MORPH_RECT, Size(3,3), Point(1,1));
    }
#ifdef HAVE_OPENCL
    Size ksize = kernel.size();
    anchor = normalizeAnchor(anchor, ksize);

    CV_OCL_RUN(_dst.isUMat() && _src.dims() <= 2 && _src.channels() <= 4 &&
        anchor.x == ksize.width >> 1 && anchor.y == ksize.height >> 1 &&
        borderType == cv::BORDER_CONSTANT && borderValue == morphologyDefaultBorderValue(),
        ocl_morphologyEx(_src, _dst, op, kernel, anchor, iterations, borderType, borderValue))
#endif

    Mat src = _src.getMat(), temp;
    _dst.create(src.size(), src.type());
    Mat dst = _dst.getMat();

    Mat k1, k2, e1, e2;		//only for hit and miss op

    switch( op )
    {
    case MORPH_ERODE:
        erode( src, dst, kernel, anchor, iterations, borderType, borderValue );
        break;
    case MORPH_DILATE:
        dilate( src, dst, kernel, anchor, iterations, borderType, borderValue );
        break;
    case MORPH_OPEN:
        erode( src, dst, kernel, anchor, iterations, borderType, borderValue );
        dilate( dst, dst, kernel, anchor, iterations, borderType, borderValue );
        break;
    case CV_MOP_CLOSE:
        dilate( src, dst, kernel, anchor, iterations, borderType, borderValue );
        erode( dst, dst, kernel, anchor, iterations, borderType, borderValue );
        break;
    case CV_MOP_GRADIENT:
        erode( src, temp, kernel, anchor, iterations, borderType, borderValue );
        dilate( src, dst, kernel, anchor, iterations, borderType, borderValue );
        dst -= temp;
        break;
    case CV_MOP_TOPHAT:
        if( src.data != dst.data )
            temp = dst;
        erode( src, temp, kernel, anchor, iterations, borderType, borderValue );
        dilate( temp, temp, kernel, anchor, iterations, borderType, borderValue );
        dst = src - temp;
        break;
    case CV_MOP_BLACKHAT:
        if( src.data != dst.data )
            temp = dst;
        dilate( src, temp, kernel, anchor, iterations, borderType, borderValue );
        erode( temp, temp, kernel, anchor, iterations, borderType, borderValue );
        dst = temp - src;
        break;
    case MORPH_HITMISS:
        CV_Assert(src.type() == CV_8UC1);
        k1 = (kernel == 1);
        k2 = (kernel == -1);
        if (countNonZero(k1) <= 0)
            e1 = src;
        else
            erode(src, e1, k1, anchor, iterations, borderType, borderValue);
        if (countNonZero(k2) <= 0)
            e2 = src;
        else
        {
            Mat src_complement;
            bitwise_not(src, src_complement);
            erode(src_complement, e2, k2, anchor, iterations, borderType, borderValue);
        }
        dst = e1 & e2;
        break;
    default:
        CV_Error( CV_StsBadArg, "unknown morphological operation" );
    }
}
#endif