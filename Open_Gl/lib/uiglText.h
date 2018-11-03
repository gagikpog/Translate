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
		//��������� ������� ������
		void setFontSize(int _size);
		//��������� ������� ������
		void setHeightText(int _h);
		//��������� ������� ������
		void setWidthText(int _w);
		//�������� ����� �� �������� �����������
		void glText(float x, float y, const std::string txt, UiglColor col = Black);
		//
		float getTextLength(std::string txt);
		//������������� ���������� ��������� ����������
		void setHDC(HDC* _hdc);
		void setFont(std::string font_name);
	private:
		//�������� ������ 
		void BildFont();
		//�������� ������
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