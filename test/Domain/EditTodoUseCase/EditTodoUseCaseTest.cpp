#include "gtest/gtest.h"

#include "../../../src/Domain/EditTodoUseCase/EditTodoUseCase.h"

using namespace Domain::EditTodoUseCase;

namespace Test::Domain::EditTodoUseCaseTest {
	class MockRepo : virtual public EditTodoUseCaseRepositoryInterface {
	public:
		bool flagEditWasCalled = false;

		void edit(const Task& task) {
			EXPECT_EQ(task.id, 1);
			EXPECT_EQ(task.title, "This is my task");

			this->flagEditWasCalled = true;
		}
	};

	TEST(DomainEditTodoUseCaseTest, CanEdit) {
		MockRepo repo = MockRepo();

		EditTodoUseCase(repo).edit(Task(1, "This is my task"));
		EXPECT_TRUE(repo.flagEditWasCalled);
	}
}
