#include "gtest/gtest.h"
#include <fstream>

#include "../../src/Data/Repository.h"

using namespace Data;

namespace Test::Data::RepositoryTest {
	class DataRepositoryTest : public testing::Test {
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
	};

	TEST_F(DataRepositoryTest, CanCreate) {
		Repository repo = Repository(this->store);

		EXPECT_NE(&repo, nullptr);
	}

	TEST_F(DataRepositoryTest, GetTasks) {
		this->populateStore();

		std::vector<Task> tasks = Repository(this->store).get();

		EXPECT_EQ(tasks.size(), 1);
		EXPECT_EQ(tasks[0].id, 1);
		EXPECT_EQ(tasks[0].title, "My Task");
	}

	TEST_F(DataRepositoryTest, CanCreateTask) {
		Repository repo = Repository(this->store);

		ASSERT_NO_THROW(repo.create(Task(1, "My Task")));

		std::vector<Task> tasks = repo.get();
		ASSERT_EQ(tasks.size(), 1);
		EXPECT_EQ(tasks[0].id, 1);
		EXPECT_EQ(tasks[0].title, "My Task");
	}

	TEST_F(DataRepositoryTest, CanEditTask) {
		this->populateStore();

		Repository repo = Repository(this->store);

		EXPECT_NO_THROW(repo.edit(Task(1, "My Task Modified")));

		std::vector<Task> tasks = repo.get();
		EXPECT_EQ(tasks.size(), 1);
		EXPECT_EQ(tasks[0].id, 1);
		EXPECT_EQ(tasks[0].title, "My Task Modified");
	}

	TEST_F(DataRepositoryTest, CanRemoveTask) {
		this->populateStore();

		Repository repo = Repository(this->store);

		EXPECT_NO_THROW(repo.remove(1));
		EXPECT_TRUE(repo.get().empty());
	}
}
