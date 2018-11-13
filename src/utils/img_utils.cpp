#include "utils/img_utils.h"
#include "ScreenCapture.h"
#include <iostream>
#ifdef WITH_OPENCV
    #include <opencv2/core.hpp>
    #include <opencv2/imgcodecs.hpp>
#else
    #include <exception>
#endif
namespace SL{
    namespace utils{
#ifdef WITH_OPENCV
    bool write_image_to_file(const SL::Screen_Capture::Image &img, const std::string& filepath){
        unsigned int height;
        unsigned int width;
      //  std::cout << "Converting image" << std::endl;
        std::unique_ptr<unsigned char[]>  buff = convert_to_buffer(img, height, width);
       // std::cout << "Converted image" << std::endl;
        cv::Mat img_cv(height, width, CV_8UC4, buff.get());
       // std::cout << "Made CV image" << std::endl;
        cv::imwrite(filepath,img_cv);
        //std::cout << "Wrote image" << std::endl;
    }
#else
        bool write_image_to_file(const SL::Screen_Capture::Image &img, const std::string& filepath){
            throw std::runtime_error("Image writing only supported through OpenCV interface");
        }
#endif

        std::unique_ptr<unsigned char[]> convert_to_buffer(const SL::Screen_Capture::Image &img, unsigned int& height, unsigned int& width){
            auto imgsrc = SL::Screen_Capture::StartSrc(img);
            height = SL::Screen_Capture::Height(img);
            width = SL::Screen_Capture::Width(img);
            unsigned int size = height * width * sizeof(SL::Screen_Capture::ImageBGRA);
            auto imgbuffer(std::make_unique<unsigned char[]>(size));
            unsigned char* imgdist = imgbuffer.get();

            for (auto h = 0; h < Height(img); h++) {
                auto startimgsrc = imgsrc;
                for (auto w = 0; w < Width(img); w++) {
                    //std::cout << "Converting pixel (" <<h<<", "<<w<<")"<<std::endl;
                    *imgdist++ = imgsrc->B;
                    *imgdist++ = imgsrc->G;
                    *imgdist++ = imgsrc->R;
                    *imgdist++ = imgsrc->A;
                    imgsrc++;
                }
                imgsrc = SL::Screen_Capture::GotoNextRow(img, startimgsrc);
            }
            return imgbuffer;
        }
    }
}
