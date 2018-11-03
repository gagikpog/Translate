#ifndef UIGLPROGRESSBAR_H
#define UIGLPROGRESSBAR_H

#include "../uiglIForms.h"
#include "../uiglFunc.h"

namespace UIGL {

	//Прогресс бар
	class uiglProgressbar :public UiglIForms
	{
	public:
		uiglProgressbar();
		uiglProgressbar(std::string name) :uiglProgressbar() { Name = name; }
		~uiglProgressbar() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		int Step_forward();
		//шаг назад
		int Step_ago();
		//длина шага
		int Step = 10;
		//
		UiglColor BorderColor = Green;
		//минимальная позиция
		int Min = 0;
		//максимальная позиция
		int Max = 100;
		//позиция 
		int PositionBar = 0;
	private:
		float Pos = 0.0f;
	};
}
#endif // !UIGLPROGRESSBAR_H