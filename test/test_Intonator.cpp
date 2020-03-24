#include "../src/Intonator.h"

TEST ( Intonator, create_and_delete ) {
  Intonator* intonator;
  intonator = new Intonator();
  delete intonator;
}

TEST ( Intonator, read_parameter_file ) {
  Intonator* intonator;
  intonator = new Intonator();

  ASSERT_EQ(intonator->get_num_of_voices(), 0);

  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong4.txt"
    ),
    std::invalid_argument
  );
  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong5.txt"
    ),
    std::invalid_argument
  );
  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong6.txt"
    ),
    std::invalid_argument
  );
  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong1.txt"
    ),
    std::invalid_argument
  );
  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong2.txt"
    ),
    std::invalid_argument
  );
  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong3.txt"
    ),
    std::invalid_argument
  );

  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong7.txt"
    ),
    std::invalid_argument
  );

  ASSERT_THROW(
    intonator->read_parameter_file(
      "../test/testfiles/parameters_wrong8.txt"
    ),
    std::invalid_argument
  );

  intonator->read_parameter_file(
    "../test/testfiles/parameters.txt"
  );

  ASSERT_EQ(intonator->get_num_of_voices(), 4);

  delete intonator;
}

TEST ( Intonator, read_tunetable_file ) {
  Intonator* intonator;
  intonator = new Intonator();

  ASSERT_THROW(
    intonator->read_tunetable_file(
      "../test/testfiles/notexistingfile.txt"
    ),
    std::invalid_argument
  );

  ASSERT_THROW(
    intonator->read_tunetable_file(
      "../test/testfiles/tunetable_wrong1.txt"
    ),
    std::invalid_argument
  );

  ASSERT_THROW(
    intonator->read_tunetable_file(
      "../test/testfiles/tunetable_wrong2.txt"
    ),
    std::invalid_argument
  );

  ASSERT_THROW(
    intonator->read_tunetable_file(
      "../test/testfiles/tunetable_wrong3.txt"
    ),
    std::invalid_argument
  );

  ASSERT_THROW(
    intonator->read_tunetable_file(
      "../test/testfiles/tunetable_wrong4.txt"
    ),
    std::invalid_argument
  );
  
  ASSERT_THROW(
    intonator->read_tunetable_file(
      "../test/testfiles/tunetable_wrong5.txt"
    ),
    std::invalid_argument
  );

  intonator->read_tunetable_file(
    "../test/testfiles/tunetable.txt"
  );

  ASSERT_FLOAT_EQ(
    intonator->get_frequency(13),
    34.567890
  );

  delete intonator;
}

TEST ( Intonator, tune ) {
  Intonator* intonator;
  intonator = new Intonator();

  intonator->tune(57);

  ASSERT_FLOAT_EQ(
      intonator->get_frequency(64)
    / intonator->get_frequency(57),
    3.0/2.0
  );

  delete intonator;
}
