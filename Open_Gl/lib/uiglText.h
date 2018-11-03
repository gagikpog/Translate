#include <Windows.h>
#include <string>
#include "uiglColor.h"

#ifndef UIGLTEXT_H
#define UIGLTEXT_H
namespace UIGL {

	class UiglText
	{
	public:
		UiglText();
		~UiglText();
		//установка размера шрифта
		void setFontSize(int _size);
		//установка размера шрифта
		void setHeightText(int _h);
		//установка размера шрифта
		void setWidthText(int _w);
		//печатает текст по заданным координатам
		void glText(float x, float y, const std::string txt, UiglColor col = Black);
		//
		float getTextLength(std::string txt);
		//устанавливает дескриптор контекста устройства
		void setHDC(HDC* _hdc);
		void setFont(std::string font_name);
	private:
		//создание шрифта 
		void BildFont();
		//удаление шрифта
		void KillFont();
		float W, H;
		HFONT font;
		int size_text;
		HDC* hdc;
		GLuint arial;
		std::string Font = "Arial";
	};
}
#endif // !UIGLTEXT_H