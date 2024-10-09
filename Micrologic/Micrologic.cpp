#include "Interpreter.h"

using namespace std;

int main(int argc, const char* argv[]) {
	Blocks blocks;
	string exepath = string(_getcwd(NULL, 0));
	Interpreter Micrologic(blocks, exepath);
	if (argc == 2) {
		Micrologic.Echo = Micrologic.command("open " + string(argv[1]));
	}
	while (1) {
		printf(">>>");
		string cmd;
		getline(cin, cmd);
		Micrologic.command(cmd);
		if (Micrologic.Exit == 1) break;
	}
}