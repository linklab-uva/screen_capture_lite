#include "utils/img_utils.h"
#include "ScreenCapture.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <exception>
namespace SL{
    namespace utils{
    cv::Mat convert_to_cv(const SL::Screen_Capture::Image &img){
        unsigned int height = SL::Screen_Capture::Height(img);
        unsigned int width = SL::Screen_Capture::Width(img);
        unsigned int size = height*width*sizeof(SL::Screen_Capture::ImageBGRA);
        
        cv::Mat img_cv;
        img_cv.create(height, width, CV_8UC4);
        SL::Screen_Capture::Extract(img,img_cv.data,size);
        return img_cv;
    }
    bool write_image_to_file(const SL::Screen_Capture::Image &img, const std::string& filepath){
        cv::Mat img_cv = convert_to_cv(img);
        return cv::imwrite(filepath,img_cv);
    }

    }
}
