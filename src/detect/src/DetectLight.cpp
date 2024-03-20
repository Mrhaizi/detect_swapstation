#include <detect.h>

DetectLight::DetectLight(const float min_area, const float angle, const float number, const float max_area) {
    max_light_area = max_area;
    min_light_area = min_area;
    light_angle = angle;
    weightbyheight = number;
}
void DetectLight::DetectLightInSwapStation(const cv::Mat &image, const cv::Mat &image1) {
    std::vector<std::vector<cv::Point>> contours; // 存放临时轮廓的vector向量
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(image,contours,hierarchy,0,2);
    cv::RotatedRect rotated_rect;// 拟合由灯条轮廓匹配的椭圆得来的旋转矩形
    cv::Rect max_rect;
    LightBar light;
    for (const auto &contour : contours) {
        if (contour.size() < 6) {
            continue;
        }
        if (cv::contourArea(contour) < min_light_area) {
            continue;
        }
        if (cv::contourArea(contour) > max_light_area) {
            continue;
        }
        rotated_rect = cv::minAreaRect(contour);// 拟合旋转矩形
        // max_rect = cv::boundingRect(contour);
        // cv::rectangle(image1, max_rect, cv::Scalar(0, 255, 0), 1, 8, 0);
        float height = std::max(rotated_rect.size.height, rotated_rect.size.width);
        float width = std::min(rotated_rect.size.height, rotated_rect.size.width);
        if (height / width > weightbyheight) {
            continue;
        }
        light = LightBar(rotated_rect);
        cv::Point2f rectPoints[4];
        light.light_rect.points(rectPoints);
        for (int i = 0; i < 4; i++) {   
            cv::line(image1, rectPoints[i], rectPoints[(i + 1) % 4], cv::Scalar(0, 0, 255), 2);
        } 
        lights.push_back(light);
    }
}
void DetectLight::MatchPreSwapStation() {
    std::vector<std::vector<LightBar>> swapstation_half;
    std::vector<LightBar> pre_swap_station;
    std::cout << lights.size() << std::endl;
    if (lights.size() > 4) {
        std::vector<LightBar> temp_arr1;
        for (int i = 0; i < lights.size() - 1; i++) {
            temp_arr1.push_back(lights[i]);
            for (int j = i + 1; j <lights.size(); j++) {
                temp_arr1.push_back(lights[j]);
                for ( int k = j + 1; k < lights.size() + 1; k++) {
                    temp_arr1.push_back(lights[k]);
                    for (int l = k + 1; l < lights.size() + 2; l++) {
                        temp_arr1.push_back(lights[l]);
                        pre_swap_station_arry.push_back(temp_arr1);
                        temp_arr1.pop_back();
                    }
                    temp_arr1.pop_back();
                }
                temp_arr1.pop_back();
            }
            temp_arr1.pop_back();
        }
        // std::clock_t end_two = clock();
        // std::cout << "第二种方法的计算时间为 = " << end_two - start_one << std::endl;
        std::cout << "兑换站匹配完毕" << std::endl;
    } else if (lights.size() == 4) {
        std::vector<LightBar> temp;
        temp.push_back(lights[0]);
        temp.push_back(lights[1]);
        temp.push_back(lights[2]);
        temp.push_back(lights[3]);
        pre_swap_station_arry.push_back(temp);
    } else {
        std::cout << "point is not enough" << std::endl;

    }
}   