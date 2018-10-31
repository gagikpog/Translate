#ifndef EASY_OPENGL_CPP_
#define EASY_OPENGL_CPP_
#include "EasyOpenGL.h"

namespace UIGL
{
#pragma region Function
float rotate_x(float x, float y, float alpha)
{
	if (alpha == 0)
		return x;
	float l, a1;
	l = sqrtf(x*x + y*y);
	if (x || y)
		a1 = atan2f(y, x) * 180.0f / PI;
	else a1 = 0.0f;
	alpha += a1;

	x = cosf(alpha*PI / 180.0f)*l;
	return x;
}
float rotate_y(float x, float y, float alpha)
{
	if (alpha == 0)
		return y;
	float l, a1;
	l = sqrtf(x*x + y*y);
	if (x || y)
		a1 = atan2f(y, x) * 180.0f / PI;
	else a1 = 0.0f;
	alpha += a1;

	y = sinf(alpha*PI / 180.0f)*l;
	return y;
}
//прямоугольник с закругленными краями контур
inline void Gl_Print_Roundrect_Contour(float X, float Y, float W, float H, float R, UiglColor Outline_color, float _angle,float line_width)
{
	float fx, fy, RX, RY;
	float R1 = R;
	
	if (R < H / 2.0f && R < W / 2.0f)
	{
		R1 = R;
	}
	else
	{
		if (W > H)
			R1 = H / 2.0f;
		else R1 = W / 2.0f;
	}

	float siny(0), cosx(0);
	float fi;
	glLineWidth(line_width);
	glBegin(GL_LINE_LOOP);
	Outline_color.Init();

	RX = X + W - R1;
	RY = Y + H - R1;
	for (float i = 0; i <= PI / 2; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}

	RX = X + R1;
	RY = Y + H - R1;
	for (float i = PI / 2.0f; i <= PI; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}

	RX = X + R1;
	RY = Y + R1;
	for (float i = PI; i <= PI * 3 / 2; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}

	RX = X + W - R1;
	RY = Y + R1;
	for (float i = PI * 3 / 2; i <= PI * 2.0f; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}
	glEnd();
	glLineWidth(1);
}
//прямоугольник с закругленными краями
inline void Gl_Print_Roundrect(float X, float Y, float W, float H, float R, UiglColor Color, UiglColor Outline_color, float _angle, bool glossy,float line_width)
{
	float fx, fy, RX, RY;
	float R1 = R;

	if (R < H / 2.0f && R < W / 2.0f)
	{
		R1 = R;
	}
	else
	{
		if (W > H)
			R1 = H / 2.0f;
		else R1 = W / 2.0f;
	}

	float siny(0), cosx(0);
	float fi;
	glBegin(GL_POLYGON);
	Color.Init();

	RX = X + W - R1;
	RY = Y + H - R1;
	for (float i = 0; i <= PI / 2; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X,fy - Y, _angle) + X, rotate_y(fx - X,fy - Y,_angle) + Y);
	}

	RX = X + R1;
	RY = Y + H - R1;
	for (float i = PI / 2.0f; i <= PI; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}

	RX = X + R1;
	RY = Y + R1;
	for (float i = PI; i <= PI * 3 / 2; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}

	RX = X + W - R1;
	RY = Y + R1;
	for (float i = PI * 3 / 2; i <= PI * 2.0f; i += 0.1f)
	{
		fx = RX + cos(i)*R1;
		fy = RY + sin(i)*R1;
		glVertex2f(rotate_x(fx - X, fy - Y, _angle) + X, rotate_y(fx - X, fy - Y, _angle) + Y);
	}
	glEnd();
	Gl_Print_Roundrect_Contour(X, Y, W, H, R, Outline_color, _angle, line_width);
}
//окружность контур
inline void Gl_Print_Circle_Contour(float X, float Y, float R, UiglColor Outline_color, float line_width)
{
	glLineWidth(line_width);
	glBegin(GL_LINE_LOOP);
	Outline_color.Init();
	for (float i = 0; i < 2 * PI; i += 0.1f)
	{
		glVertex2f(cos(i)*R + R + X, sin(i)*R + R + Y);
	}
	glEnd();
	glLineWidth(1);
}
//окружность
inline void Gl_Print_Circle(float X, float Y, float R, UiglColor Color, UiglColor Outline_color, float line_width)
{
	glBegin(GL_POLYGON);
	Color.Init();
	for (float i = 0; i < 2 * PI; i += 0.1f)
	{
		glVertex2f(cos(i)*R + R + X, sin(i)*R + R + Y);
	}
	glEnd();
	Gl_Print_Circle_Contour(X, Y, R, Outline_color, line_width);
}
//прямоугольник контур
inline void Gl_Print_Rectangle_Contour(float X, float Y, float W, float H, UiglColor Outline_color, float _angle, float line_width)
{
	glLineWidth(line_width);
	glBegin(GL_LINE_LOOP);
	Outline_color.Init();
	glVertex2f(X, Y);
	glVertex2f(X + rotate_x(W, 0, _angle), Y + rotate_y(W, 0, _angle));
	glVertex2f(X + rotate_x(W, H, _angle), Y + rotate_y(W, H, _angle));
	glVertex2f(X + rotate_x(0, H, _angle), Y + rotate_y(0, H, _angle));
	glEnd();
	glLineWidth(1);
}
//прямоугольник 
inline void Gl_Print_Rectangle(float X, float Y, float W, float H, UiglColor Color, UiglColor Outline_color, float _angle, bool glossy, float line_width)
{
	Color.Init();
	glBegin(GL_POLYGON);
	if (glossy)
		Color.Init(0);
	glVertex2f(X, Y);
	if (glossy)
		Color.Init(0);
	glVertex2f(X + rotate_x(W, 0, _angle), Y + rotate_y(W, 0, _angle));
	if (glossy)
		Color.Init(0);
	glVertex2f(X + rotate_x(W, H, _angle), Y + rotate_y(W, H, _angle));
	if (glossy)
		Color.Init(0);
	glVertex2f(X + rotate_x(0, H, _angle), Y + rotate_y(0, H, _angle));
	glEnd();
	Gl_Print_Rectangle_Contour(X,Y,W,H,Outline_color,_angle,line_width);
}
//круг контур
inline void Gl_Print_Circle_Contour(float X, float Y, float r, float R, UiglColor Color, UiglColor Outline_color)
{
	glBegin(GL_TRIANGLE_STRIP);
	Color.Init();
	for (float i = 0; i <= 2 * PI; i += 0.001f)
	{
		glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
		glVertex2f(X + R + cosf(i)*r, Y + R + sinf(i)*r);
	}
	glEnd();
	Outline_color.Init();
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i <= 2 * PI; i += 0.001f)
		glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (float i = 0; i <= 2 * PI; i += 0.001f)
		glVertex2f(X + R + cosf(i)*r, Y + R + sinf(i)*r);
	glEnd();
}
//многоугольник контур
inline void Gl_Print_Polygon_Contour(float X, float Y, float R, int Sides, UiglColor Outline_color , float initial_angle, float line_width)
{
	glLineWidth(line_width);
	Outline_color.Init();
	glBegin(GL_LINE_LOOP);
	for (float i = initial_angle * PI / 180; i < PI * 2 + initial_angle * PI / 180; i += PI * 2 / Sides)
		glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
	glEnd();
	glLineWidth(1);
}
//многоугольник
inline void Gl_Print_Polygon(float X, float Y, float R, int Sides, UiglColor Color, UiglColor Outline_color , float initial_angle,float line_width)
{
	Color.Init();
	glBegin(GL_POLYGON);
	for (float i = initial_angle * PI / 180.0f; i < PI * 2.0f + initial_angle * PI / 180.0f; i += PI * 2.0f / Sides)
		glVertex2f(X + R + cosf(i)*R, Y + R + sinf(i)*R);
	glEnd();
	Gl_Print_Polygon_Contour(X, Y, R, Sides, Outline_color, initial_angle, line_width);
}

char *str_cpy(char *l, const char *r) {
	while (*r) *l++ = *r++;
	++*l = '\0';
	return l;
}

#pragma endregion

#pragma region Structurs Glui_Position AND Glui_Size
void Glui_Position::SetPosition(float Xvalue, float Yvalue, float Zvalue)
	{
		X = Xvalue;
		Y = Yvalue;
		Z = Zvalue;
		if (UpdatePtr != nullptr)
			UpdatePtr->Update();
	}
void Glui_Position::SetPosition(const Vector3f& value)
{
	X = value.X;
	Y = value.Y;
	Z = value.Z;
	if (UpdatePtr != nullptr)
		UpdatePtr->Update();
}
void Glui_Position::SetPosition(const Vector2f& value)
{
	X = value.X;
	Y = value.Y;
	Z = 0;
	if (UpdatePtr != nullptr)
		UpdatePtr->Update();
}
void Glui_Size::SetSize(float width, float height, float depth)
{
	W = width;
	H = height;
	D = depth;
	if (UpdatePtr != nullptr)
		UpdatePtr->Update();
}
#pragma endregion

