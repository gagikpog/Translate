#ifndef UIGLSIZE_H
#define UIGLSIZE_H
#include <cstdlib>

namespace UIGL {

	class UiglObj;

	struct uiglSize
	{
		void setSize(float width, float height, float depth = 0);
		float getSizeW() const { return W; }
		float getSizeH() const { return H; }
		float getSizeD() const { return D; }
		UiglObj* UpdatePtr = NULL;
	private:
		float W = 10, H = 10, D = 0;
	};
}
#endif // !UIGLSIZE_H

