#include <iostream>
#include <queue>
#include <math.h>
#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "Voice.h"
#include "Intonator.h"

Intonator::Intonator() {
  for ( unsigned int i=0; i<12; i++ ) {
    zTunetable.push_back(cFrequenciesEqual[i]);
  }
}

Intonator::~Intonator() {

}

void Intonator::read_parameter_file(
 std::string filename) {
  Parameters* parameters;
  parameters = new Parameters();

  parameters->read_file(filename);

  read_channel_parameters(parameters);

  delete parameters;
}

void Intonator::read_channel_parameters(
 Parameters* parameters) {
   if ( ! (
       (parameters->name_occurs("channels"))
    && (parameters->name_occurs("bending"))
    && (parameters->name_occurs("tuning"))
  )) {
    throw std::invalid_argument(
      "All parameters 'channels', 'bending' and "
      "'tuning' must occur in the parameter file."
    );
  }

  std::vector< std::string > channels =
   parameters->get_values("channels");
  std::vector< std::string > bending =
   parameters->get_values("bending");
  std::vector< std::string > tuning = 
   parameters->get_values("tuning");

  if ( ! (
       (channels.size() == bending.size())
    && (channels.size() == tuning.size())
  )) {
    throw std::invalid_argument(
      "The parameters 'channel', 'bending' and "
      "'tuning' must have the same length."
    );
  } 
  zVoices.clear();

  for ( unsigned int i=0; i<channels.size(); i++ ) {
    zVoices.push_back(Voice());
    zVoices.back().set_channel(channels[i]);
    zVoices.back().set_bending(std::stof(bending[i]));
  }
}

int Intonator::get_num_of_voices() {
  return zVoices.size();
}

void Intonator::tune(unsigned char midicode) {

  midicode = midicode % 12;

  float freq = zTunetable[midicode];
  int diff = 0;
  for ( unsigned int i=0; i<12; i++ ) {
    diff = i - midicode;
    if (diff == 7) {
      zTunetable[i] = 3.0/2.0 * freq;
    }
    else if (diff == -7) {
      zTunetable[i] = 2.0/3.0 * freq;
    }
    else if (diff == 5) {
      zTunetable[i] = 4.0/3.0 * freq;
    }
    else if (diff == -5) {
      zTunetable[i] = 3.0/4.0 * freq;
    }
    else if (diff == 4) {
      zTunetable[i] = 5.0/4.0 * freq;
    }
    else if (diff == -4) {
      zTunetable[i] = 4.0/5.0 * freq;
    }
    else if (diff == 3) {
      zTunetable[i] = 6.0/5.0 * freq;
    }
    else if (diff == -3) {
      zTunetable[i] = 5.0/6.0 * freq;
    }
    else if (diff == 9) {
      zTunetable[i] = 5.0/3.0 * freq;
    }
    else if (diff == -9) {
      zTunetable[i] = 3.0/5.0 * freq;
    }
    else if (diff == 8) {
      zTunetable[i] = 8.0/5.0 * freq;
    }
    else if (diff == -8) {
      zTunetable[i] = 5.0/8.0 * freq;
    }
  }
}

float Intonator::get_frequency(
 unsigned char midicode) {
  unsigned char midicode0 = midicode % 12;
  int octaves = (midicode - midicode0) / 12;
  return zTunetable[midicode0] * pow(2.0, octaves);
}

void Intonator::push(std::vector< unsigned char > message) {
  StatusByteType type
   = utils::status_byte_type(message);
  unsigned int channel = utils::channel(message);
  unsigned char midicode = 0;
  unsigned char velocity = 0;
  for ( Voice &voice : zVoices ) {
    if (channel == voice.get_channel()) {
      if (type == note_on) {
        midicode = message[1];
        velocity = message[2];
        tune(midicode);
        voice.set_frequency(get_frequency(midicode));
        voice.set_velocity(velocity);
        voice.calculate();
//        if (channel == 0) {
        zMessages.push_back(
          voice.get_bending_message()
        );
        zMessages.push_back(
          voice.get_note_on_message()
        );
//        }
      }
      else if (type == note_off) {
//        if (channel == 0) {
          zMessages.push_back(
            voice.get_note_off_message()
          );
//        }
      }
    }
  }
}

int Intonator::something_to_pull() {
  return (zMessages.size());
}

std::vector< unsigned char > Intonator::pull() {
  std::vector< unsigned char > result =
   zMessages.front();
  zMessages.pop_front();
  return result;
};
