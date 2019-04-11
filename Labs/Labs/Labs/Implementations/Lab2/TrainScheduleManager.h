#pragma once
#include <iostream>
#include <string>

#include "TrainSchedule.h"

using namespace std;


class TrainScheduleManager
{
	const string FileName = "train.txt";
	const char Delimiter = '|';

public:
	void Add();

	void ShowAll();

	void DeleteAll();

	void DeleteByTrainNo(string trainNo);

	void Search();

private:
	// appendToFile = true, має значення за замочуванням. 
	// Це означає, що ми можемо не вказувати значення кожен раз 
	// як викликаємо метод
	void SaveToFile(vector<TrainSchedule*> schedules, bool appendToFile = true);

	void SaveToFile(TrainSchedule& schedule, bool appendToFile = true);

	void Show(vector<TrainSchedule*> schedules);

	vector<TrainSchedule*> LoadFromFile();

	string ReadSearchParameter(string label);

	bool IsMatch(string& arrivalStation, string& searchArrivalStation);

	bool IsMatchRange(tm& departureTime, int& departureHourFrom, int& departureHourTo);

	bool IsMatchRange(int& travelTime, int& travelTimeFrom, int& travelTimeTo);
};

