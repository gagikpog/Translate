#include "uiglCheckbox.h"
#include "../uiglFunc.h"

namespace UIGL {

	UiglCheckbox::UiglCheckbox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 50.0f;
		Line_length = 2.0f;
		Text_size = W;
		Color = White;
		//	textprint.setHDC(hdc);
	}
	UiglEvent UiglCheckbox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (button == 0 && state == 0)
			if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + W))
			{
				if (Checked)
				{
					Checked = 0;
				}
				else Checked = 1;
				result.Name = Name;
				result.Event = UIGL::uiglEvents::uiglChanged;
			}
		return result;
	}
	UiglEvent UiglCheckbox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + W))
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
	UiglEvent UiglCheckbox::MotionFunc(float ax, float ay)
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
	UiglEvent UiglCheckbox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglCheckbox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglCheckbox::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglCheckbox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && key == ' ')
		{
			Checked = !Checked;
			result.Name = Name;
			result.Event = UIGL::uiglEvents::uiglChanged;
		}

		return result;
	}
	UiglEvent UiglCheckbox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void UiglCheckbox::Init()
	{
		UiglColor _col = Color, _col1 = Outline_color;
		if (Mouse_in_button)
			_col = _col + 72;
		if (in_focus)
			_col1 = _col1.getNegative();
		drawRectangle(X, Y, W, W, _col, _col1);
		drawRectangleContour(X, Y, W, W, Outline_color, 0, Line_length);
		textprint.glText(X + W*1.1, Y + (W*1.3 - Text_size) / 2, Text.c_str());

		if (Checked)
		{
			float Line_length1 = W*0.1;
			glTranslatef(X + W*0.4, Y + W*0.2, 0);//перемешать
			glRotatef(45, 0, 0, -1);//поворот
			glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(-W*0.4, 0);
			glVertex2f(-W*0.4, 0 + Line_length1);
			glVertex2f(0, 0);
			glVertex2f(-Line_length1, Line_length1);
			glVertex2f(0, W*0.7);
			glVertex2f(-Line_length1, W*0.7);
			glEnd();
			glRotatef(45, 0, 0, 1);//поворот
			glTranslatef(-X - W*0.4, -Y - W*0.2, 0);//перемешать
		}
	}
	void UiglCheckbox::Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.setFontSize(Text_size);
	}
	void UiglCheckbox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.setHDC(_hdc);
		textprint.setFontSize(Text_size);
	}
}