#ifndef SETTINGSSTRUCT_H
#define SETTINGSSTRUCT_H

#include "lib\freeuigl.h"

struct SettingsStruct
{
	static UIGL::UiglColor ButtonsColor;
	static UIGL::UiglColor LinesColor;
	static UIGL::UiglColor SelectedColor;
	static UIGL::UiglColor TextsColor;
	static UIGL::UiglColor BackgroundColor;
	static int TestWordsCount;
};
static SettingsStruct Parameters;

#endif // !SETTINGSSTRUCT_H
