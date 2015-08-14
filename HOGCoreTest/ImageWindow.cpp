//#include "ImageWindow.h"
//
//#include <stdio.h>
//#include <fl_draw.H>
//
//ImageWindow::ImageWindow(int width, int height, char* title) :
//Fl_Window(width, height, title)
//{
//
//	this->width = width;
//	this->height = height;
//
//	this->begin();
//	imageWidget = new ImageWidget(0, 0, width, height);
//	this->end();
//
//	doStuff = 0;
//}
//
//ImageWindow::ImageWindow(HOGImage* image, char* title) :
//Fl_Window(image->width, image->height, title)
//{
//	this->width = image->width;
//	this->height = image->height;
//
//	this->begin();
//	imageWidget = new ImageWidget(0, 0, image->width, image->height, image->pixels);
//	this->end();
//
//	doStuff = 0;
//}
//
//ImageWindow::~ImageWindow(void) { }
//
//void ImageWindow::show(int x, int y)
//{
//	if (x == -1 || y == 1)
//		Fl_Window::show();
//	else
//	{
//		this->position(x, y);
//		Fl_Window::show();
//	}
//}
//
//void ImageWindow::setImage(HOGImage* image)
//{
//	this->begin();
//	imageWidget->setImage((unsigned char*)image->pixels);
//	imageWidget->draw();
//	this->end();
//}
//
//int ImageWindow::handle(int eventId)
//{
//	int ret = 0;
//	/*switch (eventId)
//	{
//	case fltk::MOVE:
//		ret = 1;
//
//		break;
//	case fltk::PUSH:
//
//		imageWidget->rects.clear();
//
//		if (doStuff != 0)
//			doStuff();
//
//		break;
//	}*/
//
//	return ret;
//}
//
//void ImageWindow::drawRect(int x, int y, int w, int h)
//{
//	imageWidget->drawRect(x, y, w, h);
//}
//
//void ImageWindow::Close()
//{
//	delete imageWidget;
//
//	//this->destroy();
//}
