#pragma once

class Observer {
public:
	virtual ~Observer() = default;
	virtual void onSubjectChanged() = 0;
};