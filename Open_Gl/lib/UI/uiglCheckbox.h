#ifndef UIGLCHECKBOX_H
#define UIGLCHECKBOX_H

#include "../uiglIForms.h"
#include "../uiglText.h"

namespace UIGL {

	//флажок
	class UiglCheckbox :public UiglIForms
	{
	public:
		UiglCheckbox();
		UiglCheckbox(std::string name) :UiglCheckbox() { Name = name; }
		~UiglCheckbox() {}
		virtual UiglEvent MouseFunc(int button, int state, int ax, int ay);
		virtual UiglEvent PassiveMotionFunc(int ax, int ay);
		virtual UiglEvent MotionFunc(float ax, float ay);
		virtual UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		virtual UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		virtual UiglEvent SpecialFunc(int key, int ax, int ay);
		virtual UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		virtual UiglEvent SpecialUpFunc(int key, int ax, int ay);
		virtual void Init();
		//ширина линий контура
		float Line_length;
		std::string Text;
		void Set_text_size(float _size);
		bool Checked;
	private:
		void SetHDC(HDC* _hdc);
		UiglText textprint;
		float Text_size;
	};
}
#endif // !UIGLCHECKBOX_H