#pragma once
#include <string>
#include <sstream>
using namespace std;

class TrainSchedule
{
public:
	string TrainNo;
	tm DepartureTime;
	string ArrivalStation;
	int TravelTime;
};
