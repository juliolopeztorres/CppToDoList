#include "gtest/gtest.h"

#include "../../../src/Framework/Mapper/TaskListMapper.h"

using namespace Framework::Mapper;

namespace Test::Framework::Mapper::TaskListMapperTest {
	TEST(FrameworkMapperTaskListMapperTest, CanMap) {
		std::vector<Task> tasks = {
			Task(1, "My title"), 
			Task(2, "Another task")
		};

		string expectedOutput = R"(	Task ID: 1
	Title: My title

	Task ID: 2
	Title: Another task
)";

		EXPECT_EQ(TasksMapper::map(tasks), expectedOutput);
	}
}
