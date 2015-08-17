#include <stdio.h>
//#include <HOGEngine.h>
//#include <HOGImage.h>
//#include <Fl.H>
//#include <fl_draw.H>
//#include <Fl_Widget.H>
#include "Timer.h"
#include "persondetectorwt.tcc"
#include "ImageWindow.h"
#include "../Core/HOGCore/HOG/HOGImage.h"
#include "../Core/HOGCore/HOG/HOGEngine.h"
#include "../Core/CaptorCore/Captor.h"

using namespace HOG;
HOGImage* image;
HOGImage* imageCUDA;
Captor* captor;

void doStuffHere()
{
	HOGEngine::Instance()->InitializeHOG(image->width, image->height,
		PERSON_LINEAR_BIAS, PERSON_WEIGHT_VEC, PERSON_WEIGHT_VEC_LENGTH);

	//HOGEngine::Instance()->InitializeHOG(image->width, image->height,
	//		"Files//SVM//head_W24x24_C4x4_N2x2_G4x4_HeadSize16x16.alt");

	Timer t;
	t.restart();
	HOGEngine::Instance()->BeginProcess(image);
	HOGEngine::Instance()->EndProcess();
	t.stop(); t.check("Processing time");

	printf("Found %d positive results.\n", HOGEngine::Instance()->formattedResultsCount);

	HOGEngine::Instance()->GetImage(imageCUDA, HOGEngine::IMAGE_ROI);
	//fastHOGWindow->setImage(imageCUDA);

	for (int i = 0; i < HOGEngine::Instance()->nmsResultsCount; i++)
	{
		printf("%1.5f %1.5f %4d %4d %4d %4d %4d %4d\n",
			HOGEngine::Instance()->nmsResults[i].scale,
			HOGEngine::Instance()->nmsResults[i].score,
			HOGEngine::Instance()->nmsResults[i].origX,
			HOGEngine::Instance()->nmsResults[i].origY,
			HOGEngine::Instance()->nmsResults[i].x,
			HOGEngine::Instance()->nmsResults[i].y,
			HOGEngine::Instance()->nmsResults[i].width,
			HOGEngine::Instance()->nmsResults[i].height);

		/*fastHOGWindow->drawRect(HOGEngine::Instance()->nmsResults[i].x,
			HOGEngine::Instance()->nmsResults[i].y,
			HOGEngine::Instance()->nmsResults[i].width,
			HOGEngine::Instance()->nmsResults[i].height);*/
	}

	printf("Drawn %d positive results.\n", HOGEngine::Instance()->nmsResultsCount);

	HOGEngine::Instance()->FinalizeHOG();
}

void Process()
{
	string window_name = "video | q or esc to quit";
	cout << "press space to save a picture. q or esc to quit" << endl;
	cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
	
	
	for (;;)
	{
		captor->InitCapture();
		if (captor->frame.empty())
			break;

		cv::imshow(window_name, captor->frame);
		char key = char(cv::waitKey(5)); //delay N millis, usually long enough to display and capture input

		image = new HOGImage(captor->frame.data, captor->frame.rows, captor->frame.cols);
		imageCUDA = new HOGImage(image->width, image->height);
		doStuffHere();

		switch (key) {
		case 'q':
		case 'Q':
		case 27: //escape key
			return;
		default:
			break;
		}
	}

}

int main(int ac, char** av)
{
	captor = new Captor();
	char * arg = "C:/Users/Alvaro/Documents/Cursos/PUCP/TESIS/Dataset/TownCentreXVID.avi";
	captor->Connect(0, arg);
	if (captor->camconnected)
		Process();

	free(captor);
	//image = new HOGImage("C:/Users/Alvaro/Documents/GitHub/PeopleTracker/HOGCoreTest/Images/testImage.bmp");
	//imageCUDA = new HOGImage(image->width,image->height);

	///*fastHOGWindow = new ImageWindow(image, "fastHOG");
	//fastHOGWindow->doStuff = &doStuffHere;
	//fastHOGWindow->show();

	//Fl::run();*/
	//doStuffHere();
	//delete image;
	//delete imageCUDA;

	//return 0;
}
