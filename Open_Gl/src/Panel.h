#ifndef PANEL_H
#define PANEL_H

#include "../lib/freeuigl.h"

class Panel :public UIGL::UiglIForms
{
public:
	Panel()
	{
		is_move = 0;
		IsHover = 0;
		Position.UpdatePtr = this;
		Size.UpdatePtr = this;
	}
	~Panel() {}
	UIGL::UiglEvent MouseFunc(int button, int state, int ax, int ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent PassiveMotionFunc(int ax, int ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent MotionFunc(float ax, float ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent MouseWheelFunc(int button, int state, int ax, int ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent KeyboardFunc(unsigned char key, int ax, int ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent SpecialFunc(int key, int ax, int ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay) { return UIGL::UiglEvent(); }
	UIGL::UiglEvent SpecialUpFunc(int key, int ax, int ay) { return UIGL::UiglEvent(); }
	void Init()
	{
		UIGL::drawRectangle(X, Y, W, H, Color, Outline_color);
	}
};

#endif // !PANEL_H