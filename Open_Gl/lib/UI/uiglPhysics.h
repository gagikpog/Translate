#ifndef UIGLPHYSICS_H
#define UIGLPHYSICS_H

#include "../uiglObj.h"

namespace UIGL {
	class UiglPhysics :virtual public UiglObj
	{
	public:
		UiglPhysics() {}
		~UiglPhysics() {}
		//��������
		float Velocity = 1;
		//�����������  �������� � ��������
		float V_angle = 0;
		//���������
		float Accelaction = 0;
		//����������� ��������� � ��������
		float  A_angle = 0;
		//���� ���������� ������� 
		float Grav = 10;
		//�����
		float Mass = 1;
		void Move();
		void Gravity();
		void Rotate(float _alpha);
		void Bounce_X() { Bounce1(1); }
		void Bounce_Y() { Bounce1(0); }
		//������ ������� �������
		float Ground_h = 0;
		//���� ������
		float Friction_force = 0;
		//���������� ������ �������
		float Cmass_x = 0, Cmass_y = 0;
		//������� �������� (������/������)
		float Angular_V = 0;
	private:
		float Get_min_Y();
		//�������� �� X
		float  vx = 0;
		//�������� �� Y
		float  vy = 0;
		//��������� �� X
		float  ax = 0;
		//��������� �� Y
		float  ay = 0;
		void Bounce1(int a);
	};
}
#endif // !UIGLPHYSICS_H