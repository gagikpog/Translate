#ifndef UIGLCIRCLE_H
#define UIGLCIRCLE_H

#include "../uigl.h"
#include "../uiglIForms.h"

namespace UIGL {
	//окружность
	class uiglCircle :public UiglIForms
	{
	public:
		uiglCircle();
		uiglCircle(std::string name) :uiglCircle() { Name = name; }
		~uiglCircle() {}
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
		void Init();
		void Update();
		//радиус
		float R;
	protected:
	private:
		uiglSize Size;
	};
}
#endif // !UIGLCIRCLE_H