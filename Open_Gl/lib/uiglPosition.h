#ifndef UIGLPOSITION_H
#define UIGLPOSITION_H

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace UIGL {
	class UiglObj;

	struct uiglPosition
	{
		void setPosition(float Xvalue, float Yvalue, float Zvalue = 0);
		void setPosition(const Vector3f &value);
		void setPosition(const Vector2f &value);
		Vector2<float> getPosition2f() const { return Vector2<float>(X, Y); }
		Vector3<float> getPosition3f() const { return Vector3<float>(X, Y, Z); }
		float getPositionX() const { return X; }
		float getPositionY() const { return Y; }
		float getPositionZ() const { return Z; }
		UiglObj *UpdatePtr = NULL;
	private:
		float X = 0, Y = 0, Z = 0;
	};
}
#endif