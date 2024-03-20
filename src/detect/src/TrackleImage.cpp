#include <detect.h>

ImageTrackle::ImageTrackle(const DetectColor &color,
                           const int &thresold_gray,
                           const int &thresold_color,
                           const int &thresold_yuv) {
   color_image_thresold = thresold_color;
   gray_image_thresold = thresold_gray;
   my_color = color;
   yuv_image_thresold =thresold_yuv; 
}
cv::Mat ImageTrackle::TrackleImageSubtract(const cv::Mat &image) {
    cv::Mat img_color, img_subtract, img_yuv, kernel_a, kernel_b, img_gray, result;
    std::vector<cv::Mat> split_img;
    cv::split(image,split_img);
    if (my_color == BLUE) {
        // cv::cvtColor(image)
        img_subtract = split_img[0] - split_img[2];

    } else {
        img_subtract = split_img[2] - split_img[0];
        // cv::Mat img_subtract_other = split_img[2] + split_img[1];
        // cv::bitwise_and(img_subtract, img_subtract_other, img_subtract);
    }
    cv::cvtColor(image,img_gray,10);
    cv::threshold(img_gray,img_gray,gray_image_thresold,255,0);
    cv::threshold(img_subtract,img_subtract,color_image_thresold,255,0);
    cv::bitwise_and(img_gray,img_subtract,result);
    // cv::bitwise_and(result, vector_yuv[1],result);
    kernel_b = cv::getStructuringElement(0,cv::Size(2, 2));
    kernel_a = cv::getStructuringElement(0,cv::Size(3, 3));
    // cv::morphologyEx(result,result,0,kernel_a,cv::Point(-1,-1),2);
    // cv::morphologyEx(result, result, 0, kernel_b, cv::Point(-1,-1), 1);
    // cv::morphologyEx(result, result, 1, kernel_a, cv::Point(-1,-1), 2);
    cv::imshow("img_subtract",img_subtract);
    cv::imshow("result", result);
    cv::imshow("img_gray", img_gray);
    cv::waitKey(1);
    return result;
}

   