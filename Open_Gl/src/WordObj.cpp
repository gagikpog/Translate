#include "WordObj.h"

WordObj::WordObj()
{
	Visible = false;
	textprint.setFont("Consolas");
	Position.UpdatePtr = this;
	Size.UpdatePtr = this;
	Set_text_size(Text_size);
	is_move = true;
	moved = false;
	Color = UIGL::uiglColornum::Blue;
	contextmenu.Size.setSize(75, 20);
	contextmenu.Set_text_size(15);
	contextmenu.Visible = false;
}

UIGL::UiglEvent WordObj::MouseFunc(int button, int state, int ax, int ay)
{
	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;

	UIGL::UiglEvent result;
	if (!Visible) return result;
	if (LineTranslation)
		return MouseFunc2(button, state, ax, ay);

	if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
	{

		result.Name = Name;
		if (state == 0 && button == 0)
		{
			result.Event = UIGL::uiglMouseLeftDown;
			moved = true;
			mx = ax - X;
			my = ay - Y;

			if (clock() - double_ckick < 350)
			{
				double_ckick = clock();
				result.Event = UIGL::uiglDoubleClick;
			}
			else double_ckick = clock();

			return result;
		}
		if (state == 1 && button == 0)
		{
			result.Event = UIGL::uiglMouseLeftUp;
			moved = false;
			return result;
		}
		if (state == 0 && button == 1)
		{
			result.Event = UIGL::uiglMouseCenterDown;
			return result;
		}
		if (state == 1 && button == 1)
		{
			result.Event = UIGL::uiglMouseCenterUp;
			return result;
		}
		if (state == 0 && button == 2)
		{
			result.Event = UIGL::uiglMouseRightDown;
			return result;
		}
		if (state == 1 && button == 2)
		{
			result.Event = UIGL::uiglMouseRightUp;
			return result;
		}
	}
	else {
		moved = false;
	}
	return result;
}

UIGL::UiglEvent WordObj::PassiveMotionFunc(int ax, int ay)
{
	contextmenu.PassiveMotionFunc(ax, ay);
	UIGL::UiglEvent result;
	if (!Visible) return result;
	if (!LineTranslation)
	{
		if ((ax > X) && (ax < X + W) && (ay > Y) && (ay < Y + H))
		{
			if (!Mouse_in_button)
			{
				Mouse_in_button = true;
				result.Name = Name;
				result.Event = UIGL::uiglMouseOver;
				return result;
			}
			else {
				result.Name = Name;
				result.Event = UIGL::uiglMousemove;
				return result;
			}
		}
		else {
			if (Mouse_in_button)
			{
				result.Name = Name;
				result.Event = UIGL::uiglMouseOut;
			}
			Mouse_in_button = false;
			return result;
		}
	}
	else {
		float h = (Text_size + 6);
		if ((ax > W) && (ax < h + W) && (ay > H) && (ay < h + H))
			hover2 = true;
		else hover2 = false;

		if ((ax > X) && (ax < h + X) && (ay > Y) && (ay < h + Y))
			Mouse_in_button = true;
		else Mouse_in_button = false;

	}
	return result;
}

UIGL::UiglEvent WordObj::MotionFunc(float ax, float ay)
{
	UIGL::UiglEvent result;
	if (!Visible) return result;
	if (LineTranslation)
		return MotionFunc2(ax, ay);

	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;
	if (is_move&&moved)
	{
		WordObj* _next = NULL;
		float _w = W + H / 4;
		for (_next = Next; _next != nullptr; _next = _next->Next)
		{
			if (!_next->LineTranslation)
			{
				_w = _next->Position.getPositionX() + _next->Size.getSizeW() - X + H / 4;
			}
			else {
				_w += Text_size*1.5f;
				break;
			}
		}
		//	_w += ;
		X = ax - mx;
		Y = ay - my;

		if (X + _w > UIGL::UiglMainForm::WndMinX + UIGL::UiglMainForm::WndW)
			X = UIGL::UiglMainForm::WndMinX + UIGL::UiglMainForm::WndW - _w;

		if (X < UIGL::UiglMainForm::WndMinX)
			X = UIGL::UiglMainForm::WndMinX;

		if (Y < UIGL::UiglMainForm::WndMinY)
			Y = UIGL::UiglMainForm::WndMinY;

		if (Y > UIGL::UiglMainForm::WndMinY + UIGL::UiglMainForm::WndH*0.8f - H)
			Y = UIGL::UiglMainForm::WndMinY + UIGL::UiglMainForm::WndH*0.8f - H;

		Position.setPosition(X, Y);
		UpdateStec(moved);
		double_ckick = 0;
	}
	return result;
}

