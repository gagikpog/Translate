/*
* User interface for graphics library
*/

#include <GL/freeglut.h>
#include <string>
#include "uiglColor.h"

#ifndef UIGL_H
#define UIGL_H

const float PI = 3.14159265358979323846f;

namespace UIGL
{
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
	enum class uiglEventsOld: unsigned int {
		uiglEventEmpty = 1, uiglEraseMsg = 2, uiglChanged = 4, uiglEnter = 8,
		uiglMouseLeftUp = 16,	uiglMouseCenterUp = 32,		uiglMouseRightUp = 64,
		uiglMouseLeftDown = 128,	uiglMouseCenterDown = 256,	uiglMouseRightDown = 1024,
		uiglMouseOver = 2048, uiglMouseOut = 4096, uiglMousemove = 8192, uiglWheelUp = 16384, uiglWheelDown = 32768, uiglDoubleClick = 65536,
		uiglMsgYes = 131072, uiglMsgNo = 262144, uiglMsgCancel = 524288
	};

	class uiglEvents
	{
	public:
		enum Events : unsigned int {
			uiglEventEmpty = 1, uiglEraseMsg = 2, uiglChanged = 4, uiglEnter = 8,
			uiglMouseLeftUp = 16, uiglMouseCenterUp = 32, uiglMouseRightUp = 64,
			uiglMouseLeftDown = 128, uiglMouseCenterDown = 256, uiglMouseRightDown = 1024,
			uiglMouseOver = 2048, uiglMouseOut = 4096, uiglMousemove = 8192, uiglWheelUp = 16384, uiglWheelDown = 32768, uiglDoubleClick = 65536,
			uiglMsgYes = 131072, uiglMsgNo = 262144, uiglMsgCancel = 524288
		};
		uiglEvents() {}
		uiglEvents(Events e) { ev = e; }
		~uiglEvents() {}
		uiglEvents operator|(const uiglEvents& a)const
		{
			uiglEvents res = Events((int)ev | (int)a.ev);
			return res;
		}
		uiglEvents operator&(const uiglEvents& a)const
		{
			uiglEvents res = Events((int)ev & (int)a.ev);
			return res;
		}
		bool operator==(const uiglEvents& a)
		{
			return (int)a.ev & (int)ev;
		}
		bool operator!=(const uiglEvents& a)
		{
			return (bool) ((int)a.ev & (int)ev) == 0;
		}
		friend std::ostream& operator<<(std::ostream& out, const uiglEvents& o)
		{
			out << o.ev;
			return out;
		}
		Events ev = Events::uiglEventEmpty;
	private:
	};
	
	inline uiglEvents::Events operator| (uiglEvents::Events t1, uiglEvents::Events t2) {
		return uiglEvents::Events(int(t1) | int(t2));
	}/*
	bool operator==(const UiglEvents_t& a, const UiglEvents_t& b)
	{
		return (int)a.ev & (int)b.ev;
	}*/

	/*using uiglEvents_t = std::underlying_type<uiglEvents>::type;
	inline uiglEvents_t operator& (uiglEvents t1, uiglEvents t2) {
		return static_cast<uiglEvents_t>(t1) & static_cast<uiglEvents_t>(t2);
	}
	inline uiglEvents_t operator| (uiglEvents t1, uiglEvents t2) {
		return static_cast<uiglEvents_t>(t1) | static_cast<uiglEvents_t>(t2);
	}
	bool UIGL::uiglEvents::operator==(UIGL::uiglEvents& a, UIGL::uiglEvents& b)
	{
		return a & b;
	}*/
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
		uiglEvents Event = UIGL::uiglEvents::uiglEventEmpty;
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