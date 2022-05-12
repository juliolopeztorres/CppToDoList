#pragma once
#include <nlohmann/json.hpp>
#include "../Domain/GetTodosUseCase/GetTodosUseCaseRepositoryInterface.h"
#include "../Domain/CreateTodoUseCase/CreateTodoUseCaseRepositoryInterface.h"
#include "../Domain/EditTodoUseCase/EditTodoUseCaseRepositoryInterface.h"
#include "../Domain/RemoveTodoUseCase/RemoveTodoUseCaseRepositoryInterface.h"


namespace Data {
	using json = nlohmann::json;
	using namespace Domain::GetTodosUseCase;
	using namespace Domain::CreateTodoUseCase;
	using namespace Domain::EditTodoUseCase;
	using namespace Domain::RemoveTodoUseCase;

	class Repository :
		virtual public GetTodosUseCaseRepositoryInterface,
		virtual public CreateTodoUseCaseRepositoryInterface,
		virtual public EditTodoUseCaseRepositoryInterface,
		virtual public RemoveTodoUseCaseRepositoryInterface
	{
	private:
		string storePath;

		bool existsPath() const;
		json getJson() const;
		void saveJson(const json& j) const;

	public:
		Repository(const string& storePath);

		std::vector<Task> get();
		void create(const Task& task);
		void edit(const Task& task);
		void remove(const int& id);
	};
}