UIGL::UiglEvent WordObj::MouseWheelFunc(int button, int state, int ax, int ay)
{
	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;
	UIGL::UiglEvent result;
	if (!Visible) return result;
	if ((ax > X) && (ax < X + W) && (ay>Y) && (ay < Y + H))
	{
		result.Name = Name;
		if (state == -1)
			result.Event = UIGL::uiglWheelDown;
		if (state == 1)
			result.Event = UIGL::uiglWheelUp;
	}
	return result;
}

UIGL::UiglEvent WordObj::KeyboardFunc(unsigned char key, int ax, int ay)
{
	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;
	UIGL::UiglEvent result;
	if (!Visible) return result;
	if (in_focus && key == 13)
	{
		result.Event = UIGL::uiglEnter;
		result.Name = Name;
	}
	return result;
}

UIGL::UiglEvent WordObj::SpecialFunc(int key, int ax, int ay)
{
	UIGL::UiglEvent result;
	return result;
	if (!Visible) return result;
	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;
}

UIGL::UiglEvent WordObj::KeyboardUpFunc(unsigned char key, int ax, int ay)
{
	UIGL::UiglEvent result;
	return result;
	if (!Visible) return result;
	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;
}

UIGL::UiglEvent WordObj::SpecialUpFunc(int key, int ax, int ay)
{
	UIGL::UiglEvent result;
	return result;
	if (!Visible) return result;
	float axt = UIGL::rotate_x(ax - X, ay - Y, -Angle) + X;
	ay = UIGL::rotate_y(ax - X, ay - Y, -Angle) + Y;
	ax = axt;
}

void WordObj::Init()
{
	if (!Visible) return;
	if (LineTranslation)
	{
		Init2();
		return;
	}
	float r = H / 4.0f;
	int _n = 0;
	if (Mouse_in_button)
		_n = 70;
	Color.Init(_n);

	glBegin(GL_POLYGON);
	glVertex2f(X + W / 2.0f, Y + H / 2.0f);
	glVertex2f(X + r, Y);
	for (float i = -PI / 2.0f; i < PI / 2.0f; i += 0.1f)
		glVertex2f(X + cosf(i)*r, Y + r * 2 + sinf(i)*r);
	glVertex2f(X + r, Y + H);
	glVertex2f(X + W + r, Y + H);

	for (float i = PI / 2.0f; i > -PI / 2.0f; i -= 0.1f)
		glVertex2f(X + W + cosf(i)*r, Y + r * 2 + sinf(i)*r);
	glVertex2f(X + W + r, Y);
	glVertex2f(X + W, Y);
	glVertex2f(X + r, Y);
	glEnd();

	Outline_color.Init();

	if (Back != nullptr)
	{
		glBegin(GL_POLYGON);
		for (float i = 0.0f; i < PI * 2.0f; i += 0.1f)
			glVertex2f(X + cosf(i)*r, Y + r * 2 + sinf(i)*r);
		glEnd();
	}
	if (Next != nullptr)
	{
		glBegin(GL_POLYGON);
		for (float i = 0.0f; i < PI * 2.0f; i += 0.1f)
			glVertex2f(X + W + cosf(i)*r, Y + r * 2 + sinf(i)*r);
		glEnd();
	}
	glBegin(GL_LINE_LOOP);
	glVertex2f(X + r, Y);
	for (float i = -PI / 2.0f; i < PI / 2.0f; i += 0.1f)
		glVertex2f(X + cosf(i)*r, Y + r * 2 + sinf(i)*r);
	glVertex2f(X + r, Y + H);
	glVertex2f(X + W + r, Y + H);
	for (float i = PI / 2.0f; i > -PI / 2.0f; i -= 0.1f)
		glVertex2f(X + W + cosf(i)*r, Y + r * 2.0f + sinf(i)*r);
	glVertex2f(X + W + r, Y);
	glVertex2f(X + W, Y);
	glEnd();

	textprint.glText(X + 3.0f*r, Y + H*0.2f, Text, Text_color);

}

void WordObj::SetHDC(HDC * _hdc)
{
	hdc = _hdc;
	textprint.setHDC(_hdc);
	contextmenu.SetHDC(_hdc);
}

void WordObj::Set_text_size(float _size)
{
	Text_size = _size;
	textprint.setHeightText(_size);
}

