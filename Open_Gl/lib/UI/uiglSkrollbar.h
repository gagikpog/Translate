#ifndef UIGLSCROLLBAR_H
#define UIGLSCROLLBAR_H

#include "../uiglIForms.h"

namespace UIGL {
	
	//������ ���������(��������)
	class UiglSkrollbar :public UiglIForms
	{
	public:
		UiglSkrollbar();
		UiglSkrollbar(std::string name) :UiglSkrollbar() { Name = name; };
		~UiglSkrollbar() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		//��� ������
		float Step_forward();
		//��� �����
		float Step_ago();
		//����������� �������
		int Min;
		//������������ �������
		int Max;
		//������ ������ 
		int Step;
		//���� ��������
		UiglColor Color_slider;
		//���������� ����� ��������
		void Set_Slider_length(float length);
		//���������� ������� �������� 
		float Set_Position(float position);
		//���������� ������� �������� 
		float Get_Position();
		void Update();
	private:
		int passiv_hover = 0;
		float Slider_length, Position_p, Px, Mx;
		bool Move_slider;
	protected:
	};
}
#endif // !UIGLSCROLLBAR_H