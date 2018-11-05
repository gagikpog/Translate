#ifndef UIGLFORM_H
#define UIGLFORM_H

#include <vector>
#include <list>

#include "uiglIForms.h"
namespace UIGL {

	class UiglForms
	{
	public:
		UiglForms();
		UiglForms(bool add_in_main_forms);
		~UiglForms() {}
		static std::vector<UiglForms*> Forms;
		void MouseWheelFunc_g(int button, int state, int ax, int ay);
		void PassiveMotionFunc_g(int ax, int ay);
		void MotionFunc_g(int ax, int ay);
		void MouseFunc_g(int button, int state, int ax, int ay);
		void KeyboardFunc_g(unsigned char key, int ax, int ay);
		void SpecialFunc_g(int key, int ax, int ay);
		void KeyboardUpFunc_g(unsigned char key, int ax, int ay);
		void SpecialUpFunc_g(int key, int ax, int ay);
		virtual void ReshapeFunc_g(int aw, int ah) {}
		void Init_g(bool OnlyFocus = 0, bool clear_background = true);
		//принимает ссылку на объект класса UiglIForms
		void Focus_push_back(UiglIForms* func);
		void Focus_pop_back();
		void Focus_erase(int num);
		void Stec_erase(int num);
		//принимает ссылку на объект класса UiglIForms
		void Stec_push_back(UiglIForms* func);
		void Stec_pop_back();
		//устанавливает дескриптор контекста устройства
		void SetHDC(HDC* _hdc_);
		UiglColor Background_color = White;
		//0==disable, 1==enable, 2==(disable+(Init==enable))
		int Enabled = 1;//
		void(*Wnd_proc)(uiglEvents, std::string);
	private:
		void Set_Focus();
		int in_focus = 0;
		std::list<UiglIForms*>Stec;
		std::vector<UiglIForms*>Focus;
		HDC* _hdc;
		bool Shift_press;
	};
}
#endif // !UIGLFORM_H