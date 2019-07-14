#include <tclap/CmdLine.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "hsv_range.hpp"

int main(int argc, char** argv) {
  // Parse arguments
  std::string camera_device;
  // wrap everything in a try block.
  // do this every time, because exceptions will be thrown for problems.
  try {
    TCLAP::CmdLine cmd("Color segmentation for live video stream", ' ',
                       "1.0.0");
    TCLAP::ValueArg<std::string> dev_arg("d", "device", "path to camera device",
                                         false, "", "string");
    cmd.add(dev_arg);

    // parse the argv array.
    cmd.parse(argc, argv);

    // get the value parsed by each arg.
    camera_device = dev_arg.getValue();
  } catch (TCLAP::ArgException& e)  // catch any exceptions
  {
    std::cerr << "Error: " << e.error() << " for arg " << e.argId()
              << std::endl;
  }

  // Open camera device
  cv::VideoCapture cap;
  if (camera_device.empty()) {
    camera_device = "0";
    cap.open(0);
  } else {
    cap.open(camera_device);
  }
  if (!cap.isOpened()) {
    std::cerr << "VideoCapture not opened" << std::endl;
    return -1;
  }
  std::cout << "Camera device: " << camera_device << std::endl;

  // Get properties of input video frame
  int camera_width(640), camera_height(480), camera_fps(30);
#if (CV_VERSION_MAJOR >= 4)
  camera_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  camera_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  camera_fps = cap.get(cv::CAP_PROP_FPS);
#else
  camera_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  camera_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  camera_fps = cap.get(CV_CAP_PROP_FPS);
#endif
  std::cout << "Frame property: " << camera_width << "x" << camera_height << "@"
            << camera_fps << "fps" << std::endl;

  // Feed captured frames into the writer
  std::cout << "\033[1;34mStart capturing\033[0m" << std::endl;
  std::cout << "Press any key to exit" << std::endl;
  while (true) {
    cv::Mat frame;
    // get a new frame from camera
    cap >> frame;
    if (!frame.empty()) {
      // show the original frame
#if (CV_VERSION_MAJOR >= 4)
      cv::namedWindow("Original", cv::WINDOW_NORMAL);
#else
      cv::namedWindow("Original", CV_WINDOW_NORMAL);
#endif
      cv::imshow("Original", frame);
      // process frame
      cv::Mat processed = hsv_range(frame);
    } else {
      std::cerr << "Skip invalid frame" << std::endl;
    }
    // wait for key event to keep fps
    if (cv::waitKey(30) >= 0) {
      break;
    }
  }
  // the camera will be de-initialized automatically in VideoCapture destructor
  cv::destroyAllWindows();
  return 0;
}
