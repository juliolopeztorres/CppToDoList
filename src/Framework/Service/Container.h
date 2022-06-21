#pragma once
#include "../../Domain/GetTodosUseCase/GetTodosUseCase.h"
#include "../../Domain/CreateTodoUseCase/CreateTodoUseCase.h"
#include "../../Domain/EditTodoUseCase/EditTodoUseCase.h"
#include "../../Domain/RemoveTodoUseCase/RemoveTodoUseCase.h"
#include "../../Data/Repository.h"

namespace Framework::Service {
	using namespace Domain::Model;
	using namespace Domain::GetTodosUseCase;
	using namespace Domain::CreateTodoUseCase;
	using namespace Domain::EditTodoUseCase;
	using namespace Domain::RemoveTodoUseCase;
	using namespace Data;

	class Container {
	public:
		enum class CommandType {
			CommandList,
			Help,
			List,
			Create,
			Edit,
			Remove,
			NotRecognized
		};

		class Command {
		private:
			CommandType commandType;
		public:
			Command() = default;
			Command(CommandType type) : commandType(type) {}
			Command(const string& commandName) : commandType(CommandType::NotRecognized) {
				for (auto commandType : commands)
				{
					Command command = Command(commandType);
					string toCheck = std::string(command);
					if (commandName == std::string(Command(commandType))) {
						this->commandType = commandType;
						return;
					}
				}
			}

			operator CommandType() const { return commandType; }
			constexpr bool operator == (Command command) const { return commandType == command.commandType; }
			constexpr bool operator != (Command command) const { return commandType != command.commandType; }
			constexpr bool operator == (CommandType aCommandType) const { return commandType == aCommandType; }
			constexpr bool operator != (CommandType aCommandType) const { return commandType != aCommandType; }

			operator std::string() const {
				switch (commandType) {
				case CommandType::CommandList:
					return "command-list";
				case CommandType::Help:
					return "help";
				case CommandType::List:
					return "list";
				case CommandType::Create:
					return "create";
				case CommandType::Edit:
					return "edit";
				case CommandType::Remove:
					return "remove";
				}

				return "not-recognized";
			}
		};

		Container(const string& storePath);

		string handle(const string& commandString) const;
		string handleCommand(const Command& command, const std::vector<string>& arguments) const;

	private:
		inline static const std::vector<CommandType> commands = {
			CommandType::CommandList,
			CommandType::Help,
			CommandType::List,
			CommandType::Create,
			CommandType::Edit,
			CommandType::Remove
		};

		Task validateCreateCommandAndCreateTask(const std::vector<string>& createCommandOptions) const;
		Task validateEditCommandAndCreateTask(const std::vector<string>& editCommandOptions) const;
		int validateRemoveCommandAndGetId(const std::vector<string>& removeCommandOptions) const;

		std::vector<string> string_split(string myString, const char& delimiter) const;

		string printHelp() const;
		string printCommandList() const;

		int validateId(const string& proposedId) const;
		string parseTitle(const std::vector<string>& commandOptions) const;

		Repository repo;
		GetTodosUseCase getTodosUseCase;
		CreateTodoUseCase createTodoUseCase;
		EditTodoUseCase editTodoUseCase;
		RemoveTodoUseCase removeTodoUseCase;
	};
}
