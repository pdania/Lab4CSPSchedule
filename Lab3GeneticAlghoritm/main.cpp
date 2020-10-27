#include"InitializeAlghoritm.h"
#include"CSPAlgorithm.h"

const char* File = "Input.txt";

int main() {
	srand(time(0));

	Config config;
	config.ParseFile(File);

	size_t pairCount;
	ShowStartingWindwow(pairCount);

	CSPAlgorithm algo(config, pairCount);
	algo.Init();
	algo.ProcessAlgorithm();

	ShowShedule(algo);

	return 0;
}