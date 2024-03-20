#include <detect.h>

MatchSwapStation::MatchSwapStation(AllInformation information) {
    all_information = information;
}
void MatchSwapStation::MatchRelSwapStation(const SwapStation &preswapstation, const cv::Mat &image) {
    if (SwapStationIssuable(preswapstation)) {
        std::cout << "match successful" << std::endl;
        // rel_swapstations.push_back(preswapstation);
        rel_swapstation = preswapstation;
    }
    std::cout << "matched swapstation successfully = " << rel_swapstations.size() << std::endl;
} 
bool MatchSwapStation::SwapStationIssuable(const SwapStation &preswapstation) {
    // std::cout << "tan_difference_lr = " << abs(preswapstation.tan_left - preswapstation.tan_right) << std::endl;
    // std::cout << "tan_difference_ou = " << abs(preswapstation.tan_on - preswapstation.tan_under) << std::endl;
    return 
        //    abs(preswapstation.tan_left - preswapstation.tan_right) < tan_difference_left_right &&
        //    abs(preswapstation.tan_on - preswapstation.tan_under ) < tan_difference_on_under &&
           abs(preswapstation.length_left - preswapstation.length_right) < all_information.left_sub_right_length_thresold &&
           abs(preswapstation.length_on - preswapstation.length_under) < all_information.on_sub_width_thresold;
}
void MatchSwapStation::draw_swapstation(const cv::Mat &image) {
        std::vector<cv::Point2f> Points;
        cv::Point2d points_left_on, points_left_under, points_right_on, points_right_under;
        points_left_on.x = rel_swapstation.left_on.lingt_center.x - rel_swapstation.length_on / 10;
        points_left_on.y = rel_swapstation.left_on.lingt_center.y + rel_swapstation.length_left / 10;
        points_right_on.x = rel_swapstation.right_on.lingt_center.x + rel_swapstation.length_on / 10;
        points_right_on.y = rel_swapstation.right_on.lingt_center.y + rel_swapstation.length_right / 10;
        points_left_under.x = rel_swapstation.left_under.lingt_center.x - rel_swapstation.length_under / 10;
        points_left_under.y = rel_swapstation.left_under.lingt_center.y - rel_swapstation.length_left / 10;
        points_right_under.x = rel_swapstation.right_under.lingt_center.x + rel_swapstation.length_under / 10;
        points_right_under.y = rel_swapstation.right_under.lingt_center.y - rel_swapstation.length_right / 10;
        Points.push_back(points_left_on);
        Points.push_back(points_left_under);
        Points.push_back(points_right_under);
        Points.push_back(points_right_on);
        // std::cout << "左上角的点 = " << Points[0] 
        //           << "左下角的点 = " << Points[1]
        //           << "右下角的点 = " << Points[2]
        //           << "右上角的点 = " << Points[3] << std::endl;
        cv::line(image,Points[0], Points[1],cv::Scalar(0,255,0),2 );
        cv::line(image,Points[1], Points[2],cv::Scalar(0,255,0),2 );
        cv::line(image,Points[2], Points[3],cv::Scalar(0,255,0),2 );
        cv::line(image,Points[3], Points[0],cv::Scalar(0,255,0),2 );
        Points.clear();
        cv::imshow("终图", image);   
    }
void MatchSwapStation::run(const cv::Mat &image) {
    cv::Mat result;
    ImageTrackle trakle_image(all_information.detect_color, all_information.gray_thresolod, all_information.substract_thresold, 120); // 红色 185, 25, 123
    DetectLight my_detect(all_information.min_area,all_information.angle_thresold,all_information.lenbywidth_thresold,all_information.max_area);
    result = trakle_image.TrackleImageSubtract(image);
    my_detect.DetectLightInSwapStation(result,image);
    SwapStation temp_swapstation;
    my_detect.MatchPreSwapStation();
    for (std::vector<LightBar> &swapstation : my_detect.pre_swap_station_arry) {
        temp_swapstation.MatchPreSwapStation(swapstation);
        MatchRelSwapStation(temp_swapstation,image);
    }  
    draw_swapstation(image);
    temp_swapstation.pre_swapstation.clear();
    my_detect.lights.clear();
    my_detect.pre_swap_station_arry.clear();
    rel_swapstation = SwapStation();
}