#include <iostream>

#include "Framework/Service/Container.h"

typedef std::string string;

using namespace Framework::Service;

int main(int argc, char** argv) {
	if (argc != 1 && argc != 2) {
		std::cout << "This program should be executed with 0 or 1 optional parameter (path to json store file)." << std::endl << std::endl;
		std::cout << "Exiting..." << std::endl << std::endl;

		return EXIT_FAILURE;
	}

	string storePath = "store.json";

	if (argc == 2) {
		storePath = argv[1];
	}

	Container container = Container(storePath);

	string command;

	std::cout << "Welcome to the CLI Todo List in C++!" << std::endl << std::endl;
	std::cout << container.handle(
		std::string(
			Container::Command(Container::CommandType::CommandList)
		)
	) << std::endl;

	while (true) {
		std::getline(std::cin, command);

		if (command == "exit") {
			std::cout << "Exiting..." << std::endl;
			break;
		}

		std::cout << container.handle(command) << std::endl;
	}

	return EXIT_SUCCESS;
}
