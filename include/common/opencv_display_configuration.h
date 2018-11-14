#include "ScreenCapture.h"
namespace SL
{
    namespace common
    {
        class OpenCVDisplayCapture
        {
            public:
                OpenCVDisplayCapture(const std::string& search_string);
                virtual ~OpenCVDisplayCapture();
                std::shared_ptr< SL::Screen_Capture::ICaptureConfiguration<SL::Screen_Capture::WindowCaptureCallback> > getConfig();
                void start();
            private:
                void newWindowCB(const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Window &window);
                std::vector<SL::Screen_Capture::Window> findWindowsCB(std::string& srchterm);


                std::shared_ptr< SL::Screen_Capture::ICaptureConfiguration<SL::Screen_Capture::WindowCaptureCallback> > capture_config;
                std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager> framegrabber;
                std::vector<std::string> window_names;
                const std::string search_string;
                unsigned long counter;
        };
    }
}