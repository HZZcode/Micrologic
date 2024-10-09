#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <variant>
#include <array>
#include <cstdarg>
#include <direct.h>
#include "Blocks.h"
#include "Messages.h"

inline bool assertPositive(int a) {
	if (a <= 0) {
		std::cerr << "[ERROR] Should be positive: " << a << std::endl;
		return false;
	}
	return true;
}
inline bool assertBit(int a) {
	if (a != 0 && a != 1) {
		std::cerr << "[ERROR] Should be bit: " << a << std::endl;
		return false;
	}
	return true;
}
template <typename T>
inline bool assertInRange(int i, std::vector<T> vec) {
	if (i < 0 || i >= vec.size()) {
		std::cerr << "[ERROR] Number out of range: " << i << std::endl;
		return false;
	}
	return true;
}
template <typename T, typename T1>
inline bool assertInMap(T t, std::map<T, T1> mp) {
	if (mp.find(t) == mp.end()) {
		std::cerr << "[ERROR] Key not found: " << t << std::endl;
		return false;
	}
	return true;
}
inline bool assertGoodFile(std::ifstream& f) {
	if (!f.good()) {
		std::cerr << "[ERROR] File not found" << std::endl;
		return false;
	}
	return true;
}

template <typename T>
inline std::vector<T> subVec(const std::vector<T>& vec, int start, int end) {
	if (start < 0 || end > vec.size() || start > end) {
		throw std::out_of_range("");
	}
	return std::vector<T>(vec.begin() + start, vec.begin() + end);
}

class Interpreter {
public:
	bool Echo;
	bool Exit = false;
	std::string lang;
	Blocks& blocks;
	std::string path;
	std::string exepath;

	Interpreter(Blocks& blocks, std::string exepath, std::string path = "", std::string lang = "en_us", bool Echo = true)
		:blocks(blocks), exepath(exepath), path(path), lang(lang), Echo(Echo) {
	}

	bool isNum(std::string);
	int toInt(std::string);
	std::vector<int> toInt(std::vector<std::string>);
	std::array<bool, 4> toBoolArray(std::array<int, 4>);

	std::string quotedPart(std::string);
	std::string firstWord(std::string);
	std::string pathPart(std::string);
	std::string addSlash(std::string filename); //add backslash to the end if none
	std::string convertSlash(std::string filename); //convert all slashes to backslashes

	std::vector<std::string> breakLine(std::string);

	void writeDebug();
	std::vector<std::string> getHelp();
	void writeMessage(std::string message, ...);

	void line(int = 1);
	void wline(int = 1);
	void N(int, int);
	void A(int, int, int);
	void R(int, int, int);
	void T(int, int);
	void C(std::array<int, 4>, int);
	void P(int, std::array<int, 4>);
	void check();
	void check(int);
	void set(int, int);
	void set(int, std::array<int, 4>);
	void input_(int);
	void input(int, int);
	void input(int, std::array<int, 4>);
	void output_(int);
	void output();
	void output(int);
	void tick();
	void tick(int);
	void tick_();
	void tick_(int);
	void speed(int);
	void open(std::string);
	void mod(std::string, std::string);
	void block(std::string, std::vector<int>);
	void block_old(std::string, std::vector<int>);
	void tag(int);
	void type(int);
	void check_input();
	void check_input(int);
	void check_output();
	void check_output(int);
	void inspect(std::string, int);
	void echo(std::string);
	void _echo(int);
	void __path();
	void __path(std::string);
	void clear();
	void help();
	void help(std::string);
	void __lang(std::string);
	void neko();

	bool command(std::string cmd);
};