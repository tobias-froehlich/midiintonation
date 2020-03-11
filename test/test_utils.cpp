#include "../src/const.h"
#include "../src/utils.h"

TEST(utils, split) {
  std::string str;
  std::vector< std::string > words;


  str = "eins zwei drei";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ' '), words);

  str = " eins  zwei   drei ";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ' '), words);

  str = "eins,zwei,drei";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ','), words);
}

TEST(utils, split_equal) {
  std::string str;
  std::vector< std::string > words;

  str = "abcdef";
  words = {"abc", "def"};
  ASSERT_EQ(utils::split_equal(str, 3), words);

  str = "abcdef";
  words = {"ab", "cd", "ef"};
  ASSERT_EQ(utils::split_equal(str, 2), words);

  str = "abcdef";
  words = {"abcd", "ef"};
  ASSERT_EQ(utils::split_equal(str, 4), words);

  str = "";
  words = {};
  ASSERT_EQ(utils::split_equal(str, 4), words);
}

TEST(utils, remove_comment) {
  std::string line = "hallo du \% da \% huhu";
  ASSERT_EQ(utils::remove_comment(line), "hallo du ");
  line = "hallo du ";
  ASSERT_EQ(utils::remove_comment(line), "hallo du ");
}

TEST(utils, square) {
  ASSERT_FLOAT_EQ(utils::square(3.0), 9.0);
  ASSERT_FLOAT_EQ(utils::square(-4.0), 16.0);
}

TEST(utils, float_equal) {
  ASSERT_TRUE(utils::float_equal(1.2345, 1.2345));
  ASSERT_FALSE(utils::float_equal(1.2345, 1.2346));
  ASSERT_TRUE(utils::float_equal(1.0, 1.0));
}

TEST( utils, inc_ending_number ) {
  ASSERT_EQ(
    utils::inc_ending_number("bla_1"),
    "bla_2"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla_9"),
    "bla_10"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla_100"),
    "bla_101"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla1"),
    "bla2"
  );
  ASSERT_EQ(
    utils::inc_ending_number("bla_blub99"),
    "bla_blub100"
  );
  
}

TEST ( utils, status_byte_type ) {
  std::vector< unsigned char > message1 {144, 5, 6};
  std::vector< unsigned char > message2 {145, 5, 6};
  std::vector< unsigned char > message3 {159, 5, 6};
  std::vector< unsigned char > message4 {128, 5, 6};
  std::vector< unsigned char > message5 {142, 5, 6};
  std::vector< unsigned char > message6 {143, 5, 6};
  std::vector< unsigned char > message7 {127, 5, 6};
  std::vector< unsigned char > message8 {161, 5, 6};
  std::vector< unsigned char > message9 {176, 64, 70};
  std::vector< unsigned char > message10 {191, 64, 40};

  ASSERT_EQ(
    utils::status_byte_type(message1),
    note_on
  );
  ASSERT_EQ(
    utils::status_byte_type(message2),
    note_on
  );
  ASSERT_EQ(
    utils::status_byte_type(message3),
    note_on
  );
  ASSERT_EQ(
    utils::status_byte_type(message4),
    note_off
  );
  ASSERT_EQ(
    utils::status_byte_type(message5),
    note_off
  );
  ASSERT_EQ(
    utils::status_byte_type(message6),
    note_off
  );
  ASSERT_EQ(
    utils::status_byte_type(message7),
    unknown
  );
  ASSERT_EQ(
    utils::status_byte_type(message8),
    unknown
  );
  ASSERT_EQ(
    utils::status_byte_type(message9),
    pedal_pressed
  );
  ASSERT_EQ(
    utils::status_byte_type(message10),
    pedal_released
  ); 
}

TEST ( utils, channel ) {
  std::vector< unsigned char > message1 {147, 5, 6};
  std::vector< unsigned char > message2 {131, 5, 6};
  std::vector< unsigned char > message3 {179, 64, 6};
  
  ASSERT_EQ(utils::channel(message1), 3);
  ASSERT_EQ(utils::channel(message2), 3);
  ASSERT_EQ(utils::channel(message3), 3);

}

TEST ( utils, find_nearest_midicode ) {
  ASSERT_EQ(utils::find_nearest_midicode(15.0), 0);
  ASSERT_EQ(utils::find_nearest_midicode(16.4), 0);
  ASSERT_EQ(utils::find_nearest_midicode(17.2), 1);
  ASSERT_EQ(utils::find_nearest_midicode(17.5), 1);
  ASSERT_EQ(utils::find_nearest_midicode(18.3), 2);
  ASSERT_EQ(utils::find_nearest_midicode(25087.0), 127);
  ASSERT_EQ(utils::find_nearest_midicode(25090.0), 127);
}
