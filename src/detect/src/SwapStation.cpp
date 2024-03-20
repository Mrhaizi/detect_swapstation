#include <detect.h>
SwapStation::SwapStation() {

}
SwapStation::~SwapStation() {
    pre_swapstation.clear();
}
void SwapStation::MatchPreSwapStation(const std::vector<LightBar> light_arry) {
    pre_swapstation = light_arry;
    if (pre_swapstation.size()>1) {
        for (int i = 0; i < pre_swapstation.size() - 1; i++) {
            for (int j = i+1; j < pre_swapstation.size(); j++) {
                LightBar temporay_light;
                if (pre_swapstation[i].lingt_center.x > pre_swapstation[j].lingt_center.x) {
                    temporay_light = pre_swapstation[j];
                    pre_swapstation[j] = pre_swapstation[i];
                    pre_swapstation[i] = temporay_light;
                }
            }
        } 
        if (pre_swapstation[0].lingt_center.y < pre_swapstation[1].lingt_center.y) {
            left_on = pre_swapstation[1];
            left_under = pre_swapstation[0];
        } else {
            left_on = pre_swapstation[0];
            left_under = pre_swapstation[1];
        }
        if (pre_swapstation[2].lingt_center.y < pre_swapstation[3].lingt_center.y) {
            right_on = pre_swapstation[3];
            right_under = pre_swapstation[2];
        } else { 
            right_on = pre_swapstation[2];
            right_under = pre_swapstation[3];
        }
        ComputerParam();
    }
}
void SwapStation::ComputerParam() {
    length_left = std::sqrt((left_on.lingt_center.x - left_under.lingt_center.x) *  (left_on.lingt_center.x - left_under.lingt_center.x) +(left_on.lingt_center.y - left_under.lingt_center.y) *  (left_on.lingt_center.y - left_under.lingt_center.y));
    length_right = std::sqrt((right_on.lingt_center.x - right_under.lingt_center.x) *  (right_on.lingt_center.x - right_under.lingt_center.x) +(left_on.lingt_center.y - left_under.lingt_center.y) *  (left_on.lingt_center.y - left_under.lingt_center.y));
    length_on = std::sqrt((left_on.lingt_center.x - right_on.lingt_center.x) * (left_on.lingt_center.x - right_on.lingt_center.x) + (left_on.lingt_center.y - right_on.lingt_center.y) * (left_on.lingt_center.y - right_on.lingt_center.y));
    length_under = std::sqrt((left_under.lingt_center.x - right_under.lingt_center.x) *  (left_under.lingt_center.x - right_under.lingt_center.x) + (left_under.lingt_center.y - right_under.lingt_center.y) *  (left_under.lingt_center.y - right_under.lingt_center.y));
    diagonal_len_loru = std::sqrt((left_on.lingt_center.x - right_under.lingt_center.x) *  (left_on.lingt_center.x - right_under.lingt_center.x) + (left_on.lingt_center.y - right_under.lingt_center.y) *  (left_on.lingt_center.y - right_under.lingt_center.y));
    diagonal_len_luro = std::sqrt((left_under.lingt_center.x - right_on.lingt_center.x) * (left_under.lingt_center.x - right_on.lingt_center.x) + (left_under.lingt_center.y - right_on.lingt_center.y) * (left_under.lingt_center.y - right_on.lingt_center.y));
}   

