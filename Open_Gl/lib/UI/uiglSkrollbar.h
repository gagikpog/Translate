#ifndef UIGLSCROLLBAR_H
#define UIGLSCROLLBAR_H

#include "../uiglIForms.h"

namespace UIGL {
	
	//полоса прокрутки(ползунок)
	class UiglSkrollbar :public UiglIForms
	{
	public:
		UiglSkrollbar();
		UiglSkrollbar(std::string name) :UiglSkrollbar() { Name = name; };
		~UiglSkrollbar() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		//шаг вперед
		float Step_forward();
		//шаг назад
		float Step_ago();
		//минимальная позиция
		int Min;
		//максимальная позиция
		int Max;
		//размер сдвига 
		int Step;
		//цвет ползунка
		UiglColor Color_slider;
		//установить длину ползунка
		void Set_Slider_length(float length);
		//установить позицию ползунка 
		float Set_Position(float position);
		//возвращает позицию ползунка 
		float Get_Position();
		void Update();
	private:
		int passiv_hover = 0;
		float Slider_length, Position_p, Px, Mx;
		bool Move_slider;
	protected:
	};
}
#endif // !UIGLSCROLLBAR_H