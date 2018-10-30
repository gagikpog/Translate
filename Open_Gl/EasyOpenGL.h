#ifndef EASY_OPENGL_H_ //если файл не включен
#define EASY_OPENGL_H_ //включить файл
/// Библиотека EasyOpenGL начало разработки 25.07.2017
/// Библиотека EasyOpenGL возобновление разработки 30.10.2018
#include <gl\freeglut.h>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

const float PI = 3.14159265358979323846f;

namespace easyGL {
	
	//перечисление цветов 
	enum Glui_Colornum {
		Black, White, Red, Green, Blue, Cyan, Magenta, Yellow, Water, Plastic, Glass, Diamond, Iron, Copper, Gold, Aluminum, Silver, Deepskyblue,
		Lightskyblue, Mistyrose, Burlywood, Violet, Whitesmoke, Lime, Tan, Lightgray, Lightsteelblue, Yellowgreen, Orange, Coral, Fuchsia, Dodgerblue,
		Plum, Limegreen, Olive, Darkmagenta, Gray, Dimgray, Brown, Darkslategray, Firebrick, Sienna, Maroon, Darkblue, Navy, Other
	};
	enum Glui_Alignment { Top_left, Top_center, Top_right, Middle_left, Middle_center, Middle_right, Bottom_left, Bottom_center, Bottom_right };
	enum Guil_Primitives { GP_POINTS, GP_LINES, GP_LINE_LOOP, GP_LINE_STRIP, GP_TRANGLES, GP_TRIANGLE_STRIP, GP_TRIANGLE_FAN, GP_QUADS, GP_QUAD_STRIP, GP_POLYGON };
	//перечисление событий
	enum Glui_Event {
		Gl_EventEmpty,Gl_MouseLeftDown, Gl_MouseLeftUp, Gl_MouseRightDown, Gl_MouseRightUp, Gl_MouseCenterDown, Gl_MouseCenterUp,
		Gl_MouseOver, Gl_MouseOut, Gl_Mousemove, Gl_wheelup, Gl_WheelDown, Gl_DoubleClick, Gl_EraseMsg, Gl_Changed, Gl_Enter,
		Gl_MsgYes,Gl_MsgNo,Gl_MsgCancel
	};
	enum Glui_MsgBoxButton{
		Gl_ButtonOK, Gl_ButtonNO, Gl_ButtonCancel, Gl_ButtonOKNO, Gl_ButtonOKCancel, Gl_ButtonNoCancel, Gl_ButtonOKNOCancel
	};
	enum Glui_Language {Gl_LanguageEN,Gl_LanguageRU};
	enum Glui_Orientacion {Gl_Vertical,Gl_Horizontal};

	class Glui_Obj;
	class Glui_Forms;
	class Glui_Text;
	class Glui_MessageBox;
	class Glui_Color;
	class Glui_Combobox;


