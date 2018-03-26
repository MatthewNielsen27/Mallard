#ifndef DUCK_HPP
#define DUCK_HPP

#include <fstream>
#include <string>

//Duck testing object
class Duck{
  public:
  //Stats
  //Total number of tests executed
  int total;
  //Total number of failed tests                                                                 
  int passed;
  //Total number of failed tests
  int failed;

  //Configs
  //If successful tests are logged
  bool show_passes;
  //If failed tests are logged
  bool show_fails;
  //If the outcome of failed tests is logged
  bool show_reason;
  //If results are logged in a file
  bool file_logging;
  //If version control is enabled
  bool version_control;
  //If time series tracking is enabled                                                       
  bool time_series;
  //Name of implementation file
  std::string filename;
  //Output file stream for log file                                                          
  std::ofstream log_file;
  //std::string to hold unique test signature
  std::string test_signature;
  //The duck's duck_name
  std::string duck_name;

  //Constructor(s)
  //Default constructor
  Duck(std::string duckname);
  //Constructor for when a duck supervises a certain implementation file
  Duck(std::string duckname, std::string hostname);

  //Watch functionality
  //Print the outcome of a test [INTEGER EQUALITY]
  void watch(int expected, int actual, std::string test_name, int line); 
  //Print the outcome of a test [std::string EQUALITY]          
  void watch(std::string expected, std::string actual, std::string test_name, int line);
  //Print outcome of a test [FLOAT EQUALITY]     
  void watch(float expected, float actual, float tolerance, std::string test_name, int line);
  //Print the outcome of a test [INTEGER RETURN] 
  void watch(int result, std::string test_name, int line);
  //Print the outcome of a test [BOOLEAN RETURN]
  void watch(bool result, std::string test_name, int line);                        

  //Logging
  //Start logging
  void take_notes();
  //Stop logging
  void end_notes();
  //Display current info about the test suite
  void status();

  private:
  //Executes version control
  void _track_version();
  //Logs time series data
  void _log_time_series();
  //If a certain file already exists
  bool _file_exists(std::string fileName);
  //Return absolute value of a floating-point number
  float _fabs(float val);
  //If two floating-point numbers are within range of a given tolerance
  bool _within_range(float expected, float actual, float tolerance);
};
#endif
