#ifndef UIGLTEXTBOX_H
#define UIGLTEXTBOX_H

#include "../uiglIForms.h"
#include "../uiglText.h"

namespace UIGL {

	//Поле для ввода
	class UiglTextbox :public UiglIForms
	{
	public:
		UiglTextbox();
		UiglTextbox(std::string name) :UiglTextbox() { Name = name; };
		~UiglTextbox() {}
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
		void SetHDC(HDC* _hdc);
		bool NumbersOnly = 0;
		bool Read_only = false;
		int Text_max_length = 0;
		//Цвет текста
		UiglColor Text_color = Black;
		//Цвет выделенного
		UiglColor Selection_color = Iron;
		//Текст
		std::string Text;
		friend class UiglCombobox;
	private:
		bool Cursor_enbl;
		unsigned int Cursor_time;
	protected:
		bool Shift_press = 0;
		int	text_pos_begin = 0;
		int Select_begin = 0, Select_end = 0;
		int Cursor_pos = 0;
		float Text_size;
		UiglText textprint;
	};
}
#endif // !UIGLTEXTBOX_H
