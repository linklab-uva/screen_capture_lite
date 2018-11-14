#include "common/opencv_display_configuration.h"
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <functional>
#include "utils/img_utils.h"
namespace SL
{
    namespace common
    {

            OpenCVDisplayCapture::OpenCVDisplayCapture(const std::string& search_string) : search_string(search_string), counter(0)
            {
                std::string search(search_string);
                capture_config = SL::Screen_Capture::CreateCaptureConfiguration(std::bind(&OpenCVDisplayCapture::findWindowsCB,this,search));
                capture_config->onNewFrame(std::bind(&OpenCVDisplayCapture::newWindowCB,this,std::placeholders::_1,std::placeholders::_2));
            }
            OpenCVDisplayCapture::~OpenCVDisplayCapture()
            {
              for(std::string window: window_names)
              {
                  cv::destroyAllWindows();
              }
            }
            void OpenCVDisplayCapture::start()
            {
                framegrabber = capture_config->start_capturing();
                framegrabber->setFrameChangeInterval(std::chrono::milliseconds(5));
            }
            std::shared_ptr< SL::Screen_Capture::ICaptureConfiguration<SL::Screen_Capture::WindowCaptureCallback> > OpenCVDisplayCapture::getConfig()
            {
                return capture_config;
            }
            void OpenCVDisplayCapture::newWindowCB(const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Window &window)
            {
                cv::Mat im = SL::utils::convert_to_cv(img);
                cv::imshow("asdf",im);
                cv::imwrite("~/tmpfsfolder/"+ search_string + "/" + std::to_string(counter++) + ".jpg",im);
            }
            std::vector<SL::Screen_Capture::Window> OpenCVDisplayCapture::findWindowsCB(std::string& srchterm)
            {
                auto windows = SL::Screen_Capture::GetWindows();
                std::transform(srchterm.begin(), srchterm.end(), srchterm.begin(), [](char c) { return std::tolower(c, std::locale()); });
                std::vector<SL::Screen_Capture::Window> rtn;
                std::vector<SL::Screen_Capture::Window> filtereditems;
                unsigned int length = windows.size();
                unsigned int filtered_item_number = 0;
                for (unsigned int i = 0; i < length; i++) {
                    SL::Screen_Capture::Window a = windows.at(i);
                    std::string name = a.Name;
                   // std::cout << "Found a window with name: " << name << std::endl;
                    window_names.push_back(name);
                    std::transform(name.begin(), name.end(), name.begin(), [](char c) { return std::tolower(c, std::locale()); });
                    //if (name.compare(srchterm) == 0) {
                    if (name.find(srchterm) != std::string::npos) {
                        filtereditems.push_back(a);
                        printf("[%d] For %s\n", filtered_item_number++, name.c_str());
                    }
                }
                printf("\nWhich windows would you like to track?\n");
                unsigned int blah;
                std::cin >> blah;
                rtn.push_back(filtereditems.at(blah));

                return rtn;
            }
    }
}