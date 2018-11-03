#include "lib/freeuigl.h"
#include "resource.h"

using namespace std;
using namespace UIGL;

///////////////////////////////////////////////////structures and classes
struct Mytext
{
	string en;
	string ru;
};
struct Sentence
{
	Sentence() {}
	void SetText(std::string _text)
	{
		const int _N_ = 30;
		bool b = 1;
		Text = "";
		for (int i = 0; i < _text.length(); i++)
		{
			if (_text[i] == ' ')
			{
				if (b == 1)
					continue;
				b = 1;
			}
			else b = 0;
			Text.push_back(_text[i]+_N_);
		}
		if (Text.back() == ' '+_N_)
			Text.pop_back();
	}
	bool AddText(std::string _txt)
	{
		const int _N_ = 30;
		std::string _text;
		for (int i = 0; i < Text.size(); i++)
			_text += (char)Text[i] - _N_;
		
		bool b = 1;
		std::string _t;
		for (int i = 0; i < _txt.length(); i++)
		{
			if (_txt[i] == ' ')
			{
				if (b == 1)
					continue;
				b = 1;
			}
			else b = 0;
			_t.push_back(_txt[i]);
		}
		if (_t.back() == ' ')
			_t.pop_back();
		
		vector<pair<std::string,int>> T1;
		vector<pair<std::string,int>> T2;
		pair<std::string, int> _tmp;
		int _begin = 0;
		for (int i = 0; i < _text.size(); i++)
		{
			if (_text[i] == ' ' || _text.size() == i + 1)
			{
				_tmp.first = _text.substr(_begin, i - _begin);
				_tmp.second = T1.size();
				T1.push_back(_tmp);
				_begin = i + 1;
			}
		}
		_begin = 0;
		for (int i = 0; i < _t.size(); i++)
		{
			if (_t[i] == ' ' || _t.size() == i + 1)
			{
				_tmp.first = _t.substr(_begin, i - _begin);
				_tmp.second = T2.size();
				T2.push_back(_tmp);
				_begin = i + 1;
			}
		}
		
		if (T1.size() != T2.size())
			return 0;
		std::sort(T1.begin(), T1.end(), [](pair<std::string, int> a, pair<std::string, int> b) {return a.first < b.first; });
		std::sort(T2.begin(), T2.end(), [](pair<std::string, int> a, pair<std::string, int> b) {return a.first < b.first; });

		for (int i = 0; i < T1.size(); i++)
		{
			if (T1[i].first != T2[i].first)
				return 0;
		}

		arr.push_back(vector<char>());
		arr.back().insert(arr.back().end(), T1.size(),0);
		for (int j = 0; j < T1.size(); j++)
			arr.back()[T1[j].second] = T2[j].second;
		return 1;
	}
	std::string GetText()
	{
		const int _N_ = 30;
		std::string _text;
		for (int i = 0; i < Text.size(); i++)
		{
			_text += (char)Text[i] - _N_;
		}
		return _text;
	}
	int GetSize()
	{
		return arr.size() + 1;
	}
	void Clear()
	{
		Text = "";
		for (int i = 0; i < arr.size(); i++)
			arr[i].clear();
		arr.clear();
	}
	bool Test(std::string _txt)
	{
		const int _N_ = 30;
		std::string _text;
		for (int i = 0; i < Text.size(); i++)
			_text += (char)Text[i] - _N_;

		bool b = 1;
		std::string _t;
		for (int i = 0; i < _txt.length(); i++)
		{
			if (_txt[i] == ' ')
			{
				if (b == 1)
					continue;
				b = 1;
			}
			else b = 0;
			_t.push_back(_txt[i]);
		}
		if (_t.back() == ' ')
			_t.pop_back();

		if (_t == _text)
		{
			Rating++;
			return true;
		}

		vector<pair<std::string, int>> T1;
		vector<pair<std::string, int>> T2;
		pair<std::string, int> _tmp;
		int _begin = 0;
		for (int i = 0; i < _text.size(); i++)
		{
			if (_text[i] == ' ' || _text.size() == i + 1)
			{
				_tmp.first = _text.substr(_begin, i - _begin);
				_tmp.second = T1.size();
				T1.push_back(_tmp);
				_begin = i + 1;
			}
		}
		_begin = 0;
		for (int i = 0; i < _t.size(); i++)
		{
			if (_t[i] == ' ' || _t.size() == i + 1)
			{
				_tmp.first = _t.substr(_begin, i - _begin);
				_tmp.second = T2.size();
				T2.push_back(_tmp);
				_begin = i + 1;
			}
		}

		if (T1.size() != T2.size())
		{
			Rating--;
			return 0;
		}
		std::sort(T1.begin(), T1.end(), [](pair<std::string, int> a, pair<std::string, int> b) {return a.first < b.first; });
		std::sort(T2.begin(), T2.end(), [](pair<std::string, int> a, pair<std::string, int> b) {return a.first < b.first; });

		for (int i = 0; i < T1.size(); i++)
		{
			if (T1[i].first != T2[i].first)
			{
				Rating--;
				return 0;
			}
		}

		vector<char> arr1(T1.size());
		for (int j = 0; j < T1.size(); j++)
			arr1[T1[j].second] = T2[j].second;

		b = 1;
		for (int i = 0; i < arr.size(); i++)
		{
			b = 1;
			for (int j = 0; j < arr[i].size(); j++)
			{
				if (arr[i][j] != arr1[j])
				{
					break;
					b = 0;
				}
			}
			if (b) { Rating++; return true; }
		}
		Rating--;
		return 0;
	}
	int Rating = 1000;
	std::string Text = "";
	vector<vector<char>> arr{};
	bool use = 0;
};

class textbox :public Glui_Textbox
{
public:
	textbox() {}
	~textbox() {}
	void Init()
	{

		float align_h = 0, align_w = 0;
		switch (Text_align)
		{
		case UIGL::uiglTopLeft:
		case UIGL::uiglTopCenter:
		case UIGL::uiglTopRight:
			align_h = H + 10;
			break;
		case UIGL::uiglMiddleLeft:
		case UIGL::uiglMiddleCenter:
		case UIGL::uiglMiddleRight:
			align_h = H*0.1f;
			break;
		case UIGL::uiglBottomLeft:
		case UIGL::uiglBottomCenter:
		case UIGL::uiglBottomRight:
			align_h = -Text_size - 5;
			break;
		}
		switch (Text_align)
		{
		case UIGL::uiglTopLeft:
		case UIGL::uiglMiddleLeft:
		case UIGL::uiglBottomLeft:
			align_w = -10;
			break;
		case UIGL::uiglMiddleCenter:
		case UIGL::uiglTopCenter:
		case UIGL::uiglBottomCenter:
			align_w = 5;
			break;
		case UIGL::uiglBottomRight:
		case UIGL::uiglTopRight:
		case UIGL::uiglMiddleRight:
			align_w = W + 10;
			break;
		}

		Glui_Textbox::Init();
		Glui_Textbox::textprint.glText(X + align_w, Y + align_h, Title, Text_color);
	}

	string Title;
	uiglAlignments Text_align = uiglAlignments::uiglMiddleRight;
private:
};

