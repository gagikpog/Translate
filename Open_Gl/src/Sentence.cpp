#include "Sentence.h"

void Sentence::SetText(std::string _text)
{
	const int _N_ = 30;
	bool b = 1;
	Text = "";
	for (int i = 0; i < _text.length(); i++)
	{
		if (_text[i] == ' ')
		{
			if (b == 1)
				continue;
			b = 1;
		}
		else b = 0;
		Text.push_back(_text[i] + _N_);
	}
	if (Text.back() == ' ' + _N_)
		Text.pop_back();
}

bool Sentence::AddText(std::string _txt)

{
	const int _N_ = 30;
	std::string _text;
	for (int i = 0; i < Text.size(); i++)
		_text += (char)Text[i] - _N_;

	bool b = 1;
	std::string _t;
	for (int i = 0; i < _txt.length(); i++)
	{
		if (_txt[i] == ' ')
		{
			if (b == 1)
				continue;
			b = 1;
		}
		else b = 0;
		_t.push_back(_txt[i]);
	}
	if (_t.back() == ' ')
		_t.pop_back();

	std::vector<std::pair<std::string, int>> T1;
	std::vector<std::pair<std::string, int>> T2;
	std::pair<std::string, int> _tmp;
	int _begin = 0;
	for (int i = 0; i < _text.size(); i++)
	{
		if (_text[i] == ' ' || _text.size() == i + 1)
		{
			_tmp.first = _text.substr(_begin, i - _begin);
			_tmp.second = T1.size();
			T1.push_back(_tmp);
			_begin = i + 1;
		}
	}
	_begin = 0;
	for (int i = 0; i < _t.size(); i++)
	{
		if (_t[i] == ' ' || _t.size() == i + 1)
		{
			_tmp.first = _t.substr(_begin, i - _begin);
			_tmp.second = T2.size();
			T2.push_back(_tmp);
			_begin = i + 1;
		}
	}

	if (T1.size() != T2.size())
		return 0;
	std::sort(T1.begin(), T1.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.first < b.first; });
	std::sort(T2.begin(), T2.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.first < b.first; });

	for (int i = 0; i < T1.size(); i++)
	{
		if (T1[i].first != T2[i].first)
			return 0;
	}

	arr.push_back(std::vector<char>());
	arr.back().insert(arr.back().end(), T1.size(), 0);
	for (int j = 0; j < T1.size(); j++)
		arr.back()[T1[j].second] = T2[j].second;
	return 1;
}

std::string Sentence::GetText()
{
	const int _N_ = 30;
	std::string _text;
	for (int i = 0; i < Text.size(); i++)
	{
		_text += (char)Text[i] - _N_;
	}
	return _text;
}

int Sentence::GetSize()
{
	return arr.size() + 1;
}

void Sentence::Clear()
{
	Text = "";
	for (int i = 0; i < arr.size(); i++)
		arr[i].clear();
	arr.clear();
}

bool Sentence::Test(std::string _txt)

{
	const int _N_ = 30;
	std::string _text;
	for (int i = 0; i < Text.size(); i++)
		_text += (char)Text[i] - _N_;

	bool b = 1;
	std::string _t;
	for (int i = 0; i < _txt.length(); i++)
	{
		if (_txt[i] == ' ')
		{
			if (b == 1)
				continue;
			b = 1;
		}
		else b = 0;
		_t.push_back(_txt[i]);
	}
	if (_t.back() == ' ')
		_t.pop_back();

	if (_t == _text)
	{
		Rating++;
		return true;
	}

	std::vector<std::pair<std::string, int>> T1;
	std::vector<std::pair<std::string, int>> T2;
	std::pair<std::string, int> _tmp;
	int _begin = 0;
	for (int i = 0; i < _text.size(); i++)
	{
		if (_text[i] == ' ' || _text.size() == i + 1)
		{
			_tmp.first = _text.substr(_begin, i - _begin);
			_tmp.second = T1.size();
			T1.push_back(_tmp);
			_begin = i + 1;
		}
	}
	_begin = 0;
	for (int i = 0; i < _t.size(); i++)
	{
		if (_t[i] == ' ' || _t.size() == i + 1)
		{
			_tmp.first = _t.substr(_begin, i - _begin);
			_tmp.second = T2.size();
			T2.push_back(_tmp);
			_begin = i + 1;
		}
	}

	if (T1.size() != T2.size())
	{
		Rating--;
		return 0;
	}
	std::sort(T1.begin(), T1.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.first < b.first; });
	std::sort(T2.begin(), T2.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.first < b.first; });

	for (int i = 0; i < T1.size(); i++)
	{
		if (T1[i].first != T2[i].first)
		{
			Rating--;
			return 0;
		}
	}

	std::vector<char> arr1(T1.size());
	for (int j = 0; j < T1.size(); j++)
		arr1[T1[j].second] = T2[j].second;

	b = 1;
	for (int i = 0; i < arr.size(); i++)
	{
		b = 1;
		for (int j = 0; j < arr[i].size(); j++)
		{
			if (arr[i][j] != arr1[j])
			{
				break;
				b = 0;
			}
		}
		if (b) { Rating++; return true; }
	}
	Rating--;
	return 0;
}