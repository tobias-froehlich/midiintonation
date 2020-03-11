#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "const.h"
#include "utils.h"
#include "Voice.h"

Voice::Voice() {

}

Voice::~Voice() {

}

void Voice::set_channel(std::string channel_str) {
  zChannel = std::stoi(channel_str) - 1;
  if ((zChannel < 0) || (zChannel >=16) ) {
    throw std::invalid_argument(
      "Channel number must be between 1 and 16."
    );
  }
}

unsigned int Voice::get_channel() {
  return zChannel;
}

void Voice::set_bending(float bending) {
  zBending = bending;
}

float Voice::get_bending() {
  return zBending;
}

void Voice::set_velocity(unsigned char velocity) {
  zVelocity = velocity;
}

unsigned char Voice::get_velocity() {
  return zVelocity;
}

void Voice::set_midicodein(
 unsigned char midicodein) {
  zMidiCodeIn = midicodein;
}

unsigned char Voice::get_midicodein() {
  return zMidiCodeIn;  
}

void Voice::set_frequency(float frequency) {
  zFrequency = frequency;
}

float Voice::get_frequency() {
  return zFrequency;
}

void Voice::calculate() {

  zMidiCodeOut = utils::find_nearest_midicode(
    zFrequency
  );

  float deviation_float =
      log(
        zFrequency / cFrequenciesEqual[zMidiCodeOut]
      )
    / cLogTwelfthRootOfTwo / zBending;
  int deviation_int =
   (int)(deviation_float * 8192.0) + 8192;


  std::vector< unsigned char > message{};

  message.push_back(224 + zChannel);
  message.push_back(
    (unsigned char)(deviation_int % 128)
  );
  message.push_back(
    (unsigned char)((deviation_int - deviation_int % 128)/128)
  );
  zBendingMessage = message;

  message.clear();

  message.push_back(144 + zChannel);
  message.push_back(zMidiCodeOut);
  message.push_back(zVelocity);
  zNoteOnMessage = message;

  message.clear();

  message.push_back(128 + zChannel);
  message.push_back(zMidiCodeOut);
  message.push_back(0);
  zNoteOffMessage = message;

}

std::vector< unsigned char >
 Voice::get_bending_message() {
  return zBendingMessage;
}

std::vector< unsigned char >
 Voice::get_note_on_message() {
  return zNoteOnMessage;
}

std::vector< unsigned char >
 Voice::get_note_off_message() {
  return zNoteOffMessage;
}

int Voice::something_to_pull() {
  return (zMessages.size());
}

std::vector< unsigned char > Voice::pull() {
  std::vector< unsigned char > result =
   zMessages.front();
  zMessages.pop_front();
  return result;
}