#pragma region Glui_Forms
	std::vector<Glui_Forms*> Glui_Forms::Forms;
	Glui_Forms::Glui_Forms()
	{
		Forms.push_back(this);
		Glui_MainForm::AddForm();
	}
	Glui_Forms::Glui_Forms(bool add_in_main_forms)
	{
		if (add_in_main_forms) 
		{
			Forms.push_back(this);
			Glui_MainForm::AddForm();
		}
	}
	void Glui_Forms::MouseWheelFunc_g(int button, int state, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) {
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->MouseWheelFunc(button, state, ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "") 
				Wnd_proc(msg.Event, msg.Name);
		}else {
			int i = 0;
			for (std::list<Glui_IForms*>::iterator it = Stec.begin(); it != Stec.end(); it++, i++)
			{
				msg = (*it)->MouseWheelFunc(button, state, ax, ay);
				if (msg.Event == uiglEraseMsg) {
					Stec.erase(it);
					if (i <= in_focus)
						in_focus--;
				}
				if (msg.Name != "")
				{
					Wnd_proc(msg.Event, msg.Name);
					break;
				}
			}
		}
	}
	void Glui_Forms::PassiveMotionFunc_g(int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) 
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->PassiveMotionFunc(ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "") {
				Wnd_proc(msg.Event, msg.Name);
			}
		}else {
			int i = 0;
			for (std::list<Glui_IForms*>::iterator it = Stec.begin(); it != Stec.end(); i++)
			{
				msg = (*it)->PassiveMotionFunc(ax, ay);
				if (msg.Event == uiglEraseMsg)
				{
					Stec.erase(it);
					it = Stec.begin();
					std::advance(it, i);
					if (i <= in_focus)
						in_focus--;
				}
				else it++;
				if (msg.Name != "")
					Wnd_proc(msg.Event, msg.Name);
			}
		}
	}
	void Glui_Forms::MotionFunc_g(int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) 
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->MotionFunc(ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}else {
			int i = 0;
			for (std::list<Glui_IForms*>::iterator it = Stec.begin() ; it != Stec.end(); it++, i++)
			{
				msg = (*it)->MotionFunc( ax, ay);
				if (msg.Event == uiglEraseMsg) 
				{
					Stec.erase(it);
					if (i <= in_focus)
						in_focus--;
				}
				if (msg.Name != "") 
				{
					Wnd_proc(msg.Event, msg.Name);
					break;
				}
			}
		}
	}
	void Glui_Forms::MouseFunc_g(int button, int state, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) 
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->MouseFunc(button, state, ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "") 
				Wnd_proc(msg.Event, msg.Name);
		}
		else {
			int i = 0;
			for (std::list<Glui_IForms*>::iterator it = Stec.begin(); it != Stec.end(); it++, i++)
			{
				msg = (*it)->MouseFunc(button, state, ax, ay);
				if (msg.Event == uiglEraseMsg) 
				{
					Stec.erase(it);
					if (i <= in_focus)
						in_focus--;
				}
				if (msg.Name != "") 
				{
					Wnd_proc(msg.Event, msg.Name);
					in_focus = 0; 
					if (it != Stec.begin())
					{
						Stec.push_front(*it);
						Stec.erase(it);
					}
					break;
				}
			}
		}
		Set_Focus();
	}
	void Glui_Forms::KeyboardFunc_g(unsigned char key, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) 
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->KeyboardFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
			{
				Wnd_proc(msg.Event, msg.Name);
			}
		}else {
			if (key == 9 && !Shift_press)
			{
				if (in_focus < Stec.size() - 1)
					in_focus++;
				else in_focus = 0;
				Set_Focus();
			}
			if (Shift_press && key == 9)
			{
				if (in_focus > 0)
					in_focus--;
				else in_focus = Stec.size() - 1;
				Set_Focus();
			}
			std::list<Glui_IForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->KeyboardFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg) 
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
			
		}
	}
	void Glui_Forms::SpecialFunc_g(int key, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) 
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (key == 112)
			Shift_press = 1;
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->SpecialFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
			{
				Wnd_proc(msg.Event, msg.Name);
			}
		}else {
			std::list<Glui_IForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->SpecialFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
	}
	void Glui_Forms::KeyboardUpFunc_g(unsigned char key, int ax, int ay)
	{
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL) {
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->KeyboardUpFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
			{
				Wnd_proc(msg.Event, msg.Name);
			}
		}else {
			std::list<Glui_IForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->KeyboardUpFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
	}
	void Glui_Forms::SpecialUpFunc_g(int key, int ax, int ay)
	{
		if (key == 112)
			Shift_press = 0;
		if (1 != Enabled)
			return;
		UiglEvent msg;
		if (Wnd_proc == NULL)
		{
			std::cout << "Function Win_proc not found\n";
			return;
		}
		if (Focus.size())
		{
			msg = Focus[Focus.size() - 1]->SpecialUpFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
				Focus.pop_back();
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}else {
			std::list<Glui_IForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			msg = (*it)->SpecialUpFunc(key, ax, ay);
			if (msg.Event == uiglEraseMsg)
			{
				Stec.erase(it);
				in_focus--;
			}
			if (msg.Name != "")
				Wnd_proc(msg.Event, msg.Name);
		}
	}
	void Glui_Forms::Init_g(bool focus_only,bool clear_background)
	{
		if (Enabled == 0)
			return;
		if(clear_background)
			Gl_Print_Rectangle(Glui_MainForm::WndMinX, Glui_MainForm::WndMinY, Glui_MainForm::WndW, Glui_MainForm::WndH, Background_color, Background_color);
		
		if (!Focus.size() || !focus_only)
			for (std::list<Glui_IForms*>::reverse_iterator it = Stec.rbegin(); it != Stec.rend(); ++it)
				(*it)->Init();
		
		for (int i = 0; i < Focus.size(); i++)
			Focus[i]->Init();
	}
	void Glui_Forms::Focus_push_back(Glui_IForms * func)
	{
		func->SetHDC(_hdc);
		Focus.push_back(func);
	}
	void Glui_Forms::Focus_pop_back()
	{
		Focus.pop_back();
	}
	void Glui_Forms::Focus_erase(int num)
	{
		if (num<Focus.size())
			Focus.erase(Focus.begin() + num);
	}
	void Glui_Forms::Stec_erase(int num)
	{
		if (num < Stec.size()) 
		{
			std::list<Glui_IForms*>::iterator it = Stec.begin();
			std::advance(it, num);
			Stec.erase(it);
		}			
		if (in_focus < num)
		{
			in_focus--;
		}
	}
	void Glui_Forms::Stec_push_back(Glui_IForms * func)
	{
		func->SetHDC(_hdc);
		Stec.push_back(func);
	}
	void Glui_Forms::Stec_pop_back()
	{
		Stec.pop_back();
		if (in_focus == Stec.size() - 1)
			in_focus--;		
	}
	void Glui_Forms::SetHDC(HDC * _hdc_)
	{
		_hdc = _hdc_;
		for (std::list<Glui_IForms*>::iterator it = Stec.begin(); it != Stec.end(); it++)
			(*it)->SetHDC(_hdc);
		for (int i = 0; i < Focus.size(); i++)
			Focus[i]->SetHDC(_hdc);
	}
	void Glui_Forms::Set_Focus()
	{
		for (std::list<Glui_IForms*>::iterator it = Stec.begin(); it != Stec.end(); it++)
			(*it)->in_focus = 0;
		if (!Stec.empty())
		{
			std::list<Glui_IForms*>::iterator it = Stec.begin();
			std::advance(it, in_focus);
			(*it)->in_focus = 1;
		}
	}
#pragma endregion

