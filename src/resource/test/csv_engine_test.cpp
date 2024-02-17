#include "csv_engine_test.h"

// Resource
#include "includes/resource/csv/engine/string_parser.h"


TEST_F(CSV_Engine_Test, null_CSV_File)
{
	CSV::Engine::String_Parser test(std::string(""), ';');
	
	auto line = test.Next_Line();
	EXPECT_FALSE(line.has_value());
	line = test.Next_Line();
	EXPECT_FALSE(line.has_value());
}

TEST_F(CSV_Engine_Test, wrong_string)
{
	CSV::Engine::String_Parser test(std::string("123456789skjdfhskjdfhjsdklqsjdfh"), ';');

	auto line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 1);
	EXPECT_EQ(line.value()[0], "123456789skjdfhskjdfhjsdklqsjdfh");
	line = test.Next_Line();
	EXPECT_FALSE(line.has_value());
}

TEST_F(CSV_Engine_Test, diferent_size)
{
	CSV::Engine::String_Parser test(std::string("1;2;3\n1;2;3\n1;2;3;4\n1\n"), ';');

	auto line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 3);
	EXPECT_EQ(line.value(), std::vector<std::string>({"1", "2", "3"}));
	line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 3);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1", "2", "3" }));
	line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 4);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1", "2", "3","4" }));
	line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 1);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1" }));
	line = test.Next_Line();
	EXPECT_FALSE(line.has_value());
}

TEST_F(CSV_Engine_Test, wrong_delimiter)
{
	CSV::Engine::String_Parser test(std::string("1;2;3\n1;2;3\n1;2;3;4\n1\n"), ' ');

	auto line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 1);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1;2;3" }));
	line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 1);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1;2;3"}));
	line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 1);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1;2;3;4" }));
	line = test.Next_Line();
	EXPECT_TRUE(line.has_value());
	EXPECT_EQ(line.value().size(), 1);
	EXPECT_EQ(line.value(), std::vector<std::string>({ "1" }));
	line = test.Next_Line();
	EXPECT_FALSE(line.has_value());
}

TEST_F(CSV_Engine_Test, paralelle_reading)
{
	std::string base_test_str = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50\n";
	std::string test_str;
	const int repetition = 500;
	for (int i = 0; i < repetition; i++)
		test_str += base_test_str;

	CSV::Engine::String_Parser test(std::move(test_str),',');
	std::vector<std::thread> thread_container;
	for (int i = 0; i < repetition; i++)
	{
		thread_container.emplace_back([&]() {
			auto line = test.Next_Line();
			EXPECT_TRUE(line.has_value());
			EXPECT_EQ(line.value().size(), 50);
			EXPECT_EQ(line.value(), std::vector<std::string>({ "1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50"}));
		});
	}

	for (std::thread& thread : thread_container)
		thread.join();
	auto line = test.Next_Line();
	EXPECT_FALSE(line.has_value());
}
	