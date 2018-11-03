#ifndef UIGLNUMERICUPDOWN_H
#define UIGLNUMERICUPDOWN_H

#include "uiglTextbox.h"

namespace UIGL {
	//
	class UiglNumericupdown :public UiglTextbox
	{
	public:
		UiglNumericupdown();
		UiglNumericupdown(std::string name) :UiglNumericupdown() { Name = name; }
		~UiglNumericupdown() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		void Init();
		int SetMax(int max) { return Max = max; }
		int SetMin(int min) { return Min = min; }
		int GetMin() { return Min; }
		int GetMax() { return Max; }
	private:
		int Max = 100, Min = 0;
		bool Mouse_in_button_up = 0;
		bool Mouse_in_button_down = 0;
	};
}
#endif // ! UIGLNUMERICUPDOWN_H