void WordObj::Update()
{
	if (LineTranslation)
		return Update2();

	if (Position.UpdatePtr != this)
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
	}
	float _length = textprint.getTextLength(Text);
	_length += Size.getSizeH();

	if (Size.getSizeH() == Text_size + 6 && _length == Size.getSizeW())
	{
		X = Position.getPositionX();
		Y = Position.getPositionY();
		H = Size.getSizeH();
		W = Size.getSizeW();
	}
	else Size.setSize(_length, Text_size + 6);
}

void WordObj::UpdateStec(bool m)
{
	if (Back != nullptr && m)
	{
		Back->Next = NULL;
		Back = NULL;
	}
	UIGL::Vector2f t;
	for (WordObj* _next = Next; _next != nullptr; _next = _next->Next)
	{
		//			if (_next->Back == NULL){cout << "error\n";	Next = NULL;break;}
		if (!_next->Back->LineTranslation)
		{
			t = _next->Back->Position.getPosition2f();
			t.X += _next->Back->Size.getSizeW();
			_next->Position.setPosition(t);
		}
		else {
			t = UIGL::Vector2f(_next->Back->Size.getSizeW(), _next->Back->Size.getSizeH());
			t.X += Text_size + 6;
			_next->Position.setPosition(t);
		}
		if (_next->LineTranslation == 1)break;
	}
}

void WordObj::Jamp()
{
	if (Y < (UIGL::Jora::WndMinY + UIGL::Jora::WndH)*0.5f - Text_size - 6)
		Position.setPosition(X, Y + Text_size + 10);
	else  Position.setPosition(X, Y - Text_size - 10);
	UpdateStec(1);
}

WordObj WordObj::operator=(WordObj operator2)
{
	//		UiglObj
	Position = operator2.Position;
	Size = operator2.Size;
	X = operator2.X;
	Y = operator2.Y;
	W = operator2.W;
	H = operator2.H;
	Angle = operator2.Angle;
	//		Points = operator2.Points;
	//		UiglIForms
	Name = operator2.Name;
	Color = operator2.Color;
	Outline_color = operator2.Outline_color;
	IsHover = operator2.IsHover;
	Visible = operator2.Visible;
	is_move = operator2.is_move;
	hdc = operator2.hdc;
	Position.UpdatePtr = this;
	Size.UpdatePtr = this;
	//		in_focus = operator2.in_focus;
	//		Mouse_in_button = operator2.Mouse_in_button;
	//		moved = operator2.moved;
	//		double_click = operator2.double_ckick;
	//		mx = operator2.mx;
	//		my = operator2.my;
	return operator2;
}

void WordObj::Reset()
{
	Next = NULL;
	Back = NULL;
	Text = "";
	LineTranslation = 0;
	Visible = 0;
}

