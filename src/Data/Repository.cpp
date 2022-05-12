#pragma once
#include "Repository.h"

#include <fstream>
#include <vector>
#include "Mapper/TaskListMapper.h"

using namespace Data;

Repository::Repository(const string& storePath)
{
	this->storePath = storePath;

	if (!this->existsPath()) {
		this->saveJson(json::parse("[]"));
	}
}

bool Repository::existsPath() const {
	struct stat buffer;
	return (stat(this->storePath.c_str(), &buffer) == 0);
}

json Repository::getJson() const {
	std::ifstream i(this->storePath);

	return json::parse(i);
}

void Repository::saveJson(const json& j) const {
	std::ofstream file(this->storePath);
	file << j;
	file.close();
}

std::vector<Task> Repository::get() {
	return Mapper::TasksMapper::map(this->getJson());
}

void Repository::create(const Task& task) {
	json j = this->getJson();

	for (json element : j) {
		if (element["id"].get<int>() == task.id) {
			throw std::invalid_argument("Already existing task with id " + std::to_string(task.id));
		}
	}

	j.insert(j.begin(), Mapper::TaskMapper::mapForSaving(task));

	this->saveJson(j);
}

void Repository::edit(const Task& task) {
	json j = this->getJson();

	bool found = false;
	for (json& element : j) {
		if (element["id"].get<int>() == task.id) {
			found = true;
			element["title"] = task.title;
			break;
		}
	}

	if (!found) {
		throw std::invalid_argument("A task with the id " + std::to_string(task.id) + " was not found on the list");
	}

	this->saveJson(j);
}

void Repository::remove(const int& id) {
	json j = this->getJson();

	int keyToRemove = -1;
	for (auto& el : j.items())
	{
		json element = el.value();

		if (element["id"].get<int>() == id) {
			keyToRemove = stoi(el.key());
			break;
		}
	}

	if (keyToRemove == -1) {
		throw std::invalid_argument("A task with the id " + std::to_string(id) + " was not found on the list");
	}

	j.erase(keyToRemove);

	this->saveJson(j);
}