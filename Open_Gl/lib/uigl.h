/*
* User interface for graphics library
*/

#include <GL/freeglut.h>
#include <string>
#include "uiglColor.h"

#ifndef UIGL_H
#define UIGL_H

namespace UIGL
{
	const float PI = 3.14159265358979323846f;

	enum uiglAlignments
	{
		uiglTopLeft, uiglTopCenter, uiglTopRight,
		uiglMiddleLeft, uiglMiddleCenter, uiglMiddleRight,
		uiglBottomLeft, uiglBottomCenter, uiglBottomRight
	};
	//UIGL Drawing Primitives
	enum uiglPrimitives
	{
		uiglPOINTS = GL_POINTS,
		uiglLINES = GL_LINES,
		uiglLINE_LOOP = GL_LINE_LOOP,
		uiglLINE_STRIP = GL_LINE_STRIP,
		uiglTRIANGLES = GL_TRIANGLES,
		uiglTRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		uiglTRIANGLE_FAN = GL_TRIANGLE_FAN,
		uiglQUADS = GL_QUADS,
		uiglQUAD_STRIP = GL_QUAD_STRIP,
		uiglPOLYGON = GL_POLYGON
	};
	//Events
	enum uiglEvents {
		uiglEventEmpty, uiglEraseMsg, uiglChanged, uiglEnter,
		uiglMouseLeftUp,	uiglMouseCenterUp,		uiglMouseRightUp,
		uiglMouseLeftDown,	uiglMouseCenterDown,	uiglMouseRightDown,
		uiglMouseOver, uiglMouseOut, uiglMousemove, uiglWheelUp, uiglWheelDown, uiglDoubleClick,
		uiglMsgYes, uiglMsgNo, uiglMsgCancel
	};

	enum uiglMsgBoxButtons {
		uiglButtonOK, uiglButtonNO, uiglButtonCancel, uiglButtonOKNO, 
		uiglButtonOKCancel, uiglButtonNoCancel, uiglButtonOKNOCancel
	};

	enum uiglLanguages {
		uiglLanguageEN, uiglLanguageRU
	};

	enum uiglOrientations {
		uiglVertical, uiglHorizontal
	};

	struct UiglEvent
	{
		uiglEvents Event = uiglEventEmpty;
		std::string Name = "";
	};

	struct UiglPoint
	{
		float X = 0;
		float Y = 0;
		UiglColor Color;
	};
}
#endif