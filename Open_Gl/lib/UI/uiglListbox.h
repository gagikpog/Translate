#ifndef UIGLLISTBOX

#include "../uiglIForms.h"
#include "uiglSkrollbar.h"
#include "../uiglText.h"

namespace UIGL {
	//листбокс
	class UiglListbox :public UiglIForms
	{
	public:
		UiglListbox();
		UiglListbox(std::string name) :UiglListbox() { Name = name; }
		~UiglListbox() {};
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Set_text_size(float _size);
		std::string Get_Selected_text();
		void SetHDC(HDC* _hdc);
		UiglColor Text_color;
		std::vector<std::string> Items;
		int Selected = -1;
		UiglColor Select_color = Lightsteelblue;
	protected:
		UiglSkrollbar Skrol;
		float Text_size = 12;
		UiglText textprint;
		int item_up_num = 0;
	};
}
#endif // !UIGLLISTBOX