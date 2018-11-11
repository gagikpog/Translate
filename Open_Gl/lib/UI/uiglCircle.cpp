#include <ctime>

#include "uiglcircle.h"
#include "../uiglFunc.h"

namespace UIGL {
	uiglCircle::uiglCircle()
	{
		Position.UpdatePtr = this;
		//		Size.UpdatePtr = this;
		R = 10;
	}
	UiglEvent uiglCircle::MouseFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;

		if (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R)
		{

			result.Name = Name;
			if (state == 0 && button == 0)
			{
				result.Event = UIGL::uiglEvents::uiglMouseLeftDown;
				moved = true;
				mx = ax - X;
				my = ay - Y;

				if (clock() - double_ckick < 350)
				{
					double_ckick = clock();
					result.Event = UIGL::uiglEvents::uiglDoubleClick;
				}
				else double_ckick = clock();

				return result;
			}
			if (state == 1 && button == 0)
			{
				result.Event = UIGL::uiglEvents::uiglMouseLeftUp;
				moved = false;
				return result;
			}
			if (state == 0 && button == 1)
			{
				result.Event = UIGL::uiglEvents::uiglMouseCenterDown;
				return result;
			}
			if (state == 1 && button == 1)
			{
				result.Event = UIGL::uiglEvents::uiglMouseCenterUp;
				return result;
			}
			if (state == 0 && button == 2)
			{
				result.Event = UIGL::uiglEvents::uiglMouseRightDown;
				return result;
			}
			if (state == 1 && button == 2)
			{
				result.Event = UIGL::uiglEvents::uiglMouseRightUp;
				return result;
			}
		}
		return result;
	}
	UiglEvent uiglCircle::PassiveMotionFunc(int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		if (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R)
		{

			if (!Mouse_in_button)
			{
				Mouse_in_button = true;
				result.Name = Name;
				result.Event = UIGL::uiglEvents::uiglMouseOver;
				return result;
			}
			else {

				result.Name = Name;
				result.Event = UIGL::uiglEvents::uiglMousemove;
				return result;
			}
		}
		else
		{
			if (Mouse_in_button)
			{
				result.Name = Name;
				result.Event = UIGL::uiglEvents::uiglMouseOut;
				Mouse_in_button = false;
				return result;
			}
		}
		return result;
	}
	UiglEvent uiglCircle::MotionFunc(float ax, float ay)
	{
		if (!Visible) return UiglEvent();
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
	UiglEvent uiglCircle::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		if (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R)
		{
			result.Name = Name;
			if (state == -1)
				result.Event = UIGL::uiglEvents::uiglWheelDown;
			if (state == 1)
				result.Event = UIGL::uiglEvents::uiglWheelUp;
		}
		return result;
	}
	UiglEvent uiglCircle::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;
	}
	UiglEvent uiglCircle::SpecialFunc(int key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;
	}
	UiglEvent uiglCircle::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;

	}
	UiglEvent uiglCircle::SpecialUpFunc(int key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;
	}
	void uiglCircle::Init()
	{
		if (!Visible) return;
		if (Position.UpdatePtr != this)
		{
			Position.UpdatePtr = this;
		}
		int _n = 0;
		if (Mouse_in_button&&IsHover)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		drawCircle(X, Y, R, Color + _n, Outline_color_temp);
	}
	void uiglCircle::Update()
	{
		Position.UpdatePtr = this;
		X = Position.getPositionX();
		Y = Position.getPositionY();
		H = Size.getSizeH();
		W = Size.getSizeW();
	}
}