#pragma region  Glui_MainForm
	///Glui_MainForm 
	void(*Glui_MainForm::WinProc)(uiglEvents, std::string);
	void(*Glui_MainForm::KeyboardFunc_ptr)(unsigned char, int, int) = NULL;
	void(*Glui_MainForm::SpecialFunc_ptr)(int, int, int) = NULL;
	void(*Glui_MainForm::MouseFunc_ptr)(int, int, int, int) = NULL;
	void(*Glui_MainForm::MotionFunc_ptr)(int, int) = NULL;
	void(*Glui_MainForm::PassiveMotionFunc_ptr)(int, int) = NULL;
	void(*Glui_MainForm::MouseWheelFunc_ptr)(int, int, int, int) = NULL;
	void(*Glui_MainForm::KeyboardUpFunc_ptr)(unsigned char, int, int) = NULL;
	void(*Glui_MainForm::SpecialUpFunc_ptr)(int, int, int) = NULL;
	void(*Glui_MainForm::PositionFunc_ptr)(int, int) = NULL;
	void(*Glui_MainForm::ReshapeFunc_ptr)(int, int) = NULL;

	int Glui_MainForm::WndH = 800;
	int Glui_MainForm::WndW = 600;
	int Glui_MainForm::WndX = 0;
	int Glui_MainForm::WndY = 0;
	int Glui_MainForm::WndMinX = 0;
	int Glui_MainForm::WndMinY = 0;
	HDC Glui_MainForm::hDC = NULL;
	HWND Glui_MainForm::hWnd = NULL;
	int Glui_MainForm::argc = 0;
	uiglLanguages Glui_MainForm::Language = uiglLanguageEN;
	Glui_Text Glui_MainForm::_t;
	std::vector<std::string> Glui_MainForm::argv;
	std::string Glui_MainForm::Name;
	Glui_ColDiаlog Glui_MainForm::ColDial;
	Glui_MessageBox Glui_MainForm::MsgBox;
	///Glui_MainForm end
	void Glui_MainForm::GluiInit(int _argc_, char ** _argv_)
	{
		std::string prog_name, prog_name1;
		Name = "";
		prog_name = _argv_[0];
		for (int i = prog_name.length() - 1; i >= 0; i--)
			if (prog_name[i] != 92)
				prog_name1 += prog_name[i];
			else break;
			if (prog_name1.length()>4)
				for (int i = prog_name1.length() - 1; i >= 4; i--)
					Name += prog_name1[i];
			else Name = "GLUI";

			glutInit(&_argc_, _argv_);
			glutInitWindowPosition(Glui_MainForm::WndX, Glui_MainForm::WndY);
			glutInitWindowSize(Glui_MainForm::WndW, Glui_MainForm::WndH);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutCreateWindow(Name.c_str());

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(WndMinX, WndW, WndMinY, WndH);

			for (int i = 0; i < _argc_; i++)
				argv.push_back((std::string)_argv_[i]);

			hWnd = FindWindowA(0, Name.c_str());
			hDC = GetDC(hWnd);

			glutKeyboardFunc(KeyboardFunc);
			glutSpecialFunc(SpecialFunc);
			glutMouseWheelFunc(MouseWheelFunc);
			glutPassiveMotionFunc(PassiveMotionFunc);
			glutMotionFunc(MotionFunc);
			glutMouseFunc(MouseFunc);
			glutKeyboardUpFunc(KeyboardUpFunc);
			glutSpecialUpFunc(SpecialUpFunc);
			glutReshapeFunc(ReshapeFunc);
			glutPositionFunc(PositionFunc);
			_t.SetHDC(&hDC);
			MsgBox.SetHDC(&hDC);
	}
	void Glui_MainForm::Display(bool OnlyFocus,bool clear_background)
	{
		int i = 0;
		for (auto it : Glui_Forms::Forms)
		{
			if (it != nullptr)
				it->Init_g(OnlyFocus, clear_background);
			else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
			i++;
		}
		if (MsgBox.Visible)MsgBox.Init();
	}
	void Glui_MainForm::AddForm()
	{
		int i = 0;
		for (auto it : Glui_Forms::Forms)
		{
			if (it != nullptr) 
			{
				it->SetHDC(&hDC);
				if (it->Wnd_proc == nullptr && WinProc != nullptr)
					it->Wnd_proc = WinProc;
			}
			else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
			i++;
		}
	}
	void Glui_MainForm::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->KeyboardFunc_g(key, ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (KeyboardFunc_ptr != nullptr)
				KeyboardFunc_ptr(key, ax, WndH - ay);
		}else { 
			UiglEvent ev;
			ev = MsgBox.KeyboardFunc(key, ax, WndH - ay); 
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
				WinProc(ev.Event, ev.Name);
		}
	}
	void Glui_MainForm::SpecialFunc(int key, int ax, int ay)
	{
		if (key == GLUT_KEY_F1)
		{
			if (Language == uiglLanguageRU)
				MsgBox.Show("Гагик Погосян", "Автор"); 
			else MsgBox.Show("Gagik Pogosyan", "Author");
			MsgBox.Name = "Author"; 
		}

		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->SpecialFunc_g(key, ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (SpecialFunc_ptr != nullptr)
				SpecialFunc_ptr(key, ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev = MsgBox.SpecialFunc(key, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
				WinProc(ev.Event, ev.Name);
		} 
	//	ColDial.SpecialFunc(key, ax, WndH - ay);
	}
	void Glui_MainForm::MouseFunc(int button, int state, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->MouseFunc_g(button, state, ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (MouseFunc_ptr != nullptr)
				MouseFunc_ptr(button, state, ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev =  MsgBox.MouseFunc(button, state, ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
				WinProc(ev.Event, ev.Name);
		}
	//	ColDial.MouseFunc(button,state, ax, WndH - ay);
	}
	void Glui_MainForm::MotionFunc(int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->MotionFunc_g(ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (MotionFunc_ptr != nullptr)
				MotionFunc_ptr(ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev = MsgBox.MotionFunc(ax, WndH - ay);
			if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
				WinProc(ev.Event, ev.Name);
		} 
	//	ColDial.MotionFunc(ax, WndH - ay);
	}
	void Glui_MainForm::PassiveMotionFunc(int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->PassiveMotionFunc_g(ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (PassiveMotionFunc_ptr != nullptr)
				PassiveMotionFunc_ptr(ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev = MsgBox.PassiveMotionFunc(ax, WndH - ay);
				if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
					WinProc(ev.Event, ev.Name);
		} 
	//	ColDial.PassiveMotionFunc(ax, WndH - ay);
	}
	void Glui_MainForm::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->MouseWheelFunc_g(button, state, ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (MouseWheelFunc_ptr != nullptr)
				MouseWheelFunc_ptr(button, state, ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev = MsgBox.MouseWheelFunc(button, state, ax, WndH - ay);
				if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
					WinProc(ev.Event, ev.Name);
		}
	//	ColDial.MouseWheelFunc(button, state, ax, WndH - ay);
	}
	void Glui_MainForm::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->KeyboardUpFunc_g(key, ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (KeyboardUpFunc_ptr != nullptr)
				KeyboardUpFunc_ptr(key, ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev = MsgBox.KeyboardUpFunc(key, ax, WndH - ay);
				if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
					WinProc(ev.Event, ev.Name);
		}
	//	ColDial.KeyboardUpFunc(key, ax, WndH - ay);
	}
	void Glui_MainForm::SpecialUpFunc(int key, int ax, int ay)
	{
		if (!MsgBox.Visible) {
			int i = 0;
			for (auto it : Glui_Forms::Forms)
			{
				if (it != nullptr)
					it->SpecialUpFunc_g(key, ax, WndH - ay);
				else Glui_Forms::Forms.erase(Glui_Forms::Forms.begin() + i);
				i++;
			}
			if (SpecialUpFunc_ptr != nullptr)
				SpecialUpFunc_ptr(key, ax, WndH - ay);
		}else {
			UiglEvent ev;
			ev = MsgBox.SpecialFunc(key, ax, WndH - ay);
				if (ev.Event != uiglEvents::uiglEventEmpty && ev.Name != "" && WinProc != nullptr)
					WinProc(ev.Event, ev.Name);
		}
	//	ColDial.SpecialFunc(key, ax, WndH - ay);
	}
	void Glui_MainForm::PositionFunc(int ax, int ay)
	{
		WndX = ax;
		WndY = ay;
		if (PositionFunc_ptr != nullptr)
			PositionFunc_ptr(ax, ay);
	}
	void Glui_MainForm::ReshapeFunc(int aw, int ah)
	{
		WndH = ah;
		WndW = aw;
		if (ReshapeFunc_ptr != nullptr)
			ReshapeFunc_ptr(aw, ah);
	}
#pragma endregion

#pragma region Glui_Text
	Glui_Text::Glui_Text()
	{
		size_text = 12;
		W = H = 0;
	}
	Glui_Text::~Glui_Text()
	{
		KillFont();
	}
	void Glui_Text::Setfontsize(int _size)
	{
		//	KillFont();
		size_text = _size;
		H = 0;
		bildfont();

	}
	void Glui_Text::SetHeightText(int _h)
	{
		H = _h;
		size_text = _h;
		bildfont();
	}
	void Glui_Text::SetWidthText(int _w)
	{
		W = _w;
	}
	void Glui_Text::glText(float x, float y, const std::string txt, UiglColor col)
	{
		col.Init();
		if (H > 0)
			y += H*0.1;

		glRasterPos2d(x, y);
		glPushAttrib(GL_LIST_BIT);
		glListBase(arial - 32);
#ifndef NDEBUG
		glCallLists((GLsizei)txt.length(), GL_UNSIGNED_BYTE, txt.c_str());
#else// NDEBUG
		std::wstring stemp = std::wstring(txt.begin(), txt.end());
		LPCWSTR sw = stemp.c_str();
		glCallLists((GLsizei)txt.length(), GL_SHORT, sw);
#endif// NDEBUG
		glPopAttrib();
	}
	float Glui_Text::Get_text_length(std::string txt)
	{
		if ("Consolas" != Font)
			return 0;

		float _l = 0.55f;
		int _count(0);

		for (int i = 0; i < txt.size(); i++)
			if (txt[i] >= ' ' && txt[i] <= '~' || txt[i] >= 'А' && txt[i] <= 'я')
				_count++;

		switch (size_text)
		{
		case	1: _l = 1; break;
		case	2: _l = 0.5; break;
		case	3: _l = 0.6666; break;
		case	4: _l = 0.501001; break;
		case	5: _l = 0.60099; break;
		case	6: _l = 0.501001; break;
		case	7: _l = 0.571; break;
		case	8: _l = 0.5; break;
		case	9: _l = 0.556; break;
		case	10: _l = 0.501001; break;
		case	11: _l = 0.547; break;
		case	12: _l = 0.584; break;
		case	13: _l = 0.539; break;
		case	14: _l = 0.572; break;
		case	15: _l = 0.533; break;
		case	16: _l = 0.562; break;
		case	17: _l = 0.529; break;
		case	18: _l = 0.556; break;
		case	19: _l = 0.526; break;
		case	20: _l = 0.55; break;
		case	21: _l = 0.571; break;
		case	22: _l = 0.545; break;
		case	23: _l = 0.565; break;
		case	24: _l = 0.542; break;
		case	25: _l = 0.56; break;
		case	26: _l = 0.538; break;
		case	27: _l = 0.555; break;
		case	28: _l = 0.535; break;
		case	29: _l = 0.551; break;
		case	30: _l = 0.533; break;
		case	31: _l = 0.548; break;
		case	32: _l = 0.561; break;
		case	33: _l = 0.545; break;
		case	34: _l = 0.558; break;
		case	35: _l = 0.542; break;
		case	36: _l = 0.556; break;
		case	37: _l = 0.541; break;
		case	38: _l = 0.553; break;
		case	39: _l = 0.539; break;
		case	40: _l = 0.55; break;
		case	41: _l = 0.561; break;
		case	42: _l = 0.548; break;
		case	43: _l = 0.558; break;
		case	44: _l = 0.545; break;
		case	45: _l = 0.556; break;
		case	46: _l = 0.543; break;
		case	47: _l = 0.553; break;
		case	48: _l = 0.541; break;
		case	49: _l = 0.551; break;
		case	50: _l = 0.54; break;
		case	51: _l = 0.548; break;
		case	52: _l = 0.557; break;
		case	53: _l = 0.547; break;
		case	54: _l = 0.555; break;
		case	55: _l = 0.545; break;
		case	56: _l = 0.553; break;
		case	57: _l = 0.543; break;
		case	58: _l = 0.551; break;
		case	59: _l = 0.542; break;
		case	60: _l = 0.549; break;
		case	61: _l = 0.557; break;
		case	62: _l = 0.548; break;
		case	63: _l = 0.555; break;
		case	64: _l = 0.546; break;
		case	65: _l = 0.553; break;
		case	66: _l = 0.545; break;
		case	67: _l = 0.551; break;
		case	68: _l = 0.544; break;
		case	69: _l = 0.55; break;
		case	70: _l = 0.543; break;
		case	71: _l = 0.549; break;
		case	72: _l = 0.555; break;
		case	73: _l = 0.547; break;
		case	74: _l = 0.553; break;
		case	75: _l = 0.546; break;
		case	76: _l = 0.552; break;
		case	77: _l = 0.545; break;
		case	78: _l = 0.551; break;
		case	79: _l = 0.544; break;
		case	80: _l = 0.549; break;
		case	81: _l = 0.554; break;
		case	82: _l = 0.548; break;
		case	83: _l = 0.553; break;
		case	84: _l = 0.547; break;
		case	85: _l = 0.551; break;
		case	86: _l = 0.546; break;
		case	87: _l = 0.551; break;
		case	88: _l = 0.544; break;
		case	89: _l = 0.55; break;
		case	90: _l = 0.544; break;
		case	91: _l = 0.548; break;
		case	92: _l = 0.553; break;
		case	93: _l = 0.547; break;
		case	94: _l = 0.552; break;
		case	95: _l = 0.547; break;
		case	96: _l = 0.552; break;
		case	97: _l = 0.546; break;
		case	98: _l = 0.551; break;
		case	99: _l = 0.545; break;
		case	100: _l = 0.55; break;
		case	101: _l = 0.554; break;
		case	102: _l = 0.549; break;
		case	103: _l = 0.553; break;
		case	104: _l = 0.548; break;
		case	105: _l = 0.552; break;
		case	106: _l = 0.547; break;
		case	107: _l = 0.551; break;
		case	108: _l = 0.546; break;
		case	109: _l = 0.55; break;
		case	110: _l = 0.545; break;
		case	111: _l = 0.549; break;
		case	112: _l = 0.553; break;
		case	113: _l = 0.548; break;
		case	114: _l = 0.552; break;
		case	115: _l = 0.547; break;
		default:
			_l = 0.55;
			break;
		}
		return _l*(float)(size_text*_count);
	}
	void Glui_Text::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		bildfont();
	}
	void Glui_Text::SetFont(std::string font_name)
	{
		Font = font_name;
		//	KillFont();
		bildfont();
	}
	void Glui_Text::bildfont()
	{
		hdc = &Glui_MainForm::hDC;
		HFONT   oldfont;
		if (!hdc)
			return;
		KillFont();
		arial = glGenLists(255);
		font = CreateFontA(-size_text, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, DEFAULT_QUALITY | DEFAULT_PITCH,
			Font.c_str());

		oldfont = (HFONT)SelectObject(*hdc, font);
		wglUseFontBitmaps(*hdc, 32, 224, arial);
		SelectObject(*hdc, oldfont);
		DeleteObject(font);

	}
	void Glui_Text::KillFont()
	{
		glDeleteLists(arial, 255);
	}
#pragma endregion

#pragma region Glui_Roundrect
	Glui_Roundrect::Glui_Roundrect()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 50;
		H = 50;
		R = 20;
		Color = Silver;
	}
	UiglEvent Glui_Roundrect::MouseFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		UiglEvent result;
		bool lu, ld, ru, rd, B1, B2;
		B1 = ((ax > X) && (ax < X + W) && (ay>Y + R) && (ay < Y + H - R));
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
	UiglEvent Glui_Roundrect::PassiveMotionFunc(int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		if (R > H / 2 || R > W / 2)
		{
			if (W > H)
				R = H / 2;
			else R = W / 2;
		}
		UiglEvent result;
		bool lu, ld, ru, rd, B1, B2;
		B1 = ((ax > X) && (ax < X + W) && (ay>Y + R) && (ay < Y + H - R));
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
	UiglEvent Glui_Roundrect::MotionFunc(float ax, float ay)
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
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent Glui_Roundrect::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		bool lu, ld, ru, rd, B1, B2;
		B1 = ((ax > X) && (ax < X + W) && (ay>Y + R) && (ay < Y + H - R));
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
	UiglEvent Glui_Roundrect::KeyboardFunc(unsigned char key, int ax, int ay)
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
	UiglEvent Glui_Roundrect::SpecialFunc(int key, int ax, int ay) 
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Roundrect::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Roundrect::SpecialUpFunc(int key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		return result;
	}
	void Glui_Roundrect::Init()
	{
		if (!Visible) return;
		
		int _n = 0;
		if (Mouse_in_button&&IsHover)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		Gl_Print_Roundrect(X, Y, W, H, R, Color + _n, Outline_color_temp,Angle);
	}
#pragma endregion

#pragma region Glui_Circle
	Glui_Circle::Glui_Circle()
	{
		Position.UpdatePtr = this;
//		Size.UpdatePtr = this;
		R = 10;
	}
	UiglEvent Glui_Circle::MouseFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;

		if (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R)
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
	UiglEvent Glui_Circle::PassiveMotionFunc(int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		if (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R)
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
	UiglEvent Glui_Circle::MotionFunc(float ax, float ay) 
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent Glui_Circle::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		if (sqrt((X + R - ax)*(X + R - ax) + (Y + R - ay)*(Y + R - ay)) < R)
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent Glui_Circle::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Circle::SpecialFunc(int key, int ax, int ay) 
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Circle::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;

	}
	UiglEvent Glui_Circle::SpecialUpFunc(int key, int ax, int ay)
	{
		if (!Visible) return UiglEvent();
		UiglEvent result;
		return result;
	}
	void Glui_Circle::Init()
	{
		if (!Visible) return;
		if (Position.UpdatePtr != this)
		{
			Position.UpdatePtr = this;
		}
		int _n = 0;
		if (Mouse_in_button&&IsHover)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		Gl_Print_Circle(X, Y, R, Color + _n, Outline_color_temp);
	}
	void Glui_Circle::Update()
	{
		Position.UpdatePtr = this;
		X = Position.GetPositionX();
		Y = Position.GetPositionY();
		H = Size.GetSizeH();
		W = Size.GetSizeW();
	}
#pragma endregion 

#pragma region Glui_Rectangle
	Glui_Rectangle::Glui_Rectangle()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		H = W = 20;
		Color = White;
	}
	UiglEvent Glui_Rectangle::MouseFunc(int button, int state, int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		UiglEvent result;
		if (!Visible) return result;
		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Rectangle::PassiveMotionFunc(int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (!Visible) return result;
		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Rectangle::MotionFunc(float ax, float ay)
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
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent Glui_Rectangle::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		UiglEvent result;
		if (!Visible) return result;
		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent Glui_Rectangle::KeyboardFunc(unsigned char key, int ax, int ay)
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
	UiglEvent Glui_Rectangle::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent Glui_Rectangle::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent Glui_Rectangle::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	void Glui_Rectangle::Init()
	{
		if (!Visible) return;

		int _n = 0;
		if (Mouse_in_button&&IsHover)
			_n = 80;

		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();

		Gl_Print_Rectangle(X, Y, W, H, Color + _n, Outline_color_temp,Angle);
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
	void Glui_Rectangle::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.SetHDC(_hdc);
	}
	void Glui_Rectangle::Set_text_size(float _size)
	{
		Text_size = _size;
		//textprint.Setfontsize(Text_size);
		textprint.SetHeightText(_size);
	}
#pragma endregion
	
#pragma region Glui_Skrollbar
	Glui_Skrollbar::Glui_Skrollbar()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		H = 20;
		W = 100;
		Size.SetSize(W, H);
		Max = 100;
		Min = 0;
		Slider_length = 10;
		Position_p = Min;
		Px = H + Slider_length;
		Step = 1;
		Color_slider.setColor(Silver);
		Color = White;
	}
	UiglEvent Glui_Skrollbar::MouseFunc(int button, int state, int ax, int ay)
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
	UiglEvent Glui_Skrollbar::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		int _X = X, _Y = Y;
		if (!Visible) return result;
		if ((ax > _X) && (ax < _X + W) && (ay>_Y) && (ay < _Y + H))
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
			}else {

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
	UiglEvent Glui_Skrollbar::MotionFunc(float ax, float ay) {
		UiglEvent result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
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
	UiglEvent Glui_Skrollbar::MouseWheelFunc(int button, int state, int ax, int ay)
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
	UiglEvent Glui_Skrollbar::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent Glui_Skrollbar::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent Glui_Skrollbar::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent Glui_Skrollbar::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	void Glui_Skrollbar::Init()
	{
		if (!Visible) return;

		Gl_Print_Rectangle(X, Y, W, H, Color, Outline_color, Angle);
		UiglColor _col = Color;
		if (passiv_hover == 1 && IsHover)
			_col = _col + 70;
		Gl_Print_Rectangle(X, Y, H*0.9f, H, _col, Outline_color, Angle);
		_col = Color;
		if (passiv_hover == 2 && IsHover)
			_col = _col + 70;
		Gl_Print_Rectangle(rotate_x(W - H*0.9f, 0, Angle) + X, rotate_y(W - H*0.9f, 0, Angle) + Y, H*0.9f, H, _col, Outline_color, Angle);
		_col = Color_slider;
		if (passiv_hover == 3 && IsHover)
			_col = _col + 100;
		Gl_Print_Rectangle(X + rotate_x(Px - Slider_length, H*0.1, Angle), Y + rotate_y(Px - Slider_length, H*0.1, Angle), Slider_length * 2, H*0.8, _col, Outline_color, Angle);

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
	float Glui_Skrollbar::Step_forward()
	{
		if (Position_p < Max)
			Position_p++;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
		return Position_p;
	}
	float Glui_Skrollbar::Step_ago()
	{
		if (Position_p > Min)
			Position_p--;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min) + 1.0f;
		return Position_p;
	}
	void Glui_Skrollbar::Set_Slider_length(float length)
	{
		Slider_length = length;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
	}
	float Glui_Skrollbar::Set_Position(float position)
	{
		Position_p = position;
		if (position>Max)
			Position_p = Max;
		if (position < Min)
			Position_p = Min;
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
		return Position_p;
	}
	float Glui_Skrollbar::Get_Position()
	{
		return Position_p;
	}
	void Glui_Skrollbar::Update()
	{
		X = Position.GetPositionX();
		Y = Position.GetPositionY();
		W = Size.GetSizeW();
		H = Size.GetSizeH();
		Px = Slider_length + H + (W - 2.0f * (H + Slider_length)) / (Max - Min)*(Position_p - Min);
	}
#pragma endregion

#pragma region Glui_Checkbox
	Glui_Checkbox::Glui_Checkbox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 50.0f;
		Line_length = 2.0f;
		Text_size = W;
		Color = White;
		//	textprint.SetHDC(hdc);
	}
	UiglEvent Glui_Checkbox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (button == 0 && state == 0)
			if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + W))
			{
				if (Checked)
				{
					Checked = 0;
				}
				else Checked = 1;
				result.Name = Name;
				result.Event = uiglChanged;
			}
		return result;
	}
	UiglEvent Glui_Checkbox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;

		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + W))
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
	UiglEvent Glui_Checkbox::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent Glui_Checkbox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Checkbox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Checkbox::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Checkbox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && key == ' ')
		{
			Checked = !Checked;
			result.Name = Name;
			result.Event = uiglChanged;
		}

		return result;
	}
	UiglEvent Glui_Checkbox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void Glui_Checkbox::Init()
	{
		UiglColor _col = Color,_col1 = Outline_color;
		if (Mouse_in_button)
			_col = _col + 72;
		if (in_focus)
			_col1 = _col1.getNegative();
		Gl_Print_Rectangle(X, Y, W, W, _col, _col1);
		Gl_Print_Rectangle_Contour(X, Y, W, W, Outline_color,0, Line_length);
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
	void Glui_Checkbox::Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.Setfontsize(Text_size);
	}
	void Glui_Checkbox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.SetHDC(_hdc);
		textprint.Setfontsize(Text_size);
	}
