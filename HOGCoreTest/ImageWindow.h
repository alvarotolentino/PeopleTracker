//#ifndef __IMAGE_WINDOW_H__
//#define __IMAGE_WINDOW_H__
//
//#include <Fl_Window.H>
//#include <fl_draw.H>
////#include <Rectangle.h>
//#include <Fl_Widget.H>
////#include <events.h>
//
//#include <HOGImage.h>
//
//#include <vector>
//
//using namespace HOG;
//
//class rectangle : public Fl_Widget {
//private:
//	Fl_Color color;
//	void draw(){
//		fl_color(color);
//		fl_rectf(x(), y(), w(), h(), color);
//	}
//
//public:
//	rectangle(int X, int Y, int W, int H, Fl_Color c)
//		:Fl_Widget(X, Y, W, H), color(c) {}
//};
//
//class ImageWidget : public Fl_Widget
//{
//	struct rect
//	{
//		int x, y, w, h;
//		rect(int _x, int _y, int _w, int _h) { x = _x; y = _y; w = _w; h = _h; }
//	};
//
//public:
//	std::vector<rect> rects;
//
//	unsigned char* pixels;
//	rectangle* shape;
//
//	ImageWidget(int x, int y, int w, int h) :
//		Fl_Widget(x, y, w, h)
//	{
//		shape = new rectangle(0, 0, w, h, 256);
//		/*this->box(fltk::BORDER_BOX);
//		this->buttonbox(fltk::FLAT_BOX);*/
//	}
//
//	ImageWidget(int x, int y, int w, int h, unsigned char* pixels) :
//		Fl_Widget(x, y, w, h)
//	{
//		this->pixels = pixels;
//		shape = new rectangle(0, 0, w, h, 256);
//		/*this->box(fltk::BORDER_BOX);
//		this->buttonbox(fltk::FLAT_BOX);*/
//	}
//
//	void draw()
//	{
//		/*fltk::drawimage((unsigned char*)pixels, fltk::RGB32, *shape);
//		fltk::setcolor(fltk::RED);
//		for (size_t i = 0; i < rects.size(); i++)
//			fltk::strokerect(rects[i].x, rects[i].y, rects[i].w, rects[i].h);*/
//		this->redraw();
//	}
//
//	void setImage(unsigned char* pixelsNew)
//	{
//		this->pixels = pixelsNew;
//	}
//
//	void drawRect(int x, int y, int w, int h)
//	{
//		rects.push_back(rect(x, y, w, h));
//		this->redraw();
//	}
//};
//
//class ImageWindow : public Fl_Window
//{
//	bool colorImage;
//
//	int width, height;
//
//	ImageWidget* imageWidget;
//	Fl_Window *otherWindow;
//
//public:
//
//	void(*doStuff)();
//
//	ImageWindow(int width, int height, char* title);
//	ImageWindow(HOGImage* image, char* title);
//
//	void setImage(HOGImage* image);
//
//	void show(int x = -1, int y = -1);
//	void drawRect(int x, int y, int w, int h);
//
//	int handle(int);
//
//	void Close();
//
//	~ImageWindow(void);
//};
//
//#endif
