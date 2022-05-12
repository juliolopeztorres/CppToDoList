#include "gtest/gtest.h"

#include "../../../src/Domain/CreateTodoUseCase/CreateTodoUseCase.h"

using namespace Domain::CreateTodoUseCase;

namespace Test::Domain::CreateTodoUseCaseTest {
	class MockRepo : virtual public CreateTodoUseCaseRepositoryInterface {
	public:
		bool flagCreateWasCalled = false;

		void create(const Task& task) {
			EXPECT_EQ(task.id, 1);
			EXPECT_EQ(task.title, "This is my task");

			this->flagCreateWasCalled = true;
		}
	};

	TEST(DomainCreateTodoUseCaseTest, CanCreate) {
		MockRepo repo = MockRepo();

		CreateTodoUseCase(repo).create(Task(1, "This is my task"));
		EXPECT_TRUE(repo.flagCreateWasCalled);
	}
}
