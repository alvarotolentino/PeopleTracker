#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <arrayfire.h>

#include "Captor.h"

Captor::Captor()
{
	capture = NULL;
	camconnected = 0;
}

Captor::~Captor()
{
	if (capture.isOpened())
		capture.release();
}

int Captor::Connect(int deviceID, const char* filename)
{
	if (filename == nullptr)
		capture.open(deviceID);
	else
		capture.open(filename);

	if (capture.isOpened())
	{
		camconnected = 1;
		return 1;
	}
	camconnected = 0;
	printf("Error connecting to camera \n");
	exit(-1);
	return 0;
}

int Captor::isValid()
{
	return camconnected;
}

int Captor::InitCapture()
{
	if (capture.isOpened())
	{
		capture >> frame;
		return 1;
	}
	return 0;
}

// mem layout for gpu
inline void mat_to_array_(cv::Mat& input, af::array& output) {
	const unsigned size = input.rows * input.cols;
	const unsigned w = input.cols;
	const unsigned h = input.rows;
	const unsigned channels = input.channels();
	if (channels == 1) {
		// bw
		input.convertTo(input, CV_32F);
		output = af::array(w, h, input.ptr<float>(0)).T();
	}
	else if (channels == 3) {
		// color
		input.convertTo(input, CV_32FC3);
		std::vector<cv::Mat> rgb;
		cv::split(input, rgb);
		output = af::array(h, w, 3);
		output(af::span, af::span, 0) = af::array(w, h, rgb[2].ptr<float>(0)).T();
		output(af::span, af::span, 1) = af::array(w, h, rgb[1].ptr<float>(0)).T();
		output(af::span, af::span, 2) = af::array(w, h, rgb[0].ptr<float>(0)).T();
	}
	else {
		// 2 ch
		input.convertTo(input, CV_32FC2);
		std::vector<cv::Mat> gb; split(input, gb);
		output = af::array(h, w, 2);
		output(af::span, af::span, 0) = af::array(w, h, gb[1].ptr<float>(0)).T();
		output(af::span, af::span, 1) = af::array(w, h, gb[0].ptr<float>(0)).T();
	}
}

// mem layout for gpu
void Captor::mat_to_array(const cv::Mat& input, af::array& output)
{
	cv::Mat tmp = input.clone();
	mat_to_array_(tmp, output);
}

af::array Captor::mat_to_array(const cv::Mat& input)
{
	af::array output;
	cv::Mat mtmp = input.clone();
	mat_to_array_(mtmp, output);
	return output;
}

void Captor::array_to_mat(const af::array& input_, cv::Mat& output, int type)
{
	const int channels = input_.dims(2);
	int ndims = input_.numdims();
	af::array input;
	if (channels == 1)
		input = input_.T();
	else {
		input = af::constant(0, channels, input_.dims(1), input_.dims(0));
		gfor(af::array ii, channels)
		{
			input(channels - ii - 1, af::span, af::span) = input_(af::span, af::span, ii).T();
		}
	}
	output = cv::Mat(input.dims(ndims - 1), input.dims(ndims - 2), CV_MAKETYPE(type, channels));

	if (type == CV_32F) {
		float* data = output.ptr<float>(0);
		input.host((void*)data);
	}
	else if (type == CV_64F) {
		double* data = output.ptr<double>(0);
		input.as(f64).host((void*)data);
	}
	else if (type == CV_8U) {
		uchar* data = output.ptr<uchar>(0);
		input.as(b8).host((void*)data);
	}
	else
	{
		printf("array_to_mat: invalid conversion");
	}
}

cv::Mat Captor::array_to_mat(const af::array& input, int type)
{
	cv::Mat output;
	array_to_mat(input, output, type);
	return output;
}

//int main(int argc, char** argv)
//{
//	// Open a webcamera
//	cv::VideoCapture cap;
//
//	if (argc < 2)
//		cap.open(0);
//	else
//		cap.open(std::string(argv[1]));
//
//	if (!cap.isOpened())
//	{
//		printf("\nCan not open camera or video file\n");
//		return -1;
//	}
//
//
//	cv::Mat frame;
//	cap >> frame;
//	if (!frame.data)
//	{
//		printf("can not read data from the video source\n");
//		return -1;
//	}
//
//	// Create the capture windows
//	cv::namedWindow("Source", 1);
//
//	cv::TickMeter tm;
//	std::vector<double> gpu_times;
//	// Loop while capturing images
//	for (;;)
//	{
//		tm.reset(); tm.start();
//		cap >> frame;
//		if (!frame.data)
//			break;
//		tm.stop();
//		gpu_times.push_back(tm.getTimeMilli());
//
//		// Show the results
//		cv::imshow("Source", frame);
//		int keycode = cv::waitKey(30);
//		if (keycode == 27)
//			break;
//	}
//
//	if (!gpu_times.empty())
//	{
//		std::cout << std::endl << "Results:" << std::endl;
//
//		std::sort(gpu_times.begin(), gpu_times.end());
//
//		double gpu_avg = std::accumulate(gpu_times.begin(), gpu_times.end(), 0.0) / gpu_times.size();
//
//		std::cout << "GPU : Avg : " << gpu_avg << " ms FPS : " << 1000.0 / gpu_avg << std::endl;
//	}
//	std::cin.get();
//	return 0;
//}
