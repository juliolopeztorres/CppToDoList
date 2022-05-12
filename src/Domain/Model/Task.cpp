#pragma once
#include "Task.h"

using namespace Domain::Model;

Task::Task(const int& id, const string& title) {
	this->id = id;
	this->title = title;
};