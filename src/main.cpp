#include <detect.h>
#define VIDEO_PATH "../../file/front_red.mp4"
int main() {
    AllInformation allinformation;
    allinformation.detect_color = RED;
    allinformation.angle_thresold  = 60; // 旋转矩形与水平面夹角阈值
    allinformation.min_area =  300; // 匹配灯条旋转矩形的最小面积
    allinformation.max_area = 1000;
    allinformation.lenbywidth_thresold = 9; // 灯条旋转矩形的长宽比
    allinformation.gray_thresolod = 160; // 灰度图二值化阈值
    allinformation.substract_thresold = 8; // 通道想加减图二值化阈值
    allinformation.left_sub_right_length_thresold = 10; // 匹配的兑换站左右边长度之差的最小值
    allinformation.on_sub_width_thresold = 10; // 匹配的兑换站上下边长度之差的最小值
    allinformation.diagonal_difference = 10; // 对角线的差值
    cv::VideoCapture my_cap(VIDEO_PATH);
    cv::Mat frame, result; 
    MatchSwapStation my_match(allinformation);
    while (1) {
        my_cap.read(frame);  
        if (frame.empty()) {
            std::cout << "读取失败" << std::endl;
            break;
        }
        my_match.run(frame); // 运行
    }
    return 0;
}