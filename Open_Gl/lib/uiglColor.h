#ifndef UIGLCOLOR_H

#include <GL/freeglut.h>

#define UIGLCOLOR_H
#define BYTE unsigned char

namespace UIGL
{
	//перечисление цветов 
	enum uiglColornum {
		Black, White, Red, Green, Blue, Cyan, Magenta, Yellow, Water, Plastic, Glass, Diamond, Iron, Copper, Gold, Aluminum, Silver, Deepskyblue,
		Lightskyblue, Mistyrose, Burlywood, Violet, Whitesmoke, Lime, Tan, Lightgray, Lightsteelblue, Yellowgreen, Orange, Coral, Fuchsia, Dodgerblue,
		Plum, Limegreen, Olive, Darkmagenta, Gray, Dimgray, Brown, Darkslategray, Firebrick, Sienna, Maroon, Darkblue, Navy, Other
	};

	//глют цвета
	class UiglColor
	{
	public:
		UiglColor(BYTE red, BYTE green, BYTE blue, BYTE alpha = 255);
		UiglColor(const uiglColornum& _color = Black);
		UiglColor(const UiglColor& _color);
		//UiglColor();
		~UiglColor() {}
		//установка цвета
		UiglColor& setColor(const uiglColornum& _color);
		UiglColor& setColor(const UiglColor& _color);
		//установка цвета
		UiglColor& setColor(BYTE _red, BYTE _green, BYTE _blue, BYTE _alpha = 255);
		//установка прозрачности
		UiglColor& setAlpha(const BYTE& _alpha);
		//определяет цвет отрисовки
		void Init(short bright = 0, BYTE _alpha = 0)const;
		//Возвращает цвета в uint
		unsigned int getUInt()const;
		//переобразует uint в цвета RGBA
		UiglColor& setUInt(unsigned int count);
		//возвращает цвет в негативе
		UiglColor getNegative()const;
		//не меняет значение
		UiglColor operator+(int _c)const;
		//не меняет значение
		UiglColor operator-(int _c)const;
		bool operator==(const uiglColornum& _col)const;
		bool operator==(const UiglColor& _col)const;
		UiglColor operator+(const UiglColor& operator2)const;
		UiglColor operator-(const UiglColor& operator2)const;
		//static
		static unsigned int ColorToUInt(UiglColor color);
		static UiglColor UIntToColor(unsigned int intValue);
		
		friend class UiglColDiаlog;
	private:
	protected:
		UiglColor bildColor(uiglColornum _Color)const;
		uiglColornum  Color;
		BYTE R, G, B, A;
	};
}
#endif // !UIGLCOLOR_H