class numbox :public Glui_Numericupdown
{
public:
	numbox() {}
	~numbox() {}
	void Init()
	{
		float align_h = 0, align_w = 0;
		switch (Text_align)
		{
		case UIGL::uiglTopLeft:
		case UIGL::uiglTopCenter:
		case UIGL::uiglTopRight:
			align_h = H + 10;
			break;
		case UIGL::uiglMiddleLeft:
		case UIGL::uiglMiddleCenter:
		case UIGL::uiglMiddleRight:
			align_h = H*0.1f;
			break;
		case UIGL::uiglBottomLeft:
		case UIGL::uiglBottomCenter:
		case UIGL::uiglBottomRight:
			align_h = -Text_size - 5;
			break;
		}
		switch (Text_align)
		{
		case UIGL::uiglTopLeft:
		case UIGL::uiglMiddleLeft:
		case UIGL::uiglBottomLeft:
			align_w = -10;
			break;
		case UIGL::uiglMiddleCenter:
		case UIGL::uiglTopCenter:
		case UIGL::uiglBottomCenter:
			align_w = 5;
			break;
		case UIGL::uiglBottomRight:
		case UIGL::uiglTopRight:
		case UIGL::uiglMiddleRight:
			align_w = W + 10;
			break;
		}
		Glui_Numericupdown::Init();
		Glui_Textbox::textprint.glText(X + align_w, Y + align_h, Title, Text_color);
	}

	string Title;
	uiglAlignments Text_align = uiglAlignments::uiglMiddleRight;
private:
};

class listbox :public Glui_Listbox
{
public:
	listbox() {}
	~listbox() {}
	void Init()
	{
		int _count = ((H - 10.0f) / Text_size);
		Glui_Listbox::Init();
		for (int i = 0; i < Items1.size() - item_up_num && i < _count; i++)
		{
			textprint.glText(X + W / 2 + 5, Y + H - 2 - (i + 1)*Text_size, Items1[i + item_up_num], Text_color);
		}
		Outline_color.Init();
		glBegin(GL_LINES);
		glVertex2f(Position.getPositionX() + Size.getSizeW() / 2.0f, Position.getPositionY());
		glVertex2f(Position.getPositionX() + Size.getSizeW() / 2.0f, Position.getPositionY() + Size.getSizeH());
		glEnd();

	}
	vector<string>Items1;
private:

};

class WordObj :public Glui_IForms
{
public:
	WordObj()
	{
		Visible = false;
		textprint.setFont("Consolas");
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
		Set_text_size(Text_size);
		is_move = true;
		moved = false;
		Color = uiglColornum::Blue;
		contextmenu.Size.setSize(75, 20);
		contextmenu.Set_text_size(15);
		contextmenu.Visible = false;
	}
	~WordObj() {}
	UiglEvent MouseFunc(int button, int state, int ax, int ay)
	{ 
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;

		UiglEvent result;
		if (!Visible) return result;
		if (LineTranslation)
			return MouseFunc2(button, state, ax, ay);
		
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
		}else {
			moved = false;
		}
		return result;
	}
	UiglEvent PassiveMotionFunc(int ax, int ay)
	{
		contextmenu.PassiveMotionFunc(ax, ay);
		UiglEvent result;
		if (!Visible) return result;
		if (!LineTranslation)
		{
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
			else {
				if (Mouse_in_button)
				{
					result.Name = Name;
					result.Event = uiglMouseOut;
				}
				Mouse_in_button = false;
				return result;
			}
		}else {
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
	UiglEvent MotionFunc(float ax, float ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		if (LineTranslation)
			return MotionFunc2(ax, ay);

		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
		if (is_move&&moved)
		{
			WordObj* _next = NULL;
			float _w = W + H / 4;
			for (_next = Next; _next != nullptr; _next = _next->Next)
			{
				if (!_next->LineTranslation)
				{
					_w = _next->Position.getPositionX() + _next->Size.getSizeW() - X+H / 4;
				}
				else {
					_w += Text_size*1.5f;
					break;
				}
			}
		//	_w += ;
			X = ax - mx;
			Y = ay - my;

			if (X + _w > Glui_MainForm::WndMinX + Glui_MainForm::WndW)
				X = Glui_MainForm::WndMinX + Glui_MainForm::WndW - _w;

			if (X < Glui_MainForm::WndMinX)
				X = Glui_MainForm::WndMinX;

			if (Y < Glui_MainForm::WndMinY)
				Y = Glui_MainForm::WndMinY;

			if (Y > Glui_MainForm::WndMinY + Glui_MainForm::WndH*0.8f-H)
				Y = Glui_MainForm::WndMinY + Glui_MainForm::WndH*0.8f-H;

			Position.setPosition(X, Y);
			UpdateStec(moved);
			double_ckick = 0;
		}
		return result;
	}
	UiglEvent MouseWheelFunc(int button, int state, int ax, int ay)
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
	UiglEvent KeyboardFunc(unsigned char key, int ax, int ay)
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
	UiglEvent SpecialFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	UiglEvent SpecialUpFunc(int key, int ax, int ay)
	{
		UiglEvent result;
		return result;
		if (!Visible) return result;
		float axt = rotate_x(ax - X, ay - Y, -Angle) + X;
		ay = rotate_y(ax - X, ay - Y, -Angle) + Y;
		ax = axt;
	}
	void Init()
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

		textprint.glText(X + 3.0f*r, Y + H*0.2f , Text, Text_color);

	}
	void SetHDC(HDC* _hdc)
	{
		hdc = _hdc;
		textprint.setHDC(_hdc);
		contextmenu.SetHDC(_hdc);
	}
	void Set_text_size(float _size)
	{
		Text_size = _size;
		textprint.setHeightText(_size);
	}
	void Update()
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
			
		if (Size.getSizeH() == Text_size+6 && _length == Size.getSizeW())
		{
			X = Position.getPositionX();
			Y = Position.getPositionY();
			H = Size.getSizeH();
			W = Size.getSizeW();
		}
		else Size.setSize(_length, Text_size+6);
	}
	void UpdateStec(bool m = 0)
	{
		if (Back != nullptr && m)
		{
			Back->Next = NULL;
			Back = NULL;
		}
		Vector2f t;
		for (WordObj* _next = Next; _next != nullptr ; _next = _next->Next)
		{
//			if (_next->Back == NULL){cout << "error\n";	Next = NULL;break;}
			if (!_next->Back->LineTranslation)
			{
				t = _next->Back->Position.getPosition2f();
				t.X += _next->Back->Size.getSizeW();
				_next->Position.setPosition(t);
			}else {
				t = Vector2f( _next->Back->Size.getSizeW(), _next->Back->Size.getSizeH());
				t.X += Text_size + 6;
				_next->Position.setPosition(t);
			}
			if (_next->LineTranslation == 1)break;
		}
	}
	void Jamp()
	{
		if (Y < (Jora::WndMinY + Jora::WndH)*0.5f - Text_size-6)
			Position.setPosition(X, Y + Text_size + 10);
		else  Position.setPosition(X, Y - Text_size - 10);
		UpdateStec(1);
	}
	WordObj operator=(WordObj operator2)
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
//		Glui_IForms
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
	}
	void Reset()
	{
		Next = NULL;
		Back = NULL;
		Text = "";
		LineTranslation = 0;
		Visible = 0;
	}
	UiglColor Text_color;
	std::string Text;
	WordObj* Next = NULL;
	WordObj* Back = NULL;
	bool LineTranslation = 0;
