#ifndef UIGLPICTURE_H
#define UIGLPICTURE_H

#include "../uiglIForms.h"

namespace UIGL {
	
	struct Layer
	{
		int count = 0;
		uiglPrimitives primitive = uiglLINE_LOOP;
		float line_length = 1;
	};

	class UiglPicture :public UiglIForms
	{
	public:
		UiglPicture();
		UiglPicture(std::string name) : UiglPicture() { Name = name; }
		~UiglPicture() {}
		std::vector<std::vector<UiglPoint>> points;
		std::vector<Layer> layers;
		std::string file_name;
		void Init();
		bool Open(std::string _file_name);
		UiglEvent MouseFunc(int button, int state, int ax, int ay);
		UiglEvent PassiveMotionFunc(int ax, int ay);
		UiglEvent MotionFunc(float ax, float ay);
		UiglEvent MouseWheelFunc(int button, int state, int ax, int ay);
		UiglEvent KeyboardFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialFunc(int key, int ax, int ay);
		UiglEvent KeyboardUpFunc(unsigned char key, int ax, int ay);
		UiglEvent SpecialUpFunc(int key, int ax, int ay);
	protected:
		float w_p = 0, h_p = 0;
		void Line_init(uiglPrimitives prim, float length = 1);
	};
}
#endif // ! UIGLPICTURE_H