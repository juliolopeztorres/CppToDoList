#include "gtest/gtest.h"

#include "../../../src/Framework/Mapper/TaskMapper.h"

using namespace Framework::Mapper;

namespace Test::Framework::Mapper::TaskMapperTest {
	TEST(FrameworkMapperTaskMapperTest, CanMap) {
		string expectedOutput = R"(	Task ID: 1
	Title: My title
)";

		EXPECT_EQ(
			TaskMapper::map(Task(1, "My title")),  
			expectedOutput
		);
	}
};
