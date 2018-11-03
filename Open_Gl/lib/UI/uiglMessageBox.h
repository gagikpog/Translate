#ifndef UIGLMESSAGEBOX_H
#define UIGLMESSAGEBOX_H

#include "../uiglIForms.h"
#include "uiglRectangle.h"
#include "../uiglText.h"

namespace UIGL {
///	class UiglRectangle;

	class UiglMessageBox : public UiglIForms
	{
	public:
		UiglMessageBox();
		UiglMessageBox(std::string name) :UiglMessageBox() { Name = name; }
		~UiglMessageBox() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Show(std::string text, std::string title = "", uiglMsgBoxButtons _buttons = uiglButtonOK);
		void SetHDC(HDC* _hdc);
		UiglColor Panel_color = Deepskyblue;
		UiglColor Button_color = Deepskyblue;
		friend class UiglMainForm;
		uiglLanguages Language = uiglLanguageEN;
	private:
		std::vector<std::string> Base_Text;
		bool lp = 0;
		int l = 0;
		bool Visible = 0;
		UiglRectangle panel;
		UiglRectangle exit;
		UiglRectangle B_ok;
		UiglRectangle B_no;
		UiglRectangle B_cancel;
		float Win_fon_H = 30.0f;
		std::string Text;
		UiglText textprint;
		const std::string Text_en_ru[2][3] = { "   NO", "   OK",	"Concel",
			"  Нет", "   Да","Отмена" };
	};
}
#endif // !UIGLMESSAGEBOX_H