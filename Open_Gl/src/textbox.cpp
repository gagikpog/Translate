#include "textbox.h"

void textbox::Init()

{
	float align_h = 0, align_w = 0;
	switch (Text_align)
	{
	case UIGL::uiglTopLeft:
	case UIGL::uiglTopCenter:
	case UIGL::uiglTopRight:
		align_h = H + 10;
		break;
	case UIGL::uiglMiddleLeft:
	case UIGL::uiglMiddleCenter:
	case UIGL::uiglMiddleRight:
		align_h = H*0.1f;
		break;
	case UIGL::uiglBottomLeft:
	case UIGL::uiglBottomCenter:
	case UIGL::uiglBottomRight:
		align_h = -Text_size - 5;
		break;
	}
	switch (Text_align)
	{
	case UIGL::uiglTopLeft:
	case UIGL::uiglMiddleLeft:
	case UIGL::uiglBottomLeft:
		align_w = -10;
		break;
	case UIGL::uiglMiddleCenter:
	case UIGL::uiglTopCenter:
	case UIGL::uiglBottomCenter:
		align_w = 5;
		break;
	case UIGL::uiglBottomRight:
	case UIGL::uiglTopRight:
	case UIGL::uiglMiddleRight:
		align_w = W + 10;
		break;
	}

	UiglTextbox::Init();
	UiglTextbox::textprint.glText(X + align_w, Y + align_h, Title, Text_color);
}