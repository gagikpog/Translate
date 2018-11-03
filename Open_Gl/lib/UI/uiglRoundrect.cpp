#include <ctime>

#include "uiglRoundrect.h"
#include "../uiglFunc.h"

namespace UIGL{
	UiglRoundrect::UiglRoundrect()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 50;
		H = 50;
		R = 20;
		Color = Silver;
	}
	UiglEvent UiglRoundrect::MouseFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = (int)rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = (int)axt;

		UiglEvent result;
		bool lu, ld, ru, rd, B1, B2;
		B1 = ((ax > X) && (ax < X + W) && (ay > Y + R) && (ay < Y + H - R));
		B2 = (ax > X + R && ax < X + W - R && ay>Y     && ay < Y + H);
		lu = (sqrt((X + R - ax)*(X + R - ax) + (Y + H - R - ay)*(Y + H - R - ay)) < R);
		ld = (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R);
		ru = (sqrt((X + W - R - ax)*(X + W - R - ax) + (Y + H - R - ay)*(Y + H - R - ay)) < R);
		rd = (sqrt((X + W - R - ax)*(X + W - R - ax) + (Y + R - ay)*(Y + R - ay)) < R);

		if (B1 || B2 || lu || ld || ru || rd)
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
	UiglEvent UiglRoundrect::PassiveMotionFunc(int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = (int)rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = (int)axt;

		if (R > H / 2 || R > W / 2)
		{
			if (W > H)
				R = H / 2;
			else R = W / 2;
		}
		UiglEvent result;
		bool lu, ld, ru, rd, B1, B2;
		B1 = ((ax > X) && (ax < X + W) && (ay > Y + R) && (ay < Y + H - R));
		B2 = (ax > X + R && ax < X + W - R && ay>Y     && ay < Y + H);
		lu = (sqrt((X + R - ax)*(X + R - ax) + (Y + H - R - ay)*(Y + H - R - ay)) < R);
		ld = (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R);
		ru = (sqrt((X + W - R - ax)*(X + W - R - ax) + (Y + H - R - ay)*(Y + H - R - ay)) < R);
		rd = (sqrt((X + W - R - ax)*(X + W - R - ax) + (Y + R - ay)*(Y + R - ay)) < R);

		if (B1 || B2 || lu || ld || ru || rd)
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
	UiglEvent UiglRoundrect::MotionFunc(float ax, float ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

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
	UiglEvent UiglRoundrect::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		bool lu, ld, ru, rd, B1, B2;
		B1 = ((ax > X) && (ax < X + W) && (ay > Y + R) && (ay < Y + H - R));
		B2 = (ax > X + R && ax < X + W - R && ay>Y     && ay < Y + H);
		lu = (sqrt((X + R - ax)*(X + R - ax) + (Y + H - R - ay)*(Y + H - R - ay)) < R);
		ld = (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R);
		ru = (sqrt((X + W - R - ax)*(X + W - R - ax) + (Y + H - R - ay)*(Y + H - R - ay)) < R);
		rd = (sqrt((X + W - R - ax)*(X + W - R - ax) + (Y + R - ay)*(Y + R - ay)) < R);

		if (B1 || B2 || lu || ld || ru || rd)
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent UiglRoundrect::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (in_focus && key == 13)
		{
			result.Event = uiglEnter;
			result.Name = Name;
		}
		return result;
	}
	UiglEvent UiglRoundrect::SpecialFunc(int key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		return result;
	}
	UiglEvent UiglRoundrect::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		return result;
	}
	UiglEvent UiglRoundrect::SpecialUpFunc(int key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		return result;
	}
	void UiglRoundrect::Init()
	{
		if (!Visible) return;

		int _n = 0;
		if (Mouse_in_button&&IsHover)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		drawRoundrect(X, Y, W, H, R, Color + _n, Outline_color_temp, Angle);
	}
}