private:
	Glui_Rectangle contextmenu;
	void Init2()
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
			if (Y > Jora::WndH / 2)
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
	UiglEvent MouseFunc2(int button, int state, int ax, int ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		float h = (Text_size + 6);
		
		result = contextmenu.MouseFunc(button, state, ax, ay);
			if (result.Event == uiglEvents::uiglMouseLeftDown)
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
				contextmenu.Visible = false;
				result.Event = uiglMouseLeftUp;
				moved = false;
				return result;
			}
			if (state == 0 && button == 1)
			{
				contextmenu.Visible = false;
				result.Event = uiglMouseCenterDown;
				return result;
			}
			if (state == 1 && button == 1)
			{
				contextmenu.Visible = false;
				result.Event = uiglMouseCenterUp;
				return result;
			}
			if (state == 0 && button == 2)
			{
				contextmenu.Visible = true;
				float ax1 = ax;
				if (ax1 + 75 > Jora::WndW)
					ax1 = Jora::WndW - 80;
				contextmenu.Position.setPosition(ax1, ay);
				if (Jora::Language != uiglLanguageEN)contextmenu.Text = "Delete";
				else contextmenu.Text = "Удалить";
				contextmenu.Color = Color;
				contextmenu.Outline_color = Outline_color;
				contextmenu.Text_color = Text_color;
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
			if ((ax > W) && (ax < W + h) && (ay > H) && (ay < H + h))
			{
				if (state == 0 && button == 0)
				{
					contextmenu.Visible = false;
					result.Name = Name;
					_moved = 1;
					result.Event = uiglMouseLeftDown;
					moved = true;
					mx = ax - W;
					my = ay - H;

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
					contextmenu.Visible = false;
					result.Event = uiglMouseLeftUp;
					moved = false;
					return result;
				}
				if (state == 0 && button == 1)
				{
					contextmenu.Visible = false;
					result.Event = uiglMouseCenterDown;
					return result;
				}
				if (state == 1 && button == 1)
				{
					contextmenu.Visible = false;
					result.Event = uiglMouseCenterUp;
					return result;
				}
				if (state == 0 && button == 2)
				{
					contextmenu.Visible = true;
					float ax1 = ax;
					if (ax1 + 75 > Jora::WndW)
						ax1 = Jora::WndW - 80;
					contextmenu.Position.setPosition(ax1, ay);
					if (Jora::Language != uiglLanguageEN)contextmenu.Text = "Delete";
					else contextmenu.Text = "Удалить";
					contextmenu.Color = Color;
					contextmenu.Outline_color = Outline_color;
					contextmenu.Text_color = Text_color;
					result.Event = uiglMouseRightDown;
					return result;
				}	
				if (state == 1 && button == 2)
				{
					result.Event = uiglMouseRightUp;
					return result;
				}
			}
			moved = false;
		}
		contextmenu.Visible = false;
		return result;
	}
	UiglEvent MotionFunc2(float ax, float ay)
	{
		UiglEvent result;
		if (!Visible) return result;
		if (is_move&&moved)
		{
			float h = (Text_size + 6);
			if (_moved == 0)
			{
				float _w = h*1.5f;
				X = ax - mx;
				Y = ay - my;

				if (X + _w > Glui_MainForm::WndMinX + Glui_MainForm::WndW)
					X = Glui_MainForm::WndMinX + Glui_MainForm::WndW - _w;

				if (X < Glui_MainForm::WndMinX)
					X = Glui_MainForm::WndMinX;

				if (Y < Glui_MainForm::WndMinY)
					Y = Glui_MainForm::WndMinY;

				if (Y > Glui_MainForm::WndMinY + Glui_MainForm::WndH*0.8f - h)
					Y = Glui_MainForm::WndMinY + Glui_MainForm::WndH*0.8f - h;

				Position.setPosition(X, Y);
				UpdateStec(moved);
			}
			else {
				WordObj* _next = NULL;
				float _w = h*1.5f-h/4.0f;
				for (_next = Next; _next != nullptr; _next = _next->Next)
				{
					if (!_next->LineTranslation)
					{
						_w = _next->Position.getPositionX() + _next->Size.getSizeW() - W+h/4.0f;
					}
					else {
						_w += Text_size*1.5f;
						break;
					}
				}
				W = ax - mx;
				H = ay - my;

				if (W + _w > Glui_MainForm::WndMinX + Glui_MainForm::WndW)
					W = Glui_MainForm::WndMinX + Glui_MainForm::WndW - _w;

				if (W < Glui_MainForm::WndMinX + h / 2)
					W = Glui_MainForm::WndMinX + h / 2;

				if (H < Glui_MainForm::WndMinY)
					H = Glui_MainForm::WndMinY;

				if (H > Glui_MainForm::WndMinY + Glui_MainForm::WndH*0.8f - h)
					H = Glui_MainForm::WndMinY + Glui_MainForm::WndH*0.8f - h;

				Size.setSize(W, H);
				UpdateStec(0);
			}
			double_ckick = 0;
		}
		return result;
	}
	void Update2()
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
	int _moved = 0;
	bool hover2 = 0;
protected:
	float Text_size = 30;
	UiglText textprint;
private:
};

class Panel:public Glui_IForms
{
public:
	Panel() 
	{
		is_move = 0;
		IsHover = 0;
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
	}
	~Panel() {}
	UiglEvent MouseFunc(int button, int state, int ax, int ay) { return UiglEvent(); }
	UiglEvent PassiveMotionFunc(int ax, int ay) { return UiglEvent(); }
	UiglEvent MotionFunc(float ax, float ay) { return UiglEvent(); }
	UiglEvent MouseWheelFunc(int button, int state, int ax, int ay) { return UiglEvent(); }
	UiglEvent KeyboardFunc(unsigned char key, int ax, int ay) { return UiglEvent(); }
	UiglEvent SpecialFunc(int key, int ax, int ay) { return UiglEvent(); }
	UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay) { return UiglEvent(); }
	UiglEvent SpecialUpFunc(int key, int ax, int ay) { return UiglEvent(); }
	void Init() 
	{
		drawRectangle(X, Y, W, H, Color, Outline_color);
	}
};

//////////////////////////////////////////////////

int word_count(20), ans_wrong(0), ans_correct(0), sentence_selection = 0;
int state_wnd(2);
bool Translate_to(0);

std::string  MakeSentencr();
void WordsPosUpdate(int n);
void BildWords(std::string text);
void Bild_Window();
void Wnd_init();
bool SaveSentence(const vector<Sentence>& _sentence, std::string file_name);
bool OpenSentence(vector<Sentence>& _sentence, std::string file_name);
bool cut_data(vector<string_int*>& sub_mas, vector<string_int>& mas, int sub_mas_size);
bool Find_in_file(std::string file_name, std::string Text_en, std::string &Text_ru);
bool open(string file_name, vector<string_int>& mas);
bool save(string file_name, vector<string_int>& mas);
bool Open_dataen(string file_name1, vector<Mytext>& mas);
string translate(string text_en);
void resetlist();
void list_updat();
bool Add_word();

const string Text_en_ru[2][13]{ 
"Проверка","Далее","    Меню",
"Число отображаемых слов",
"     Фон",
"     Текст",
"     Линия",
"     Кнопки",
"     Выбранный",
"EN",
"--",
"Ответы",
"Ошибки",

"Checkup","Next","    Menu",
"The number of displayed words",
"     Background",
"     Text",
"     Line",
"     Buttons",
"     Selected",
"РУ",
"--",
"Correct",
"Wrong"
};
const string Head_en_ru[2][8]{	"     Настрoйки",	"   Переводчик",	"    Тренировка",	"    В разработке" ,	"Английский",	"Русский","Добавить в избранные"," Удалить",
								"        Settings",	"       Translate",	"       Training",	"   In developing",	"English",		"Russian","Add to favorites"," Remove"};
const string Text_Form5[2][2]{	 "Перевод строки",""
								,"Line translation","" };
