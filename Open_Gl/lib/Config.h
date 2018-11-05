#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

#include "uiglColor.h"

namespace UIGL {

	struct string_int
	{
		std::string Text = "";
		std::string Text1 = "";
		unsigned int Count = 0;
		int Num = 0;
	};

	//сохранение параметров (имя,значения)
	class UiglConfig
	{
	public:
		UiglConfig(std::string file_name);
		UiglConfig();
		~UiglConfig();
		bool Open(std::string file_name = "");
		bool is_open() { return _is_open; }
		bool Get_count(std::string name, int& count);
		bool Get_color(std::string name, UiglColor& col);
		bool Set_count(std::string name, int count, bool _save = 0);
		bool setColor(std::string name, UiglColor col, bool _save = 0);
		bool Save(std::string file_name = "");
		bool Add_item(std::string name, int count);
		bool Erase_item(std::string name);
		bool Clear();
		friend UiglColor;
	private:
		std::vector<string_int> Data;
		bool _is_open;
		std::string _file_name;
	};
}
#endif // !CONFIG_H