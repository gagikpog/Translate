#ifndef UIGLCOLDIALOG_H
#define UIGLCOLDIALOG_H

#include <string>

#include "../uiglIForms.h"
#include "uiglNumericupdown.h"

namespace UIGL {
	//äèàëîãîâîå îêíî âûáîğà öâåòà
	class UiglColDiàlog : public UiglIForms
	{
	public:
		UiglColDiàlog();
		UiglColDiàlog(std::string name) :UiglColDiàlog() { Name = name; }
		~UiglColDiàlog() {}
		void Init();
		void Diolog(UiglColor* col, std::string _title = "Defoult");
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent KeyboardFunc(unsigned char key, int x, int y);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void SetHDC(HDC* _hdc);
		uiglLanguages Language = uiglLanguageEN;
	private:
		bool lp = 0;
		int l = 0;
		UiglNumericupdown num[4];
		UiglText textprint;
		bool Made_color, spector, is_cur_move, is_cur2_move, is_cur3_move;
		int act = 0;
		UiglColor* Color_result = NULL;
		UiglColor Color_temp;
		float Win_fon_H = 30.0f, h, cur2_h, cur3_h;
		float M_x, M_y, c_x, c_y;
		std::string Title;
		void D_color(float x, float y, float _h);
		UiglColor Color_spector(float x, float y);
		void spector_print(float x, float y, float w, float h);
		void cursor(float x, float y);
		void brightness(float x, float y, float h, float cur_h, UiglColor col);
		void updatenum();
		const std::string Text_en_ru_dialog[2][4] = { "Èçìåíåíèå ïàëèòğû",	"Îñíîâíûå öâåòà",	"Ïàëèòğà",	"ÎÊ",
			"Change the palette",	"Recen colors",		"Palette",	"OK" };
	};

}
#endif // !UIGLCOLDIALOG_H
