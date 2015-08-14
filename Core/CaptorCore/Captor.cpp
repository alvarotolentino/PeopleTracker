#include <stdio.h>
#include <iostream>
#include <numeric>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>

int main(int argc, char** argv)
{
	// Open a webcamera
	cv::VideoCapture cap;

	if (argc < 2)
		cap.open(0);
	else
		cap.open(std::string(argv[1]));

	if (!cap.isOpened())
	{
		printf("\nCan not open camera or video file\n");
		return -1;
	}


	cv::Mat frame;
	cap >> frame;
	if (!frame.data)
	{
		printf("can not read data from the video source\n");
		return -1;
	}

	// Create the capture windows
	cv::namedWindow("Source", 1);

	cv::TickMeter tm;
	std::vector<double> gpu_times;
	// Loop while capturing images
	for (;;)
	{
		tm.reset(); tm.start();
		cap >> frame;
		if (!frame.data)
			break;
		tm.stop();
		gpu_times.push_back(tm.getTimeMilli());

		// Show the results
		cv::imshow("Source", frame);
		int keycode = cv::waitKey(30);
		if (keycode == 27)
			break;
	}

	if (!gpu_times.empty())
	{
		std::cout << std::endl << "Results:" << std::endl;

		std::sort(gpu_times.begin(), gpu_times.end());

		double gpu_avg = std::accumulate(gpu_times.begin(), gpu_times.end(), 0.0) / gpu_times.size();

		std::cout << "GPU : Avg : " << gpu_avg << " ms FPS : " << 1000.0 / gpu_avg << std::endl;
	}
	std::cin.get();
	return 0;
}