	struct gleventstruct
	{
		Glui_Event Event = Gl_EventEmpty;
		std::string Name = "";
	};
	struct string_int
	{
		std::string Text = "";
		std::string Text1 = "";
		unsigned int Count = 0;
		int Num = 0;
	};
	struct Vector2f
	{
		Vector2f() {}
		Vector2f(float x, float y)
		{
			X = x;
			Y = y;
		}
		Vector2f(const Vector2f& value)
		{
			X = value.X;
			Y = value.Y;
		}
		Vector2f operator+(const Vector2f& value) const
		{
			return Vector2f(X + value.X, Y + value.Y);
		}
		Vector2f operator-(const Vector2f& value) const
		{
			return Vector2f(X - value.X, Y - value.Y);
		}
		Vector2f& operator=(const Vector2f& value)
		{
			X = value.X;
			Y = value.Y;
			return *this;
		}
		Vector2f& operator+=(const Vector2f& value)
		{
			X += value.X;
			Y += value.Y;
			return *this;
		}
		Vector2f& operator-=(const Vector2f& value)
		{
			X -= value.X;
			Y -= value.Y;
			return *this;
		}
		bool operator==(const Vector2f& operator2)
		{
			return (X == operator2.X && Y == operator2.Y);
		}
		float X = 0;
		float Y = 0;
	};
	struct Vector3f
	{
		Vector3f() {}
		Vector3f(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}		
		Vector3f(const Vector3f& value)
		{
			X = value.X;
			Y = value.Y;
			Z = value.Z;
		}
		Vector3f operator+(const Vector3f& value) const 
		{
			return Vector3f(X + value.X, Y + value.Y,Z + value.Z);
		}
		Vector3f operator-(const Vector3f& value) const
		{
			return Vector3f(X - value.X, Y - value.Y,Z + value.Z);
		}
		Vector3f operator=(const Vector3f& value)
		{
			X = value.X;
			Y = value.Y;
			Z = value.Z;
			return *this;
		}
		Vector3f operator+=(const Vector3f& value)
		{
			X += value.X;
			Y += value.Y;
			Z += value.Z;
			return *this;
		}
		Vector3f operator-=(const Vector3f& value)
		{
			X -= value.X;
			Y -= value.Y;
			Z -= value.Z;
			return *this;
		}
		//Векторное произведение
		Vector3f operator*(const Vector3f& value)const
		{
			Vector3f _tmp;
			_tmp.X = Y*value.Z - Z*value.Y;
			_tmp.Y = -X*value.Z + Z*value.X;
			_tmp.Z = X*value.Y - Y*value.X;
			return _tmp;
		}	
		Vector3f operator/(const float& value) const
		{
			return Vector3f(X / value, Y / value, Z / value);
		}
		Vector3f operator*(const float& value) const
		{
			return Vector3f(X * value, Y * value, Z * value);
		}
		friend std::ostream& operator<<(std::ostream& _out,const Vector3f& b)
		{
			_out <<"X = "<< b.X <<", Y = "<< b.Y <<", Z = "<< b.Z;
			return _out;
		}
		float GetLength() const
		{
			return std::sqrtf(X*X + Y*Y + Z*Z);
		}
		float X = 0;
		float Y = 0;
		float Z = 0;
	};
	struct Glui_Position
	{
		void SetPosition(float Xvalue, float Yvalue, float Zvalue = 0);
		void SetPosition(const Vector3f& value);
		void SetPosition(const Vector2f& value);
		Vector2f GetPosition2f() const { return Vector2f(X, Y); }
		Vector3f GetPosition3f() const { return Vector3f(X, Y, Z); }
		float GetPositionX() const { return X; }
		float GetPositionY() const { return Y; }
		float GetPositionZ() const { return Z; }
		Glui_Obj* UpdatePtr = NULL;
	private:
		float X = 0,Y = 0,Z = 0;
	};
	struct Glui_Size
	{
		void SetSize(float width, float height, float depth = 0);
		float GetSizeW() const { return W; }
		float GetSizeH() const { return H; }
		float GetSizeD() const { return D; }
		Glui_Obj* UpdatePtr = NULL;
	private:
		float W = 10, H = 10, D = 0;
	};
	struct Layer
	{
		int count = 0;
		Guil_Primitives primitive = GP_LINE_LOOP;
		float line_length = 1;
	};

	//глют цвета
	class Glui_Color
	{
	public:
		Glui_Color(BYTE red, BYTE green, BYTE blue, BYTE alpha = 255);
		Glui_Color(const Glui_Colornum& _color = Black);
		Glui_Color(const Glui_Color& _color);
		~Glui_Color() {}
		//установка цвета
		Glui_Color& Set_color(const Glui_Colornum& _color);
		Glui_Color& Set_color(const Glui_Color& _color);
		//установка цвета
		Glui_Color& Set_color(BYTE _red, BYTE _green, BYTE _blue, BYTE _alpha = 255);
		//установка прозрачности
		Glui_Color& Set_alpha(const BYTE& _alpha);
		//определяет цвет отрисовки
		void Init(short bright = 0, BYTE _alpha = 0)const;
		//Возвращает цвета в uint
		unsigned int Get_uint()const;
		//переобразует uint в цвета RGBA
		Glui_Color& Set_uint(unsigned int count);
		//возвращает цвет в негативе
		Glui_Color Get_negative()const;
		//не меняет значение
		Glui_Color operator+(int _c)const;
		//не меняет значение
		Glui_Color operator-(int _c)const;
		bool operator==(const Glui_Colornum& _col)const;
		bool operator==(const Glui_Color& _col)const;
		Glui_Color operator+(const Glui_Color& operator2)const;
		Glui_Color operator-(const Glui_Color& operator2)const;
		friend class Glui_ColDiаlog;
	private:
	protected:
		Glui_Color Bild_color(Glui_Colornum _Color)const;
		Glui_Colornum  Color;
		BYTE R, G, B, A;
	};

