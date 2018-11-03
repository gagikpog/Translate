#ifndef UIGLCOMBOBOX_H
#define UIGLCOMBOBOX_H

#include "../uiglIForms.h"
#include "uiglSkrollbar.h"
#include "uiglTextbox.h"

namespace UIGL {
	//Комбинированный список
	class UiglCombobox :public UiglIForms
	{
	public:
		UiglCombobox();
		UiglCombobox(std::string name) :UiglCombobox() { Name = name; };
		~UiglCombobox() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		UiglColor Color_select = Green;
		std::vector<std::string> Items;
		int Select = 0;
		int MaxDropDownItems;
		void Set_text_size(float _size);
		void Update();
	private:
		int hover_index = 0;
		UiglTextbox tbox;
		UiglSkrollbar Skroll;
		int Select_temp;
		int Select_min;
		bool open;
		int Text_size;
		void initiation();
		void SetHDC(HDC* _hdc);
	};
}
#endif // !UIGLCOMBOBOX_H