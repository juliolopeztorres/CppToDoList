#include "gtest/gtest.h"
#include "../../../src/Data/Mapper/TaskListMapper.h"

using namespace Domain::Model;
using namespace Data::Mapper;

namespace Test::Data::Mapper::TaskListMapperTest {
	TEST(DataTaskListMapper, CanMap) {
		std::vector<Task> tasks = TasksMapper::map(
			json::parse(
				R"([{"id": 1, "title": "My task"}])"
			)
		);		

		EXPECT_EQ(tasks.size(), 1);
		EXPECT_EQ(tasks[0].id, 1);
		EXPECT_EQ(tasks[0].title, "My task");
	}
};
