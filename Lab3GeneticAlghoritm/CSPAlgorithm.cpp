#include"CSPAlgorithm.h"

CSPAlgorithm::CSPAlgorithm(Config& config,  size_t pairCount, size_t algorithmType) :
	_config(config),
	_pairCount(pairCount),
	_removedPairs(0),
	_algorithmType(algorithmType){
}

void CSPAlgorithm::ProcessAlgorithm() {
	switch (static_cast<Heuristics>(_algorithmType)) {
	case Heuristics::MRV:
	{
		break;
	}
	case Heuristics::DegreeHeuristics:
	{
		break;
	}
	case Heuristics::LCV:
	{
		break;
	}
	case Heuristics::ForwardChecking:
	{
		break;
	}
	case Heuristics::ConstraintPropagation:
	{
		break;
	}
	case Heuristics::BestSolution:
	{
		break;
	}
	}
}
