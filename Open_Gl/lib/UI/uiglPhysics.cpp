#include "uiglPhysics.h"
#include "../uiglFunc.h"

namespace UIGL {

	void UiglPhysics::Move()
	{
		Rotate(Angular_V);
		if (Velocity > 0)
			Velocity -= Friction_force;
		else if (Velocity != 0) Velocity += Friction_force;

		vx = std::cosf(V_angle*PI / 180)*Velocity;
		vy = std::sinf(V_angle*PI / 180)*Velocity;
		ax = std::cosf(A_angle*PI / 180)*Accelaction;
		ay = std::sinf(A_angle*PI / 180)*Accelaction;

		vx += ax;
		vy += ay;

		if (vx || vy)
			V_angle = std::atan2f(vy, vx) * 180 / PI;
		else V_angle = 0;
		Velocity = sqrtf(vx*vx + vy*vy);
		X += vx;
		Y += vy;
	}
	void UiglPhysics::Gravity()
	{
		if (Y - Grav > Ground_h)
		{
			vy = std::sinf(V_angle*PI / 180)*Velocity;
			vx = std::cosf(V_angle*PI / 180)*Velocity;

			vy -= Grav;

			if (vx || vy)
				V_angle = std::atan2f(vy, vx) * 180 / PI;
			else V_angle = 0;
			Velocity = sqrtf(vx*vx + vy*vy);
		}
		else
		{
			vy = -vy;

			if (vx || vy)
				V_angle = std::atan2f(vy, vx) * 180 / PI;
			else V_angle = 0;
			Velocity = sqrtf(vx*vx + vy*vy);

		}

		Move();
		if (Get_min_Y() < Ground_h)
			Y += Ground_h - Get_min_Y();
	}
	void UiglPhysics::Rotate(float _alpha)
	{
		X += Cmass_x - rotate_x(Cmass_x, Cmass_y, _alpha);
		Y += Cmass_y - rotate_y(Cmass_x, Cmass_y, _alpha);
		Cmass_x = rotate_x(Cmass_x, Cmass_y, _alpha);
		Cmass_y = rotate_y(Cmass_x, Cmass_y, _alpha);
		Angle += _alpha;
	}
	float UiglPhysics::Get_min_Y()
	{
		float  min = Y;
		if (Angle > 90 && Angle < 360)
			min = Y - Cmass_y;

		return min;
	}
	void UiglPhysics::Bounce1(int a)
	{
		vx = std::cosf(V_angle*PI / 180)*Velocity;
		vy = std::sinf(V_angle*PI / 180)*Velocity;
		if (a)
			vx = -vx;
		else
			vy = -vy;

		if (vx || vy)
			V_angle = std::atan2f(vy, vx) * 180 / PI;
		else V_angle = 0;
		Velocity = sqrtf(vx*vx + vy*vy);
	}
}