const string MsgString[2][8]{	"Справка",	"Это слово уже существует",	"Заполните поля"	,"Слово не найдено"	,"Вы действительно хотите удалить это слово?",	"","","",
								"Reference","This word already exists",	"Fill in the fields","Word not found"	,"Are you sure you want to delete this word?",	"","","" };

//menu setings
UiglColor text_col = Black;
UiglColor backgr_col = Green;
UiglColor line_col = Black;
UiglColor button_col = White;
UiglColor select_col = White;
UiglColor Alpha_anim(0,255,0,0);
///menu setings

vector<Sentence>ArrSentence;
vector<string_int> My_data;
vector<string_int*> My_sub_data;
vector<WordObj> words(30);

Glui_Forms FormTraining,FormSetting,FormMain,FormTranslate,Form5;
listbox list_l;
Glui_Listbox list1,list2;
textbox inp2,out2;
Glui_Config conf("settings.conf");
numbox inp;
Glui_Picture swap1;
Panel panel1;

Glui_Rectangle butt,butt1,butt2,butt3,favor,cutword,AddLineTranslation, TestTranslation;
Glui_Rectangle sett_col[7];
Glui_Rectangle Head_menu[4];

void Display()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glClear(GL_COLOR_BUFFER_BIT);
	Jora::Display();
	drawRectangle(Jora::WndMinX, Jora::WndMinY, Jora::WndW, Jora::WndH, Alpha_anim, Alpha_anim);
	glutSwapBuffers();
}

void Reshop(int aw, int ah)
{
	glViewport(0, 0, aw, ah);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Jora::WndW, 0, Jora::WndH);
	Bild_Window();
	glMatrixMode(GL_MODELVIEW);
}

void Pos_Func(int ax, int ay)
{
	conf.Set_count("WndX", ax);
	conf.Set_count("WndY", ay);
}

void timer(int)
{
	glutPostRedisplay();//обновляет экран
	glutTimerFunc(50, timer, 0);
}

void Animation1(int p)
{
	if (p <= 240 && p%2 == 0)
		p += 10;
	if (p >= 240) {
		p++;
		Bild_Window();
	}
	if (p > 0 && p %2 == 1)
		p -= 10;
	if (p > 0 && p < 255) {
		Alpha_anim = backgr_col;
		Alpha_anim.setAlpha(p);
	}
	glutPostRedisplay();
	if(p>0)
		glutTimerFunc(10, Animation1, p);
}

void Wnd_proc(uiglEvents ev,string name)
{
	cout << "Wnd_proc1  " << ev << "  " << name << endl;
	
	if (ev == uiglEvents::uiglMsgYes&&name == "del")
	{
		for (int i = 0; i < My_data.size(); i++)
		{
			if (list_l.Get_Selected_text() == My_data[i].Text)
			{
				My_data.erase(My_data.begin() + i);
			}
		}
		list_updat();
		save("selfnew.txt", My_data);
	}


	if (name == "enter" && ev == uiglMouseLeftUp||((name=="list1"||name=="list2") && (ev == uiglDoubleClick || ev == uiglEnter)))
	{
		if (list1.Selected >= 0 && list1.Selected < My_sub_data.size())
		{
			if (translate(list1.Get_Selected_text()) == list2.Get_Selected_text())
			{
				My_sub_data[list1.Selected]->Count++;
				My_sub_data.erase(My_sub_data.begin() + list1.Selected);
				list1.Items.clear();
				list2.Items.clear();
				list1.Selected = 0;
				list2.Selected = 0;
				ans_correct++;
				for (int i = 0; i < My_sub_data.size(); i++)
				{
					list1.Items.push_back(My_sub_data[i]->Text);
					list2.Items.push_back(My_sub_data[i]->Text1);
				}
				sort(list2.Items.begin(), list2.Items.end());
			}else 
			{
				ans_wrong++;
				My_sub_data[list1.Selected]->Count--;
			}
			butt3.Text = to_string(word_count) + "/ "+ Text_en_ru[(int)Jora::Language][11] +":"+ to_string(ans_correct)+" "+
				Text_en_ru[(int)Jora::Language][12]+":"+ to_string(ans_wrong);
			save("selfnew.txt", My_data);
			conf.Save("settings.conf");

		}
	}
	if (name == "next" && ev == uiglMouseLeftUp)
	{
		cut_data(My_sub_data, My_data, word_count);
		ans_wrong = ans_correct = 0;
		resetlist();
	}

	if(name == "dialog"&&ev == uiglEraseMsg)
	{
		Bild_Window();
	}
	
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name.substr(0, 6) == "setcol")
	{
		switch (name[6])
		{
		case '0':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&backgr_col, Text_en_ru[(int)Jora::Language][4]);
			break;
		case '1':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&text_col, Text_en_ru[(int)Jora::Language][5]);
			break;
		case '2':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&line_col, Text_en_ru[(int)Jora::Language][6]);
			break;
		case '3':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(&button_col, Text_en_ru[(int)Jora::Language][7]);
			break;
		case '4':
			FormSetting.Focus_push_back(&Jora::ColDial);
			Jora::ColDial.Diolog(& select_col, Text_en_ru[(int)Jora::Language][8]);
			break;
		case '5':
			if (Jora::Language == uiglLanguageRU)
				Jora::Language = uiglLanguageEN;
			else Jora::Language = uiglLanguageRU;
			conf.Set_count("en", (int)Jora::Language);
			Bild_Window();
			break;
		default:
			break;
		}
	}

	if ((ev == uiglMouseLeftDown||ev == uiglEnter) && name == "setting")
	{
		if(inp.Text != "")
			word_count = stoi(inp.Text);
		else inp.Text = to_string(word_count);

		state_wnd = 2;
		Animation1(0);		 
	}
}
void Wnd_proc1(uiglEvents ev, string name)
{
	cout << "Wnd_proc1  "<< ev << "  " << name << endl;

	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name.substr(0,4)=="head")
	{
		switch (name[4])
		{
		case '0': {
			state_wnd = 1;
			inp.Text = to_string(word_count);
			Animation1(0);

		}break;
		case '1':{
			state_wnd = 3;
			Animation1(0);
			inp2.Text = "";
			out2.Text = "";
		}break;
		case '2': {
			cut_data(My_sub_data, My_data, word_count);
			resetlist();
			state_wnd = 0;
			Animation1(0);
			ans_wrong = 0;
			ans_correct = 0;

		}break;	
		case '3': {
			resetlist();
			state_wnd = 4;
			Animation1(0);
			if (sentence_selection < ArrSentence.size())
			{
				BildWords(ArrSentence[sentence_selection].GetText());
				sentence_selection++;
				if(sentence_selection == ArrSentence.size())
					sentence_selection = 0;
			}
		}break;
		}
	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter)&& name == "setting")
	{
		if (inp.Text != "")
			word_count = stoi(inp.Text);
		else inp.Text = to_string(word_count);

		state_wnd = 2;
		Animation1(0);
	}
	
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "swap1")
	{
		if (Translate_to)
			Translate_to = 0;
		else Translate_to = 1;
		inp2.Text = "";
		out2.Text = "";
		Bild_Window();
	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter)&& name == "favor")
	{
		if (inp2.Text != "" && out2.Text != "")
		{
			if (!Add_word())
			{
				Jora::MsgBox.Show(MsgString[(int)Jora::Language][1], MsgString[(int)Jora::Language][0]);
				Jora::MsgBox.Name = "msgbax";
			}
		}
		else
		{
			Jora::MsgBox.Show(MsgString[(int)Jora::Language][2], MsgString[(int)Jora::Language][0]);
			Jora::MsgBox.Name = "msgbax";
		}
	}
	
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "cutword")
	{
		Jora::MsgBox.Show(MsgString[(int)Jora::Language][4], MsgString[(int)Jora::Language][0],uiglButtonOKNO);
		Jora::MsgBox.Name = "del";
	}

	if (ev == uiglEnter && name == "inp2")
	{
		if (inp2.Text != "") 
		{
			if (Translate_to)
			{//ru to en
				if (!Find_in_file("ru.txt", inp2.Text, out2.Text))
				{
					Jora::MsgBox.Show(MsgString[(int)Jora::Language][3], MsgString[(int)Jora::Language][0]);
					Jora::MsgBox.Name = "msgbax";
				}
			}
			else
			{
				if (!Find_in_file("en.txt", inp2.Text, out2.Text))
				{
					Jora::MsgBox.Show(MsgString[(int)Jora::Language][3], MsgString[(int)Jora::Language][0]);
					Jora::MsgBox.Name = "msgbax";
				}
			}
		}
	}

	if((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "setting")
	{
		if (inp.Text != "")
			word_count = stoi(inp.Text);
		else inp.Text = to_string(word_count);

		state_wnd = 2;
	}
}

