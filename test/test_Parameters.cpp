#include "../src/Parameters.h"

TEST ( Parameters, create_and_delete ) {
  Parameters* parameters;
  parameters = new Parameters();
  delete parameters;
}

TEST ( Parameters, read_line_and_name_occurs ) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_FALSE(parameters->name_occurs("hallo"));
  parameters->read_line(" \% comment");
  ASSERT_FALSE(parameters->name_occurs("hallo"));
  parameters->read_line("hallo du da \% comment");
  ASSERT_TRUE(parameters->name_occurs("hallo"));
  ASSERT_THROW(
    parameters->read_line("hallo dibi dub dub"),
    std::invalid_argument
  );

  delete parameters;
}

TEST ( Parameters, get_values) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_THROW(
    parameters->get_values("Eins"),
    std::invalid_argument
  );
  parameters->read_line("Zwei dup di");
  ASSERT_THROW(
    parameters->get_values("Eins"),
    std::invalid_argument
  );
  std::vector < std::string > values{"dup", "di"};
  ASSERT_EQ(
    parameters->get_values("Zwei"),
    values
  );
  delete parameters;
}

TEST (Parameters, read_file) {
  Parameters* parameters;
  parameters = new Parameters();
  ASSERT_THROW(
    parameters->read_file("notexisting_file.txt"),
    std::invalid_argument
  );
  ASSERT_THROW(
    parameters->read_file(
      "../test/testfiles/parameters1.txt"
    ),
    std::invalid_argument
  );
  parameters->read_file(
    "../test/testfiles/parameters2.txt"
  );
  std::vector< std::string > output {"du", "da"};
  ASSERT_EQ(
    parameters->get_values("hallo"),
    output
  );
  delete parameters;
}
