#pragma once

#include <cstdio>
#include <string>
#include <array>

class Line {
public:
	enum {
		LINE = 0,
		WIDELINE = 1
	};
	short mode;
	bool nextValue;
	bool value;
	std::array<bool, 4> nextWideValue;
	std::array<bool, 4> wideValue;
	Line(int mode = LINE);
	void set(bool value);
	void set(std::array<bool, 4> wideValue);
	void flush();
	std::string checkValue();
};
