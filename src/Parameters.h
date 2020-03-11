#ifndef PARAMETERS_H_
#define PARAMETERS_H_

class Parameters {
  private:
    std::vector< std::string > zNames {};
    std::vector< std::vector < std::string > >
      zValues {};
  public:
    Parameters();
    ~Parameters();
    void init();
    void read_line(std::string line);
    int name_occurs(std::string name);
    std::vector < std::string > get_values(
      std::string name
    );
    void read_file(std::string filename);
};

#endif
