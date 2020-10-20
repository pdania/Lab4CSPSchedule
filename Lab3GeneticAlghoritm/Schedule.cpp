//#include"Schedule.h"
//
//// Initializes chromosomes with configuration block (setup of chromosome)
//Schedule::Schedule(int numberOfCrossoverPoints, int mutationSize,
//	int crossoverProbability, int mutationProbability) : _mutationSize(mutationSize),
//	_numberOfCrossoverPoints(numberOfCrossoverPoints),
//	_crossoverProbability(crossoverProbability),
//	_mutationProbability(mutationProbability),
//	_fitness(0)
//{
//	// reserve space for time-space slots in chromosomes code
//	_slots.resize(DAYS * DAY_HOURS * Config::GetInstance().GetNumberOfRooms());
//
//	// reserve space for flags of class requirements
//	_criteria.resize(Config::GetInstance().GetNumberOfCourseClasses() * 5);
//}