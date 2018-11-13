#include <ScreenCapture.h>
namespace SL{
    namespace utils{
        bool write_image_to_file(const SL::Screen_Capture::Image &img, const std::string& filepath);
        std::unique_ptr<unsigned char[]> convert_to_buffer(const SL::Screen_Capture::Image &img, unsigned int& height, unsigned int& width);
    }
}