#include <ScreenCapture.h>
namespace cv{
    class Mat;
}
namespace SL{
    namespace utils{
        bool write_image_to_file(const SL::Screen_Capture::Image &img, const std::string& filepath);
        cv::Mat convert_to_cv(const SL::Screen_Capture::Image &img);
    }
}