#include"InitializeAlghoritm.h"
#include"Config.h"
#include"CSPAlgorithm.h"

const char* File = "Input.txt";

int main() {
	srand(time(0));

	Config config;
	config.ParseFile(File);

	size_t algorithmType, pairCount;
	ShowStartingWindwow(algorithmType, pairCount);

	CSPAlgorithm algo(config, pairCount, algorithmType);
	//algo.ProcessAlgorithm();

	return 0;
}