void Wnd_proc_Form5(uiglEvents ev, string name) 
{
	cout << "Wnd_proc_Form5  "<< ev << "  " << name << endl;

	if (((ev == uiglMouseLeftDown) || (ev == uiglEnter)) && name == "setting")
	{
		state_wnd = 2;
		Animation1(0);
	}

	if ((ev == uiglMouseLeftUp) && name.substr(0,4) == "word")
	{		
		WordsPosUpdate(std::stoi(name.substr(4)));
	}
	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "Translation")
	{

		for (int i = 0; i < words.size(); i++)
		{
			if (words[i].Visible == 0)
			{
				words[i].Visible = 1;
				words[i].LineTranslation = 1;
				words[i].Position.setPosition(Jora::WndW *0.5f, Jora::WndH*0.4f);
				words[i].Size.setSize(Jora::WndW *0.5f, Jora::WndH*0.2f);
				break;
			}
		}
	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "enter")
	{		
		std::string txt = MakeSentencr();
		if (txt == "loop")
		{
			Jora::MsgBox.Show("loop", "");
			return;
		}
		if (txt == "gap")
		{
			Jora::MsgBox.Show("gap", "");
			return;
		}
		int num = sentence_selection;
		num--;
		if (num < 0)
			num = ArrSentence.size() - 1;
		if (ArrSentence[num].Test(txt))
		{
			Jora::MsgBox.Show("Done", "");
			Wnd_proc_Form5(ev, "next");
			return;
		}else {
			Jora::MsgBox.Show("Wrong", "");
			return;
		}

	}

	if ((ev == uiglMouseLeftDown || ev == uiglEnter) && name == "next")
	{
		if (sentence_selection < ArrSentence.size())
		{
			BildWords(ArrSentence[sentence_selection].GetText());
			sentence_selection++;
			if (sentence_selection == ArrSentence.size())
				sentence_selection = 0;
			return;
		}
	}
}

