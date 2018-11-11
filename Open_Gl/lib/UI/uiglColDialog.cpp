#include "uiglColDialog.h"
#include "../uiglFunc.h"
#include "../uiglMainForm.h"

namespace UIGL {

	UiglColDiàlog::UiglColDiàlog()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 440.0f;
		H = 300.0f;
		Size.setSize(440, 300);
		for (int i = 0; i < 4; i++)
		{
			num[i].W = 70;
			num[i].H = Win_fon_H;
			num[i].SetMax(255);
		}
		//	R = 0;
		c_x = c_y = 20;
		cur2_h = 100;
		Made_color = 0;
		is_move = 1;
		spector = 0;
		Name = "dialog";
	}
	void UiglColDiàlog::Init()
	{
		if (l != 0) { if (lp)  l += 2; else l -= 2; }
		if (l > 6) lp = 0;
		drawRectangle(X - l, Y - l, W + 2 * l, H + 2 * l, UiglColor(0, 255, 0, 100), UiglColor(0, 255, 0, 100));

		drawRectangle(X, Y, W, H, Color, Outline_color);
		drawRectangle(X, Y + H - Win_fon_H, W, Win_fon_H, Lightsteelblue, Outline_color);
		textprint.glText(X + 10, Y + H + 10 - Win_fon_H, Title);// Text_en_ru_dialog[Language][0]);

		if (act == 1)
			drawRectangle(X + W - Win_fon_H, Y + H - Win_fon_H, Win_fon_H, Win_fon_H, Red, Outline_color);
		else drawRectangle(X + W - Win_fon_H, Y + H - Win_fon_H, Win_fon_H, Win_fon_H, Silver, Outline_color);

		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2f(X + W - 7, Y + H - 7);
		glVertex2f(X + W - Win_fon_H + 7, Y + H - Win_fon_H + 7);
		glVertex2f(X + W - 7, Y + H - Win_fon_H + 7);
		glVertex2f(X + W - Win_fon_H + 7, Y + H - 7);
		glEnd();
		glLineWidth(1);

		if (spector)
		{
			drawRectangle(X, Y + H - Win_fon_H * 2, 150, Win_fon_H, Silver, Outline_color);
			drawRectangle(X + 150, Y + H - Win_fon_H * 2, 150, Win_fon_H, Color, Outline_color);
			spector_print(X + 15, Y + 15, (H - Win_fon_H * 2), 6 * (H - Win_fon_H * 2) / 7);
			cursor(X + c_x, Y + c_y);
			brightness(X + 20 + h * 7, Y + 15, h * 6, cur2_h, Color_spector(c_x + X, c_y + Y));
		}
		else
		{
			drawRectangle(X, Y + H - Win_fon_H * 2, 150, Win_fon_H, Color, Outline_color);
			drawRectangle(X + 150, Y + H - Win_fon_H * 2, 150, Win_fon_H, Silver, Outline_color);
			D_color(X + 15, Y + 15, (H - Win_fon_H * 2) / 7);
		}

		textprint.glText(X + 10, Y + H + 10 - Win_fon_H * 2, Text_en_ru_dialog[Language][1]);
		textprint.glText(X + 170, Y + H + 10 - Win_fon_H * 2, Text_en_ru_dialog[Language][2]);

		drawRectangle(X + W - 85, Y + 15, 70, Win_fon_H, White, Outline_color);
		textprint.glText(X + W - 60, Y + 24, Text_en_ru_dialog[Language][3]);

		drawRectangle(X + W - 85, Y + 20 + Win_fon_H, 70, Win_fon_H, Color_temp, Outline_color);

		brightness(X + 50 + h * 7, Y + 15, h * 6, cur3_h, White);

		for (int i = 0; i < 4; i++)
		{
			num[i].X = X + W - 85;
			num[i].Y = Y + H - Win_fon_H*(3 + i) - 5 * (i);
			num[i].Init();
		}
		textprint.glText(X + W - 100, Y + H - Win_fon_H*(3 + 0) - 5 * (0) + 12, "R");
		textprint.glText(X + W - 100, Y + H - Win_fon_H*(3 + 1) - 5 * (1) + 12, "G");
		textprint.glText(X + W - 100, Y + H - Win_fon_H*(3 + 2) - 5 * (2) + 12, "B");
		textprint.glText(X + W - 100, Y + H - Win_fon_H*(3 + 3) - 5 * (3) + 12, "A");
	}
	void UiglColDiàlog::Diolog(UiglColor * col, std::string _title)
	{
		Language = UiglMainForm::Language;
		if (_title == "Defoult")
			Title = Text_en_ru_dialog[Language][0];
		else Title = _title;

		Color_result = col;
		Color_temp = *Color_result;
		Made_color = 1;
		spector = 0;
		X = UiglMainForm::WndW / 2 - W / 2;
		Y = UiglMainForm::WndH / 2 - H / 2;
		updatenum();
		h = (H - Win_fon_H * 2) / 7;
		//	Color_temp.setAlpha((cur3_h - 5) / (h * 6 - 10) * 255);
		cur3_h = (float(Color_temp.A) / 255.0f)*(h * 6.0f - 10.0f) + 5.0f;
	}
	UiglEvent UiglColDiàlog::MouseFunc(int button, int state, int ax, int ay)
	{
		is_cur_move = false;
		UiglEvent result;
		if (button == 0 && state == 0)
		{
			if (ax<X || ax>X + W || ay<Y || ay>Y + H)if (l == 0)
			{
				l = 2;
				lp = 1;
				MessageBeep(1);
			}
			if (ax > X + W - 100)
			{
				if (num[0].MouseFunc(button, state, ax, ay).Event == UIGL::uiglEvents::uiglChanged)
				{
					Color_temp.R = stoi(num[0].Text);
				}
				if (num[1].MouseFunc(button, state, ax, ay).Event == UIGL::uiglEvents::uiglChanged)
				{
					Color_temp.G = stoi(num[1].Text);
				}
				if (num[2].MouseFunc(button, state, ax, ay).Event == UIGL::uiglEvents::uiglChanged)
				{
					Color_temp.B = stoi(num[2].Text);
				}
				if (num[3].MouseFunc(button, state, ax, ay).Event == UIGL::uiglEvents::uiglChanged)
				{
					Color_temp.A = stoi(num[3].Text);
					cur3_h = (float(Color_temp.A) / 255.0f)*(h * 6.0f - 10.0f) + 5.0f;
				}
			}
			//close
			if (ax > X + W - Win_fon_H && ax<X + W&&ay>Y + H - Win_fon_H&& ay < H + Y)
			{
				result.Name = Name;
				result.Event = UIGL::uiglEvents::uiglEraseMsg;
				Color_result = NULL;
			}
			//colors
			if (ax > X && ax < X + 150 && ay>Y + H - Win_fon_H * 2 && ay < H + Y - Win_fon_H)
			{
				spector = 0;
			}
			//spector
			if (ax > X + 150 && ax < X + 300 && ay>Y + H - Win_fon_H * 2 && ay < H + Y - Win_fon_H)
			{
				spector = 1;
				/*
				cur3_h = (1-Color_temp.A)*6*h;

				float r1, g1,b1,Gr,Bl;
				Gr = h * 7 / 3;
				Bl = h * 14 / 3;

				r1 = (h * 7 / 6) * Color_temp.R;
				g1 = (h * 7 / 6) * Color_temp.G;
				b1 = (h * 7 / 6) * Color_temp.B;
				if (Color_temp.R == 0)
				{
				if (Color_temp.B == 1)
				{
				c_x = (14 * h) / 3 - g1 + 15;
				}
				if (Color_temp.G == 1)
				{
				c_x = (7 * h) / 3 + b1 + 15;
				}
				cur2_h = std::min(b1, g1);

				}else
				{
				if (Color_temp.R == 1)
				{
				if (Color_temp.B == 0)
				{
				c_x = g1 + 15;
				cur2_h = std::min(r1, g1);
				}

				if (Color_temp.G == 0)
				{
				c_x = (7 * h) - b1 + 15;
				cur2_h = std::min(b1, r1);
				}
				}
				else
				{
				if (Color_temp.B == 1)
				{
				c_x = (14 * h) / 3 + r1 + 15;
				cur2_h = std::min(b1, r1);

				}

				if (Color_temp.G == 1)
				{
				c_x = (7 * h) / 3 - r1 + 15;
				cur2_h = std::min(g1, r1);
				}
				}
				}

				c_y = 30;
				*/
			}
			//title
			if (ax > X && ax < X + W && ay > Y + H - Win_fon_H  && ay < H + Y)
			{
				moved = true;
				mx = ax - X;
				my = ay - Y;

			}
			//select color
			if (ax > X + 15 && ax < X + 15 + h * 7 && ay > Y + 15 && ay < Y + 15 + h * 6)
			{
				float a_temp = Color_temp.A;
				if (!spector)
				{
					if (h != 0)
					{
						int i = (ax - (X + 15.0f)) / h;
						int j = (ay - (Y + 15.0f)) / h;
						Color_temp = uiglColornum(i * 6 + j);
					}
				}
				else
				{
					is_cur_move = true;
					c_x = ax - X;
					c_y = ay - Y;
					int col_h = (2.0f*255.0f * (cur2_h - h * 3.0f)) / (h * 6.0f - 10);
					Color_temp = Color_spector(c_x + X, c_y + Y);
					short _r, _g, _b;
					_r = Color_temp.R + col_h;
					_g = Color_temp.G + col_h;
					_b = Color_temp.B + col_h;

					if (_r > 255)		_r = 255;
					if (_g > 255)		_g = 255;
					if (_b > 255)		_b = 255;

					if (_r < 0)			_r = 0;
					if (_g < 0)			_g = 0;
					if (_b < 0)			_b = 0;

					Color_temp.R = _r;
					Color_temp.G = _g;
					Color_temp.B = _b;

				}
				Color_temp.setAlpha(a_temp);
				updatenum();
			}
			//ok
			if (ax > X + W - 85 && ax < X + W - 15 && ay > Y + 15 && ay < Y + 15 + Win_fon_H)
			{
				Color_result[0] = Color_temp;
				//	Color_result->setColor(Color_temp.R, Color_temp.G, Color_temp.B, Color_temp.A);
				result.Event = UIGL::uiglEvents::uiglEraseMsg;
				result.Name = Name;
			}
			//yarkost
			if (spector)
			{
				if (ax > X + 20 + h * 7 && ax<X + 40 + h * 7 && ay > Y + 15 && ay < Y + 15 + h * 6)
				{
					//	return result;
					cur2_h = ay - Y - 10;
					if (ay > Y + 5 + h * 6)
						cur2_h = h * 6 - 5;

					is_cur2_move = 1;

					int col_h = (2.0f*255.0f * (cur2_h - h * 3.0f)) / (h * 6.0f - 10);
					BYTE _alpha_ = Color_temp.A;
					Color_temp = Color_spector(c_x + X, c_y + Y);
					short _r, _g, _b;
					_r = Color_temp.R + col_h;
					_g = Color_temp.G + col_h;
					_b = Color_temp.B + col_h;

					if (_r > 255)		_r = 255;
					if (_g > 255)		_g = 255;
					if (_b > 255)		_b = 255;

					if (_r < 0)			_r = 0;
					if (_g < 0)			_g = 0;
					if (_b < 0)			_b = 0;

					Color_temp.R = _r;
					Color_temp.G = _g;
					Color_temp.B = _b;

					Color_temp.setAlpha(_alpha_);
					updatenum();
				}

			}

			if (ax > X + 50 + h * 7 && ax<X + 70 + h * 7 && ay > Y + 15 && ay < Y + 15 + h * 6)
			{
				is_cur3_move = 1;
				cur3_h = ay - Y - 10;
				if (ay > Y + 5 + h * 6)
					cur3_h = h * 6 - 5;
				Color_temp.setAlpha((cur3_h - 5) / (h * 6 - 10) * 255);
				//	std::cout <<"col_temp_A "<< (int)Color_temp.A<<"\n";
				num[3].Text = std::to_string((int)Color_temp.A);

			}
		}
		else {
			moved = false;
			is_cur_move = false;
			is_cur2_move = false;
			is_cur3_move = false;
		}
		return result;
	}
	UiglEvent UiglColDiàlog::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (ax > X + W - Win_fon_H && ax<X + W && ay>Y + H - Win_fon_H && ay<H + Y)
			act = 1;
		else act = 0;

		for (int i = 0; i < 4; i++)
			num[i].PassiveMotionFunc(ax, ay);

		return  result;
	}
	UiglEvent UiglColDiàlog::MotionFunc(float ax, float ay)
	{
		UiglEvent result;

		if (is_move && moved)//window move
		{

			if (ax - mx < 0)
				ax = mx;
			if (ay - my < 0)
				ay = my;
			if (ax - mx + W > UiglMainForm::WndW)
				ax = UiglMainForm::WndW - W + mx;
			if (ay - my + H > UiglMainForm::WndH)
				ay = UiglMainForm::WndH - H + my;

			X = ax - mx;
			Y = ay - my;
			Position.setPosition(X, Y);
			double_ckick = 0;
			return result;
		}

		float ax1, ay1;

		if (is_cur_move)
		{
			ax1 = ax;
			ay1 = ay;

			if (ax < X + 15)
				ax1 = X + 15;
			if (ax > X + 14 + h * 7)
				ax1 = X + 14 + h * 7;
			if (ay < Y + 15)
				ay1 = Y + 15;
			if (ay > Y + 15 + h * 6)
				ay1 = Y + 15 + h * 6;

			c_y = ay1 - Y;
			c_x = ax1 - X;

			BYTE a_temp = Color_temp.A;

			int col_h = (2.0f*255.0f * (cur2_h - h * 3.0f)) / (h * 6.0f - 10);
			Color_temp = Color_spector(c_x + X, c_y + Y);
			short _r, _g, _b;
			_r = Color_temp.R + col_h;
			_g = Color_temp.G + col_h;
			_b = Color_temp.B + col_h;

			if (_r > 255)		_r = 255;
			if (_g > 255)		_g = 255;
			if (_b > 255)		_b = 255;

			if (_r < 0)			_r = 0;
			if (_g < 0)			_g = 0;
			if (_b < 0)			_b = 0;

			Color_temp.R = _r;
			Color_temp.G = _g;
			Color_temp.B = _b;

			Color_temp.setAlpha(a_temp);
			updatenum();
		}
		if (is_cur2_move)
		{
			ax1 = ax;
			ay1 = ay;
			if (ay < Y + 15)
				ay1 = Y + 15;
			if (ay > Y + 5 + h * 6)
				ay1 = Y + 5 + h * 6;

			cur2_h = ay1 - Y - 10;

			int col_h = (2.0f*255.0f * (cur2_h - h * 3.0f)) / (h * 6.0f - 10);
			BYTE _alpha_ = Color_temp.A;
			Color_temp = Color_spector(c_x + X, c_y + Y);
			short _r, _g, _b;
			_r = Color_temp.R + col_h;
			_g = Color_temp.G + col_h;
			_b = Color_temp.B + col_h;

			if (_r > 255)		_r = 255;
			if (_g > 255)		_g = 255;
			if (_b > 255)		_b = 255;

			if (_r < 0)			_r = 0;
			if (_g < 0)			_g = 0;
			if (_b < 0)			_b = 0;

			Color_temp.R = _r;
			Color_temp.G = _g;
			Color_temp.B = _b;

			Color_temp.setAlpha(_alpha_);
			updatenum();
		}
		if (is_cur3_move)
		{
			ax1 = ax;
			ay1 = ay;
			if (ay < Y + 15)
				ay1 = Y + 15;
			if (ay > Y + 5 + h * 6)
				ay1 = Y + 5 + h * 6;

			cur3_h = ay1 - Y - 10;
			Color_temp.setAlpha((cur3_h - 5) / (h * 6 - 10) * 255);
			//	std::cout <<"col_temp_A "<< (int)Color_temp.A<<"\n";	
			updatenum();

		}

		return result;
	}
	UiglEvent UiglColDiàlog::KeyboardFunc(unsigned char key, int x, int y)
	{
		UiglEvent result;
		if (key == 27)
		{
			result.Name = Name;
			result.Event = UIGL::uiglEvents::uiglEraseMsg;
		}
		if (key == 13)
		{

			Color_result[0] = Color_temp;
			result.Name = Name;
			result.Event = UIGL::uiglEvents::uiglEraseMsg;
		}
		return result;
	}
	UiglEvent UiglColDiàlog::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglColDiàlog::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglColDiàlog::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent UiglColDiàlog::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void UiglColDiàlog::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.setHDC(_hdc);
		textprint.setHeightText(Win_fon_H - 15);
		for (int i = 0; i < 4; i++)
		{
			num[i].SetHDC(_hdc);
			num[i].Set_text_size(25);
		}
	}
	void UiglColDiàlog::D_color(float x, float y, float _h)
	{
		UiglColor col(Red);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				col.setColor(uiglColornum(i * 6 + j)).Init();
				drawRectangle(x + _h*i, y + _h*j, _h, _h, col, Outline_color, 0, 0);
			}
		}
	}
	UiglColor UiglColDiàlog::Color_spector(float x, float y)
	{
		glutPostRedisplay();
		BYTE _col[4];
		glReadBuffer(GL_FRONT);
		glutUseLayer(GLUT_NORMAL);
		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &_col);

		UiglColor temp(_col[0], _col[1], _col[2], 255);
		return temp;
	}
	void UiglColDiàlog::spector_print(float x, float y, float w, float h)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, y);
		glVertex2f(x, y + h);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(x + w*1.0f / 6.0f, y);
		glVertex2f(x + w*1.0f / 6.0f, y + h);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(x + w*1.0f / 3.0f, y);
		glVertex2f(x + w*1.0f / 3.0f, y + h);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(x + w*1.0f / 2.0f, y);
		glVertex2f(x + w*1.0f / 2.0f, y + h);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(x + w*2.0f / 3.0f, y);
		glVertex2f(x + w*2.0f / 3.0f, y + h);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2f(x + w*5.0f / 6.0f, y);
		glVertex2f(x + w*5.0f / 6.0f, y + h);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		glVertex2f(x, y);
		glVertex2f(x + w, y);

		glColor4f(0.5f, 0.5f, 0.5f, 0.0f);
		glVertex2f(x, y + h);
		glVertex2f(x + w, y + h);
		glEnd();
	}
	void UiglColDiàlog::cursor(float x, float y)
	{
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);

		glVertex2f(x + 7, y);
		glVertex2f(x + 11, y);
		glVertex2f(x - 7, y);
		glVertex2f(x - 11, y);

		glVertex2f(x, y + 7);
		glVertex2f(x, y + 11);
		glVertex2f(x, y - 7);
		glVertex2f(x, y - 11);

		glColor3f(0, 0, 0);

		glVertex2f(x + 7, y + 1);
		glVertex2f(x + 11, y + 1);
		glVertex2f(x - 7, y + 1);
		glVertex2f(x - 11, y + 1);

		glVertex2f(x + 7, y - 1);
		glVertex2f(x + 11, y - 1);
		glVertex2f(x - 7, y - 1);
		glVertex2f(x - 11, y - 1);

		glVertex2f(x + 1, y + 7);
		glVertex2f(x + 1, y + 11);
		glVertex2f(x + 1, y - 7);
		glVertex2f(x + 1, y - 11);

		glVertex2f(x - 1, y + 7);
		glVertex2f(x - 1, y + 11);
		glVertex2f(x - 1, y - 7);
		glVertex2f(x - 1, y - 11);

		glEnd();
	}
	void UiglColDiàlog::brightness(float x, float y, float h, float cur_h, UiglColor col)
	{
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0, 0, 0);
		glVertex2f(x, y);
		glVertex2f(x + 20, y);

		col.Init();
		glVertex2f(x, y + h / 2);
		glVertex2f(x + 20, y + h / 2);

		glColor3f(1, 1, 1);
		glVertex2f(x, y + h);
		glVertex2f(x + 20, y + h);

		glEnd();

		glBegin(GL_LINES);

		glColor3f(0, 0, 0);
		glVertex2f(x - 2, y + cur_h + 5);
		glVertex2f(x + 22, y + cur_h + 5);
		glVertex2f(x - 2, y + cur_h - 5);
		glVertex2f(x + 22, y + cur_h - 5);

		glVertex2f(x - 2, y + cur_h - 5);
		glVertex2f(x - 2, y + cur_h + 5);
		glVertex2f(x + 22, y + cur_h - 5);
		glVertex2f(x + 22, y + cur_h + 5);

		glColor3f(1, 1, 1);
		glVertex2f(x - 2, y + cur_h + 4);
		glVertex2f(x + 22, y + cur_h + 4);
		glVertex2f(x - 2, y + cur_h - 4);
		glVertex2f(x + 22, y + cur_h - 4);

		glEnd();
		glBegin(GL_LINE_LOOP);

		glColor3f(0, 0, 0);
		glVertex2f(x, y);
		glVertex2f(x + 20, y);
		glVertex2f(x + 20, y + h);
		glVertex2f(x, y + h);

		glEnd();
	}
	void UiglColDiàlog::updatenum()
	{
		num[0].Text = std::to_string((int)Color_temp.R);
		num[1].Text = std::to_string((int)Color_temp.G);
		num[2].Text = std::to_string((int)Color_temp.B);
		num[3].Text = std::to_string((int)Color_temp.A);
	}
}