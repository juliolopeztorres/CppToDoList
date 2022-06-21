#pragma once
#include "Container.h"
#include "../Mapper/TaskListMapper.h"

using namespace Framework::Service;

Container::Container(const string& storePath) :
	repo(Repository(storePath)),
	getTodosUseCase(GetTodosUseCase(repo)),
	createTodoUseCase(CreateTodoUseCase(repo)),
	editTodoUseCase(EditTodoUseCase(repo)),
	removeTodoUseCase(RemoveTodoUseCase(repo))
{};

string Container::handle(const string& commandString) const {
	const std::vector<string> words = this->string_split(commandString, ' ');

	if (words.size() == 0) {
		return "Please, enter a valid command\n";
	}

	const Command command = Command(words[0]);

	if (command == CommandType::NotRecognized) {
		return "Option: '" + words[0] + "' not recognized. Please, try it again\n";
	}

	try {
		return this->handleCommand(command, words);
	}
	catch (const std::invalid_argument& exception) {
		string message = exception.what();

		return message + "\n";
	}

	throw std::invalid_argument("This should not happen");
}

string Container::handleCommand(const Command& command, const std::vector<string>& arguments) const {
	switch (command)
	{
	case CommandType::CommandList:
		return this->printCommandList();
	case CommandType::Help:
		return this->printHelp() + "\n\n" + this->printCommandList();
	case CommandType::List:
		return Framework::Mapper::TasksMapper::map(this->getTodosUseCase.get());
	case CommandType::Create:
		this->createTodoUseCase.create(
			this->validateCreateCommandAndCreateTask(arguments)
		);

		return "Task created!\n";
	case CommandType::Edit:
		this->editTodoUseCase.edit(
			this->validateEditCommandAndCreateTask(arguments)
		);

		return "Task edited!\n";
	case CommandType::Remove:
		this->removeTodoUseCase.remove(
			this->validateRemoveCommandAndGetId(arguments)
		);

		return "Task removed!\n";
	}

	throw std::invalid_argument("This should not happen");
}

string Container::printCommandList() const {
	return R"(Please, type a command to navigate
	`help`: Show an app description and a list of the available commands
	`exit`: Finish and exit the program with code 0

	-------------------------------------------------------------------

	`list`: List the current TODO list
	`create`: Type `create {id} {title}` where {id} is the number 
		  for identifying the task and {title} is a string with a 
		  description/name
	`edit`: Type `edit {id} {newTitle}` where {id} is an existing task 
		  id number and {newTitle} is the new description/name
	`remove`: Type `remove {id}` where {id} is an existing task
		  id number
)";
}

string Container::printHelp() const {
	return R"(This is an CLI app to handle To-Do elements in a JSON file list. You can:
	Check the current content of the list
	Add new elements to the end of the list
	Edit and remove elements of the list

At every transaction, the JSON file would be updated.

You can call the program with a path to use that specific json. If not, `store.json` would be used as default. 

The program would create the JSON file, if that path does not exist at runtime.)";
}

std::vector<string> Container::string_split(string myString, const char& delimiter) const {
	std::vector<string> out;

	char* next = NULL;

	char* token = strtok_s(myString.data(), &delimiter, &next);
	while (token != NULL)
	{
		out.push_back(string(token));
		token = strtok_s(NULL, &delimiter, &next);
	}

	return out;
}

int Container::validateId(const string& proposedId) const {
	try {
		return stoi(proposedId);
	}
	catch (...) {
		throw std::invalid_argument("{id} must be a valid integer");
	}
}

string Container::parseTitle(const std::vector<string>& commandOptions) const {
	string title = "";
	for (int i = 2; i < commandOptions.size(); i++) {
		title += commandOptions[i] + ((i + 1 != commandOptions.size()) ? " " : "");
	}

	return title;
}

Task Container::validateCreateCommandAndCreateTask(const std::vector<string>& createCommandOptions) const {
	if (createCommandOptions.size() < 3) {
		throw std::invalid_argument("Create command must have an {id} and a {title}. See `help`");
	}

	return Task(this->validateId(createCommandOptions[1]), this->parseTitle(createCommandOptions));
}

Task Container::validateEditCommandAndCreateTask(const std::vector<string>& editCommandOptions) const {
	if (editCommandOptions.size() < 3) {
		throw std::invalid_argument("Edit command must have an {id} to edit and a new {title}. See `help`");
	}

	return Task(this->validateId(editCommandOptions[1]), this->parseTitle(editCommandOptions));
}

int Container::validateRemoveCommandAndGetId(const std::vector<string>& removeCommandOptions) const {
	if (removeCommandOptions.size() < 2) {
		throw std::invalid_argument("Remove command must have an {id} related to the task to be removed. See `help`");
	}

	return this->validateId(removeCommandOptions[1]);
}
