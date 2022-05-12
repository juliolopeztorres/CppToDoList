cmake_minimum_required(VERSION 3.0)

add_sources(. SRCS)

find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(LearningCpp_tests ${SRCS})

target_link_libraries(
	LearningCpp_tests 
	GTest::gtest 
	GTest::gtest_main 
	FrameworkLayer
)

add_test(LearningCpp LearningCpp_tests)