#pragma endregion

#pragma region Glui_Progressbar
	Glui_Progressbar::Glui_Progressbar()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Color = White;
	}
	UiglEvent Glui_Progressbar::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Progressbar::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Progressbar::MotionFunc(float ax, float ay) 
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent Glui_Progressbar::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent Glui_Progressbar::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Progressbar::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Progressbar::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Progressbar::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void Glui_Progressbar::Init()
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
			BorderColor.Init(-50,100);
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
			Gl_Print_Rectangle(X + PositionBar*W / (Max - Min), Y, W - PositionBar*W / (Max - Min) - 0.0f, H - 2.0f, Color, Color);
		Gl_Print_Rectangle_Contour(X, Y, W, H, Outline_color);

		if (Pos <  W*1.2f-5.0f)
			Pos += 5.0f;
		else Pos = 0.0f;

	}
	int Glui_Progressbar::Step_forward()
	{
		if (PositionBar + Step < Max)
			PositionBar += Step;
		else PositionBar = Max;
		return PositionBar;
	}
	int Glui_Progressbar::Step_ago()
	{
		if (PositionBar - Step > Min)
			PositionBar -= Step;
		else PositionBar = Min;
		return PositionBar;
	}
#pragma endregion 

#pragma region Glui_Textbox
	Glui_Textbox::Glui_Textbox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 200.0f;
		H = 40.0f;
		textprint.SetHeightText(H - H*0.2f);
		Color = White;
		Cursor_time = clock();
		textprint.SetFont("Consolas");
		Selection_color.setAlpha(100);
		Text_max_length = Text.max_size();
	}
	UiglEvent Glui_Textbox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == 0 && button == 0)
			{
				result.Event = uiglMouseLeftDown;
				moved = true;
				mx = ax - X;
				my = ay - Y;

				Cursor_pos = text_pos_begin + (int)(ax - X) / textprint.Get_text_length("a");
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
	UiglEvent Glui_Textbox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Textbox::MotionFunc(float ax, float ay) 
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		if (moved == true) 
		{
			int _n = ax - X;
		//	if (_n > 0)
		//		_n = -1;
			Cursor_pos = Select_end = text_pos_begin + int(_n / textprint.Get_text_length("a"));
			if (Select_end > Text.length())
				Select_end = Text.length();
		}
		return result;
	}
	UiglEvent Glui_Textbox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent Glui_Textbox::KeyboardFunc(unsigned char key, int ax, int ay)
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
	UiglEvent Glui_Textbox::SpecialFunc(int key, int ax, int ay) 
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
	UiglEvent Glui_Textbox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Textbox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
			Shift_press = 0;
		return result;
	}
	void Glui_Textbox::Init()
	{
		if (Cursor_pos >= Text.length())
			Cursor_pos = Text.length();

		if (clock() - Cursor_time  > 400)
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

		Gl_Print_Rectangle(X, Y, W, H, Color + _n, Outline_color_temp);


		std::string Text1 = Text;
		int out_l = 0;
		while (textprint.Get_text_length(Text1) > W)
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


		float char_length = textprint.Get_text_length("a");
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
				Gl_Print_Rectangle(sel_b + X, Y + H*0.1, sel_l, H*0.7, Selection_color, Selection_color);
			textprint.glText(X + 2, Y + H*0.2, Text.substr(text_pos_begin, _length), Text_color);
		}
		else {
			textprint.glText(X + 2, Y + H*0.2, Text.substr(0, _length), Text_color);
		}

		if (in_focus && !Read_only) {
			cursor_line_pos = textprint.Get_text_length(Text.substr(text_pos_begin, Cursor_pos - text_pos_begin)) + X + 2;
			if (Cursor_enbl) {
				Text_color.Init();
				glBegin(GL_LINES);
				glVertex2f(cursor_line_pos, Y + H*0.1);
				glVertex2f(cursor_line_pos, Y + H*0.9);
				glEnd();
			}
		}
	}
	void Glui_Textbox::Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.SetHeightText(Text_size - 2);
	}
	void Glui_Textbox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.SetHDC(_hdc);
	}
