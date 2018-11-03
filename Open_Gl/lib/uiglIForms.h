#ifndef UIGLIFORMS_H
#define UIGLIFORMS_H

#include "uiglObj.h"
#include "uiglColor.h"
#include "uigl.h"

namespace UIGL {
	class UiglIForms :virtual public UiglObj
	{
	public:
		UiglIForms() {}
		~UiglIForms() {}
		//��� ������� //���������� � ������� Wnd_proc
		std::string Name = "no_naem";
		//���� �������
		UiglColor Color = White;
		//���� �������
		UiglColor Outline_color = UiglColor(70, 70, 70, 255);
		bool IsHover = 1;
		bool Visible = 1;
		//���� ������, �� ��������� �������������� ������� �����
		bool is_move = 0;
		virtual UiglEvent MouseFunc(int button, int state, int ax, int ay) = 0;
		virtual UiglEvent PassiveMotionFunc(int ax, int ay) = 0;
		virtual UiglEvent MotionFunc(float ax, float ay) = 0;
		virtual UiglEvent MouseWheelFunc(int button, int state, int ax, int ay) = 0;
		virtual UiglEvent KeyboardFunc(unsigned char key, int ax, int ay) = 0;
		virtual UiglEvent SpecialFunc(int key, int ax, int ay) = 0;
		virtual UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay) = 0;
		virtual UiglEvent SpecialUpFunc(int key, int ax, int ay) = 0;
		virtual UiglEvent PositionFunc(int aw, int ah) { return UiglEvent(); }
		virtual UiglEvent ReshapeFunc(int ax, int ay) { return UiglEvent(); }
		//��������� ��������� �������
		virtual void Init() = 0;
		//������������� ���������� ��������� ����������
		virtual void SetHDC(HDC* _hdc) { hdc = _hdc; }

		friend class UiglForms;
		friend class UiglColDi�log;
	protected:
		//��������� �� ������ � ������
		bool in_focus = false;
		bool Mouse_in_button = 0, moved = 0;
		//����� ����������� ������� ���� � clock -��
		unsigned int double_ckick = 0;
		//������� ����� ����������� ���� � ����������� ������� �� ����� �������������� �������
		float  mx = 0, my = 0;
		//���������� ����
		HDC* hdc;
	};
}
#endif // !UIGLIFORMS_H