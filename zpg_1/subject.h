#pragma once
#include <vector>
#include "observer.h"
class Subject
{
protected:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* observer)
	{
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void notifyObservers()
	{
		for (auto observer : observers)
		{
			observer->onSubjectChanged();
		}
	}
};