#pragma endregion
	
#pragma region Glui_Combobox
	Glui_Combobox::Glui_Combobox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Size.SetSize(200, 30);
		tbox.Size.SetSize(200-30*0.8f, 30);
		tbox.Position.SetPosition(0, 0);
		tbox.Read_only = true;
		Color = White;
		Skroll.Set_Position(2);
		MaxDropDownItems = 5;
		Select_min = 0;
	}
	UiglEvent Glui_Combobox::MouseFunc(int button, int state, int ax, int ay)
	{
		tbox.MouseFunc(button, state, ax, ay);
			
		UiglEvent result;
		if (button == 0 && state == 0)
		{
			if (Position.GetPositionX()<ax && Position.GetPositionX() + Size.GetSizeW()>ax &&
				Position.GetPositionY()<ay && Position.GetPositionY() + Size.GetSizeH()>ay)
			{
				result.Name = Name;
				result.Event = uiglMouseLeftDown;
				if (ax > Position.GetPositionX() + Size.GetSizeW() - Size.GetSizeH()*0.8f)
					open = true;
			}
		}
		if (button == 0 && state == 1)
		{
			if (Position.GetPositionX()<ax && Position.GetPositionX() + Size.GetSizeW()>ax &&
				Position.GetPositionY()<ay && Position.GetPositionY() + Size.GetSizeH()>ay)
			{
				result.Name = Name;
				result.Event = uiglMouseLeftUp;
			}
		}
		if (button == 1 && state == 0)
		{
			if (Position.GetPositionX()<ax && Position.GetPositionX() + Size.GetSizeW()>ax &&
				Position.GetPositionY()<ay && Position.GetPositionY() + Size.GetSizeH()>ay)
			{
				result.Name = Name;
				result.Event = uiglMouseCenterDown;
			}
		}
		if (button == 1 && state == 1)
		{
			if (Position.GetPositionX()<ax && Position.GetPositionX() + Size.GetSizeW()>ax &&
				Position.GetPositionY()<ay && Position.GetPositionY() + Size.GetSizeH()>ay)
			{
				result.Name = Name;
				result.Event = uiglMouseCenterUp;
			}
		}
		if (button == 2 && state == 0)
		{
			if (Position.GetPositionX()<ax && Position.GetPositionX() + Size.GetSizeW()>ax &&
				Position.GetPositionY()<ay && Position.GetPositionY() + Size.GetSizeH()>ay)
			{
				result.Name = Name;
				result.Event = uiglMouseRightDown;
			}
		}	
		if (button == 2 && state == 1)
		{
			if (Position.GetPositionX()<ax && Position.GetPositionX() + Size.GetSizeW()>ax &&
				Position.GetPositionY()<ay && Position.GetPositionY() + Size.GetSizeH()>ay)
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
	UiglEvent Glui_Combobox::PassiveMotionFunc(int ax, int ay)
	{
		tbox.PassiveMotionFunc(ax, ay);
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			if(ax>X+W-H*0.8f)
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
	UiglEvent Glui_Combobox::MotionFunc(float ax, float ay) 
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
	UiglEvent Glui_Combobox::MouseWheelFunc(int button, int state, int ax, int ay)
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
	UiglEvent Glui_Combobox::KeyboardFunc(unsigned char key, int ax, int ay)
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
	UiglEvent Glui_Combobox::SpecialFunc(int key, int ax, int ay) 
	{
		tbox.SpecialFunc(key,ax,ay);

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
	UiglEvent Glui_Combobox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		tbox.KeyboardUpFunc(key, ax, ay);
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Combobox::SpecialUpFunc(int key, int ax, int ay)
	{
		tbox.SpecialUpFunc(key, ax, ay);
		UiglEvent result;
		return result;
	}
	void Glui_Combobox::Init()
	{
		tbox.Color = Color;
		tbox.in_focus = in_focus;
		if(Items.size()>0&&Select>=0&&Select<Items.size())
			tbox.Text = Items[Select];

		tbox.Init();
		UiglColor Outline_Color_Temp = Outline_color, Color_temp = Color;
		if (in_focus)
			Outline_Color_Temp = Outline_color.getNegative();
		if (hover_index == 1)
			Color_temp = Color + 70;
		Gl_Print_Rectangle(X + W - H*0.8f, Y, H*0.8f, H, Color_temp, Outline_Color_Temp);
		
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
					Gl_Print_Rectangle(X, Y - (i + 1.0f)*H, W, H, Color, Outline_color);
				else Gl_Print_Rectangle(X, Y - (i + 1.0f)*H, W, H, Color_select, Outline_color);
				tbox.textprint.glText(X + H*0.1f, Y - (i + 1.0f)*H + H*0.25f, Items[i + Select_min].c_str());
			}
		}
		/*
		
			
			initiation();
			if(MaxDropDownItems<Items.size())
				Skroll.Init();
		}*/
	}
	void Glui_Combobox::Set_text_size(float _size)
	{
		Text_size = _size;
		tbox.Set_text_size(_size);
	}
	void Glui_Combobox::initiation()
	{
		Skroll.SetAngle(90);
		Skroll.Size.SetSize(Skroll.Size.GetSizeW(),H*0.8f);
		if (MaxDropDownItems < Items.size())
		{
			Skroll.Size.SetSize(H *MaxDropDownItems,Skroll.Size.GetSizeH());
			Skroll.Position.SetPosition(X + W - H*0.8f, Y - H*MaxDropDownItems);
		}
		else {
			Skroll.Size.SetSize(H *Items.size(), Skroll.Size.GetSizeH());
			Skroll.Position.SetPosition(X + W - H*0.8f, Y - H*Items.size());
		}
		Skroll.Max = Items.size() - MaxDropDownItems;
		Skroll.Color = Color;
		Skroll.Color_slider = Color_select;
		Skroll.Outline_color = Outline_color;
	}
	void Glui_Combobox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		tbox.SetHDC(_hdc);
	}
	void Glui_Combobox::Update()
	{
		X = Position.GetPositionX();
		Y = Position.GetPositionY();
		H = Size.GetSizeH();
		W = Size.GetSizeW();
		tbox.Size.SetSize(W-H*0.8f, H);
		tbox.Position.SetPosition(X, Y);
	}
#pragma endregion

#pragma region Glui_Listbox
	Glui_Listbox::Glui_Listbox()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 200;
		H = 400;
		Color = White;
		Skrol.SetAngle(90);
		Skrol.Set_Position(100);
	}
	UiglEvent Glui_Listbox::MouseFunc(int button, int state, int ax, int ay)
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
	UiglEvent Glui_Listbox::PassiveMotionFunc(int ax, int ay)
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
	UiglEvent Glui_Listbox::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		if (Skrol.MotionFunc(ax, ay).Event == uiglChanged)
		{
			int _count = ((H - 10) / Text_size);
			item_up_num = Items.size() - _count - Skrol.Get_Position();

		}


		return result;
	}
	UiglEvent Glui_Listbox::MouseWheelFunc(int button, int state, int ax, int ay)
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
	UiglEvent Glui_Listbox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;

		if (key == 13 && in_focus)
		{
			result.Name = Name;
			result.Event = uiglEnter;
		}
		return result;
	}
	UiglEvent Glui_Listbox::SpecialFunc(int key, int ax, int ay)
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
	UiglEvent Glui_Listbox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Listbox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void Glui_Listbox::Init()
	{
		int _count = ((H - 10.0f) / Text_size);
		Gl_Print_Rectangle(X, Y, W, H, Color, Outline_color);

		if (Selected >= 0 && Selected >= item_up_num && Selected < item_up_num + _count)
		{
			Gl_Print_Rectangle(X + 1, Y + H - 5 - (Selected - item_up_num + 1)*Text_size, W - 2, Text_size, Select_color, Outline_color);
		}

		for (int i = 0; i < Items.size() - item_up_num && i<_count; i++)
		{
			textprint.glText(X + 5, Y + H - 2 - (i + 1)*Text_size, Items[i + item_up_num], Text_color);
		}
		if (_count<Items.size()) {
			Skrol.Color = Color;
			Skrol.Color_slider = Select_color;
			Skrol.Outline_color = Outline_color;
			Skrol.Size.SetSize(H, 19);
			Skrol.Position.SetPosition(X + W, Y);
			Skrol.Set_Position(Items.size() - _count - item_up_num);
			if (Items.size() > _count)
				Skrol.Max = Items.size() - _count;
			else Skrol.Max = 1;
			Skrol.Init();
			Skrol.Set_Slider_length(20);
		}
		else item_up_num = 0;
	}
	void Glui_Listbox::Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.SetHeightText(_size);
	}
	std::string Glui_Listbox::Get_Selected_text()
	{
		if (Selected >= 0 && Selected<Items.size())
			return Items[Selected];
		else return "Do not selection";
	}
	void Glui_Listbox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.SetHDC(_hdc);
	}
