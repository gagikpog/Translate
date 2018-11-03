#include "uiglTextbox.h"

#include <ctime>

#include "../uiglFunc.h"

namespace UIGL {

	UiglTextbox::UiglTextbox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 200.0f;
		H = 40.0f;
		textprint.setHeightText(H - H*0.2f);
		Color = White;
		Cursor_time = clock();
		textprint.setFont("Consolas");
		Selection_color.setAlpha(100);
		Text_max_length = Text.max_size();
	}
	UiglEvent UiglTextbox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == 0 && button == 0)
			{
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
		else if (!in_focus) Cursor_pos = Text.length();
		return result;
	}
	UiglEvent UiglTextbox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

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
	UiglEvent UiglTextbox::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.setPosition(X, Y);
			double_ckick = 0;
		}
		if (moved == true)
		{
			int _n = ax - X;
			//	if (_n > 0)
			//		_n = -1;
			Cursor_pos = Select_end = text_pos_begin + int(_n / textprint.getTextLength("a"));
			if (Select_end > Text.length())
				Select_end = Text.length();
		}
		return result;
	}
	UiglEvent UiglTextbox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

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
	UiglEvent UiglTextbox::KeyboardFunc(unsigned char key, int ax, int ay)
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
							if (Text.length() > Cursor_pos) {
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
						if (!NumbersOnly)
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
						else
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
	UiglEvent UiglTextbox::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && !Read_only)
		{

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
			default:
				Select_begin = Select_end = Cursor_pos;
				break;
			}


		}
		return result;
	}
	UiglEvent UiglTextbox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglTextbox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
			Shift_press = 0;
		return result;
	}
	void UiglTextbox::Init()
	{
		if (Cursor_pos >= Text.length())
			Cursor_pos = Text.length();

		if (clock() - Cursor_time > 400)
		{
			if (Cursor_enbl) {
				Cursor_enbl = 0;
			}
			else {
				Cursor_enbl = 1;
			}
			Cursor_time = clock();
		}
		int _n = 0;
		if (Mouse_in_button)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		drawRectangle(X, Y, W, H, Color + _n, Outline_color_temp);


		std::string Text1 = Text;
		int out_l = 0;
		while (textprint.getTextLength(Text1) > W)
		{
			Text1 = Text1.substr(1);
			out_l++;
		}

		float cursor_line_pos = 0.0f;
		int _length = Text.length() - out_l;

		if (Cursor_pos > text_pos_begin + _length)
			text_pos_begin = Cursor_pos - _length;


		if (Cursor_pos < text_pos_begin)
			text_pos_begin = Cursor_pos;


		if (text_pos_begin > out_l)
			text_pos_begin--;


		float char_length = textprint.getTextLength("a");
		float sel_b = 0, sel_l = char_length*(Select_end - Select_begin);

		if (Select_begin < Select_end)
		{
			if (Select_begin < text_pos_begin)
			{
				sel_b = 2;
				sel_l = char_length*(Select_end - text_pos_begin);
			}
			else
				sel_b = char_length*(Select_begin - text_pos_begin) + 2;
		}
		else
		{
			sel_b = (Cursor_pos - text_pos_begin)*char_length;
			if (Select_begin < out_l + _length)
				sel_l = char_length*(Select_begin - Select_end);
			else sel_l = char_length*(text_pos_begin + _length - Select_end);
		}

		if (in_focus) {

			if (Select_begin != Select_end)
				drawRectangle(sel_b + X, Y + H*0.1, sel_l, H*0.7, Selection_color, Selection_color);
			textprint.glText(X + 2, Y + H*0.2, Text.substr(text_pos_begin, _length), Text_color);
		}
		else {
			textprint.glText(X + 2, Y + H*0.2, Text.substr(0, _length), Text_color);
		}

		if (in_focus && !Read_only) {
			cursor_line_pos = textprint.getTextLength(Text.substr(text_pos_begin, Cursor_pos - text_pos_begin)) + X + 2;
			if (Cursor_enbl) {
				Text_color.Init();
				glBegin(GL_LINES);
				glVertex2f(cursor_line_pos, Y + H*0.1);
				glVertex2f(cursor_line_pos, Y + H*0.9);
				glEnd();
			}
		}
	}
	void UiglTextbox::Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.setHeightText(Text_size - 2);
	}
	void UiglTextbox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.setHDC(_hdc);
	}
}