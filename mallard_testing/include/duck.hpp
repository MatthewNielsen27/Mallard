#include <fstream>
#include <string>

using namespace::std;

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
  string filename;
  //Output file stream for log file                                                          
  ofstream log_file;
  //String to hold unique test signature
  string test_signature;
  //The duck's duck_name
  string duck_name;

  //Constructor(s)
  //Default constructor
  Duck(string duckname);
  //Constructor for when a duck supervises a certain implementation file
  Duck(string duckname, string hostname);

  //Watch functionality
  //Print the outcome of a test [INTEGER EQUALITY]
  void watch(int expected, int actual, string test_name, int line); 
  //Print the outcome of a test [STRING EQUALITY]          
  void watch(string expected, string actual, string test_name, int line);
  //Print outcome of a test [FLOAT EQUALITY]     
  void watch(float expected, float actual, float tolerance, string test_name, int line);
  //Print the outcome of a test [INTEGER RETURN] 
  void watch(int result, string test_name, int line);
  //Print the outcome of a test [BOOLEAN RETURN]
  void watch(bool result, string test_name, int line);                        

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
  bool _file_exists(string fileName);
  //Return absolute value of a floating-point number
  float _fabs(float val);
  //If two floating-point numbers are within range of a given tolerance
  bool _within_range(float expected, float actual, float tolerance);
};