#pragma endregion

#pragma region Glui_Numericupdown
	Glui_Numericupdown::Glui_Numericupdown()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		NumbersOnly = 1;
	}
	UiglEvent Glui_Numericupdown::MouseFunc(int button, int state, int ax, int ay)
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

				Cursor_pos = text_pos_begin + (int)(ax - X) / textprint.Get_text_length("a");
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
	UiglEvent Glui_Numericupdown::PassiveMotionFunc(int ax, int ay)
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
	UiglEvent Glui_Numericupdown::KeyboardFunc(unsigned char key, int ax, int ay)
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
	UiglEvent Glui_Numericupdown::SpecialFunc(int key, int ax, int ay) 
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
	void Glui_Numericupdown::Init()
	{
		Glui_Textbox::Init();
		UiglColor Outline_color_temp = Outline_color;
		if (in_focus)
			Outline_color_temp = Outline_color.getNegative();
		int _n_up = 0, _n_down = 0;
		if (Mouse_in_button_up)
			_n_up = 80;
		if (Mouse_in_button_down)
			_n_down = 80;
		Gl_Print_Rectangle(X + W - H*0.8f, Y, H*0.8f, H*0.5f, Color + -20 + _n_down, Outline_color_temp);
		Gl_Print_Rectangle(X + W - H*0.8f, Y + H*0.5f, H*0.8f, H*0.5f, Color + -20 + _n_up, Outline_color_temp);
		Gl_Print_Polygon(X + W - H*0.5f, Y + H*0.6, H*0.1f, 3, Outline_color, Outline_color_temp, -30);
		Gl_Print_Polygon(X + W - H*0.5f, Y + H*0.1, H*0.1f, 3, Outline_color, Outline_color_temp, 30);
	}
#pragma endregion 

#pragma region Glui_Config
	Glui_Config::Glui_Config(std::string file_name)
	{
		if (Open(file_name))
		{
			_is_open = true;
			_file_name = file_name;
		}
		else _is_open = false;
	}
	Glui_Config::Glui_Config()
	{
		_is_open = false;
		_file_name = "";
	}
	Glui_Config::~Glui_Config()
	{ 
		Data.clear(); 
	}
	bool Glui_Config::Open(std::string file_name)
	{
		if (file_name == "")
			file_name = _file_name;
		else _file_name = file_name;

		std::ifstream in;
		in.open(file_name);
		if (!in.is_open())
			return false;

		Data.clear();
		std::string text;
		unsigned int count;
		in >> text;

		if (text != "GCF")
			return false;
		string_int temp;
		while (true)
		{
			if (in >> text)
			{
				temp.Text = text;
				in >> count;
				temp.Count = count;
				Data.push_back(temp);
				//	std::cout << "in   " << temp.Text << "  " << temp.Count<<std::endl;
			}
			else break;

		}
		in.close();
		return true;
	}
	bool Glui_Config::Get_count(std::string name, int & count)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			if (name == Data[i].Text)
			{
				count = Data[i].Count;
				return true;
			}
		}
		return false;
	}
	bool Glui_Config::Get_color(std::string name, UiglColor & col)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			if (name == Data[i].Text)
			{
				col.setUInt(Data[i].Count);
				return true;
			}
		}
		return false;
	}
	bool Glui_Config::Set_count(std::string name, int count, bool _save)
	{
		bool a(0);
		for (int i = 0; i < Data.size(); i++)
		{
			if (name == Data[i].Text)
			{
				Data[i].Count = count;
				a = 1;
				break;
			}
		}
		if (_save)
			Save();
		if (a)
			return true;
		return false;
	}
	bool Glui_Config::setColor(std::string name, UiglColor col, bool _save)
	{
		bool a(0);
		for (int i = 0; i < Data.size(); i++)
		{
			if (name == Data[i].Text)
			{

				Data[i].Count = col.getUInt();
				a = 1;
				break;
			}
		}
		if (_save)
			Save();
		if (a)
			return true;
		return false;
	}
	bool Glui_Config::Save(std::string file_name)
	{
		if (file_name == "")
			file_name = _file_name;
		std::ofstream out;
		out.open(file_name);
		if (!out.is_open())
			return false;
		_is_open = true;

		std::sort(Data.begin(), Data.end(), [](string_int a, string_int b) {return a.Text < b.Text; });
		out << "GCF\n";

		for (int i = 0; i < Data.size(); i++)
		{
			out << Data[i].Text << " " << Data[i].Count << std::endl;
			//	std::cout<<"out  " << Data[i].Text << " " << Data[i].Count << std::endl;
		}
		out.close();
		return true;
	}
	bool Glui_Config::Add_item(std::string name, int count)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			if (name == Data[i].Text)
			{
				return false;
			}
		}
		string_int temp;
		temp.Count = count;
		temp.Text = name;
		Data.push_back(temp);
		return true;
	}
	bool Glui_Config::Erase_item(std::string name)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			if (Data[i].Text == name)
			{
				Data.erase(Data.begin() + i);
			}
		}
		return true;
	}
	bool Glui_Config::Clear()
	{
		Data.clear();
		return 1;
	}
#pragma endregion

#pragma region Glui_Picture
	Glui_Picture::Glui_Picture()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		H = W = 100.f;
	}
	void Glui_Picture::Init()
	{
		float _w, _h;
		if (w_p != 0 && h_p != 0)
		{
			_w = W / w_p;
			_h = H / h_p;
		}
		else {
			_w = 1; _h = 1;
		}
		bool contour(0);
		for (int i = 0; i < layers.size(); i++)
		{
			glBegin(layers[i].primitive);
			Line_init(layers[i].primitive, layers[i].line_length);
			for (int j = 0; j < points[i].size(); j++)
			{
				points[i][j].Color.Init();
				glVertex2f(points[i][j].X*_w + X, points[i][j].Y*_h + Y);
				contour = 1;
			}
			Line_init(layers[i].primitive);
			glEnd();
		}
		
		if (!contour)
			Gl_Print_Rectangle_Contour(X, Y, W, H, Outline_color);

///		glLineWidth(1);
//		glPointSize(1);
	}
	bool Glui_Picture::Open(std::string _file_name)
	{
		layers.clear();
		points.clear();
		if (_file_name == "")
			_file_name = file_name;
		else file_name = _file_name;
		std::ifstream in;
		in.open(_file_name, std::ios::binary);
		if (!in.is_open())
			return 0;
		Layer _L;
		UiglPoint _P;
		int n(0);
		in >> W >> H;
		in.get();
		w_p = W;
		h_p = H;
		std::vector<UiglPoint> pp;
		while (!in.eof())
		{
			in.read((char*)&_L, sizeof(_L));
			layers.push_back(_L);
			points.push_back(std::vector<UiglPoint>());
			for (int i = 0; i < _L.count && !in.eof(); i++)
			{
				in.read((char*)&_P, sizeof(_P));
				points[n].push_back(_P);
			}
			n++;
		}
		return 1;
	}
	UiglEvent Glui_Picture::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Picture::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
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
	UiglEvent Glui_Picture::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (is_move&&moved)
		{
			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent Glui_Picture::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;

		if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
		{
			result.Name = Name;
			if (state == -1)
				result.Event = uiglWheelDown;
			if (state == 1)
				result.Event = uiglWheelUp;
		}
		return result;
	}
	UiglEvent Glui_Picture::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (in_focus && key == 13)
		{
			result.Event = uiglEnter;
			result.Name = Name;
		}
		return result;
	}
	UiglEvent Glui_Picture::SpecialFunc(int key, int ax, int ay) 
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Picture::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_Picture::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void Glui_Picture::Line_init(uiglPrimitives prim, float length)
	{
		switch (prim)
		{
		case uiglPOINTS:
			glPointSize(length);
			break;
		case uiglLINES:
		case uiglLINE_LOOP:
		case uiglLINE_STRIP:
			glLineWidth(length);
			break;
		case uiglTRIANGLES:
		case uiglTRIANGLE_STRIP:
		case uiglTRIANGLE_FAN:
		case uiglQUADS:
		case uiglQUAD_STRIP:
		case uiglPOLYGON:
			break;
		}
	}
