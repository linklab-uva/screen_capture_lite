#include "common/opencv_display_configuration.h"
#include <opencv2/highgui.hpp>


int main(int argc, char** argv)
{
    std::string search;
    if(argc>1)
    {
        search = std::string(argv[1]);
    }
    else
    {
        search = "CMake";
    }
    SL::common::OpenCVDisplayCapture capture(search);

    capture.start();
  
    cv::namedWindow("asdf",cv::WINDOW_AUTOSIZE);

    unsigned int time;
    if(argc>2)
    {   
        time = atoi(argv[2]);
    }
    else
    {
        time = 5;
    }
    cv::waitKey(0);
}