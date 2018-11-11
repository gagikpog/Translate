#include <ctime>

#include "uiglProgressbar.h"


namespace UIGL {

	uiglProgressbar::uiglProgressbar()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Color = White;
	}
	UiglEvent uiglProgressbar::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
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
	UiglEvent uiglProgressbar::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
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
	UiglEvent uiglProgressbar::MotionFunc(float ax, float ay)
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
	UiglEvent uiglProgressbar::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = UIGL::uiglEvents::uiglWheelDown;
			if (state == 1)
				result.Event = UIGL::uiglEvents::uiglWheelUp;
		}
		return result;
	}
	UiglEvent uiglProgressbar::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent uiglProgressbar::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent uiglProgressbar::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent uiglProgressbar::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void uiglProgressbar::Init()
	{
		glBegin(GL_POLYGON);
		BorderColor.Init(50);
		glVertex2f(X, Y);
		BorderColor.Init(-50);
		glVertex2f(X, Y + H / 2);
		BorderColor.Init(-50);
		glVertex2f(X + PositionBar*W / (Max - Min), Y + H / 2.0f);
		BorderColor.Init(50);
		glVertex2f(X + PositionBar*W / (Max - Min), Y);
		glEnd();


		glBegin(GL_POLYGON);
		BorderColor.Init(-30);
		glVertex2f(X, Y + H / 2.0f);
		BorderColor.Init(30);
		glVertex2f(X, Y + H);
		BorderColor.Init(30);
		glVertex2f(X + PositionBar*W / (Max - Min), Y + H);
		BorderColor.Init(-30);
		glVertex2f(X + PositionBar*W / (Max - Min), Y + H / 2.0f);
		glEnd();

		float _alpha(0.2f);
		glBegin(GL_TRIANGLE_STRIP);
		if (Pos > W*0.2f)
		{
			BorderColor.Init(-50, 100);
			glVertex2f(X + Pos - W*0.2f, Y);
			BorderColor.Init(30, 100);
			glVertex2f(X + Pos - W*0.2f, Y + H);
		}
		else
		{
			BorderColor.Init(-50, 100);
			glVertex2f(X, Y);
			BorderColor.Init(30, 100);
			glVertex2f(X, Y + H);
		}

		if (Pos > W) {
			BorderColor.Init(60);
			glVertex2f(X + W, Y);
			BorderColor.Init(80);
			glVertex2f(X + W, Y + H);
		}
		else
		{
			BorderColor.Init(60);
			glVertex2f(X + Pos, Y);
			BorderColor.Init(70);
			glVertex2f(X + Pos, Y + H);

		}
		glEnd();

		//	return;

		if (PositionBar < Max)
			drawRectangle(X + PositionBar*W / (Max - Min), Y, W - PositionBar*W / (Max - Min) - 0.0f, H - 2.0f, Color, Color);
		drawRectangleContour(X, Y, W, H, Outline_color);

		if (Pos < W*1.2f - 5.0f)
			Pos += 5.0f;
		else Pos = 0.0f;

	}
	int uiglProgressbar::Step_forward()
	{
		if (PositionBar + Step < Max)
			PositionBar += Step;
		else PositionBar = Max;
		return PositionBar;
	}
	int uiglProgressbar::Step_ago()
	{
		if (PositionBar - Step > Min)
			PositionBar -= Step;
		else PositionBar = Min;
		return PositionBar;
	}
}