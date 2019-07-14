#include <opencv2/opencv.hpp>

struct parameters {
  int h0, h1, s0, s1, v0, v1;
};

static struct parameters hsv_params = {
    .h0 = 0, .h1 = 75, .s0 = 100, .s1 = 255, .v0 = 31, .v1 = 255};

cv::Mat hsv_range(const cv::Mat& input_image) {
  cv::Mat result_image;

  cv::inRange(
      input_image, cv::Scalar(hsv_params.h0, hsv_params.s0, hsv_params.v0),
      cv::Scalar(hsv_params.h1, hsv_params.s1, hsv_params.v1), result_image);

  cv::createTrackbar("h_low", "Result", &hsv_params.h0, 255);
  cv::createTrackbar("h_high", "Result", &hsv_params.h1, 255);
  cv::createTrackbar("s_low", "Result", &hsv_params.s0, 255);
  cv::createTrackbar("s_high", "Result", &hsv_params.s1, 255);
  cv::createTrackbar("v_low", "Result", &hsv_params.v0, 255);
  cv::createTrackbar("v_high", "Result", &hsv_params.v1, 255);
#if (CV_VERSION_MAJOR >= 4)
  cv::namedWindow("Result", cv::WINDOW_NORMAL);
#else
  cv::namedWindow("Result", CV_WINDOW_NORMAL);
#endif
  cv::imshow("Result", result_image);

  return result_image;
}
