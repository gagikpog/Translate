#ifndef UIGLRECTANGLE_H
#define UIGLRECTANGLE_H

#include "../uiglIForms.h"
#include "../uiglText.h"

namespace UIGL {
	//прямоугольник 
	class UiglRectangle :public UiglIForms
	{
	public:
		UiglRectangle();
		UiglRectangle(std::string name) :UiglRectangle() { Name = name; }
		~UiglRectangle() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void SetHDC(HDC* _hdc);
		void Set_text_size(float _size);
		UiglColor Text_color;
		uiglAlignments Text_align = uiglBottomCenter;
		std::string Text;
	private:
		float Text_size;
	protected:
		UiglText textprint;
	};

	typedef UiglRectangle uiglButton;
}
#endif // !UIGLRECTANGLE_H