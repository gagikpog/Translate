#include "uiglPosition.h"
#include "uiglObj.h"

#pragma region uiglPosition
namespace UIGL {
	void uiglPosition::setPosition(float Xvalue, float Yvalue, float Zvalue)
	{
		X = Xvalue;
		Y = Yvalue;
		Z = Zvalue;
		if (UpdatePtr != nullptr)
			UpdatePtr->Update();
	}
	void uiglPosition::setPosition(const Vector3f& value)
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		if (UpdatePtr != nullptr)
			UpdatePtr->Update();
	}
	void uiglPosition::setPosition(const Vector2f& value)
	{
		X = value.X;
		Y = value.Y;
		Z = 0;
		if (UpdatePtr != nullptr)
			UpdatePtr->Update();
	}
}
#pragma endregion