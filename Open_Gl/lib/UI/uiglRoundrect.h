#ifndef UIGLROUNDRECT_H
#define UIGLROUNDRECT_H

#include "../uigl.h"
#include "../uiglIForms.h"

namespace UIGL {
	//прямоугольник с закругленными краями
	class UiglRoundrect :public UiglIForms
	{
	public:
		UiglRoundrect();
		UiglRoundrect(std::string name) :UiglRoundrect() { Name = name; }
		~UiglRoundrect() {}
		virtual UiglEvent MouseFunc(int button, int state, int ax, int ay);
		virtual UiglEvent PassiveMotionFunc(int ax, int ay);
		virtual UiglEvent MotionFunc(float ax, float ay);
		virtual UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		virtual UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		virtual UiglEvent SpecialFunc(int key, int ax, int ay);
		virtual UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		virtual UiglEvent SpecialUpFunc(int key, int ax, int ay);
		virtual void Init();
		//	float angle;
		//радиус
		float R;
	};
}
#endif //UIGLROUNDRECT_H!