int main(int argc, char**argv)
{
	//config
	{
	conf.Get_count("WndH", Jora::WndH);
	conf.Get_count("WndW", Jora::WndW);
	conf.Get_color("textcol", text_col);
	conf.Get_color("backgrcol", backgr_col);
	conf.Get_color("linecol", line_col);
	conf.Get_color("buttrcol", button_col);
	conf.Get_color("selectcol", select_col);
	conf.Get_count("word_count", word_count);
	conf.Get_count("WndX", Jora::WndX);
	conf.Get_count("WndY", Jora::WndY);
	int a0;	conf.Get_count("en", a0);	Jora::Language = (uiglLanguages)a0;

	conf.Add_item("word_count", word_count);
	conf.Add_item("en", (int)Jora::Language);
	conf.Add_item("WndH", Jora::WndH);
	conf.Add_item("WndW", Jora::WndW);
	conf.Add_item("textcol", 100);
	conf.Add_item("backgrcol", 100);
	conf.Add_item("linecol", 100);
	conf.Add_item("buttrcol", 100);
	conf.Add_item("selectcol", 100);
	conf.Add_item("WndX", Jora::WndX);
	conf.Add_item("WndY", Jora::WndY);
	}
	///config

	Jora::WinProc = Wnd_proc;
	Jora::GluiInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
#ifndef NDEBUG
	HANDLE icon = LoadImage(GetModuleHandle((Jora::Name + ".exe").c_str()), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_COLOR);
	SendMessage(Jora::hWnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
#else// NDEBUG
	string s = (Jora::Name + ".exe");
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	HANDLE icon = LoadImage(GetModuleHandle(sw), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_COLOR);
	SendMessage(Jora::hWnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
#endif

	Jora::PositionFunc_ptr = Pos_Func;
	Jora::ReshapeFunc_ptr = Reshop;

	//string T = __DATE__ ;T += "  ";	T += __TIME__;
	//glutSetWindowTitle(T.c_str());
	/*Sentence ss;
	ss.SetText("The letters are on the desk."); ArrSentence.push_back(ss);
	ss.SetText("You'll find the sugar cubes in the cupboard."); ArrSentence.push_back(ss);
	ss.SetText("The coffee table is beside the sofa."); ArrSentence.push_back(ss);
	ss.SetText("The supermarket is in front of their block of flats."); ArrSentence.push_back(ss);
	ss.SetText("The girl is sitting next to her mum."); ArrSentence.push_back(ss);
	ss.SetText("The puppy is inside the box."); ArrSentence.push_back(ss);
	ss.SetText("We have a small garden behind the house."); ArrSentence.push_back(ss);
	ss.SetText("Nastya and Gena study at a secondary school."); ArrSentence.push_back(ss);
	ss.SetText("Take the ball out of the pit."); ArrSentence.push_back(ss);
	ss.SetText("Let's go to the cinema!"); ArrSentence.push_back(ss);
	SaveSentence(ArrSentence, "Sentense.tss");*/
	OpenSentence(ArrSentence, "Sentense.tss");

	glutTimerFunc(50, timer, 0);
	glutDisplayFunc(Display);
	Bild_Window();
	Wnd_init();
	glutMainLoop();
	return 0;
}

void Bild_Window()
{
	//config
	{
		conf.Set_count("word_count", word_count);
		conf.Set_count("WndH", Jora::WndH);
		conf.Set_count("WndW", Jora::WndW);
		conf.setColor("textcol", text_col);
		conf.setColor("backgrcol", backgr_col);
		conf.setColor("linecol", line_col);
		conf.setColor("buttrcol", button_col);
		conf.setColor("selectcol", select_col);
	}
	FormTraining.Background_color = backgr_col;
	FormSetting.Background_color = backgr_col;
	FormMain.Background_color = backgr_col;
	FormTranslate.Background_color = backgr_col;
	Form5.Background_color = backgr_col;
	//////////////////////////////////////////////////////FormTraining
	
	//list1
	{
		list1.Size.setSize(Jora::WndW / 2,Jora::WndH*0.8);	
		list1.Position.setPosition(0,0);
		list1.Name = "list1";
		list1.Set_text_size(25);
		list1.Color = button_col;
		list1.Outline_color = line_col;
		list1.Select_color = select_col; 
		list1.Text_color = text_col;
	}
	//list2
	{
		list2.Size.setSize(Jora::WndW / 2,Jora::WndH*0.8);
		list2.Position.setPosition(Jora::WndW / 2, 0);
		list2.Name = "list2";
		list2.Set_text_size(25);
		list2.Color = button_col;
		list2.Outline_color = line_col;
		list2.Select_color = select_col;
		list2.Text_color = text_col;
	}
	//butt
	{
		butt.Size.setSize(150,30);
		butt.Position.setPosition(10, Jora::WndH - butt.Size.getSizeH() - 10 );
		butt.Name = "enter";
		butt.Set_text_size(butt.Size.getSizeH() - 5);
		butt.Text = Text_en_ru[(int)Jora::Language][0];
		butt.Color = button_col;
		butt.Outline_color = line_col;
		butt.Text_color = text_col;
	}
	//butt1
	{
		butt1.Size.setSize(150, 30);
		butt1.Position.setPosition(10, Jora::WndH - butt.Size.getSizeH() - 50);
		butt1.Name = "next";
		butt1.Set_text_size(butt.Size.getSizeH() - 5);
		butt1.Text = Text_en_ru[(int)Jora::Language][1];
		butt1.Color = button_col;
		butt1.Outline_color = line_col;
		butt1.Text_color = text_col;
	}
	//butt2
	{
		butt2.Size.setSize(150, 30);
		butt2.Position.setPosition(Jora::WndW - 160, Jora::WndH - 40 );
		butt2.Name = "setting";
		butt2.Set_text_size(butt.Size.getSizeH() - 5);
		butt2.Text = Text_en_ru[(int)Jora::Language][2];
		butt2.Color = button_col;
		butt2.Outline_color = line_col;
		butt2.Text_color = text_col;
	}
	//butt3
	{
		butt3.Size.setSize(Jora::WndW, 30);
		butt3.Position.setPosition(0, Jora::WndH*0.8 );
		butt3.Name = "inf";
		butt3.IsHover = 0;
		butt3.Set_text_size(butt.Size.getSizeH() - 5);
		butt3.Text = to_string(word_count) + "/ " + Text_en_ru[(int)Jora::Language][11] + ":" + to_string(ans_correct) + " " +
			Text_en_ru[(int)Jora::Language][12] + ":" + to_string(ans_wrong);
		butt3.Color = button_col;
		butt3.Outline_color = line_col;
		butt3.Text_color = text_col;
	}
	
	//////////////////////////////////////////////////////FormSetting
	
	//inp
	{
		inp.NumbersOnly = 1;
		inp.Size.setSize(70, 30);
		inp.Set_text_size(inp.Size.getSizeH() - 6);
		inp.Name = "textbox";
		inp.Position.setPosition(10, Jora::WndH - inp.Size.getSizeH() - 10 );
		inp.Title = Text_en_ru[(int)Jora::Language][3];
		inp.SetMin(5);
		inp.SetMax(99);
		inp.Text_max_length = 2;
		inp.Color = button_col;
		inp.Outline_color = line_col;
		inp.Text_color = text_col;
	}
	//sett_col
	{
		sett_col[0].Color = backgr_col;
		sett_col[1].Color = text_col;
		sett_col[2].Color = line_col;
		sett_col[3].Color = button_col;
		sett_col[4].Color = select_col;
		sett_col[5].Color = button_col;
		sett_col[6].Color = button_col;


		for (int i = 0; i < 7; i++)
		{
			sett_col[i].Size.setSize(30, 30);
			sett_col[i].Position.setPosition(Vector2f(10, Jora::WndH - 40 * (i + 2)));
			sett_col[i].Set_text_size(24);
			sett_col[i].Name = "setcol" + to_string(i);
			sett_col[i].Text_color = text_col;
			sett_col[i].Text = Text_en_ru[(int)Jora::Language][i + 4];
			sett_col[i].Outline_color = line_col;
			sett_col[i].IsHover = false;
		}
		sett_col[5].IsHover = true;
		sett_col[5].Size.setSize(50, 30);
	}
	//////////////////////////////////////////////////////FormMain

	//Head_menu
	for (int i = 0; i < 4; i++)
	{
		Head_menu[i].Size.setSize(300, 100);
		Head_menu[i].Position.setPosition(Jora::WndW / 2 - 150, Jora::WndH / 2 - 160 + i * 110);
		Head_menu[i].Name = "head" + to_string(i);
		Head_menu[i].Set_text_size(35);
		Head_menu[i].Text = Head_en_ru[(int)Jora::Language][i];
		Head_menu[i].Color = button_col;
		Head_menu[i].Outline_color = line_col;
		Head_menu[i].Text_color = text_col;
		Head_menu[i].Text_align = uiglMiddleCenter;
	}
	//////////////////////////////////////////////////////FormTranslate

	//list_l
	{
		list_l.Size.setSize(Jora::WndW,Jora::WndH*0.8);
		list_l.Position.setPosition(0, 0);
		list_l.Name = "list_l";
		list_l.Set_text_size(25);
		list_l.Color = button_col;
		list_l.Outline_color = line_col;
		list_l.Select_color = select_col;
		list_l.Text_color = text_col;
	}
	//inp2
	{
		inp2.Size.setSize(Jora::WndW*0.5 - 35, 30);
		inp2.Set_text_size(inp.Size.getSizeH() - 6);
		inp2.Name = "inp2";
		inp2.Position.setPosition(10, Jora::WndH - 80 );
		inp2.Color = button_col;
		inp2.Outline_color = line_col;
		inp2.Text_color = text_col;
		inp2.Text_align = uiglBottomCenter;
	}
	//favor
	{
		favor.Size.setSize(300,30);
		favor.Position.setPosition(10, Jora::WndH - butt.Size.getSizeH() - 10 );
		favor.Name = "favor";
		favor.Set_text_size(butt.Size.getSizeH() - 5);
		favor.Text = Head_en_ru[(int)Jora::Language][6];
		favor.Color = button_col;
		favor.Outline_color = line_col;
		favor.Text_color = text_col;
	}
	//cutword
	{
		cutword.Size.setSize(150, 30);
		cutword.Position.setPosition(Jora::WndW - 160, Jora::WndH*0.8+10 );
		cutword.Name = "cutword";
		cutword.Set_text_size(butt.Size.getSizeH() - 5);
		cutword.Text = Head_en_ru[(int)Jora::Language][7];
		cutword.Color = button_col;
		cutword.Outline_color = line_col;
		cutword.Text_color = text_col;
	}
	//out2
	{
		out2.Size.setSize(Jora::WndW*0.5f-35, 30);
		out2.Position.setPosition(Jora::WndW*0.5f+25, Jora::WndH - 80);
		out2.Name = "out2";
		out2.Set_text_size(butt.Size.getSizeH() - 5);
		out2.Color = button_col;
		out2.Outline_color = line_col;
		out2.Text_color = text_col;
		out2.Text_align = uiglBottomCenter;
	}
	//swap1
	{
		swap1.Size.setSize(40, 40);
		swap1.Position.setPosition(Jora::WndW*0.5f - 20, Jora::WndH - 85);	
//		swap1.Position.setPosition(Jora::WndW, Jora::WndH);		
		swap1.Name = "swap1";
		swap1.Color = button_col;
		swap1.Outline_color = line_col;
	}
	if (!Translate_to) 
	{
		inp2.Title = Head_en_ru[(int)Jora::Language][4];
		out2.Title = Head_en_ru[(int)Jora::Language][5];
	}else {
		inp2.Title = Head_en_ru[(int)Jora::Language][5];
		out2.Title = Head_en_ru[(int)Jora::Language][4];
	}
	////////////////////////////////////////////////Form5
	for (int i = 0; i < words.size(); i++)
	{
		words[i].Color = button_col;
		words[i].Outline_color = line_col;
		words[i].Text_color = text_col;
	}
	panel1.Position.setPosition(Jora::WndMinX, Jora::WndMinY);
	panel1.Size.setSize(Jora::WndW, Jora::WndH*0.8f);
	panel1.Color = select_col;
	panel1.Outline_color = line_col;
	
	///AddLineTranslation
	{
		AddLineTranslation.Size.setSize(210, 30);
		AddLineTranslation.Position.setPosition(10, Jora::WndH*0.8 + 10 + butt3.Size.getSizeH());
		AddLineTranslation.Set_text_size(butt.Size.getSizeH() - 5);
		AddLineTranslation.Text = Text_Form5[(int)Jora::Language][0];
		AddLineTranslation.Color = button_col;
		AddLineTranslation.Outline_color = line_col;
		AddLineTranslation.Text_color = text_col;
		AddLineTranslation.Name = "Translation";
	}
	///TestTranslation
	/*{
		TestTranslation.Size.setSize(150, 30);
		TestTranslation.Position.setPosition(10, Jora::WndH - TestTranslation.Size.getSizeH()-10);
		TestTranslation.Set_text_size(butt.Size.getSizeH() - 5);
		TestTranslation.Text = Text_en_ru[(int)Jora::Language][0];
		TestTranslation.Color = button_col;
		TestTranslation.Outline_color = line_col;
		TestTranslation.Text_color = text_col;
		TestTranslation.Name = "test";
	}*/
	///////////////////////////////////////////////
	switch (state_wnd)
	{
	case 0:
		cout << "FormTraining\n";
		FormTraining.Enabled = 1;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		resetlist();
		break;
	case 1:
		cout << "FormSetting\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 1;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		break;
	case 2:
		cout << "FormMain\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 1;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 0;
		break;
	case 3:
		cout << "FormTranslate\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 1;
		Form5.Enabled = 0;
		break;
	case 4:
		cout << "Form5\n";
		FormTraining.Enabled = 0;
		FormSetting.Enabled = 0;
		FormMain.Enabled = 0;
		FormTranslate.Enabled = 0;
		Form5.Enabled = 1;
		break;
	}
	conf.Save();
}

void Wnd_init()
{
	FormTraining.Wnd_proc = Wnd_proc;
	FormSetting.Wnd_proc = Wnd_proc;
	FormMain.Wnd_proc = Wnd_proc1;
	FormTranslate.Wnd_proc = Wnd_proc1;
	Form5.Wnd_proc = Wnd_proc_Form5;

	//////////////////////////////////////////////FormTraining
	FormTraining.Stec_push_back(&list1);
	FormTraining.Stec_push_back(&list2);
	FormTraining.Stec_push_back(&butt);
	FormTraining.Stec_push_back(&butt1);
	FormTraining.Stec_push_back(&butt2);
	FormTraining.Stec_push_back(&butt3);

	//////////////////////////////////////////////FormSetting
	FormSetting.Stec_push_back(&inp);
	FormSetting.Stec_push_back(&butt2);
	for (int i = 0; i < 7; i++)
	{
		FormSetting.Stec_push_back(&sett_col[i]);
	}
	//////////////////////////////////////////////////FormMain
	FormMain.Stec_push_back(&Head_menu[0]);
	FormMain.Stec_push_back(&Head_menu[1]);
	FormMain.Stec_push_back(&Head_menu[2]);
	FormMain.Stec_push_back(&Head_menu[3]);
	/////////////////////////////////////////////////FormTranslate
	FormTranslate.Stec_push_back(&butt2);
	FormTranslate.Stec_push_back(&list_l);
	FormTranslate.Stec_push_back(&inp2);
	FormTranslate.Stec_push_back(&out2);
	FormTranslate.Stec_push_back(&swap1);
	FormTranslate.Stec_push_back(&favor);
	FormTranslate.Stec_push_back(&cutword);
	swap1.Open("swap.ggp");
	/////////////////////////////////////////////////Form5
	Form5.Stec_push_back(&butt2);
	for (int i = 0; i < words.size(); i++)
	{
		Form5.Stec_push_back(&words[i]);
		words[i].Name = "word" + to_string(i);
	}
	Form5.Stec_push_back(&panel1);
	Form5.Stec_push_back(&AddLineTranslation);
//	Form5.Stec_push_back(&TestTranslation);
	Form5.Stec_push_back(&butt3);
	Form5.Stec_push_back(&butt);
	Form5.Stec_push_back(&butt1);

	////////////////////////////////////////////////
	srand(time(0));
	open("selfnew.txt", My_data);
	list_updat();
	cut_data(My_sub_data, My_data, word_count);
}

bool Add_word()
{
	string_int _temp;

	if (Translate_to)
	{
		if (find(list_l.Items1.begin(), list_l.Items1.end(), inp2.Text) == list_l.Items1.end())
		{
			_temp.Text1 = inp2.Text;
			_temp.Text = out2.Text;
		}
		else	return 0;

	}
	else {///en to ru
		if (find(list_l.Items.begin(), list_l.Items.end(), inp2.Text) == list_l.Items.end())
		{
			_temp.Text = inp2.Text;
			_temp.Text1 = out2.Text;
		}
		else return 0;
	}

	_temp.Count = 1000;
	My_data.push_back(_temp);
	inp2.Text = "";
	out2.Text = "";
	list_updat();
	save("selfnew.txt", My_data);

	return 1;
}

void resetlist()
{
	list1.Items.clear();
	list2.Items.clear();
	list1.Selected = 0;
	list2.Selected = 0;
	for (int i = 0; i < My_sub_data.size(); i++)
	{
		list1.Items.push_back(My_sub_data[i]->Text);
		list2.Items.push_back(My_sub_data[i]->Text1);
	}
	sort(list2.Items.begin(), list2.Items.end());
}

void list_updat()
{
	list_l.Items.clear();
	list_l.Items1.clear();

	for (int i = 0; i < My_data.size(); i++)
	{
		list_l.Items.push_back(My_data[i].Text);
		list_l.Items1.push_back(My_data[i].Text1);
	}
	list_l.Selected = 0;
}

bool Find_in_file(std::string file_name, std::string Text_find, std::string &Text_result)
{
	std::ifstream fin;
	fin.open(file_name);
	if (!fin.is_open())
		return 0;
	std::string temp;
	char T;
	bool read(1), find(0);

	fin.seekg(0,ios::end);
	int FileEnd = fin.tellg(), seekBegin = 0,seekEnd = 0;
	seekEnd = FileEnd;

	do{
		fin.seekg((seekEnd+seekBegin)/2);
		std::getline(fin,temp);
		T = fin.peek();
		if (T < Text_find[0])
			seekBegin = fin.tellg();
		if (T > Text_find[0])
			seekEnd = fin.tellg();
		if (seekEnd - seekBegin < 300)
			return 0;
	} while (T != Text_find[0] && !fin.eof());

	seekBegin = fin.tellg();
	do {
		if (seekBegin - 200 > 0)
			seekBegin -= 200;
		else { fin.seekg(0); break;}
		fin.seekg(seekBegin);
		std::getline(fin, temp);
		T = fin.peek();
	} while (T == Text_find[0] && !fin.eof());

	fin >> temp;
	bool b = 0;
	while ( !fin.eof())
	{
		if (Text_find == temp)
		{
			find = 1;
			break;
		}else std::getline(fin, temp);
		T = fin.peek();
		if (T == Text_find[0])
			b = 1;
		if (T != Text_find[0] && b == 1)
			return 0;
		fin >> temp;
	}
	fin.get();
	if (find)
	{
		Text_result = "";
		while (T = fin.get())
		{
			if (T != '\n')
				Text_result += T;
			else return 1;
		}
	}
	return 0;
}

bool open(string file_name, vector<string_int>& mas)
{
	ifstream in;
	in.open(file_name);
	if (!in.is_open())
		return 0;
	mas.clear();
	int _count;
	string_int tempdata;
	string tempstr;
	bool is_read(1);
	
	while (in >> tempstr)
	{
		tempdata.Text = tempstr;

		in >> _count;
		tempdata.Count = _count;

		in.get();
		std::getline(in, tempstr);
		tempdata.Text1 = tempstr;
		mas.push_back(tempdata);
	}
	return 1;
}

bool save(string file_name, vector<string_int>& mas)
{
	ofstream out;
	out.open(file_name);
	if (!out.is_open())
		return 0;
	for (int i = 0; i < mas.size(); i++)
		out << mas[i].Text << " "<< mas[i].Count << " "<< mas[i].Text1 <<endl;
	return 1;
}

bool Open_dataen(string file_name1,vector<Mytext>& mas)
{
	ifstream in(file_name1);
	if (!in.is_open())
		return 0;
	string _word;
	Mytext _temp;
	while (!in.eof())
	{
		in >> _word;
		_temp.en = _word;
		in.get();
		getline(in, _word);
		mas.push_back(_temp);
	}
	return 1;
}

string translate(string text_en)
{
	for (int i = 0; i < My_sub_data.size(); i++)
	{
		if (My_sub_data[i]->Text == text_en)
			return My_sub_data[i]->Text1;
	}
	return "";
}

bool cut_data(vector<string_int*>& sub_mas ,vector<string_int>& mas,int sub_mas_size)
{
	sub_mas.clear();
	sort(mas.begin(), mas.end(), [](string_int a, string_int b) {return a.Count < b.Count; });
	int i(0), j(0);
	
	while (j < sub_mas_size && i < mas.size())
	{
		if (mas[i].Num == 0)
		{
			mas[i].Num = 1;
			sub_mas.push_back(&mas[i]);
			j++;
		}
		i++;
	}

	if(i >= mas.size()-1)
		for (int k = 0; k < mas.size(); k++)
			mas[k].Num = 0;

	sort(list2.Items.begin(), list2.Items.end());
	return 1;
}

void BildWords(std::string text)
{
	int _begin = 0,w_count = 0;
	for (int i = 0; i < words.size(); i++)
		words[i].Reset();
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == ' '||text.size() == i) 
		{
			words[w_count].Text = text.substr(_begin,i-_begin);
			_begin = i+1;
			words[w_count].Visible = true;
			w_count++;
		}
	}
	words[w_count].Text = text.substr(_begin);
	words[w_count].Visible = true;
	w_count++;

	for (int i = 0; i < w_count; i++)
		words[i].Position.setPosition(rand() % (int)(Jora::WndW*0.8f)-Jora::WndMinX,rand() % (int)(Jora::WndH*0.8f-50)-Jora::WndMinY);
}

