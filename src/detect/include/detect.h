
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

enum DetectColor {
    BLUE,
    RED
};
struct  AllInformation
{
    DetectColor detect_color;
    int gray_thresolod;
    int substract_thresold;
    int angle_thresold;
    int lenbywidth_thresold;
    int min_area;
    int left_sub_right_length_thresold;
    int on_sub_width_thresold;
    int diagonal_difference;
    int max_area;
/* data */
};
class ImageTrackle
{
public:
    ImageTrackle(const DetectColor &color,
                const int &thresold_gray,
                const int &thresold_color,
                const int &thresold_yuv); // 初始化
    cv::Mat TrackleImageSubtract(const cv::Mat &image);// 对图像进行两色通道相减的处理。

public:
    cv::Mat image_trackle_subtract;
    DetectColor my_color;
    int color_image_thresold;
    int gray_image_thresold;
    int yuv_image_thresold;
};

class LightBar {
public:
    LightBar();
    ~LightBar();
    LightBar(const cv::RotatedRect roatated_rect);
public:
    float light_angle;
    float light_height;
    float light_width;
    cv::Point2f lingt_center;
    cv::RotatedRect light_rect;
};

class DetectLight {
public:
    DetectLight(const float min_area, 
                const float angle,
                const float number,
                const float max_area);
    void DetectLightInSwapStation(const cv::Mat &image,const cv::Mat &image1);
    void MatchPreSwapStation();
public:
    std::vector<LightBar> lights;
    std::vector<std::vector<LightBar>> pre_swap_station_arry;
    float min_light_area;
    float light_angle;
    float weightbyheight;
    float max_light_area;
};

class SwapStation {
public:
    SwapStation();
    ~SwapStation();
    void MatchPreSwapStation(const std::vector<LightBar> light_arry);
    void ComputerParam();
public:
    std::vector<LightBar> pre_swapstation;
    LightBar left_on;
    LightBar left_under;
    LightBar right_on;
    LightBar right_under;
    float length_left;
    float length_right;
    float length_on;
    float length_under;
    float diagonal_len_loru;
    float diagonal_len_luro;
};

class MatchSwapStation {
public:
    MatchSwapStation(AllInformation information);
    void MatchRelSwapStation(const SwapStation &preswapstation, const cv::Mat &image);
    bool SwapStationIssuable(const SwapStation &preswapstation);
    void run(const cv::Mat &image);
    void draw_swapstation(const cv::Mat &image);
public:
    AllInformation all_information;
    std::vector<SwapStation> rel_swapstations;
    SwapStation rel_swapstation; 
    SwapStation last_swapstations;

};