void WordObj::Init2()
{
	if (!Visible) return;
	float h = (Text_size + 6);
	float r = h / 4.0f;
	int _n = 0;
	if (Mouse_in_button)
		_n = 70;
	Color.Init(_n);

	glBegin(GL_POLYGON);
	glVertex2f(X + h / 2, Y + h / 2);
	glVertex2f(X + r, Y);
	for (float i = -PI / 2.0f; i < PI / 2.0f; i += 0.1)
		glVertex2f(X + cosf(i)*r, Y + r * 2 + sinf(i)*r);
	glVertex2f(X + r, Y + h);
	glVertex2f(X + h, Y + h);
	glVertex2f(X + h, Y);
	glVertex2f(X + r, Y);
	glEnd();

	if (!hover2)
		_n = 0;
	else _n = 70;
	Color.Init(_n);

	glBegin(GL_POLYGON);
	glVertex2f(W + h / 2, H + h / 2);
	glVertex2f(W, H + h);

	glVertex2f(W + h + r, H + h);
	for (float i = PI / 2.0f; i > -PI / 2.0f; i -= 0.1f)
		glVertex2f(W + h + cosf(i)*r, H + r * 2.0f + sinf(i)*r);
	glVertex2f(h + W + r, H);
	glVertex2f(h + W, H);
	glVertex2f(W, H);
	glVertex2f(W, H + h);

	glEnd();

	Outline_color.Init();

	if (Back != nullptr)
	{
		glBegin(GL_POLYGON);
		for (float i = 0.0f; i < PI * 2.0f; i += 0.1f)
			glVertex2f(X + cosf(i)*r, Y + r * 2.0f + sinf(i)*r);
		glEnd();
	}
	if (Next != nullptr)
	{
		glBegin(GL_POLYGON);
		for (float i = 0.0f; i < PI * 2.0f; i += 0.1f)
			glVertex2f(W + h + cosf(i)*r, H + r * 2.0f + sinf(i)*r);
		glEnd();
	}

	glBegin(GL_LINE_LOOP);

	glVertex2f(X + r, Y);
	for (float i = -PI / 2.0f; i < PI / 2.0f; i += 0.1f)
		glVertex2f(X + cosf(i)*r, Y + r * 2 + sinf(i)*r);
	glVertex2f(X + r, Y + h);
	glVertex2f(X + h, Y + h);
	glVertex2f(X + h, Y);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(W, H + h);
	glVertex2f(W + h + r, H + h);
	for (float i = PI / 2.0f; i > -PI / 2.0f; i -= 0.1f)
		glVertex2f(W + h + cosf(i)*r, H + r * 2 + sinf(i)*r);
	glVertex2f(h + W + r, H);
	glVertex2f(h + W, H);
	glVertex2f(W, H);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glVertex2f(X + h, Y + h / 2.0f);
	glVertex2f(X + h + h / 2.0f, Y + h / 2.0f);

	if (W < X + h*2.0f)
	{
		float _up = 0;
		if (std::abs(H - Y) < h*1.3f)
			_up = h*1.3f;
		if (Y > UIGL::Jora::WndH / 2)
			_up = -_up;
		glVertex2f(X + h + h / 2, (Y + h + H) / 2.0f + _up);
		glVertex2f(W - h / 2, (Y + h + H) / 2.0f + _up);
	}
	else glVertex2f(X + h + h / 2, H + h / 2);

	glVertex2f(W - h / 2, H + h / 2);
	glVertex2f(W, H + h / 2);
	glEnd();
	glLineWidth(1);

	contextmenu.Init();
	return;

	textprint.glText(X + 3.0f*r, Y + H*0.2f, Text, Text_color);
}

UIGL::UiglEvent WordObj::MouseFunc2(int button, int state, int ax, int ay)
{
	UIGL::UiglEvent result;
	if (!Visible) return result;
	float h = (Text_size + 6);

	result = contextmenu.MouseFunc(button, state, ax, ay);
	if (result.Event == UIGL::uiglEvents::uiglMouseLeftDown)
	{
		if (Next != nullptr)
			Next->Back = NULL;
		if (Back != nullptr)
			Back->Next = NULL;
		Back = Next = NULL;
		contextmenu.Visible = false;
		Visible = false;
		return result;
	}

	if ((ax > X) && (ax < X + h) && (ay>Y) && (ay < Y + h))
	{
		result.Name = Name;
		if (state == 0 && button == 0)
		{
			contextmenu.Visible = false;
			_moved = 0;
			result.Event = UIGL::uiglMouseLeftDown;
			moved = true;
			mx = ax - X;
			my = ay - Y;

			if (clock() - double_ckick < 350)
			{
				double_ckick = clock();
				result.Event = UIGL::uiglDoubleClick;
			}
			else double_ckick = clock();

			return result;
		}
		if (state == 1 && button == 0)
		{
			contextmenu.Visible = false;
			result.Event = UIGL::uiglMouseLeftUp;
			moved = false;
			return result;
		}
		if (state == 0 && button == 1)
		{
			contextmenu.Visible = false;
			result.Event = UIGL::uiglMouseCenterDown;
			return result;
		}
		if (state == 1 && button == 1)
		{
			contextmenu.Visible = false;
			result.Event = UIGL::uiglMouseCenterUp;
			return result;
		}
		if (state == 0 && button == 2)
		{
			contextmenu.Visible = true;
			float ax1 = ax;
			if (ax1 + 75 > UIGL::Jora::WndW)
				ax1 = UIGL::Jora::WndW - 80;
			contextmenu.Position.setPosition(ax1, ay);
			if (UIGL::Jora::Language != UIGL::uiglLanguageEN)contextmenu.Text = "Delete";
			else contextmenu.Text = "Удалить";
			contextmenu.Color = Color;
			contextmenu.Outline_color = Outline_color;
			contextmenu.Text_color = Text_color;
			result.Event = UIGL::uiglMouseRightDown;
			return result;
		}
		if (state == 1 && button == 2)
		{
			result.Event = UIGL::uiglMouseRightUp;
			return result;
		}
	}
	else {
		if ((ax > W) && (ax < W + h) && (ay > H) && (ay < H + h))
		{
			if (state == 0 && button == 0)
			{
				contextmenu.Visible = false;
				result.Name = Name;
				_moved = 1;
				result.Event = UIGL::uiglMouseLeftDown;
				moved = true;
				mx = ax - W;
				my = ay - H;

				if (clock() - double_ckick < 350)
				{
					double_ckick = clock();
					result.Event = UIGL::uiglDoubleClick;
				}
				else double_ckick = clock();

				return result;
			}
			if (state == 1 && button == 0)
			{
				contextmenu.Visible = false;
				result.Event = UIGL::uiglMouseLeftUp;
				moved = false;
				return result;
			}
			if (state == 0 && button == 1)
			{
				contextmenu.Visible = false;
				result.Event = UIGL::uiglMouseCenterDown;
				return result;
			}
			if (state == 1 && button == 1)
			{
				contextmenu.Visible = false;
				result.Event = UIGL::uiglMouseCenterUp;
				return result;
			}
			if (state == 0 && button == 2)
			{
				contextmenu.Visible = true;
				float ax1 = ax;
				if (ax1 + 75 > UIGL::Jora::WndW)
					ax1 = UIGL::Jora::WndW - 80;
				contextmenu.Position.setPosition(ax1, ay);
				if (UIGL::Jora::Language != UIGL::uiglLanguageEN)contextmenu.Text = "Delete";
				else contextmenu.Text = "Удалить";
				contextmenu.Color = Color;
				contextmenu.Outline_color = Outline_color;
				contextmenu.Text_color = Text_color;
				result.Event = UIGL::uiglMouseRightDown;
				return result;
			}
			if (state == 1 && button == 2)
			{
				result.Event = UIGL::uiglMouseRightUp;
				return result;
			}
		}
		moved = false;
	}
	contextmenu.Visible = false;
	return result;
}

