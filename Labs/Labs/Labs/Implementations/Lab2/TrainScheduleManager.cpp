#include <fstream>
#include <vector>
#include <iomanip>
#include "TrainScheduleManager.h"
#include "../../Helpers/helpers.h"

// stoi : https://www.systutorials.com/131/convert-string-to-int-and-reverse/

void TrainScheduleManager::Add() {
	TrainSchedule schedule;
	cout << "TrainNo: ";
	cin >> schedule.TrainNo;
	cout << "DepartureTime.Hours: ";
	cin >> schedule.DepartureTime.tm_hour;
	cout << "DepartureTime.Minutes: ";
	cin >> schedule.DepartureTime.tm_min;
	cout << "ArrivalStation: ";
	cin >> schedule.ArrivalStation;
	cout << "TravelTime: ";
	cin >> schedule.TravelTime;
	SaveToFile(schedule);
}

void TrainScheduleManager::ShowAll() {
	vector<TrainSchedule*> schedules = LoadFromFile();
	Show(schedules);
}

void TrainScheduleManager::DeleteAll() {
	std::ofstream ofs;
	ofs.open(FileName, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void TrainScheduleManager::DeleteByTrainNo(string trainNo) {
	vector<TrainSchedule*> schedules = LoadFromFile();
	int indexForRemove = -1;
	for (size_t i = 0; i < schedules.size(); i++)
	{
		if (IsEqualsIgnoreCase(schedules[i]->TrainNo, trainNo)) {
			indexForRemove = i;
			delete(schedules[i]);
			schedules.erase(schedules.begin() + i);
			break;
		}
	}
	SaveToFile(schedules, false);
}

void TrainScheduleManager::Search() {
	vector<TrainSchedule*> schedules = LoadFromFile();

	cin.ignore();

	string arrivalStation = ReadSearchParameter("arrival station");

	string departureHourFromStr = ReadSearchParameter("departure hour from");
	int departureHourFrom = departureHourFromStr.empty() ? -1 : stoi(departureHourFromStr);

	string departureHourToStr = ReadSearchParameter("departure hour to");
	int departureHourTo = departureHourToStr.empty() ? -1 : stoi(departureHourToStr);

	string travelTimeStrFrom = ReadSearchParameter("travel time from");
	int travelTimeFrom = travelTimeStrFrom.empty() ? -1 : stoi(travelTimeStrFrom);

	string travelTimeStrTo = ReadSearchParameter("travel time to");
	int travelTimeTo = travelTimeStrTo.empty() ? -1 : stoi(travelTimeStrTo);

	vector<TrainSchedule*> relevantSchedules;
	for (size_t i = 0; i < schedules.size(); ++i)
	{
		if (IsMatch(schedules[i]->ArrivalStation, arrivalStation)
			&& IsMatchRange(schedules[i]->DepartureTime, departureHourFrom, departureHourTo)
			&& IsMatchRange(schedules[i]->TravelTime, travelTimeFrom, travelTimeTo))
		{
			relevantSchedules.push_back(schedules[i]);
		}
	}

	Show(relevantSchedules);
}


void TrainScheduleManager::SaveToFile(vector<TrainSchedule*> schedules, bool appendToFile)
{
	for (size_t i = 0; i < schedules.size(); i++)
	{
		SaveToFile(*schedules[i], appendToFile);
		appendToFile = true;
	}
}

// Цей запис "appendToFile ? ios::app : ios::in" є тринарною умовною операцією,
// що є аналогом запису: if (condition) { if_true; } else { if_false; }
// Більше тут: http://www.cplusplus.com/forum/articles/14631/ 
void TrainScheduleManager::SaveToFile(TrainSchedule& schedule, bool appendToFile) {
	ofstream writer(FileName, appendToFile ? ios::app : ios::out);
	if (writer.is_open()) {
		writer << schedule.TrainNo << Delimiter;
		writer << schedule.DepartureTime.tm_hour << Delimiter;
		writer << schedule.DepartureTime.tm_min << Delimiter;
		writer << schedule.ArrivalStation << Delimiter;
		writer << schedule.TravelTime << Delimiter;
		writer << endl;
		writer.close();
	}
}

void TrainScheduleManager::Show(vector<TrainSchedule*> schedules) {
	int trainNoColSize = 12;
	int departureTimeColSize = 16;
	int arrivalStationColSize = 32;
	int travelTimeColSize = 12;
	int lineSize = trainNoColSize + departureTimeColSize + arrivalStationColSize + travelTimeColSize;
	cout << std::string(lineSize, '-') << endl;
	cout << left << setw(trainNoColSize) << "|Train No."
		<< setw(departureTimeColSize) << "|Departure Time"
		<< setw(arrivalStationColSize) << "|Train No."
		<< setw(travelTimeColSize) << "|Travel Time"
		<< endl;
	cout << std::string(lineSize, '-') << endl;
	for (size_t i = 0; i < schedules.size(); i++)
	{
		string time = to_string(schedules[i]->DepartureTime.tm_hour) + ":" + to_string(schedules[i]->DepartureTime.tm_min);
		cout << left
			<< setw(trainNoColSize) << "|" + schedules[i]->TrainNo
			<< setw(departureTimeColSize) << "|" + time
			<< setw(arrivalStationColSize) << "|" + schedules[i]->ArrivalStation
			<< setw(travelTimeColSize) << "|" + to_string(schedules[i]->TravelTime)
			<< endl;
	}
}

vector<TrainSchedule*> TrainScheduleManager::LoadFromFile() {
	ifstream reader(FileName);
	vector<TrainSchedule*> schedules;
	if (reader.is_open()) {
		string line;
		while (getline(reader, line))
		{
			vector<string> items = Split(line, Delimiter);
			TrainSchedule* schedule = new TrainSchedule;
			schedule->TrainNo = items.at(0);
			schedule->DepartureTime.tm_hour = std::stoi(items.at(1));
			schedule->DepartureTime.tm_min = std::stoi(items.at(2));
			schedule->ArrivalStation = items.at(3);
			schedule->TravelTime = std::stoi(items.at(4));
			schedules.push_back(schedule);
		}
		reader.close();
	}
	return schedules;
}

string TrainScheduleManager::ReadSearchParameter(string label) {
	string value;
	cout << "Please enter " << label << " (leave blank to skip): ";
	getline(std::cin, value);
	return value;
}

bool TrainScheduleManager::IsMatch(string& arrivalStation, string& searchArrivalStation) {
	// Якщо searchArrivalStation не вказано, то вважаємо,
	// що всі станції відповідають шуканому результату
	if (searchArrivalStation.empty()) return true;

	return IsEqualsIgnoreCase(arrivalStation, searchArrivalStation);
}

bool TrainScheduleManager::IsMatchRange(tm& departureTime, int& departureHourFrom, int& departureHourTo) {
	return (departureHourFrom < 0 || departureTime.tm_hour >= departureHourFrom)
		&& (departureHourTo < 0 || departureTime.tm_hour <= departureHourTo);
}

bool TrainScheduleManager::IsMatchRange(int& travelTime, int& travelTimeFrom, int& travelTimeTo) {
	return (travelTimeFrom < 0 || travelTime >= travelTimeFrom)
		&& (travelTimeTo < 0 || travelTime <= travelTimeTo);
}