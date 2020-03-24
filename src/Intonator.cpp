#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "Voice.h"
#include "Intonator.h"

Intonator::Intonator() {
  for ( unsigned int i=0; i<128; i++ ) {
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

  if (parameters->name_occurs("tunetable")) {
    if (parameters->get_values("tunetable").size()
     != 1) {
      throw std::invalid_argument(
        "If a tunetable file is given in the "
        "parameter file, it must be exactly one."
      );
    }
    else {
      read_tunetable_file(
        parameters->get_values("tunetable")[0]
      );
    }
  }

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
    if (tuning[i].compare("yes") == 0) {
      zTuning.push_back(1);
    }
    else if (tuning[i].compare("no") == 0) {
      zTuning.push_back(0);
    }
    else {
      throw std::invalid_argument("Tuning can be yes or no.");
    }
  }  
}

void Intonator::read_tunetable_file(
 std::string filename) {
  std::ifstream file(filename.c_str());

  if ( ! file ) {
    throw std::invalid_argument(
      "File not found: tunetable file"
    );
  }

  std::string line;
  std::vector < std::string > words;
  unsigned char midicode;
  float frequency;
  int linenumber = -1;
  while ( getline(file, line) ) {
    linenumber++;
    words = utils::split(line, ' ');
    if (words.size() != 2) {
      throw std::invalid_argument(
        "Tunetable file must have 2 numbers "
        "in each line."
      );
    }

    try {
      midicode = std::stoi(words[0]);
    }
    catch (const std::invalid_argument& ia) {
      throw std::invalid_argument(
        "Tunetable file must have integers "
        "in the first column."
      );
    }

    if (midicode != linenumber) {
      throw std::invalid_argument(
        "Tunetable must have the numbers "
        "0 to 127 in the first column. "
        "(This is redundant, I know.)"
      );
    }

    try {
      frequency = std::stof(words[1]);
    }
    catch (std::invalid_argument& ia) {
      throw std::invalid_argument(
        "Tunetable file must have a float "
        "in the second column."
      );
    }
    zTunetable[midicode] = frequency;
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
  for(unsigned int i=12; i<128; i++) {
    zTunetable[i] = zTunetable[i % 12] * pow(2.0, (i - i % 12)/12);
  }
}

float Intonator::get_frequency(
 unsigned char midicode) {
  return zTunetable[midicode];
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
        if (zTuning[channel]) {
          tune(midicode);
        }
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
