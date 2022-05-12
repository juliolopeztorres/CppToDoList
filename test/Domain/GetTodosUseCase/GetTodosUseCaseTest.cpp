#include "gtest/gtest.h"

#include "../../../src/Domain/GetTodosUseCase/GetTodosUseCase.h"

using namespace Domain::GetTodosUseCase;

namespace Test::Domain::GetTodosUseCaseTest {
	class MockRepo : virtual public GetTodosUseCaseRepositoryInterface {
	private:
		std::vector<Task> tasks;
	public:
		bool flagGetWasCalled = false;

		MockRepo(std::vector<Task> tasks) {
			this->tasks = tasks;
		}

		std::vector<Task> get() {
			this->flagGetWasCalled = true;
			return this->tasks;
		}
	};

	TEST(DomainGetTodosUseCaseTest, CanGet) {
		MockRepo repo = MockRepo({ Task(1, "Hey yo"), Task(2, "Yet another task") });

		std::vector<Task> tasks = GetTodosUseCase(repo).get();

		EXPECT_EQ(tasks.size(), 2);
		EXPECT_EQ(tasks[1].title, "Yet another task");
		EXPECT_TRUE(repo.flagGetWasCalled);
	}
}
