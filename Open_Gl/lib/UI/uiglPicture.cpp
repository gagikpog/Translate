#include <fstream>
#include <ctime>

#include "uiglPicture.h"
#include "../uiglFunc.h"

namespace UIGL {

	UiglPicture::UiglPicture()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		H = W = 100.f;
	}
	void UiglPicture::Init()
	{
		float _w, _h;
		if (w_p != 0 && h_p != 0)
		{
			_w = W / w_p;
			_h = H / h_p;
		}
		else {
			_w = 1; _h = 1;
		}
		bool contour(0);
		for (int i = 0; i < layers.size(); i++)
		{
			glBegin(layers[i].primitive);
			Line_init(layers[i].primitive, layers[i].line_length);
			for (int j = 0; j < points[i].size(); j++)
			{
				points[i][j].Color.Init();
				glVertex2f(points[i][j].X*_w + X, points[i][j].Y*_h + Y);
				contour = 1;
			}
			Line_init(layers[i].primitive);
			glEnd();
		}

		if (!contour)
			drawRectangleContour(X, Y, W, H, Outline_color);

		///		glLineWidth(1);
		//		glPointSize(1);
	}
	bool UiglPicture::Open(std::string _file_name)
	{
		layers.clear();
		points.clear();
		if (_file_name == "")
			_file_name = file_name;
		else file_name = _file_name;
		std::ifstream in;
		in.open(_file_name, std::ios::binary);
		if (!in.is_open())
			return 0;
		Layer _L;
		UiglPoint _P;
		int n(0);
		in >> W >> H;
		in.get();
		w_p = W;
		h_p = H;
		std::vector<UiglPoint> pp;
		while (!in.eof())
		{
			in.read((char*)&_L, sizeof(_L));
			layers.push_back(_L);
			points.push_back(std::vector<UiglPoint>());
			for (int i = 0; i < _L.count && !in.eof(); i++)
			{
				in.read((char*)&_P, sizeof(_P));
				points[n].push_back(_P);
			}
			n++;
		}
		return 1;
	}
	UiglEvent UiglPicture::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == 0 && button == 0)
			{
				result.Event = uiglMouseLeftDown;
				moved = true;
				mx = ax - X;
				my = ay - Y;

				if (clock() - double_ckick < 350)
				{
					double_ckick = clock();
					result.Event = uiglDoubleClick;
				}
				else double_ckick = clock();

				return result;
			}
			if (state == 1 && button == 0)
			{
				result.Event = uiglMouseLeftUp;
				moved = false;
				return result;
			}
			if (state == 0 && button == 1)
			{
				result.Event = uiglMouseCenterDown;
				return result;
			}
			if (state == 1 && button == 1)
			{
				result.Event = uiglMouseCenterUp;
				return result;
			}
			if (state == 0 && button == 2)
			{
				result.Event = uiglMouseRightDown;
				return result;
			}
			if (state == 1 && button == 2)
			{
				result.Event = uiglMouseRightUp;
				return result;
			}
		}
		return result;
	}
	UiglEvent UiglPicture::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{

			if (!Mouse_in_button)
			{
				Mouse_in_button = true;
				result.Name = Name;
				result.Event = uiglMouseOver;
				return result;
			}
			else {

				result.Name = Name;
				result.Event = uiglMousemove;
				return result;
			}
		}
		else
		{
			if (Mouse_in_button)
			{
				result.Name = Name;
				result.Event = uiglMouseOut;
				Mouse_in_button = false;
				return result;
			}
		}
		return result;
	}
	UiglEvent UiglPicture::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.setPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent UiglPicture::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent UiglPicture::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && key == 13)
		{
			result.Event = uiglEnter;
			result.Name = Name;
		}
		return result;
	}
	UiglEvent UiglPicture::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglPicture::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglPicture::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void UiglPicture::Line_init(uiglPrimitives prim, float length)
	{
		switch (prim)
		{
		case uiglPOINTS:
			glPointSize(length);
			break;
		case uiglLINES:
		case uiglLINE_LOOP:
		case uiglLINE_STRIP:
			glLineWidth(length);
			break;
		case uiglTRIANGLES:
		case uiglTRIANGLE_STRIP:
		case uiglTRIANGLE_FAN:
		case uiglQUADS:
		case uiglQUAD_STRIP:
		case uiglPOLYGON:
			break;
		}
	}
}