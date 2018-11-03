#include "uiglSize.h"
#include "uiglObj.h"

namespace UIGL {

	void uiglSize::setSize(float width, float height, float depth)
	{
		W = width;
		H = height;
		D = depth;
		if (UpdatePtr != nullptr)
			UpdatePtr->Update();
	}
}