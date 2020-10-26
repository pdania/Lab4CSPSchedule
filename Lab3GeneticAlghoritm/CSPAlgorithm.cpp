#include"CSPAlgorithm.h"

CSPAlgorithm::CSPAlgorithm(Config& config,  size_t pairCount) :
	_config(config),
	_pairCount(pairCount),
	_removedPairs(0) {
}
