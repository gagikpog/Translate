#include "uiglSkrollbar.h"
#include "../uiglFunc.h"

namespace UIGL {

	UiglSkrollbar::UiglSkrollbar()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		H = 20;
		W = 100;
		Size.setSize(W, H);
		Max = 100;
		Min = 0;
		Slider_length = 10;
		Position_p = Min;
		Px = H + Slider_length;
		Step = 1;
		Color_slider.setColor(Silver);
		Color = White;
	}
	UiglEvent UiglSkrollbar::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		if (button == 0 && state == 0) {
			if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
			{
				if (ax - X > Px - Slider_length && ax - X < Px + Slider_length && ay - Y>H*0.1 && ay - Y < H*0.9) {
					Move_slider = 1;
					Mx = ax - X - Px;
				}
				else {
					if (ax - X<Px && Px>H + Slider_length)
						Step_ago();
					if (ax - X > Px && Px < W - H - Slider_length)
						Step_forward();
					Move_slider = 0;
					Position_p = (Px - H - Slider_length)*(Max - Min) / (W - 2 * H - 2 * Slider_length) + Min;
					result.Name = Name;
					result.Event = uiglChanged;
				}
			}
			else { Move_slider = 0; }
		}
		else Move_slider = 0;

		return result;
	}
	UiglEvent UiglSkrollbar::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		int _X = X, _Y = Y;
		if (!Visible) return result;
		if ((ax > _X) && (ax < _X + W) && (ay > _Y) && (ay < _Y + H))
		{
			if (ax < _X + H*0.9f)
			{
				passiv_hover = 1;
			}
			else {
				if (ax > _X + W - H*0.9f)
				{
					passiv_hover = 2;
				}
				else {
					if (ax > _X + Px - Slider_length && ax < _X + Px + Slider_length)
						passiv_hover = 3;
					else passiv_hover = 0;
				}
			}

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
			passiv_hover = 0;
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
	UiglEvent UiglSkrollbar::MotionFunc(float ax, float ay) {
		UiglEvent result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.setPosition(X, Y);
			double_ckick = 0;
		}
		if (Move_slider)
		{
			Px = ax - X - Mx;
			if (ax - Mx - Slider_length < X + H)
				Px = H + Slider_length;
			if (ax - Mx + Slider_length > X + W - H)
				Px = W - H - Slider_length;
			Position_p = (Px - H - Slider_length)*(Max - Min) / (W - 2 * H - 2 * Slider_length) + Min;
			result.Name = Name;
			result.Event = uiglChanged;
		}
		return result;
	}
	UiglEvent UiglSkrollbar::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
		{
			if (state == -1)
				Step_ago();
			if (state == 1)
				Step_forward();

			Position_p = (Px - H - Slider_length)*(Max - Min) / (W - 2 * H - 2 * Slider_length) + Min;
			result.Name = Name;
			result.Event = uiglChanged;
		}
		return result;
	}
	UiglEvent UiglSkrollbar::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent UiglSkrollbar::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent UiglSkrollbar::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent UiglSkrollbar::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	void UiglSkrollbar::Init()
	{
		if (!Visible) return;

		drawRectangle(X, Y, W, H, Color, Outline_color, Angle);
		UiglColor _col = Color;
		if (passiv_hover == 1 && IsHover)
			_col = _col + 70;
		drawRectangle(X, Y, H*0.9f, H, _col, Outline_color, Angle);
		_col = Color;
		if (passiv_hover == 2 && IsHover)
			_col = _col + 70;
		drawRectangle(rotate_x(W - H*0.9f, 0, Angle) + X, rotate_y(W - H*0.9f, 0, Angle) + Y, H*0.9f, H, _col, Outline_color, Angle);
		_col = Color_slider;
		if (passiv_hover == 3 && IsHover)
			_col = _col + 100;
		drawRectangle(X + rotate_x(Px - Slider_length, H*0.1, Angle), Y + rotate_y(Px - Slider_length, H*0.1, Angle), Slider_length * 2, H*0.8, _col, Outline_color, Angle);

		glBegin(GL_LINES);
		Outline_color.Init();
		glVertex2f(X + rotate_x(Px, H*0.2f, Angle), Y + rotate_y(Px, H*0.2, Angle));
		glVertex2f(X + rotate_x(Px, H*0.8f, Angle), Y + rotate_y(Px, H*0.8, Angle));
		glVertex2f(X + rotate_x(Px - 2.0f, H*0.2f, Angle), Y + rotate_y(Px - 2.0f, H*0.2, Angle));
		glVertex2f(X + rotate_x(Px - 2.0f, H*0.8f, Angle), Y + rotate_y(Px - 2.0f, H*0.8, Angle));
		glVertex2f(X + rotate_x(Px + 2.0f, H*0.2f, Angle), Y + rotate_y(Px + 2.0f, H*0.2, Angle));
		glVertex2f(X + rotate_x(Px + 2.0f, H*0.8f, Angle), Y + rotate_y(Px + 2.0f, H*0.8, Angle));
		glVertex2f(X + rotate_x(Px - 4.0f, H*0.2f, Angle), Y + rotate_y(Px - 4.0f, H*0.2, Angle));
		glVertex2f(X + rotate_x(Px - 4.0f, H*0.8f, Angle), Y + rotate_y(Px - 4.0f, H*0.8, Angle));
		glVertex2f(X + rotate_x(Px + 4.0f, H*0.2f, Angle), Y + rotate_y(Px + 4.0f, H*0.2, Angle));
		glVertex2f(X + rotate_x(Px + 4.0f, H*0.8f, Angle), Y + rotate_y(Px + 4.0f, H*0.8, Angle));
		glEnd();

		//стрелка на лево
		glBegin(GL_POLYGON);
		Outline_color.Init();
		glVertex2f(X + rotate_x(H*0.7f, H*0.2f, Angle), Y + rotate_y(H*0.7f, H*0.2f, Angle));
		glVertex2f(X + rotate_x(H*0.7f, H*0.8f, Angle), Y + rotate_y(H*0.7f, H*0.8f, Angle));
		glVertex2f(X + rotate_x(H*0.2f, H*0.5f, Angle), Y + rotate_y(H*0.2f, H*0.5f, Angle));
		glEnd();
		//стрелка на право
		glBegin(GL_POLYGON);
		glVertex2f(X + rotate_x(W - H*0.7f, H*0.2f, Angle), Y + rotate_y(W - H*0.7f, H*0.2f, Angle));
		glVertex2f(X + rotate_x(W - H*0.7f, H*0.8f, Angle), Y + rotate_y(W - H*0.7f, H*0.8f, Angle));
		glVertex2f(X + rotate_x(W - H*0.2f, H*0.5f, Angle), Y + rotate_y(W - H*0.2f, H*0.5f, Angle));
		glEnd();
		if (Position_p > Max)
			Position_p = Max;
	}
	float UiglSkrollbar::Step_forward()
	{
		if (Position_p < Max)
			Position_p++;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
		return Position_p;
	}
	float UiglSkrollbar::Step_ago()
	{
		if (Position_p > Min)
			Position_p--;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min) + 1.0f;
		return Position_p;
	}
	void UiglSkrollbar::Set_Slider_length(float length)
	{
		Slider_length = length;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
	}
	float UiglSkrollbar::Set_Position(float position)
	{
		Position_p = position;
		if (position > Max)
			Position_p = Max;
		if (position < Min)
			Position_p = Min;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
		return Position_p;
	}
	float UiglSkrollbar::Get_Position()
	{
		return Position_p;
	}
	void UiglSkrollbar::Update()
	{
		X = Position.getPositionX();
		Y = Position.getPositionY();
		W = Size.getSizeW();
		H = Size.getSizeH();
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
	}
}