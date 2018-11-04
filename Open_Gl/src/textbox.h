#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "../lib/freeuigl.h"

class textbox :public UIGL::UiglTextbox
{
public:
	textbox() {}
	~textbox() {}
	void Init();
	std::string Title;
	UIGL::uiglAlignments Text_align = UIGL::uiglAlignments::uiglMiddleRight;
private:
};
#endif // !TEXTBOX_H