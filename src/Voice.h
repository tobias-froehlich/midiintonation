#ifndef VOICE_H_
#define VOICE_H_

class Voice {
  private:
    std::deque< std::vector< unsigned char > >
     zMessages{};
    unsigned int zChannel = 0;
    float zBending = 0.0;
    unsigned char zVelocity = 0;
    unsigned char zMidiCodeIn = 0;
    unsigned char zMidiCodeOut = 0;
    float zFrequency = 440.0;
    std::vector< unsigned char > zBendingMessage{};
    std::vector< unsigned char > zNoteOnMessage{};
    std::vector< unsigned char > zNoteOffMessage{};
  public:
    Voice();
    ~Voice();
    void set_channel(std::string channel_str);
    unsigned int get_channel();
    void set_bending(float bending);
    float get_bending();
    void set_velocity(unsigned char velocity);
    unsigned char get_velocity();
    void set_midicodein(unsigned char midicodein);
    unsigned char get_midicodein();
    void set_frequency(float frequency);
    float get_frequency();
    void calculate();
    std::vector< unsigned char >
     get_bending_message();
    std::vector< unsigned char >
     get_note_on_message();
    std::vector< unsigned char >
      get_note_off_message();
    int something_to_pull();
    std::vector< unsigned char > pull();
};

#endif
