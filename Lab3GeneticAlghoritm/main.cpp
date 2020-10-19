#include"InitializeAlghoritm.h"
#include"Config.h"


int main() {
	Config* config = new Config();
	char file[] = "Input.txt";

	config->ParseFile(file);

	ShowStartingWindwow();
	return 0;
}