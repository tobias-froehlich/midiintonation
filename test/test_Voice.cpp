#include <math.h>
#include "../src/const.h"
#include "../src/utils.h"
#include "../src/Voice.h"

TEST ( Voice, create_and_delete ) {
  Voice* voice;
  voice = new Voice();
  delete voice;
}

TEST ( Voice, set_channel ) {
  Voice* voice;
  voice = new Voice();
  
  ASSERT_THROW(
    voice->set_channel("0"),
    std::invalid_argument
  );
  ASSERT_THROW(
    voice->set_channel("17"),
    std::invalid_argument
  );
  ASSERT_THROW(
    voice->set_channel("bla"),
    std::invalid_argument
  );

  voice->set_channel("5");
  ASSERT_EQ(voice->get_channel(), 4);

  delete voice;
}

TEST ( Voice, set_bending ) {
  Voice* voice;
  voice = new Voice();

  voice->set_bending(2.0);
  ASSERT_FLOAT_EQ(voice->get_bending(), 2.0);

  delete voice;
}

TEST ( Voice, set_velocity ) {
  Voice* voice;
  voice = new Voice();

  voice->set_velocity(50);
  ASSERT_EQ(voice->get_velocity(), 50);

  delete voice;
}

TEST ( Voice, set_midicode_in ) {
  Voice* voice;
  voice = new Voice();
  
  voice->set_midicodein(5);
  ASSERT_EQ(voice->get_midicodein(), 5);

  delete voice;
}

TEST ( Voice, set_frequency ) {
  Voice* voice;
  voice = new Voice();
  
  voice->set_frequency(220.0);
  ASSERT_FLOAT_EQ(voice->get_frequency(), 220.0);
  
  delete voice;
}


TEST ( Voice, calculate ) {
  ASSERT_FLOAT_EQ(log(2.7182818284590451), 1.0);

  Voice* voice;
  voice = new Voice();

  voice->set_channel("3");
  voice->set_bending(1.0);
  voice->set_velocity(50);
  voice->set_frequency(440.0);
  
  voice->calculate();

  std::vector<unsigned char > bendingmessage
   {226, 0, 64};

  std::vector< unsigned char > noteonmessage
   {146, 57, 50};

  std::vector< unsigned char > noteoffmessage
   {130, 57, 0};

  ASSERT_EQ(voice->get_bending_message(), bendingmessage);
  ASSERT_EQ(voice->get_note_on_message(), noteonmessage);
  ASSERT_EQ(voice->get_note_off_message(), noteoffmessage);

  delete voice;
}
