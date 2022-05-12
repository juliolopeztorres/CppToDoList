#include "gtest/gtest.h"
#include <fstream>

#include "../../../src/Framework/Service/Container.h"

using namespace Framework::Service;

namespace Test::Framework::Service::ContainerTest {

	class FrameworkServiceContainerTest : public testing::Test {
	protected:
		string store = "test_store.json";

		void TearDown() override {
			struct stat buffer;

			if ((stat(this->store.c_str(), &buffer) == 0)) {
				remove(this->store.c_str());
			}
		}

		void populateStore() {
			std::ofstream file(this->store);
			file << R"([{"id": 1, "title": "My Task"}])";
			file.close();
		}

		void populateMultipleStore() {
			std::ofstream file(this->store);
			file << R"([{"id": 1, "title": "My Task"},{"id": 2, "title": "My Second Task"}])";
			file.close();
		}
	};

	TEST_F(FrameworkServiceContainerTest, CanCreate) {
		Container container = Container(this->store);

		EXPECT_NE(&container, nullptr);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleRandomCommand) {
		EXPECT_EQ(
			Container(this->store).handle("MyRandomCommand"),
			"Option: 'MyRandomCommand' not recognized. Please, try it again\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleEmptyCommand) {
		EXPECT_EQ(
			Container(this->store).handle(""),
			"Please, enter a valid command\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleCommandList) {
		EXPECT_EQ(
			Container(this->store).handle("command-list"),
			"Please, type a command to navigate\n\t`help`: Show an app description and a list of the available commands\n\t`exit`: Finish and exit the program with code 0\n\n\t-------------------------------------------------------------------\n\n\t`list`: List the current TODO list\n\t`create`: Type `create {id} {title}` where {id} is the number \n\t\t  for identifying the task and {title} is a string with a \n\t\t  description/name\n\t`edit`: Type `edit {id} {newTitle}` where {id} is an existing task \n\t\t  id number and {newTitle} is the new description/name\n\t`remove`: Type `remove {id}` where {id} is an existing task\n\t\t  id number\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleHelp) {
		EXPECT_EQ(
			Container(this->store).handle("help"),
			"This is an CLI app to handle To-Do elements in a JSON file list. You can:\n\tCheck the current content of the list\n\tAdd new elements to the end of the list\n\tEdit and remove elements of the list\n\nAt every transaction, the JSON file would be updated.\n\nYou can call the program with a path to use that specific json. If not, `store.json` would be used as default. \n\nThe program would create the JSON file, if that path does not exist at runtime.\n\nPlease, type a command to navigate\n\t`help`: Show an app description and a list of the available commands\n\t`exit`: Finish and exit the program with code 0\n\n\t-------------------------------------------------------------------\n\n\t`list`: List the current TODO list\n\t`create`: Type `create {id} {title}` where {id} is the number \n\t\t  for identifying the task and {title} is a string with a \n\t\t  description/name\n\t`edit`: Type `edit {id} {newTitle}` where {id} is an existing task \n\t\t  id number and {newTitle} is the new description/name\n\t`remove`: Type `remove {id}` where {id} is an existing task\n\t\t  id number\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleListEmptyCommand) {
		EXPECT_EQ(
			Container(this->store).handle("list"),
			"There is no tasks stored yet!\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleListCommand) {
		this->populateStore();

		EXPECT_EQ(
			Container(this->store).handle("list"),
			"\tTask ID: 1\n\tTitle: My Task\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleListMultipleCommand) {
		this->populateMultipleStore();

		EXPECT_EQ(
			Container(this->store).handle("list"),
			"\tTask ID: 1\n\tTitle: My Task\n\n\tTask ID: 2\n\tTitle: My Second Task\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleCreateCommand) {
		EXPECT_EQ(
			Container(this->store).handle("create 1 My Task"),
			"Task created!\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleCreateDuplicatedTaskCommand) {
		this->populateStore();

		EXPECT_EQ(
			Container(this->store).handle("create 1 My duplicated task"),
			"Already existing task with id 1\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleCreateWithWrongInputsCommand) {
		Container container = Container(this->store);

		EXPECT_EQ(
			container.handle("create"),
			"Create command must have an {id} and a {title}. See `help`\n"
		);

		EXPECT_EQ(
			container.handle("create myId My task"),
			"{id} must be a valid integer\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleEditTaskCommand) {
		this->populateStore();

		Container container = Container(this->store);

		EXPECT_EQ(
			container.handle("edit 1 My edited task"),
			"Task edited!\n"
		);

		EXPECT_EQ(
			container.handle("list"),
			"\tTask ID: 1\n\tTitle: My edited task\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleEditNonExistingTaskCommand) {
		EXPECT_EQ(
			Container(this->store).handle("edit 1 My edited task"),
			"A task with the id 1 was not found on the list\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleEditWithWrongInputsCommand) {
		this->populateStore();
		Container container = Container(this->store);

		EXPECT_EQ(
			container.handle("edit"),
			"Edit command must have an {id} to edit and a new {title}. See `help`\n"
		);

		EXPECT_EQ(
			container.handle("edit myId My task"),
			"{id} must be a valid integer\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleRemoveTaskCommand) {
		this->populateStore();

		Container container = Container(this->store);

		EXPECT_EQ(
			container.handle("remove 1"),
			"Task removed!\n"
		);

		EXPECT_EQ(
			container.handle("list"),
			"There is no tasks stored yet!\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleRemoveNonExistingTaskCommand) {
		EXPECT_EQ(
			Container(this->store).handle("remove 1"),
			"A task with the id 1 was not found on the list\n"
		);
	}

	TEST_F(FrameworkServiceContainerTest, CanHandleRemoveWithWrongInputsCommand) {
		Container container = Container(this->store);

		EXPECT_EQ(
			container.handle("remove"),
			"Remove command must have an {id} related to the task to be removed. See `help`\n"
		);

		EXPECT_EQ(
			container.handle("remove myId"),
			"{id} must be a valid integer\n"
		);
	}
}