#pragma endregion

#pragma region Glui_ColDiаlog
	Glui_ColDiаlog::Glui_ColDiаlog()
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		W = 440.0f;
		H = 300.0f;
		Size.SetSize(440, 300);
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
	void Glui_ColDiаlog::Init()
	{
		if (l != 0) { if (lp)  l += 2; else l -= 2; }
		if (l > 6) lp = 0;
		Gl_Print_Rectangle(X - l, Y - l, W + 2 * l, H + 2 * l, UiglColor(0, 255, 0, 100), UiglColor(0, 255, 0, 100));

		Gl_Print_Rectangle(X, Y, W, H, Color, Outline_color);
		Gl_Print_Rectangle(X, Y + H - Win_fon_H, W, Win_fon_H, Lightsteelblue, Outline_color);
		textprint.glText(X + 10, Y + H + 10 - Win_fon_H, Title);// Text_en_ru_dialog[Language][0]);

		if (act == 1)
			Gl_Print_Rectangle(X + W - Win_fon_H, Y + H - Win_fon_H, Win_fon_H, Win_fon_H, Red, Outline_color);
		else Gl_Print_Rectangle(X + W - Win_fon_H, Y + H - Win_fon_H, Win_fon_H, Win_fon_H, Silver, Outline_color);

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
			Gl_Print_Rectangle(X, Y + H - Win_fon_H * 2, 150, Win_fon_H, Silver, Outline_color);
			Gl_Print_Rectangle(X + 150, Y + H - Win_fon_H * 2, 150, Win_fon_H, Color, Outline_color);
			spector_print(X + 15, Y + 15, (H - Win_fon_H * 2), 6 * (H - Win_fon_H * 2) / 7);
			cursor(X + c_x, Y + c_y);
			brightness(X + 20 + h * 7, Y + 15, h * 6, cur2_h, Color_spector(c_x + X, c_y + Y));
		}
		else
		{
			Gl_Print_Rectangle(X, Y + H - Win_fon_H * 2, 150, Win_fon_H, Color, Outline_color);
			Gl_Print_Rectangle(X + 150, Y + H - Win_fon_H * 2, 150, Win_fon_H, Silver, Outline_color);
			D_color(X + 15, Y + 15, (H - Win_fon_H * 2) / 7);
		}

		textprint.glText(X + 10, Y + H + 10 - Win_fon_H * 2, Text_en_ru_dialog[Language][1]);
		textprint.glText(X + 170, Y + H + 10 - Win_fon_H * 2, Text_en_ru_dialog[Language][2]);

		Gl_Print_Rectangle(X + W - 85, Y + 15, 70, Win_fon_H, White, Outline_color);
		textprint.glText(X + W - 60, Y + 24, Text_en_ru_dialog[Language][3]);

		Gl_Print_Rectangle(X + W - 85, Y + 20 + Win_fon_H, 70, Win_fon_H, Color_temp, Outline_color);

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
	void Glui_ColDiаlog::Diolog(UiglColor * col, std::string _title)
	{
		Language = Glui_MainForm::Language;
		if (_title == "Defoult")
			Title = Text_en_ru_dialog[Language][0];
		else Title = _title;

		Color_result = col;
		Color_temp = *Color_result;
		Made_color = 1;
		spector = 0;
		X = Glui_MainForm::WndW / 2 - W / 2;
		Y = Glui_MainForm::WndH / 2 - H / 2;
		updatenum();
		h = (H - Win_fon_H * 2) / 7;
		//	Color_temp.setAlpha((cur3_h - 5) / (h * 6 - 10) * 255);
		cur3_h = (float(Color_temp.A) / 255.0f)*(h * 6.0f - 10.0f) + 5.0f;
	}
	UiglEvent Glui_ColDiаlog::MouseFunc(int button, int state, int ax, int ay)
	{
		is_cur_move = false;
		UiglEvent result;
		if (button == 0 && state == 0)
		{
			if(ax<X || ax>X+W || ay<Y || ay>Y+H)if (l == 0) 
			{
				l = 2;
				lp = 1;
				MessageBeep(1);
			}
			if (ax > X + W - 100)
			{
				if (num[0].MouseFunc(button, state, ax, ay).Event == uiglChanged)
				{
					Color_temp.R = stoi(num[0].Text);
				}
				if (num[1].MouseFunc(button, state, ax, ay).Event == uiglChanged)
				{
					Color_temp.G = stoi(num[1].Text);
				}
				if (num[2].MouseFunc(button, state, ax, ay).Event == uiglChanged)
				{
					Color_temp.B = stoi(num[2].Text);
				}
				if (num[3].MouseFunc(button, state, ax, ay).Event == uiglChanged)
				{
					Color_temp.A = stoi(num[3].Text);
					cur3_h = (float(Color_temp.A) / 255.0f)*(h * 6.0f - 10.0f) + 5.0f;
				}
			}
			//close
			if (ax > X + W - Win_fon_H && ax<X + W&&ay>Y + H - Win_fon_H&& ay < H + Y)
			{
				result.Name = Name;
				result.Event = uiglEraseMsg;
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
				result.Event = uiglEraseMsg;
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
	UiglEvent Glui_ColDiаlog::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (ax > X + W - Win_fon_H && ax<X + W && ay>Y + H - Win_fon_H && ay<H + Y)
			act = 1;
		else act = 0;

		for (int i = 0; i < 4; i++)
			num[i].PassiveMotionFunc(ax, ay);

		return  result;
	}
	UiglEvent Glui_ColDiаlog::MotionFunc(float ax, float ay)
	{
		UiglEvent result;

		if (is_move && moved)//window move
		{

			if (ax - mx < 0)
				ax = mx;
			if (ay - my < 0)
				ay = my;
			if (ax - mx + W > Glui_MainForm::WndW)
				ax = Glui_MainForm::WndW - W + mx;
			if (ay - my + H > Glui_MainForm::WndH)
				ay = Glui_MainForm::WndH - H + my;

			X = ax - mx;
			Y = ay - my;
			Position.SetPosition(X, Y);
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
	UiglEvent Glui_ColDiаlog::KeyboardFunc(unsigned char key, int x, int y)
	{
		UiglEvent result;
		if (key == 27)
		{
			result.Name = Name;
			result.Event = uiglEraseMsg;
		}
		if (key == 13)
		{

			Color_result[0] = Color_temp;
			result.Name = Name;
			result.Event = uiglEraseMsg;
		}
		return result;
	}
	UiglEvent Glui_ColDiаlog::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_ColDiаlog::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_ColDiаlog::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	UiglEvent Glui_ColDiаlog::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
	}
	void Glui_ColDiаlog::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		textprint.SetHDC(_hdc);
		textprint.SetHeightText(Win_fon_H - 15);
		for (int i = 0; i < 4; i++)
		{
			num[i].SetHDC(_hdc);
			num[i].Set_text_size(25);
		}
	}
	void Glui_ColDiаlog::D_color(float x, float y, float _h)
	{
		UiglColor col(Red);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				col.setColor(uiglColornum(i * 6 + j)).Init();
				Gl_Print_Rectangle(x + _h*i, y + _h*j, _h, _h, col, Outline_color, 0, 0);
			}
		}
	}
	UiglColor Glui_ColDiаlog::Color_spector(float x, float y)
	{
		glutPostRedisplay();
		BYTE _col[4];
		glReadBuffer(GL_FRONT);
		glutUseLayer(GLUT_NORMAL);
		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &_col);

		UiglColor temp(_col[0], _col[1], _col[2], 255);
		return temp;
	}
	void Glui_ColDiаlog::spector_print(float x, float y, float w, float h)
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
	void Glui_ColDiаlog::cursor(float x, float y)
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
	void Glui_ColDiаlog::brightness(float x, float y, float h, float cur_h, UiglColor col)
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
	void Glui_ColDiаlog::updatenum()
	{
		num[0].Text = std::to_string((int)Color_temp.R);
		num[1].Text = std::to_string((int)Color_temp.G);
		num[2].Text = std::to_string((int)Color_temp.B);
		num[3].Text = std::to_string((int)Color_temp.A);
	}
#pragma endregion