void WordsPosUpdate(int n)
{
	Vector2f a, b, c;
	int l = 0;
	a = words[n].Position.getPosition2f();
	for (int i = 0; i < words.size(); i++)
	{	
		if (i == n || !words[i].Visible) continue;
		if (!words[i].LineTranslation)
		{
			b = words[i].Position.getPosition2f();
			b = b + Vector2f(words[i].Size.getSizeW(), 0);
			c = a - b;
			l = std::sqrtf(c.X*c.X + c.Y*c.Y);
			if (l < 35)
			{
				if (words[i].Next != nullptr)
				{
					words[i].Next->Jamp();
				}
				words[n].Back = &words[i];
				words[i].Next = &words[n];
				words[i].UpdateStec();
				break;
			}
		}else {
			b = Vector2f(words[i].Size.getSizeW() + words[n].Size.getSizeH(), words[i].Size.getSizeH());
			c = a - b;
			l = std::sqrtf(c.X*c.X + c.Y*c.Y);
			if (l < 35)
			{
				if (words[i].Next != nullptr)
					words[i].Next->Jamp();
				words[n].Back = &words[i];
				words[i].Next = &words[n];
				words[i].UpdateStec();
				break;
			}
		}
	}
}

bool SaveSentence(const vector<Sentence>& _sentence,std::string file_name)
{
	ofstream fout(file_name);
	if (fout.is_open())
	{
		fout.write((char*)&("TSS_"),4);
		int str_count = _sentence.size(),str_length = 0,arr_length = 0;
		fout.write((char*)&str_count, sizeof(int));
		for (int i = 0; i < _sentence.size(); i++)
		{
			fout.write((char*)&(_sentence[i].Rating), sizeof(int));

			str_length = _sentence[i].Text.size();
			fout.write((char*)&str_length, sizeof(int));
			const char* _t = _sentence[i].Text.c_str();
			fout.write( _t, sizeof(char)*str_length);

			for (int j = 0; j < _sentence[i].arr.size(); j++)
				arr_length += _sentence[i].arr[j].size();
			fout.write((char*)&arr_length, sizeof(int));
			for (int k = 0; k < _sentence[i].arr.size(); k++)
			{
				for (int j = 0; j < _sentence[i].arr[k].size(); j++)
					fout <<(char)_sentence[i].arr[k][j];
			}
		}
		fout.close();
		return true;
	}
	else return false;
}

