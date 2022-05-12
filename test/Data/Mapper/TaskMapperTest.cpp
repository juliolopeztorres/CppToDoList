#include "gtest/gtest.h"

#include "../../../src/Data/Mapper/TaskMapper.h"

using namespace Data::Mapper;

namespace Test::Data::Mapper::TaskMapperTest {
	TEST(DataTaskMapper, CanMap) {
		Task task = TaskMapper::map(
			json::parse(
				R"({"id": 1, "title": "My task"})"
			)
		);

		EXPECT_EQ(task.id, 1);
		EXPECT_EQ(task.title, "My task");
	}

	TEST(DataTaskMapper, CanMapForSaving) {
		json taskJson = TaskMapper::mapForSaving(
			Task(1, "My task")
		);

		EXPECT_EQ(taskJson["id"].get<int>(), 1);

		// For some reason, EXPECT_EQ mark an error only on IDE (VS2022)
		string title = taskJson["title"].get<string>();
		EXPECT_EQ(title, "My task");
	}
};