UIGL::UiglEvent WordObj::MotionFunc2(float ax, float ay)
{
	UIGL::UiglEvent result;
	if (!Visible) return result;
	if (is_move&&moved)
	{
		float h = (Text_size + 6);
		if (_moved == 0)
		{
			float _w = h*1.5f;
			X = ax - mx;
			Y = ay - my;

			if (X + _w > UIGL::UiglMainForm::WndMinX + UIGL::UiglMainForm::WndW)
				X = UIGL::UiglMainForm::WndMinX + UIGL::UiglMainForm::WndW - _w;

			if (X < UIGL::UiglMainForm::WndMinX)
				X = UIGL::UiglMainForm::WndMinX;

			if (Y < UIGL::UiglMainForm::WndMinY)
				Y = UIGL::UiglMainForm::WndMinY;

			if (Y > UIGL::UiglMainForm::WndMinY + UIGL::UiglMainForm::WndH*0.8f - h)
				Y = UIGL::UiglMainForm::WndMinY + UIGL::UiglMainForm::WndH*0.8f - h;

			Position.setPosition(X, Y);
			UpdateStec(moved);
		}
		else {
			WordObj* _next = NULL;
			float _w = h*1.5f - h / 4.0f;
			for (_next = Next; _next != nullptr; _next = _next->Next)
			{
				if (!_next->LineTranslation)
				{
					_w = _next->Position.getPositionX() + _next->Size.getSizeW() - W + h / 4.0f;
				}
				else {
					_w += Text_size*1.5f;
					break;
				}
			}
			W = ax - mx;
			H = ay - my;

			if (W + _w > UIGL::UiglMainForm::WndMinX + UIGL::UiglMainForm::WndW)
				W = UIGL::UiglMainForm::WndMinX + UIGL::UiglMainForm::WndW - _w;

			if (W < UIGL::UiglMainForm::WndMinX + h / 2)
				W = UIGL::UiglMainForm::WndMinX + h / 2;

			if (H < UIGL::UiglMainForm::WndMinY)
				H = UIGL::UiglMainForm::WndMinY;

			if (H > UIGL::UiglMainForm::WndMinY + UIGL::UiglMainForm::WndH*0.8f - h)
				H = UIGL::UiglMainForm::WndMinY + UIGL::UiglMainForm::WndH*0.8f - h;

			Size.setSize(W, H);
			UpdateStec(0);
		}
		double_ckick = 0;
	}
	return result;
}

void WordObj::Update2()
{
	if (Position.UpdatePtr != this)
	{
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
	}
	X = Position.getPositionX();
	Y = Position.getPositionY();
	H = Size.getSizeH();
	W = Size.getSizeW();
}
