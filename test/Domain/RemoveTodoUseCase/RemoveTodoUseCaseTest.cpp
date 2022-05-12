#include "gtest/gtest.h"

#include "../../../src/Domain/RemoveTodoUseCase/RemoveTodoUseCase.h"

using namespace Domain::RemoveTodoUseCase;

namespace Test::Domain::RemoveTodoUseCaseTest {
	class MockRepo : virtual public RemoveTodoUseCaseRepositoryInterface {
	public:
		bool flagRemoveWasCalled = false;

		void remove(const int& id) {
			EXPECT_EQ(id, 1);

			this->flagRemoveWasCalled = true;
		}
	};

	TEST(DomainRemoveTodoUseCaseTest, CanRemove) {
		MockRepo repo = MockRepo();

		RemoveTodoUseCase(repo).remove(1);
		EXPECT_TRUE(repo.flagRemoveWasCalled);
	}
}
