#include "readFromFile.h"

#include <fstream>

bool TranslateFromFile(std::string file_name, std::string Text_find, std::string &Text_result)
{
	std::ifstream fin;
	fin.open(file_name);
	if (!fin.is_open())
		return 0;
	std::string temp;
	char T;
	bool read(1), find(0);

	fin.seekg(0, std::ios::end);
	int FileEnd = fin.tellg(), seekBegin = 0, seekEnd = 0;
	seekEnd = FileEnd;

	do {
		fin.seekg((seekEnd + seekBegin) / 2);
		std::getline(fin, temp);
		T = fin.peek();
		if (T < Text_find[0])
			seekBegin = fin.tellg();
		if (T > Text_find[0])
			seekEnd = fin.tellg();
		if (seekEnd - seekBegin < 300)
			return 0;
	} while (T != Text_find[0] && !fin.eof());

	seekBegin = fin.tellg();
	do {
		if (seekBegin - 200 > 0)
			seekBegin -= 200;
		else { fin.seekg(0); break; }
		fin.seekg(seekBegin);
		std::getline(fin, temp);
		T = fin.peek();
	} while (T == Text_find[0] && !fin.eof());

	fin >> temp;
	bool b = 0;
	while (!fin.eof())
	{
		if (Text_find == temp)
		{
			find = 1;
			break;
		}
		else std::getline(fin, temp);
		T = fin.peek();
		if (T == Text_find[0])
			b = 1;
		if (T != Text_find[0] && b == 1)
			return 0;
		fin >> temp;
	}
	fin.get();
	if (find)
	{
		Text_result = "";
		while (T = fin.get())
		{
			if (T != '\n')
				Text_result += T;
			else return 1;
		}
	}
	return 0;
}

bool openFavouriteWords(std::string file_name, std::vector<UIGL::string_int>& mas)
{
	std::ifstream in;
	in.open(file_name);
	if (!in.is_open())
		return 0;
	mas.clear();
	int _count;
	UIGL::string_int tempdata;
	std::string tempstr;
	bool is_read(1);

	while (in >> tempstr)
	{
		tempdata.Text = tempstr;

		in >> _count;
		tempdata.Count = _count;

		in.get();
		std::getline(in, tempstr);
		tempdata.Text1 = tempstr;
		mas.push_back(tempdata);
	}
	return 1;
}

bool saveFavouriteWords(std::string file_name, std::vector<UIGL::string_int>& mas)
{
	std::ofstream out;
	out.open(file_name);
	if (!out.is_open())
		return 0;
	for (int i = 0; i < mas.size(); i++)
		out << mas[i].Text << " " << mas[i].Count << " " << mas[i].Text1 << std::endl;
	return 1;
}

bool saveSentence(const std::vector<Sentence>& _sentence, std::string file_name)
{
	std::ofstream fout(file_name);
	if (fout.is_open())
	{
		fout.write((char*)&("TSS_"), 4);
		int str_count = _sentence.size(), str_length = 0, arr_length = 0;
		fout.write((char*)&str_count, sizeof(int));
		for (int i = 0; i < _sentence.size(); i++)
		{
			fout.write((char*)&(_sentence[i].Rating), sizeof(int));

			str_length = _sentence[i].Text.size();
			fout.write((char*)&str_length, sizeof(int));
			const char* _t = _sentence[i].Text.c_str();
			fout.write(_t, sizeof(char)*str_length);

			for (int j = 0; j < _sentence[i].arr.size(); j++)
				arr_length += _sentence[i].arr[j].size();
			fout.write((char*)&arr_length, sizeof(int));
			for (int k = 0; k < _sentence[i].arr.size(); k++)
			{
				for (int j = 0; j < _sentence[i].arr[k].size(); j++)
					fout << (char)_sentence[i].arr[k][j];
			}
		}
		fout.close();
		return true;
	}
	else return false;
}

bool openSentence(std::vector<Sentence>& _sentence, std::string file_name)
{
	std::ifstream fin(file_name);
	if (fin.is_open())
	{
		char T[] = "ABCD";
		fin.read((char*)(&T), 4);
		if (std::string(T) == "TSS_")
		{
			_sentence.clear();
			Sentence temp;
			int str_count = 0, str_length = 0, arr_length = 0, c_count = 0;
			fin.read((char*)&str_count, sizeof(int));
			for (int i = 0; i < str_count && !fin.eof(); i++)
			{
				fin.read((char*)&(temp.Rating), sizeof(int));

				fin.read((char*)&(str_length), sizeof(int));
				char* _t = new char[str_length + 1];
				fin.read(_t, sizeof(char)*str_length);
				temp.Text = _t;
				temp.Text = temp.Text.substr(0, str_length);
				c_count = 0;
				for (int j = 0; j < temp.Text.length(); j++)
					if (temp.Text[j] == ' ' + 30)
						c_count++;
				c_count++;

				fin.read((char*)&(arr_length), sizeof(int));
				char _c = 0;
				for (int k = 0; k < arr_length / c_count; k++)
				{
					temp.arr.push_back(std::vector<char>());
					for (int j = 0; j < c_count; j++)
					{
						fin >> _c;
						temp.arr.back().push_back(_c);
					}
				}
				_sentence.push_back(temp);
			}
			fin.close();
			return true;
		}
	}
	return false;
}