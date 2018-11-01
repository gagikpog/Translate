#include "uigl.h"
#include <sstream>
#include <string>
#include <stdexcept>

#ifndef UIGL_UF
#define UIGL_UF
namespace UIGL
{
	float rotate_x(float x, float y, float alpha);
	float rotate_y(float x, float y, float alpha);
	//прямоугольник с закругленными краями контур
	void drawRoundrectContour(float X, float Y, float W, float H, float R, UiglColor Outline_color = Black, float _angle = 0, float line_width = 1);
	//прямоугольник с закругленными краями
	void drawRoundrect(float X, float Y, float W, float H, float R, UiglColor Color, UiglColor Outline_color = Black, float _angle = 0, bool glossy = 1, float line_width = 1);
	//окружность контур
	void drawCircleContour(float X, float Y, float R, UiglColor Outline_color = Black, float line_width = 1);
	//окружность
	void drawCircle(float X, float Y, float R, UiglColor Color, UiglColor Outline_color = Black, float line_width = 1);

	void drawRectangleContour(float X, float Y, float W, float H, UiglColor Outline_color = Black, float _angle = 0, float line_width = 1);
	//прямоугольник
	void drawRectangle(float X, float Y, float W, float H, UiglColor Color, UiglColor Outline_color = Black, float _angle = 0, bool glossy = 1, float line_width = 1);
	//круг контур
	void drawCircleContour(float X, float Y, float r, float R, UiglColor Color, UiglColor Outline_color = Black);
	//многоугольник
	void drawPolygonContour(float X, float Y, float R, int Sides, UiglColor Outline_color = Black, float initial_angle = 0, float line_width = 1);
	//многоугольник
	void drawPolygon(float X, float Y, float R, int Sides, UiglColor Color, UiglColor Outline_color = Black, float initial_angle = 0, float line_width = 1);
	
	char *str_cpy(char *l, const char *r);
} // namespace GLUI

namespace std {
	template<typename T>
	std::string to_string(T arg)
	{
		std::stringstream res;
		res << arg;
		return res.str();
	}
}
#endif