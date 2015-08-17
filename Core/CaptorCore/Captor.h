
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <arrayfire.h>

class Captor
{
public:
	// Constructor
	Captor();

	// Destructor
	virtual ~Captor();

	// Connection to the camera
	cv::VideoCapture capture;

	// Frame
	cv::Mat frame;

	// flag for init capture connection
	int camconnected;

	// sets up the camera capture object
	int Connect(int deviceID = 0, const char* filename = nullptr);

	// returns 1 if connected to camera capture
	int isValid();

	// grabs raw opencv image (into global visCvRaw)
	int InitCapture();

	// mem layout for gpu
	void mat_to_array(const cv::Mat& input, af::array& output);
	af::array mat_to_array(const cv::Mat& input);

	// mem layout for cpu
	void array_to_mat(const af::array& input, cv::Mat& output, int type = CV_32F);
	cv::Mat array_to_mat(const af::array& input, int type = CV_32F);

};
