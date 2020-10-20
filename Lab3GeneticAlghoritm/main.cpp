#include"InitializeAlghoritm.h"
#include"Config.h"
#include"GAlgorithm.h"

const char* File = "Input.txt";

int main() {
	srand(time(0));

	Config config;
	config.ParseFile(File);

	size_t crossoverProbability, mutationProbability, pairCount;
	ShowStartingWindwow(crossoverProbability, mutationProbability, pairCount);

	GAlgorithm algo(config, crossoverProbability, mutationProbability, pairCount);
	algo.ProcessAlgorithm();

	return 0;
}