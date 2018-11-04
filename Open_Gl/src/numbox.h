#pragma once
#include "../lib/freeuigl.h"

class numbox :public UIGL::UiglNumericupdown
{
public:
	numbox() {}
	~numbox() {}
	void Init();
	std::string Title;
	UIGL::uiglAlignments Text_align = UIGL::uiglAlignments::uiglMiddleRight;
private:
};