#ifndef  UIGLOBJ_H
#define UIGLOBJ_H

#include <vector>
#include "uiglPosition.h"
#include "uiglSize.h"

namespace UIGL {
	class UiglObj
	{
	public:
		UiglObj() {}
		~UiglObj() {}
		uiglPosition Position;
		uiglSize Size;
		float setAngle(float angle) { return Angle = angle; }
		float getAngle() { return Angle; }
		virtual void Update()
		{
			X = Position.getPositionX();
			Y = Position.getPositionY();
			H = Size.getSizeH();
			W = Size.getSizeW();
		}
	protected:
		std::vector<Vector2f> Points;
		//позиция X
		float X = 0.0f;
		//позиция Y
		float Y = 0.0f;
		float H = 10.0f;
		float W = 10.0f;
		//угол
		float Angle = 0.0f;
	};
}
#endif // ! UIGLOBJ_H