bool OpenSentence(vector<Sentence>& _sentence,std::string file_name)
{
	ifstream fin(file_name);
	if (fin.is_open())
	{
		char T[] = "ABCD";
		fin.read((char*)(&T), 4);
		if (std::string(T) == "TSS_")
		{
			_sentence.clear();
			Sentence temp;
			int str_count = 0,str_length = 0, arr_length = 0,c_count = 0;
			fin.read((char*)&str_count, sizeof(int));
			for (int i = 0; i < str_count && !fin.eof(); i++)
			{
				fin.read((char*)&(temp.Rating), sizeof(int));

				fin.read((char*)&(str_length), sizeof(int));
				char* _t = new char[str_length+1];
				fin.read(_t, sizeof(char)*str_length);
				temp.Text = _t;
				temp.Text = temp.Text.substr(0, str_length);
				c_count = 0;
				for (int j = 0; j < temp.Text.length(); j++)
					if (temp.Text[j] == ' '+30)
						c_count++;
				c_count++;

				fin.read((char*)&(arr_length), sizeof(int));
				char _c = 0;
				for (int k = 0; k < arr_length/c_count; k++)
				{
					temp.arr.push_back(vector<char>());
					for (int j = 0; j < c_count; j++)
					{
						fin >> _c;
						temp.arr.back().push_back(_c);
					}
				}
				_sentence.push_back(temp);
			}

			fin.close();
			return true;
		}
	}
	return false;
}

std::string  MakeSentencr()
{
	WordObj * _W_Begin = NULL;
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i].Visible /*&& !words[i].LineTranslation*/)
		{
			if (words[i].Back == nullptr)
			{
				if (_W_Begin == nullptr)
				{
					_W_Begin = &words[i];
				}else { 
				//	if(!_W_Begin->LineTranslation)
						return "gap"; 
				}
			}
		}
	}

	if (_W_Begin == nullptr)
		return "loop";

	std::string text;
	for (; _W_Begin != nullptr; _W_Begin = _W_Begin->Next)
	{
		text += _W_Begin->Text + " ";
	}
	return text;
}
