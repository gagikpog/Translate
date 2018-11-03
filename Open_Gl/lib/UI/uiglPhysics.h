#ifndef UIGLPHYSICS_H
#define UIGLPHYSICS_H

#include "../uiglObj.h"

namespace UIGL {
	class UiglPhysics :virtual public UiglObj
	{
	public:
		UiglPhysics() {}
		~UiglPhysics() {}
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
}
#endif // !UIGLPHYSICS_H