#ifndef INTONATOR_H_
#define INTONATOR_H_

class Intonator {
  private:
    std::vector< Voice > zVoices{};
    std::vector< int > zTuning{};
    std::deque< std::vector < unsigned char > >
     zMessages{};
    std::vector< float > zTunetable{};
  public:
    Intonator();
    ~Intonator();
    void read_parameter_file(std::string filename);
    void read_channel_parameters(
     Parameters* parameters);
    void read_tunetable_file(std::string filename);
    int get_num_of_voices();
    void tune(unsigned char midicode);
    float get_frequency(unsigned char midicode);
    void push(std::vector< unsigned char > message);
    int something_to_pull();
    std::vector< unsigned char > pull();
};

#endif
