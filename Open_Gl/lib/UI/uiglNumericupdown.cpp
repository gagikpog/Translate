#include "uiglNumericupdown.h"

#include  <ctime>

#include "../uiglFunc.h"

namespace UIGL {


	UiglNumericupdown::UiglNumericupdown()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		NumbersOnly = 1;
	}
	UiglEvent UiglNumericupdown::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == 0 && button == 0)
			{
				if (NumbersOnly)
				{
					if (ax > X + W - H*0.8f)
					{
						int nom;
						if (Text != "")
							nom = stoi(Text);
						else nom = Min;
						if (nom < Min) nom = Min;
						if (nom > Max) nom = Max;
						if (ay > Y + H*0.5f)
						{
							if (nom<Max)
							{
								nom++;
							}
						}
						else {
							if (nom>Min)
								nom--;
						}
						Text = std::to_string(nom);
						Cursor_pos = Text.length();
						result.Event = uiglChanged;
						return result;
					}
				}

				result.Event = uiglMouseLeftDown;
				moved = true;
				mx = ax - X;
				my = ay - Y;

				Cursor_pos = text_pos_begin + (int)(ax - X) / textprint.getTextLength("a");
				if (Cursor_pos > Text.length())
					Cursor_pos = Text.length();

				if (Shift_press)
					Select_end = Cursor_pos;
				else Select_begin = Select_end = Cursor_pos;

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
		else {


			int nom;
			if (Text != "")
				nom = stoi(Text);
			else nom = Min;
			if (nom < Min) { result.Name = Name; result.Event = uiglChanged; nom = Min; }
			if (nom > Max) { result.Name = Name; result.Event = uiglChanged; nom = Max; }
			Text = std::to_string(nom);
			if (!in_focus)
				Cursor_pos = Text.length();
		}
		return result;
	}
	UiglEvent UiglNumericupdown::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W - H*0.8f) && (ay>Y) && (ay < Y + H))
		{
			if (!Mouse_in_button)// && !Mouse_in_button_down && !Mouse_in_button_up)
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
			if (ax > X + W - H*0.8f && ax < X + W)
			{
				if (ay < Y + H*0.5f && ay > Y) {
					Mouse_in_button_down = 1;
					Mouse_in_button_up = 0;
				}
				else
					if (ay > Y + H*0.5f && ay< Y + H) {
						Mouse_in_button_down = 0;
						Mouse_in_button_up = 1;
					}
					else {
						Mouse_in_button_down = 0;
						Mouse_in_button_up = 0;
					}
			}
			else {
				Mouse_in_button_down = 0;
				Mouse_in_button_up = 0;
			}

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
	UiglEvent UiglNumericupdown::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && !Read_only)
		{
			if (key > 31 && key < 176 || key>191 && key < 256)
			{
				if (key == 127)
				{
					if (Cursor_pos <= Text.length()) {
						std::string Text1;
						if (Select_begin == Select_end)
						{
							if (Text.length()>Cursor_pos) {
								Text1 = Text.substr(0, Cursor_pos);
								Text1 += Text.substr(Cursor_pos + 1, Text.length() - Cursor_pos - 1);
							}
							else Text1 = Text;
						}
						else {
							if (Select_begin < Select_end)
							{
								Text1 = Text.substr(0, Select_begin);
								Text1 += Text.substr(Select_end);
								Cursor_pos = Select_end = Select_begin;
							}
							else {
								Text1 = Text.substr(0, Select_end);
								Text1 += Text.substr(Select_begin);
								Cursor_pos = Select_begin = Select_end;
							}
						}
						Text = Text1;
					}
				}
				else {
					if (Text.length() < Text_max_length || Select_begin != Select_end)
					{
						if (NumbersOnly)
						{
							if (key >= '0' && key <= '9')
							{
								std::string Text1;
								if (Select_begin == Select_end)
								{
									Text1 = Text.substr(0, Cursor_pos);
									Text1 += key;
									Text1 += Text.substr(Cursor_pos, Text.length() - Cursor_pos);
									Text = Text1;
									Cursor_pos++;
								}
								else {
									if (Select_begin < Select_end)
									{
										Text1 = Text.substr(0, Select_begin);
										Text1 += key;
										Text1 += Text.substr(Select_end);
										Cursor_pos = Select_end = Select_begin;

									}
									else {
										Text1 = Text.substr(0, Select_end);
										Text1 += key;
										Text1 += Text.substr(Select_begin);
										Cursor_pos = Select_begin = Select_end;
									}
									Cursor_pos++;
								}
								Text = Text1;
							}
						}
					}
				}
			}

			if (key == 8)
			{
				std::string Text1;
				if (Select_begin == Select_end)
				{
					if (Cursor_pos > 0) {
						Text1 = Text.substr(0, Cursor_pos - 1);
						Text1 += Text.substr(Cursor_pos, Text.length() - Cursor_pos);
						Text = Text1;
						Cursor_pos--;
					}
				}
				else {
					if (Select_begin < Select_end)
					{
						Text1 = Text.substr(0, Select_begin);
						Text1 += Text.substr(Select_end);
						Cursor_pos = Select_end = Select_begin;
					}
					else {
						Text1 = Text.substr(0, Select_end);
						Text1 += Text.substr(Select_begin);
						Cursor_pos = Select_begin = Select_end;
					}
				}
				Text = Text1;
			}

			if (key == 22)
			{
				std::string fromClipboard;//в эту переменную сохраним текст из буфера обмена
				if (OpenClipboard(0))//открываем буфер обмена
				{
					HANDLE hData = GetClipboardData(CF_TEXT);//извлекаем текст из буфера обмена
					char*chBuffer = (char*)GlobalLock(hData);//блокируем память
					GlobalUnlock(hData);//разблокируем память
					CloseClipboard();//закрываем буфер обмена
					if (Select_end != Select_begin)
					{
						if (Select_begin < Select_end)
						{
							fromClipboard = Text.substr(0, Select_begin);
							fromClipboard += Text.substr(Select_end);
							Cursor_pos = Select_end = Select_begin;
						}
						else {
							fromClipboard = Text.substr(0, Select_end);
							fromClipboard += Text.substr(Select_begin);
							Cursor_pos = Select_begin = Select_end;

						}
						Text = fromClipboard;

					}
					std::string temp_str = chBuffer;
					bool b = 0;
					for (int i = 0; i < temp_str.length(); i++)
					{
						if (temp_str[i] > 0 && temp_str[i] < ' ' || temp_str[i] < -65)
							temp_str[i] = ' ';
						if (NumbersOnly && !(temp_str[i] >= '0' && temp_str[i] <= '9'))
							b = 1;
					}
					if (temp_str.length() > Text_max_length)
					{
						temp_str = temp_str.substr(0, Text_max_length);
					}
					if (NumbersOnly && !b) {
						int _t = std::stoi(Text + temp_str);
						if (_t < Min || _t > Max)
							b = 1;
					}

					if (!b) {
						fromClipboard = Text.substr(0, Cursor_pos);
						fromClipboard += temp_str;
						fromClipboard += Text.substr(Cursor_pos);
						Select_begin = Select_end = Cursor_pos += std::strlen(chBuffer);
						Text = fromClipboard;
					}
				}
			}

			if (key == 3 || key == 24)
			{
				if (OpenClipboard(0))//открываем буфер обмена
				{
					if (Select_begin != Select_end) {

						std::string temp_str;
						if (Select_begin < Select_end)
							temp_str = Text.substr(Select_begin, Select_end - Select_begin);
						else temp_str = Text.substr(Select_end, Select_begin - Select_end);

						HGLOBAL hgBuffer;
						char* chBuffer;
						EmptyClipboard(); //очищаем буфер
						hgBuffer = GlobalAlloc(GMEM_DDESHARE, temp_str.length() + 1);//выделяем память
						chBuffer = (char*)GlobalLock(hgBuffer); //блокируем память
						str_cpy(chBuffer, LPCSTR(temp_str.c_str()));
						GlobalUnlock(hgBuffer);//разблокируем память
						SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
						CloseClipboard(); //закрываем буфер обмена
						if (key == 24)
						{
							if (Select_begin < Select_end)
							{
								temp_str = Text.substr(0, Select_begin);
								temp_str += Text.substr(Select_end);
								Cursor_pos = Select_end = Select_begin;
							}
							else {
								temp_str = Text.substr(0, Select_end);
								temp_str += Text.substr(Select_begin);
								Cursor_pos = Select_begin = Select_end;
							}
							Text = temp_str;


						}
					}
				}
			}


			Select_begin = Select_end = Cursor_pos;

			if (key == 1)
			{
				Select_begin = 0;
				Select_end = Text.length();
				Cursor_pos = Select_end;
			}

			result.Name = Name;
			result.Event = uiglChanged;
			if (key == 13)
			{
				result.Event = uiglEnter;
			}
		}
		return result;
	}
	UiglEvent UiglNumericupdown::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && !Read_only)
		{
			int _nom;
			switch (key)
			{
			case GLUT_KEY_LEFT:
				if (Select_begin == Select_end)
					Select_begin = Cursor_pos;
				if (Cursor_pos > 0)
					Cursor_pos--;
				if (Shift_press)
					Select_end = Cursor_pos;
				else Select_begin = Select_end = Cursor_pos;
				break;
			case GLUT_KEY_RIGHT:
				if (Select_begin == Select_end)
					Select_begin = Cursor_pos;
				if (Cursor_pos < Text.length())
					Cursor_pos++;
				if (Shift_press)
					Select_end = Cursor_pos;
				else Select_begin = Select_end = Cursor_pos;
				break;
			case GLUT_KEY_HOME:
				if (Select_begin == Select_end)
					Select_begin = Cursor_pos;
				Cursor_pos = 0;
				if (Shift_press)
					Select_end = Cursor_pos;
				else Select_begin = Select_end = Cursor_pos;
				break;
			case GLUT_KEY_END:
				if (Select_begin == Select_end)
					Select_begin = Cursor_pos;
				Cursor_pos = Text.length();
				if (Shift_press)
					Select_end = Cursor_pos;
				else Select_begin = Select_end = Cursor_pos;
				break;
			case GLUT_KEY_SHIFT_L:
			case GLUT_KEY_SHIFT_R:
				Shift_press = 1;
				break;
			case GLUT_KEY_CTRL_L:
			case GLUT_KEY_CTRL_R:
				break;
			case GLUT_KEY_UP:
				if (!Shift_press) Select_begin = Select_end = Cursor_pos;
				_nom = std::stoi(Text);
				if (_nom < Max)
					Text = std::to_string(_nom + 1);
				break;
			case GLUT_KEY_DOWN:
				if (!Shift_press) Select_begin = Select_end = Cursor_pos;
				_nom = std::stoi(Text);
				if (_nom > Min)
					Text = std::to_string(_nom - 1);
				break;
			case GLUT_KEY_PAGE_UP:
				if (!Shift_press) Select_begin = Select_end = Cursor_pos;
				Text = std::to_string(Max);
				break;
			case GLUT_KEY_PAGE_DOWN:
				if (!Shift_press) Select_begin = Select_end = Cursor_pos;
				Text = std::to_string(Min);
				break;
			default:
				Select_begin = Select_end = Cursor_pos;
				break;
			}
		}
		return result;
	}
	void UiglNumericupdown::Init()
	{
		UiglTextbox::Init();
		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();
		int _n_up = 0, _n_down = 0;
		if (Mouse_in_button_up)
			_n_up = 80;
		if (Mouse_in_button_down)
			_n_down = 80;
		drawRectangle(X + W - H*0.8f, Y, H*0.8f, H*0.5f, Color + -20 + _n_down, Outline_color_temp);
		drawRectangle(X + W - H*0.8f, Y + H*0.5f, H*0.8f, H*0.5f, Color + -20 + _n_up, Outline_color_temp);
		drawPolygon(X + W - H*0.5f, Y + H*0.6, H*0.1f, 3, Outline_color, Outline_color_temp, -30);
		drawPolygon(X + W - H*0.5f, Y + H*0.1, H*0.1f, 3, Outline_color, Outline_color_temp, 30);
	}
#pragma endregion 

}