	struct Point
	{
		float X = 0;
		float Y = 0;
		Glui_Color Color;
	};
#pragma region Function
	float rotate_x(float x, float y, float alpha);
	float rotate_y(float x, float y, float alpha);
	//прямоугольник с закругленными краями контур
	inline void Gl_Print_Roundrect_Contour(float X, float Y, float W, float H, float R, Glui_Color Outline_color = Black, float _angle = 0, float line_width = 1);
	//прямоугольник с закругленными краями
	inline void Gl_Print_Roundrect(float X, float Y, float W, float H, float R, Glui_Color Color, Glui_Color Outline_color = Black, float _angle = 0, bool glossy = 1, float line_width = 1);
	//окружность контур
	inline void Gl_Print_Circle_Contour(float X, float Y, float R, Glui_Color Outline_color = Black, float line_width = 1);
	//окружность
	inline void Gl_Print_Circle(float X, float Y, float R, Glui_Color Color, Glui_Color Outline_color = Black, float line_width = 1);
	
	inline void Gl_Print_Rectangle_Contour(float X, float Y, float W, float H, Glui_Color Outline_color = Black, float _angle = 0, float line_width = 1);
	//прямоугольник 
	inline void Gl_Print_Rectangle(float X, float Y, float W, float H, Glui_Color Color, Glui_Color Outline_color = Black, float _angle = 0, bool glossy = 1, float line_width = 1);
	//круг контур
	inline void Gl_Print_Circle_Contour(float X, float Y, float r, float R, Glui_Color Color, Glui_Color Outline_color = Black);
	//многоугольник
	inline void Gl_Print_Polygon_Contour(float X, float Y, float R, int Sides, Glui_Color Outline_color = Black, float initial_angle = 0, float line_width = 1);
	//многоугольник
	inline void Gl_Print_Polygon(float X, float Y, float R, int Sides, Glui_Color Color, Glui_Color Outline_color = Black, float initial_angle = 0,float line_width = 1);
#pragma endregion

	class Glui_Obj
	{
	public:
		Glui_Obj() {}
		~Glui_Obj() {}
		Glui_Position Position;
		Glui_Size Size;
		float SetAngle(float angle) { return Angle = angle; }
		float GetAngle() { return Angle; }
		virtual void Update()
		{
			X = Position.GetPositionX();
			Y = Position.GetPositionY();
			H = Size.GetSizeH();
			W = Size.GetSizeW();
		}
	protected:
		std::vector<Vector2f> Points;
		//позиция X
		float X = 0.0f;
		//позиция Y
		float Y = 0.0f;
		float H = 10.0f;
		float W = 10.0f;
		//угол
		float Angle = 0.0f;
	};
	
	class Glui_IForms :virtual public Glui_Obj
	{
	public:
		Glui_IForms() {}
		~Glui_IForms() {}
		//имя объекта //передается в функцию Wnd_proc
		std::string Name = "no_naem";
		//цвет заливки
		Glui_Color Color = White;
		//цвет контура
		Glui_Color Outline_color = Glui_Color(70,70,70,255);
		bool IsHover = 1;
		bool Visible = 1;
		//если истина, то разрешает перетаскивание объекта мышью
		bool is_move = 0;
		virtual gleventstruct MouseFunc(int button, int state, int ax, int ay) = 0;
		virtual gleventstruct PassiveMotionFunc(int ax, int ay) = 0;
		virtual gleventstruct MotionFunc(float ax, float ay) = 0;
		virtual gleventstruct MouseWheelFunc(int button, int state, int ax, int ay) = 0;
		virtual gleventstruct KeyboardFunc(unsigned char key, int ax, int ay) = 0;
		virtual gleventstruct SpecialFunc(int key, int ax, int ay) = 0;
		virtual gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay) = 0;
		virtual gleventstruct SpecialUpFunc(int key, int ax, int ay) = 0;
		virtual gleventstruct PositionFunc(int aw, int ah) { return gleventstruct(); }
		virtual gleventstruct ReshapeFunc(int ax, int ay) { return gleventstruct(); }
		//выполняет отрисовку объекта
		virtual void Init() = 0;
		//устанавливает дескриптор контекста устройства
		virtual void SetHDC(HDC* _hdc) { hdc = _hdc; }

