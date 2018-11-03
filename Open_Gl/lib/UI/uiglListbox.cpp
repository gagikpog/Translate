#include <ctime>

#include "uiglListbox.h"
#include "../uiglFunc.h"

namespace UIGL {
	UiglListbox::UiglListbox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 200;
		H = 400;
		Color = White;
		Skrol.setAngle(90);
		Skrol.Set_Position(100);
	}
	UiglEvent UiglListbox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		int _count = ((H - 10.0f) / Text_size);
		int Skrol_whigth = 20;
		if (_count >= Items.size())
			Skrol_whigth = 0;
		if ((ax > X) && (ax < X + W - Skrol_whigth) && (ay>Y) && (ay < Y + H))
		{

			result.Name = Name;
			if (state == 0 && button == 0)
			{
				//	result.Event = uiglMouseLeftDown;


				moved = true;
				mx = ax - X;
				my = ay - Y;

				int n = (Y + H - 5 - ay) / Text_size;
				result.Event = uiglChanged;
				if (_count >n && n + item_up_num<Items.size())
					Selected = item_up_num + n;
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
				Skrol.MouseFunc(button, state, ax, ay);
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
		if (_count < Items.size()) {
			if ((ax > X + W - Skrol_whigth) && (ax < X + W) && (ay > Y) && (ay < Y + H))
			{
				Skrol.MouseFunc(button, state, ax, ay);
				item_up_num = Items.size() - _count - Skrol.Get_Position();
			}
			else
			{
				Skrol.MouseFunc(button, state, ax, ay);
			}
		}
		return result;
	}
	UiglEvent UiglListbox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			int _count = ((H - 10) / Text_size);

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
	UiglEvent UiglListbox::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.setPosition(X, Y);
			double_ckick = 0;
		}
		if (Skrol.MotionFunc(ax, ay).Event == uiglChanged)
		{
			int _count = ((H - 10) / Text_size);
			item_up_num = Items.size() - _count - Skrol.Get_Position();

		}


		return result;
	}
	UiglEvent UiglListbox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		int _count = ((H - 10.0f) / Text_size);
		if (Mouse_in_button && _count<Items.size())
		{
			result.Name = Name;
			if (state == -1)
			{
				Skrol.Step_ago();
				item_up_num = Skrol.Max - Skrol.Get_Position();
				result.Event = uiglWheelDown;
			}
			if (state == 1)
			{
				result.Event = uiglWheelUp;
				Skrol.Step_forward();
				item_up_num = Skrol.Max - Skrol.Get_Position();
			}
		}
		return result;
	}
	UiglEvent UiglListbox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;

		if (key == 13 && in_focus)
		{
			result.Name = Name;
			result.Event = uiglEnter;
		}
		return result;
	}
	UiglEvent UiglListbox::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus)
		{
			switch (key)
			{
			case GLUT_KEY_DOWN:
			{
				if (Items.size() >Selected + 1)
				{
					Selected++;
					result.Event = uiglChanged;
					result.Name = Name;
					int _count = ((H - 10.0f) / Text_size);
					if (Selected - item_up_num > _count - 1)
					{
						item_up_num++;
						if (_count<Items.size())
							Skrol.Step_ago();
					}
				}
				if (Selected < 0 && Items.size()>0)
					Selected = 0;
				break;
			}
			case GLUT_KEY_UP:
				if (Selected > 0)
				{
					Selected--;
					result.Event = uiglChanged;
					result.Name = Name;
					int _count = ((H - 10.0f) / Text_size);
					if (Selected - item_up_num < 0)
					{
						item_up_num--;
						if (_count<Items.size())
							Skrol.Step_forward();
					}

				}
				break;
			default:
				break;
			}
		}
		return result;
	}
	UiglEvent UiglListbox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglListbox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void UiglListbox::Init()
	{
		int _count = ((H - 10.0f) / Text_size);
		drawRectangle(X, Y, W, H, Color, Outline_color);

		if (Selected >= 0 && Selected >= item_up_num && Selected < item_up_num + _count)
		{
			drawRectangle(X + 1, Y + H - 5 - (Selected - item_up_num + 1)*Text_size, W - 2, Text_size, Select_color, Outline_color);
		}

		for (int i = 0; i < Items.size() - item_up_num && i<_count; i++)
		{
			textprint.glText(X + 5, Y + H - 2 - (i + 1)*Text_size, Items[i + item_up_num], Text_color);
		}
		if (_count<Items.size()) {
			Skrol.Color = Color;
			Skrol.Color_slider = Select_color;
			Skrol.Outline_color = Outline_color;
			Skrol.Size.setSize(H, 19);
			Skrol.Position.setPosition(X + W, Y);
			Skrol.Set_Position(Items.size() - _count - item_up_num);
			if (Items.size() > _count)
				Skrol.Max = Items.size() - _count;
			else Skrol.Max = 1;
			Skrol.Init();
			Skrol.Set_Slider_length(20);
		}
		else item_up_num = 0;
	}
	void UiglListbox::Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.setHeightText(_size);
	}
	std::string UiglListbox::Get_Selected_text()
	{
		if (Selected >= 0 && Selected<Items.size())
			return Items[Selected];
		else return "Do not selection";
	}
	void UiglListbox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.setHDC(_hdc);
	}

}