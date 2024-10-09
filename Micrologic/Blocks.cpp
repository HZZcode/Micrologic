#include "Blocks.h"

Blocks::Blocks() {
	int cap = 1024;
	this->L.reserve(cap);
	this->N.reserve(cap);
	this->A.reserve(cap);
	this->R.reserve(cap);
	this->T.reserve(cap);
	this->C.reserve(cap);
	this->Bs.reserve(cap);
	this->L.reserve(cap);
}

void Blocks::add(std::vector<Line> L) {
	for (const Line& l : L) this->L.push_back(l);
}

void Blocks::add(std::vector<BlockN> N) {
	for (const BlockN& n : N) this->N.push_back(n);
}

void Blocks::add(std::vector<BlockA> A) {
	for (const BlockA& a : A) this->A.push_back(a);
}

void Blocks::add(std::vector<BlockR> R) {
	for (const BlockR& r : R) this->R.push_back(r);
}

void Blocks::add(std::vector<BlockT> T) {
	for (const BlockT& t : T) this->T.push_back(t);
}

void Blocks::add(std::vector<BlockC> C) {
	for (const BlockC& c : C) this->C.push_back(c);
}

void Blocks::add(std::vector<BlockP> P) {
	for (const BlockP& p : P) this->P.push_back(p);
}

void Blocks::add(Blocks b) {
	this->Bs.push_back(b);
}

void Blocks::add(std::vector<Blocks> Bs) {
	for (const Blocks& b : Bs) this->Bs.push_back(b);
}

void Blocks::tick() {
	for (int i = 0; i < speed; i++) {
		for (int i = 0; i < inputLines.size(); i++) {
			L[inputs[i]].nextValue = L[inputs[i]].value = inputLines[i]->value;
			for (int j = 0; j < 4; j++) L[inputs[i]].nextWideValue[j] = L[inputs[i]].wideValue[j] = inputLines[i]->wideValue[j];
		}
		for (int i = 0; i < N.size(); i++) N[i].tick();
		for (int i = 0; i < A.size(); i++) A[i].tick();
		for (int i = 0; i < R.size(); i++) R[i].tick();
		for (int i = 0; i < T.size(); i++) T[i].tick();
		for (int i = 0; i < C.size(); i++) C[i].tick();
		for (int i = 0; i < P.size(); i++) P[i].tick();
		for (int i = 0; i < Bs.size(); i++) Bs[i].tick();
		for (int i = 0; i < L.size(); i++) L[i].flush();
		for (int i = 0; i < outputLines.size(); i++) {
			outputLines[i]->nextValue = outputLines[i]->value = L[outputs[i]].value;
			for (int j = 0; j < 4; j++) outputLines[i]->nextWideValue[j] = outputLines[i]->wideValue[j] = L[outputs[i]].wideValue[j];
		}
	}
}

void Blocks::clear() {
	clearContainer(L);
	clearContainer(N);
	clearContainer(A);
	clearContainer(R);
	clearContainer(T);
	clearContainer(C);
	clearContainer(P);
	clearContainer(Bs);
	clearContainer(inputs);
	clearContainer(outputs);
	clearContainer(mods);
}

void Blocks::addInput(std::vector<int> inputs) {
	for (int i : inputs) this->inputs.push_back(i);
}

void Blocks::addOutput(std::vector<int> outputs) {
	for (int i : outputs) this->outputs.push_back(i);
}

void Blocks::input(int order, bool value) {
	this->L[inputs[order]].value = this->L[inputs[order]].nextValue = value;
	for (int i = 0; i < 4; i++) this->L[inputs[order]].wideValue[i] = this->L[inputs[order]].nextWideValue[i] = value;
}

void Blocks::input(int order, std::array<bool, 4> value) {
	for (int i = 0; i < 4; i++) this->L[inputs[order]].wideValue[i] = this->L[inputs[order]].nextWideValue[i] = value[i];
}

std::string Blocks::output(int order) {
	return this->L[outputs[order]].checkValue();
}

std::vector<std::string> Blocks::output() {
	std::vector<std::string> outs;
	for (int i : outputs) {
		outs.push_back(L[i].checkValue());
	}
	return outs;
}

bool Blocks::isInput(int line) {
	return std::count(inputs.begin(), inputs.end(), line) != 0;
}

bool Blocks::isOutput(int line) {
	return std::count(outputs.begin(), outputs.end(), line) != 0;
}

bool Blocks::check() {
	if (!(this->inputs.size() == this->inputLines.size() && this->outputs.size() == this->outputLines.size())) return false;
	for (int i = 0; i < this->inputs.size(); i++) if (this->L[inputs[i]].mode != this->inputLines[i]->mode) return false;
	for (int i = 0; i < this->outputs.size(); i++) if (this->L[outputs[i]].mode != this->outputLines[i]->mode) return false;
	return true;
}