		friend class Glui_Forms;
		friend class Glui_ColDiаlog;
	protected:
		//находится ли объект в фокусе
		bool in_focus = false;
		bool Mouse_in_button = 0, moved = 0;
		//время предыдущего нажатия мыши в clock -ах
		unsigned int double_ckick = 0;
		//разница между координатом мышы и координатом объекта во время перетаскивания объекта
		float  mx = 0, my = 0;
		//дескриптор окна
		HDC* hdc;
	};

	class Glui_Forms
	{
	public:
		Glui_Forms();
		Glui_Forms(bool add_in_main_forms);
		~Glui_Forms() {}
		static std::vector<Glui_Forms*> Forms;
		void MouseWheelFunc_g(int button, int state, int ax, int ay);
		void PassiveMotionFunc_g(int ax, int ay);
		void MotionFunc_g(int ax, int ay);
		void MouseFunc_g(int button, int state, int ax, int ay);
		void KeyboardFunc_g(unsigned char key, int ax, int ay);
		void SpecialFunc_g(int key, int ax, int ay);
		void KeyboardUpFunc_g(unsigned char key, int ax, int ay);
		void SpecialUpFunc_g(int key, int ax, int ay);
		void Init_g(bool OnlyFocus = 0, bool clear_background = true);
		//принимает ссылку на объект класса Glui_IForms
		void Focus_push_back(Glui_IForms* func);
		void Focus_pop_back();
		void Focus_erase(int num);
		void Stec_erase(int num);
		//принимает ссылку на объект класса Glui_IForms
		void Stec_push_back(Glui_IForms* func);
		void Stec_pop_back();
		//устанавливает дескриптор контекста устройства
		void SetHDC(HDC* _hdc_);
		Glui_Color Background_color = White;
		//0==disable, 1==enable, 2==(disable+(Init==enable))
		int Enabled = 1;//
		void(*Wnd_proc)(Glui_Event, std::string);
	private:		
		void Set_Focus();
		int in_focus = 0;
		std::list<Glui_IForms*>Stec;
		std::vector<Glui_IForms*>Focus;
		HDC* _hdc;
		bool Shift_press;
	};

	class Glui_MainForm
	{
	public:
		Glui_MainForm() {}
		~Glui_MainForm() {}
		static void GluiInit(int _argc_, char** _argv_);
		static void Display(bool focus_only = false , bool clear_background = true);
		static int WndH;
		static int WndW;
		static int WndX;
		static int WndY;
		static int WndMinX;
		static int WndMinY;
		static int argc;
		static Glui_Language Language;
		static std::vector<std::string>argv;
		static std::string Name;
		static HDC hDC;
		static HWND hWnd;
		static Glui_ColDiаlog ColDial;
		static Glui_MessageBox MsgBox;
		static void(*WinProc)(Glui_Event, std::string);
		static void(*KeyboardFunc_ptr)(unsigned char, int, int);
		static void(*SpecialFunc_ptr)(int, int, int);
		static void(*MouseFunc_ptr)(int, int, int, int);
		static void(*MotionFunc_ptr)(int, int);
		static void(*PassiveMotionFunc_ptr)(int, int);
		static void(*MouseWheelFunc_ptr)(int, int, int, int);
		static void(*KeyboardUpFunc_ptr)(unsigned char, int, int);
		static void(*SpecialUpFunc_ptr)(int, int, int);
		static void(*PositionFunc_ptr)(int, int);
		static void(*ReshapeFunc_ptr)(int, int); 
		friend class Glui_Forms;
	private:
		static void AddForm();
		static void KeyboardFunc(unsigned char key, int ax, int ay);
		static void SpecialFunc(int key, int ax, int ay);
		static void MouseFunc(int button, int state, int ax, int ay);
		static void MotionFunc(int ax, int ay);
		static void PassiveMotionFunc(int ax, int ay);
		static void MouseWheelFunc(int button, int state, int ax, int ay);
		static void KeyboardUpFunc(unsigned char key, int ax, int ay);
		static void SpecialUpFunc(int key, int ax, int ay);
		static void PositionFunc(int ax, int ay);
		static void ReshapeFunc(int aw, int ah);
		static Glui_Text _t;
	};

	typedef Glui_MainForm Jora;

	class Glui_Text
	{
	public:
		Glui_Text();
		~Glui_Text();
		//установка размера шрифта
		void Setfontsize(int _size);
		//установка размера шрифта
		void SetHeightText(int _h);
		//установка размера шрифта
		void SetWidthText(int _w);
		//печатает текст по заданным координатам
		void glText(float x, float y, const std::string txt, Glui_Color col = Black);
		//
		float Get_text_length(std::string txt);
		//устанавливает дескриптор контекста устройства
		void SetHDC(HDC* _hdc);
		void SetFont(std::string font_name);
	private:
		//создание шрифта 
		void bildfont();
		//удаление шрифта
		void KillFont();
		float W, H;
		HFONT font;
		int size_text;
		HDC* hdc;
		GLuint arial;
		std::string Font = "Arial";
	};

	//прямоугольник с закругленными краями
	class Glui_Roundrect :public Glui_IForms
	{
	public:
		Glui_Roundrect();
		Glui_Roundrect(std::string name) :Glui_Roundrect() { Name = name; }
		~Glui_Roundrect() {}
		virtual gleventstruct MouseFunc(int button, int state, int ax, int ay);
		virtual gleventstruct PassiveMotionFunc(int ax, int ay);
		virtual gleventstruct MotionFunc(float ax, float ay);
		virtual gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		virtual gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		virtual gleventstruct SpecialFunc(int key, int ax, int ay);
		virtual gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		virtual gleventstruct SpecialUpFunc(int key, int ax, int ay);
		virtual void Init();
	//	float angle;
		//радиус
		float R;
	};
	//окружность
	class Glui_Circle :public Glui_IForms
	{
	public:
		Glui_Circle();
		Glui_Circle(std::string name) :Glui_Circle() { Name = name; }
		~Glui_Circle() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Update();
		//радиус
		float R;
	protected:
	private:
		Glui_Size Size;
	};
	//прямоугольник 
	class Glui_Rectangle :public Glui_IForms
	{
	public:
		Glui_Rectangle();
		Glui_Rectangle(std::string name) :Glui_Rectangle() { Name = name; }
		~Glui_Rectangle() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void SetHDC(HDC* _hdc);
		void Set_text_size(float _size);
		Glui_Color Text_color;
		Glui_Alignment Text_align = Bottom_center;
		std::string Text;
	private:
		float Text_size;
	protected:
		Glui_Text textprint;
	};
	typedef Glui_Rectangle Glui_Button;
	//полоса прокрутки(ползунок)
	class Glui_Skrollbar :public Glui_IForms
	{
	public:
		Glui_Skrollbar();
		Glui_Skrollbar(std::string name) :Glui_Skrollbar() { Name = name; };
		~Glui_Skrollbar() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		//шаг вперед
		float Step_forward();
		//шаг назад
		float Step_ago();
		//минимальная позиция
		int Min;
		//максимальная позиция
		int Max;
		//размер сдвига 
		int Step;
		//цвет ползунка
		Glui_Color Color_slider;
		//установить длину ползунка
		void Set_Slider_length(float length);
		//установить позицию ползунка 
		float Set_Position(float position);
		//возвращает позицию ползунка 
		float Get_Position();		
		void Update();
	private:
		int passiv_hover = 0;
		float Slider_length, Position_p, Px, Mx;
		bool Move_slider;
	protected:
	};
	//флажок
	class Glui_Checkbox :public Glui_IForms
	{
	public:
		Glui_Checkbox();
		Glui_Checkbox(std::string name):Glui_Checkbox() { Name = name;}
		~Glui_Checkbox() {}
		virtual gleventstruct MouseFunc(int button, int state, int ax, int ay);
		virtual gleventstruct PassiveMotionFunc(int ax, int ay);
		virtual gleventstruct MotionFunc(float ax, float ay);
		virtual gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		virtual gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		virtual gleventstruct SpecialFunc(int key, int ax, int ay);
		virtual gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		virtual gleventstruct SpecialUpFunc(int key, int ax, int ay);
		virtual void Init();
		//ширина линий контура
		float Line_length;
		std::string Text;
		void Set_text_size(float _size);
		bool Checked;
	private:
		void SetHDC(HDC* _hdc);
		Glui_Text textprint;
		float Text_size;
	};
	//Прогресс бар
	class Glui_Progressbar :public Glui_IForms
	{
	public:
		Glui_Progressbar();
		Glui_Progressbar(std::string name) :Glui_Progressbar() { Name = name; }
		~Glui_Progressbar() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		int Step_forward();
		//шаг назад
		int Step_ago();
		//длина шага
		int Step = 10;
		//
		Glui_Color BorderColor = Green;
		//минимальная позиция
		int Min = 0;
		//максимальная позиция
		int Max = 100;
		//позиция 
		int PositionBar = 0;
	private:
		float Pos = 0.0f;
	};
	//Поле для ввода
	class Glui_Textbox :public Glui_IForms
	{
	public:
		Glui_Textbox();
		Glui_Textbox(std::string name) :Glui_Textbox() { Name = name; };
		~Glui_Textbox() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Set_text_size(float _size);
		void SetHDC(HDC* _hdc);
		bool NumbersOnly = 0;
		bool Read_only = false;
		int Text_max_length = 0;
		//Цвет текста
		Glui_Color Text_color = Black;
		//Цвет выделенного
		Glui_Color Selection_color = Iron;
		//Текст
		std::string Text;
		friend class Glui_Combobox;
	private:
		bool Cursor_enbl;
		unsigned int Cursor_time;
	protected:
		bool Shift_press = 0;
		int	text_pos_begin = 0;
		int Select_begin = 0, Select_end = 0;
		int Cursor_pos = 0;
		float Text_size;
		Glui_Text textprint;		
	};
	//Комбинированный список
	class Glui_Combobox :public Glui_IForms
	{
	public:
		Glui_Combobox();
		Glui_Combobox(std::string name) :Glui_Combobox() { Name = name; };
		~Glui_Combobox() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		Glui_Color Color_select = Green;
		std::vector<std::string> Items;
		int Select = 0;
		int MaxDropDownItems;
		void Set_text_size(float _size);
		void Update();
	private:
		int hover_index = 0;
		Glui_Textbox tbox;
		Glui_Skrollbar Skroll;
		int Select_temp;
		int Select_min;
		bool open;
		int Text_size;
		void initiation();
		void SetHDC(HDC* _hdc);
	};	
	//листбокс
	class Glui_Listbox :public Glui_IForms
	{
	public:
		Glui_Listbox();
		Glui_Listbox(std::string name) :Glui_Listbox() { Name = name; }
		~Glui_Listbox() {};
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Set_text_size(float _size);
		std::string Get_Selected_text();
		void SetHDC(HDC* _hdc);
		Glui_Color Text_color;
		std::vector<std::string> Items;
		int Selected = -1;
		Glui_Color Select_color = Lightsteelblue;
	protected:
		Glui_Skrollbar Skrol;
		float Text_size = 12;
		Glui_Text textprint;
		int item_up_num = 0;
	};
	//
	class Glui_Numericupdown :public Glui_Textbox
	{
	public:
		Glui_Numericupdown();
		Glui_Numericupdown(std::string name) :Glui_Numericupdown() { Name = name; }
		~Glui_Numericupdown() {}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		void Init();
		int SetMax(int max){ return Max = max; }
		int SetMin(int min){ return Min = min; }
		int GetMin() { return Min; }
		int GetMax() { return Max; }
	private:
		int Max = 100, Min = 0;
		bool Mouse_in_button_up = 0;
		bool Mouse_in_button_down = 0;
	};
	//сохранение параметров (имя,значения)
	class Glui_Config
	{
	public:
		Glui_Config(std::string file_name);
		Glui_Config();
		~Glui_Config();
		bool Open(std::string file_name = "");
		bool is_open() { return _is_open; }
		bool Get_count(std::string name, int& count);
		bool Get_color(std::string name, Glui_Color& col);
		bool Set_count(std::string name, int count, bool _save = 0);
		bool Set_color(std::string name, Glui_Color col, bool _save = 0);
		bool Save(std::string file_name = "");
		bool Add_item(std::string name, int count);
		bool Erase_item(std::string name);
		bool Clear();
		friend Glui_Color;
	private:
		std::vector<string_int> Data;
		bool _is_open;
		std::string _file_name;
	};
	
	class Glui_Picture :public Glui_IForms
	{
	public:
		Glui_Picture();
		Glui_Picture(std::string name) : Glui_Picture() { Name = name; }
		~Glui_Picture() {}
		std::vector<std::vector<Point>> points;
		std::vector<Layer> layers;
		std::string file_name;
		void Init();
		bool Open(std::string _file_name);
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
	protected:
		float w_p = 0, h_p = 0;
		void Line_init(Guil_Primitives prim, float length = 1);
	};
	//диалоговое окно выбора цвета
	class Glui_ColDiаlog : public Glui_IForms
	{
	public:
		Glui_ColDiаlog();
		Glui_ColDiаlog(std::string name) :Glui_ColDiаlog() { Name = name; }
		~Glui_ColDiаlog(){}
		void Init();
		void Diolog(Glui_Color* col, std::string _title = "Defoult");
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct KeyboardFunc(unsigned char key, int x, int y);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void SetHDC(HDC* _hdc);
		Glui_Language Language = Gl_LanguageEN;
	private:
		bool lp = 0;
		int l = 0;
		Glui_Numericupdown num[4];
		Glui_Text textprint;
		bool Made_color, spector, is_cur_move, is_cur2_move, is_cur3_move;
		int act = 0;
		Glui_Color* Color_result = NULL;
		Glui_Color Color_temp;
		float Win_fon_H = 30.0f, h, cur2_h, cur3_h;
		float M_x, M_y, c_x, c_y;
		std::string Title;
		void D_color(float x, float y, float _h);
		Glui_Color Color_spector(float x, float y);
		void spector_print(float x, float y, float w, float h);
		void cursor(float x, float y);
		void brightness(float x, float y, float h, float cur_h, Glui_Color col);
		void updatenum();
		const std::string Text_en_ru_dialog[2][4] = {	"Изменение палитры",	"Основные цвета",	"Палитра",	"ОК",
														"Change the palette",	"Recen colors",		"Palette",	"OK" };
	}; 

	class Glui_Physics :virtual public Glui_Obj
	{
	public:
		Glui_Physics() {}
		~Glui_Physics() {}
		//скорость
		float Velocity = 1;
		//направление  скорости в градусах
		float V_angle = 0;
		//ускорение
		float Accelaction = 0;
		//направление ускорения в градусах
		float  A_angle = 0;
		//сила свободного падения 
		float Grav = 10;
		//масса
		float Mass = 1;
		void Move();
		void Gravity();
		void Rotate(float _alpha);
		void Bounce_X() { Bounce1(1); }
		void Bounce_Y() { Bounce1(0); }
		//нижняя позиция падения
		float Ground_h = 0;
		//сила трения
		float Friction_force = 0;
		//координата центра тяжести
		float Cmass_x = 0, Cmass_y = 0;
		//угловая скорость (градус/секунд)
		float Angular_V = 0;
	private:
		float Get_min_Y();
		//Скорость по X
		float  vx = 0;
		//Скорость по Y
		float  vy = 0;
		//Ускорение по X
		float  ax = 0;
		//Ускорение по Y
		float  ay = 0;
		void Bounce1(int a);
	};

	class Glui_MessageBox: public Glui_IForms
	{
	public:
		Glui_MessageBox();
		Glui_MessageBox(std::string name) :Glui_MessageBox() { Name = name; }
		~Glui_MessageBox(){}
		gleventstruct MouseFunc(int button, int state, int ax, int ay);
		gleventstruct PassiveMotionFunc(int ax, int ay);
		gleventstruct MotionFunc(float ax, float ay);
		gleventstruct MouseWheelFunc(int button, int state, int ax, int ay);
		gleventstruct KeyboardFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialFunc(int key, int ax, int ay);
		gleventstruct KeyboardUpFunc(unsigned char key, int ax, int ay);
		gleventstruct SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Show(std::string text, std::string title = "", Glui_MsgBoxButton _buttons = Gl_ButtonOK);
		void SetHDC(HDC* _hdc);
		Glui_Color Panel_color = Deepskyblue;
		Glui_Color Button_color = Deepskyblue;
		friend class Glui_MainForm;
		Glui_Language Language = Gl_LanguageEN;
	private:
		std::vector<std::string> Base_Text;
		bool lp = 0;
		int l = 0;
		bool Visible = 0;
		Glui_Rectangle panel;
		Glui_Rectangle exit;
		Glui_Rectangle B_ok;
		Glui_Rectangle B_no;
		Glui_Rectangle B_cancel;
		float Win_fon_H = 30.0f;
		std::string Text;
		Glui_Text textprint;
		const std::string Text_en_ru[2][3] = {	"   NO", "   OK",	"Concel",
												"  Нет", "   Да","Отмена" };
	};

}//end_namespace_easyGL
#endif EASY_OPENGL_H_ //конец if