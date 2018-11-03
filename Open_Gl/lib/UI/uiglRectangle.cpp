#include <ctime>

#include "uiglRectangle.h"
#include "../uiglFunc.h"

namespace UIGL {

	UiglRectangle::UiglRectangle()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		H = W = 20;
		Color = White;
	}
	UiglEvent UiglRectangle::MouseFunc(int button, int state, int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		UiglEvent result;
		if (!Visible) return result;
		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
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
	UiglEvent UiglRectangle::PassiveMotionFunc(int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (!Visible) return result;
		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
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
	UiglEvent UiglRectangle::MotionFunc(float ax, float ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (!Visible) return result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.setPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent UiglRectangle::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (!Visible) return result;
		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent UiglRectangle::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (!Visible) return result;
		if (in_focus && key == 13)
		{
			result.Event = uiglEnter;
			result.Name = Name;
		}
		return result;
	}
	UiglEvent UiglRectangle::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent UiglRectangle::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent UiglRectangle::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	void UiglRectangle::Init()
	{
		if (!Visible) return;

		int _n = 0;
		if (Mouse_in_button&&IsHover)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		drawRectangle(X, Y, W, H, Color + _n, Outline_color_temp, Angle);
		float align_h = 0;
		switch (Text_align)
		{
		case UIGL::uiglTopLeft:
		case UIGL::uiglTopCenter:
		case UIGL::uiglTopRight:
			align_h = H*0.9f - Text_size;
			break;
		case UIGL::uiglMiddleLeft:
		case UIGL::uiglMiddleCenter:
		case UIGL::uiglMiddleRight:
			align_h = H*0.5f - Text_size / 2.0f;
			break;
		case UIGL::uiglBottomLeft:
		case UIGL::uiglBottomCenter:
		case UIGL::uiglBottomRight:
			align_h = H*0.1f;
			break;
		}
		textprint.glText(X + 10, Y + align_h, Text, Text_color);
	}
	void UiglRectangle::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.setHDC(_hdc);
	}
	void UiglRectangle::Set_text_size(float _size)
	{
		Text_size = _size;
		//textprint.setFontSize(Text_size);
		textprint.setHeightText((int)_size);
	}
}