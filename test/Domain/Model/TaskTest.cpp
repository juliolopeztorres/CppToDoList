#include "gtest/gtest.h"

#include "../../../src/Domain/Model/Task.h"

using namespace Domain::Model;

namespace Test::Domain::Model::TaskTest {
	TEST(DomainModelTaskTest, CanCreate) {
		Task task = Task(1, "My title");

		EXPECT_EQ(task.id, 1);
		EXPECT_EQ(task.title, "My title");
	}

	TEST(DomainModelTaskTest, CanUpdate) {
		Task task = Task(1, "My title");

		EXPECT_EQ(task.id, 1);
		EXPECT_EQ(task.title, "My title");

		task.id = 4;
		task.title = "My new title";

		EXPECT_EQ(task.id, 4);
		EXPECT_EQ(task.title, "My new title");
	}
};