#pragma region Glui_Physics
	void Glui_Physics::Move()
	{
		Rotate(Angular_V);
		if (Velocity > 0)
			Velocity -= Friction_force;
		else if (Velocity != 0) Velocity += Friction_force;

		vx = std::cosf(V_angle*PI / 180)*Velocity;
		vy = std::sinf(V_angle*PI / 180)*Velocity;
		ax = std::cosf(A_angle*PI / 180)*Accelaction;
		ay = std::sinf(A_angle*PI / 180)*Accelaction;

		vx += ax;
		vy += ay;

		if (vx || vy)
			V_angle = std::atan2f(vy, vx) * 180 / PI;
		else V_angle = 0;
		Velocity = sqrtf(vx*vx + vy*vy);
		X += vx;
		Y += vy;
	}
	void Glui_Physics::Gravity()
	{
		if (Y - Grav > Ground_h)
		{
			vy = std::sinf(V_angle*PI / 180)*Velocity;
			vx = std::cosf(V_angle*PI / 180)*Velocity;

			vy -= Grav;

			if (vx || vy)
				V_angle = std::atan2f(vy, vx) * 180 / PI;
			else V_angle = 0;
			Velocity = sqrtf(vx*vx + vy*vy);
		}
		else
		{
			vy = -vy;

			if (vx || vy)
				V_angle = std::atan2f(vy, vx) * 180 / PI;
			else V_angle = 0;
			Velocity = sqrtf(vx*vx + vy*vy);

		}

		Move();
		if (Get_min_Y() < Ground_h)
			Y += Ground_h - Get_min_Y();
	}
	void Glui_Physics::Rotate(float _alpha)
	{
		X += Cmass_x - rotate_x(Cmass_x, Cmass_y, _alpha);
		Y += Cmass_y - rotate_y(Cmass_x, Cmass_y, _alpha);
		Cmass_x = rotate_x(Cmass_x, Cmass_y, _alpha);
		Cmass_y = rotate_y(Cmass_x, Cmass_y, _alpha);
		Angle += _alpha;
	}
	float Glui_Physics::Get_min_Y()
	{
		float  min = Y;
		if (Angle > 90 && Angle < 360)
			min = Y - Cmass_y;

		return min;
	}
	void Glui_Physics::Bounce1(int a)
	{
		vx = std::cosf(V_angle*PI / 180)*Velocity;
		vy = std::sinf(V_angle*PI / 180)*Velocity;
		if (a)
			vx = -vx;
		else
			vy = -vy;

		if (vx || vy)
			V_angle = std::atan2f(vy, vx) * 180 / PI;
		else V_angle = 0;
		Velocity = sqrtf(vx*vx + vy*vy);
	}
#pragma endregion

#pragma region Glui_MessageBox
	Glui_MessageBox::Glui_MessageBox()
	{

		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Size.SetSize(350.0f,150.0f);
		panel.IsHover = false;
		panel.is_move = true;
		panel.Color = Panel_color;
		panel.Set_text_size(22);
		B_ok.Set_text_size(22);
		B_no.Set_text_size(22);
		B_cancel.Set_text_size(22);
		textprint.Setfontsize(22);
		textprint.SetFont("Consolas");
		exit.Color = Red;
		panel.Size.SetSize(W - Win_fon_H, Win_fon_H);
		exit.Size.SetSize(Win_fon_H, Win_fon_H);
		B_ok.Size.SetSize(90, Win_fon_H);
		B_no.Size.SetSize(90, Win_fon_H);
		B_cancel.Size.SetSize(90, Win_fon_H);
		B_ok.Color = B_no.Color = B_cancel.Color = Button_color;
		B_ok.Name = "ok";
		B_no.Name = "no";
		B_cancel.Name = "cancel";
		Name = "msgbox";
	}
	UiglEvent Glui_MessageBox::MouseFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		if (ax > X && ax < X + W && ay > Y && ay < Y + H) 
		{
			if (exit.MouseFunc(button, state, ax, ay).Event == uiglMouseLeftDown)
			{
				Visible = 0;
				result.Event = uiglMsgCancel;
				result.Name = Name;
			}
			panel.MouseFunc(button, state, ax, ay);

			result = B_ok.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglMouseLeftDown && result.Name == "ok")
			{
				Visible = 0;
				result.Name = Name;
				result.Event = uiglMsgYes;
				return result;
			}
			result = B_no.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglMouseLeftDown && result.Name == "no")
			{
				Visible = 0;
				result.Name = Name;
				result.Event = uiglMsgNo;
				return result;
			}
			result = B_cancel.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglMouseLeftDown && result.Name == "cancel")
			{
				Visible = 0;
				result.Name = Name;
				result.Event = uiglMsgCancel;
				return result;
			}
		}else{
			if (l == 0) {
				l = 2;
				lp = 1;
				MessageBeep(1);
			}
		}
		return result;
	}
	UiglEvent Glui_MessageBox::PassiveMotionFunc(int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		panel.PassiveMotionFunc( ax, ay);
		exit.PassiveMotionFunc(ax, ay); 
		B_ok.PassiveMotionFunc(ax, ay);
		B_no.PassiveMotionFunc(ax, ay);
		B_cancel.PassiveMotionFunc(ax, ay);
		return result;
	}
	UiglEvent Glui_MessageBox::MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;

		panel.MotionFunc(ax, ay);
		Vector2f t = panel.Position.GetPosition2f();

		if (t.X < 0) t.X = 0;
		if (t.X + W > Glui_MainForm::WndW)t.X = Glui_MainForm::WndW-W;
		if (t.Y-H+Win_fon_H < 0) t.Y = H - Win_fon_H;
		if (t.Y + Win_fon_H > Glui_MainForm::WndH)t.Y = Glui_MainForm::WndH-Win_fon_H;
	
//		X = panel.Position.GetPositionX();
//		this->Position.SetPosition(t);

		panel.Position.SetPosition(t);
		t.Y -= H - Win_fon_H;
		this->Position.SetPosition(t);
		exit.Position.SetPosition(X + W - Win_fon_H, Y + H - Win_fon_H);
		B_no.Position.SetPosition(X + 20, Y + 10);
		B_ok.Position.SetPosition(X + 130, Y + 10);
		B_cancel.Position.SetPosition(X + 240, Y + 10);
		return result;
	}
	UiglEvent Glui_MessageBox::MouseWheelFunc(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		panel.MouseWheelFunc(button, state, ax, ay);
		return result;
	}
	UiglEvent Glui_MessageBox::KeyboardFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		if (key == 27) 
		{
			Visible = false;
			result.Event = uiglMsgCancel;
			result.Name = Name;
		}
		return result;
	}
	UiglEvent Glui_MessageBox::SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		return result;
	}
	UiglEvent Glui_MessageBox::KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		return result;
	}
	UiglEvent Glui_MessageBox::SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible)
			return result;
		return result;
	}
	void Glui_MessageBox::Init()
	{
		if (!Visible)
			return;
		if (l != 0) { if (lp)  l += 2; else l -= 2; }
		if (l > 6) lp = 0;
		Gl_Print_Rectangle(X-l, Y-l, W+2*l, H+2*l, UiglColor(0,255,0,100), UiglColor(0,255,0,100));
		Gl_Print_Rectangle(X, Y, W, H, Color, Outline_color);
		panel.Init();
		exit.Init();
		B_ok.Init();
		B_no.Init();
		B_cancel.Init();
		for (int i = 0; i < Base_Text.size(); i++)
		{
			textprint.glText(X + 10, Y + H - 23*(i+2)-3, Base_Text[i]);
		}
		

		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2f(X + W - 7, Y + H - 7);
		glVertex2f(X + W - Win_fon_H + 7, Y + H - Win_fon_H + 7);
		glVertex2f(X + W - 7, Y + H - Win_fon_H + 7);
		glVertex2f(X + W - Win_fon_H + 7, Y + H - 7);
		glEnd();
		glLineWidth(1);
	}
	void Glui_MessageBox::Show(std::string text, std::string title, uiglMsgBoxButtons _buttons)
	{
		Base_Text.clear();
		if (textprint.Get_text_length(text) < Size.GetSizeW())
		{
			Base_Text.push_back(text);
		}else {
			for (int i = text.size(); i > 0; i--)
			{
				if (text[i] == ' ')
				{
					if (textprint.Get_text_length(text.substr(0, i)) < Size.GetSizeW()-textprint.Get_text_length("a"))
					{
						Base_Text.push_back(text.substr(0, i));
						text = text.substr(i+1);
						i = text.size();
					}
				}else if(i == 1)Base_Text.push_back(text);
			}
		}
		if(Base_Text.size()>3)
			Size.SetSize(350.0f, 150.0f + Base_Text.size()*20);
		else Size.SetSize(350.0f, 150.0f);

		X = (Glui_MainForm::WndW - W) / 2;
		Y = (Glui_MainForm::WndH - H) / 2;
		Visible = 1;
		panel.Text = title;
		Text = text;
		panel.Position.SetPosition(X,Y+H-Win_fon_H);
		exit.Position.SetPosition(X + W - Win_fon_H, Y + H - Win_fon_H);
		B_no.Position.SetPosition(X + 20, Y + 10);
		B_ok.Position.SetPosition(X + 130, Y + 10);
		B_cancel.Position.SetPosition(X + 240, Y + 10);
		
		B_no.Text = Text_en_ru[Language][0];
		B_ok.Text = Text_en_ru[Language][1];
		B_cancel.Text = Text_en_ru[Language][2];
		switch (_buttons)
		{
		case UIGL::uiglButtonOK:			B_no.Visible = 0;	B_ok.Visible = 1;	B_cancel.Visible = 0;	break;
		case UIGL::uiglButtonNO:			B_no.Visible = 1;	B_ok.Visible = 0;	B_cancel.Visible = 0;	break;
		case UIGL::uiglButtonCancel:		B_no.Visible = 0;	B_ok.Visible = 0;	B_cancel.Visible = 1;	break;
		case UIGL::uiglButtonOKNO:			B_no.Visible = 1;	B_ok.Visible = 1;	B_cancel.Visible = 0;	break;
		case UIGL::uiglButtonOKCancel:		B_no.Visible = 0;	B_ok.Visible = 1;	B_cancel.Visible = 1;	break;
		case UIGL::uiglButtonNoCancel:		B_no.Visible = 1;	B_ok.Visible = 0;	B_cancel.Visible = 1;	break;
		case UIGL::uiglButtonOKNOCancel:	B_no.Visible = 1;	B_ok.Visible = 1;	B_cancel.Visible = 1;	break;
		}
	}
	void Glui_MessageBox::SetHDC(HDC * _hdc)
	{
		hdc = _hdc;
		panel.SetHDC(_hdc);
		B_no.SetHDC(_hdc); 
		B_ok.SetHDC(_hdc);
		B_cancel.SetHDC(_hdc);
		textprint.SetHDC(_hdc);
	}
#pragma endregion

}///end of namespace UIGL
#endif // !EASY_OPENGL_CPP_