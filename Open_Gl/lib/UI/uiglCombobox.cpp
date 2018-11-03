#include "uiglCombobox.h"
#include "../uiglFunc.h"


namespace UIGL {

	UiglCombobox::UiglCombobox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Size.setSize(200, 30);
		tbox.Size.setSize(200 - 30 * 0.8f, 30);
		tbox.Position.setPosition(0, 0);
		tbox.Read_only = true;
		Color = White;
		Skroll.Set_Position(2);
		MaxDropDownItems = 5;
		Select_min = 0;
	}
	UiglEvent UiglCombobox::MouseFunc(int button, int state, int ax, int ay)
	{
		tbox.MouseFunc(button, state, ax, ay);

		UiglEvent result;
		if (button == 0 && state == 0)
		{
			if (Position.getPositionX() < ax && Position.getPositionX() + Size.getSizeW() > ax &&
				Position.getPositionY() < ay && Position.getPositionY() + Size.getSizeH() > ay)
			{
				result.Name = Name;
				result.Event = uiglMouseLeftDown;
				if (ax > Position.getPositionX() + Size.getSizeW() - Size.getSizeH()*0.8f)
					open = true;
			}
		}
		if (button == 0 && state == 1)
		{
			if (Position.getPositionX() < ax && Position.getPositionX() + Size.getSizeW() > ax &&
				Position.getPositionY() < ay && Position.getPositionY() + Size.getSizeH() > ay)
			{
				result.Name = Name;
				result.Event = uiglMouseLeftUp;
			}
		}
		if (button == 1 && state == 0)
		{
			if (Position.getPositionX() < ax && Position.getPositionX() + Size.getSizeW() > ax &&
				Position.getPositionY() < ay && Position.getPositionY() + Size.getSizeH() > ay)
			{
				result.Name = Name;
				result.Event = uiglMouseCenterDown;
			}
		}
		if (button == 1 && state == 1)
		{
			if (Position.getPositionX() < ax && Position.getPositionX() + Size.getSizeW() > ax &&
				Position.getPositionY() < ay && Position.getPositionY() + Size.getSizeH() > ay)
			{
				result.Name = Name;
				result.Event = uiglMouseCenterUp;
			}
		}
		if (button == 2 && state == 0)
		{
			if (Position.getPositionX() < ax && Position.getPositionX() + Size.getSizeW() > ax &&
				Position.getPositionY() < ay && Position.getPositionY() + Size.getSizeH() > ay)
			{
				result.Name = Name;
				result.Event = uiglMouseRightDown;
			}
		}
		if (button == 2 && state == 1)
		{
			if (Position.getPositionX() < ax && Position.getPositionX() + Size.getSizeW() > ax &&
				Position.getPositionY() < ay && Position.getPositionY() + Size.getSizeH() > ay)
			{
				result.Name = Name;
				result.Event = uiglMouseRightUp;
			}
		}

		/*
		if (button == 0 && state == 0) {

		if (open && (ax > X) && (ax < X + W - H*0.8) && (ay > Y - H*Items.size()) && (ay < Y) && (ay > Y - H*MaxDropDownItems))
		{
		result.Name = Name;
		result.Event = uiglChanged;
		Select = (Y - ay) / H + Select_min;
		open = 0;
		}
		bool b1, b2;
		b1 = ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H));
		b2 = (ax > X + W - H*0.8) && (ax < X + W) && (ay > Y - MaxDropDownItems*H) && (ay < Y);
		if (b1 || b2)
		{
		if (b1)
		{
		if (open)
		open = 0;
		else open = 1;
		if (Select < Items.size() - MaxDropDownItems)
		Select_min = Select;
		else Select_min = Items.size() - MaxDropDownItems;
		Select_temp = Select;
		Skroll.Set_Position(Items.size() - MaxDropDownItems - Select_min);
		}
		if (b2) {
		Skroll.MouseFunc(button, state, ax, ay);
		Select_min = Items.size() - MaxDropDownItems - Skroll.Get_Position();
		}
		}
		else open = 0;


		}*/
		return result;
	}
	UiglEvent UiglCombobox::PassiveMotionFunc(int ax, int ay)
	{
		tbox.PassiveMotionFunc(ax, ay);
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
		{
			if (ax > X + W - H*0.8f)
				hover_index = 1;
			else hover_index = 0;

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
			hover_index = 0;
			if (Mouse_in_button)
			{
				result.Name = Name;
				result.Event = uiglMouseOut;
				Mouse_in_button = false;
				return result;
			}
		}

		return result;

		//if (open && (ax > X) && (ax < X + W - H*0.8) && (ay > Y - H*Items.size()) && (ay < Y) && (ay > Y - H*MaxDropDownItems))
		//{
		//	Select_temp = (Y - ay) / H + Select_min;
		//if(MaxDropDownItems> Items)
		//	Skroll.Set_Position(Items.size()-1- Select_temp);
		//}
	}
	UiglEvent UiglCombobox::MotionFunc(float ax, float ay)
	{
		tbox.MotionFunc(ax, ay);
		UiglEvent result;

		//	Skroll.MotionFunc(ax, ay);
		//	Select_min = Items.size() - MaxDropDownItems - Skroll.Get_Position();

		return result;

		//	Select_temp = Items.size() - 1 - Skroll.Get_Position();

		//if (Select_temp < Select_min) {
		//	if (Select_min > 0)
		//		Select_min--;
		//}
		//else
		//{
		//	if (MaxDropDownItems - Select_temp <= 0)
		//		if (Select_min < Items.size() - MaxDropDownItems)
		//			Select_min++;
		//}
	}
	UiglEvent UiglCombobox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		return result;
		if (open)
		{
			if (state == -1)
				Skroll.Step_ago();
			if (state == 1)
				Skroll.Step_forward();
			Select_min = Items.size() - MaxDropDownItems - Skroll.Get_Position();
		}

	}
	UiglEvent UiglCombobox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		tbox.KeyboardFunc(key, ax, ay);
		if (key == 27)
		{
			open = 0;
		}
		if (!in_focus)
			open = 0;
		UiglEvent result;
		return result;
		if (key == 13 && in_focus)
		{
			Select = Select_temp;
			open = 0;
			result.Name = Name;
			result.Event = uiglChanged;
		}
		/*	if (Select_temp < Select_min) {
		if (Select_min > 0)
		Select_min--;
		}
		else
		{
		if (MaxDropDownItems - Select_temp <= 0)
		if (Select_min < Items.size() - MaxDropDownItems)
		Select_min++;
		}*/
		//	Skroll.Set_Position(Items.size() - Select_temp - 1);

	}
	UiglEvent UiglCombobox::SpecialFunc(int key, int ax, int ay)
	{
		tbox.SpecialFunc(key, ax, ay);

		UiglEvent result;
		return result;

		if (!in_focus)
			open = 0;
		if (in_focus)
		{

			if (open)
			{
				if (key == GLUT_KEY_UP)
					if (Select_temp > 0)
						Select_temp--;
				if (key == GLUT_KEY_DOWN)
					if (Select_temp < Items.size() - 1)
						Select_temp++;
				if (key == GLUT_KEY_DOWN || key == GLUT_KEY_UP)
				{
					if (Select_temp < Select_min) {
						if (Select_min > 0)
						{
							Select_min--;
							Skroll.Set_Position(Items.size() - MaxDropDownItems - Select_min);
						}
					}
					else
					{
						if (MaxDropDownItems - Select_temp <= 0)
							if (Select_min < Items.size() - MaxDropDownItems)
							{
								Select_min++;
								Skroll.Set_Position(Items.size() - MaxDropDownItems - Select_min);
							}
					}

				}
			}
			else {
				if (key == GLUT_KEY_DOWN)
				{
					open = 1;
					if (Select < Items.size() - MaxDropDownItems)
						Select_min = Select;
					else Select_min = Items.size() - MaxDropDownItems;
					Select_temp = Select;
					Skroll.Set_Position(Items.size() - MaxDropDownItems - Select_min);
				}
				if (key == GLUT_KEY_LEFT)
				{
					if (Select > 0)
					{
						Select--;
						result.Name = Name;
						result.Event = uiglChanged;
						Select_temp = Select;
					}
				}
				if (key == GLUT_KEY_RIGHT)
				{
					if (Select < Items.size() - 1)
					{
						Select++;
						result.Name = Name;
						result.Event = uiglChanged;
						Select_temp = Select;
					}
				}
			}

		}

	}
	UiglEvent UiglCombobox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		tbox.KeyboardUpFunc(key, ax, ay);
		UiglEvent result;
		return result;
	}
	UiglEvent UiglCombobox::SpecialUpFunc(int key, int ax, int ay)
	{
		tbox.SpecialUpFunc(key, ax, ay);
		UiglEvent result;
		return result;
	}
	void UiglCombobox::Init()
	{
		tbox.Color = Color;
		tbox.in_focus = in_focus;
		if (Items.size() > 0 && Select >= 0 && Select < Items.size())
			tbox.Text = Items[Select];

		tbox.Init();
		UiglColor Outline_Color_Temp = Outline_color, Color_temp = Color;
		if (in_focus)
			Outline_Color_Temp = Outline_color.getNegative();
		if (hover_index == 1)
			Color_temp = Color + 70;
		drawRectangle(X + W - H*0.8f, Y, H*0.8f, H, Color_temp, Outline_Color_Temp);

		glBegin(GL_POLYGON);
		Outline_color.Init();
		glVertex2f(X + W - H*0.2f, Y + H*0.6f);
		glVertex2f(X + W - H*0.6f, Y + H*0.6f);
		glVertex2f(X + W - H*0.4f, Y + H*0.4f);
		glEnd();
		if (open)
		{
			for (int i = 0; i < Items.size() && i < MaxDropDownItems; i++)
			{
				if (i != Select_temp - Select_min)
					drawRectangle(X, Y - (i + 1.0f)*H, W, H, Color, Outline_color);
				else drawRectangle(X, Y - (i + 1.0f)*H, W, H, Color_select, Outline_color);
				tbox.textprint.glText(X + H*0.1f, Y - (i + 1.0f)*H + H*0.25f, Items[i + Select_min].c_str());
			}
		}
		/*


		initiation();
		if(MaxDropDownItems<Items.size())
		Skroll.Init();
		}*/
	}
	void UiglCombobox::Set_text_size(float _size)
	{
		Text_size = _size;
		tbox.Set_text_size(_size);
	}
	void UiglCombobox::initiation()
	{
		Skroll.setAngle(90);
		Skroll.Size.setSize(Skroll.Size.getSizeW(), H*0.8f);
		if (MaxDropDownItems < Items.size())
		{
			Skroll.Size.setSize(H *MaxDropDownItems, Skroll.Size.getSizeH());
			Skroll.Position.setPosition(X + W - H*0.8f, Y - H*MaxDropDownItems);
		}
		else {
			Skroll.Size.setSize(H *Items.size(), Skroll.Size.getSizeH());
			Skroll.Position.setPosition(X + W - H*0.8f, Y - H*Items.size());
		}
		Skroll.Max = Items.size() - MaxDropDownItems;
		Skroll.Color = Color;
		Skroll.Color_slider = Color_select;
		Skroll.Outline_color = Outline_color;
	}
	void UiglCombobox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		tbox.SetHDC(_hdc);
	}
	void UiglCombobox::Update()
	{
		X = Position.getPositionX();
		Y = Position.getPositionY();
		H = Size.getSizeH();
		W = Size.getSizeW();
		tbox.Size.setSize(W - H*0.8f, H);
		tbox.Position.setPosition(X, Y);
	}
}