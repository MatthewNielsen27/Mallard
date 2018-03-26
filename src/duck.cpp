#include <iostream>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <string>
#include "../include/duck.hpp"

Duck::Duck(std::string duckname){
  //Save file duck_name
  duck_name = duckname; 
  total = 0;
  passed = 0;
  failed = 0;
  file_logging = false;
  version_control = false;
  show_fails = true;
  show_reason = true;
  show_passes = true; 
}

Duck::Duck(std::string duckname, std::string hostname){
  //Save file duck_name
  filename = hostname.substr(0, hostname.find(".")); //Fix to leave out the dots
  duck_name = duckname; 
  total = 0;
  passed = 0;
  failed = 0;
  file_logging = false;
  version_control = false;
  show_fails = true;
  show_reason = true;
  show_passes = true; 
}

void Duck::watch(int expected, int actual, std::string test_name, int line){
  total++;
  test_signature += test_name;
  if(expected != actual){
    failed++;
    if(show_fails || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[value was '" + std::to_string(actual) + "' but '" + std::to_string(expected) + "' was expected]";

      if(show_fails)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;  
    }
  } 
}

float Duck::_fabs(float val){
  return val >= 0 ? val : -1 * val; 
}

bool Duck::_within_range(float expected, float actual, float tolerance){
  return (_fabs(expected - actual) <= _fabs(tolerance));
}

void Duck::watch(float expected, float actual, float tolerance, std::string test_name, int line){
  total++;
  test_signature += test_name;
  if(!_within_range(expected, actual, tolerance)){
    failed++;
    if(show_fails || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[value was '" + std::to_string(actual) + "' but '" + std::to_string(expected) + "' was expected, with a tolerance of " + std::to_string(tolerance) + "]";

      if(show_fails)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;  
    }
  } 
}

void Duck::watch(std::string expected, std::string actual, std::string test_name, int line){
  total++;
  test_signature += test_name;
  if(expected != actual){
    failed++;
    if(show_fails || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[value was '" + actual + "' but '" + expected + "' was expected]";

      if(show_fails)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;  
    }
  }
}

void Duck::watch(int result, std::string test_name, int line){
  total++;
  test_signature += test_name;
  if(result){
    failed++;
    if(show_fails || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[status code " + std::to_string(result) + "]";

      if(show_fails)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;  
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;
    }
  }
}

void Duck::watch(bool result, std::string test_name, int line){
  total++;
  test_signature += test_name; 
  if(!result){
    failed++;
    //Only create message if logging is enabled
    if(show_fails || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[recieved a value of FALSE]";

      if(show_fails)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;    
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      std::string message = "TEST[" + test_name + "] LINE[" + std::to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        std::cout<<message<<std::endl;
      if(file_logging)
        log_file<<message<<std::endl;   
    }
  }
}

void Duck::status(){
  //If version control is enabled
  if(version_control)
    _track_version();

  //Output current test suite statistics
  std::cout <<"--------------------Test-Suite-Statistics--------------------"<<std::endl;
  std::cout <<"TOTAL["<<total<<"] \tPASSED["<<passed<<"] \tFAILED["<<failed<<"]"<<std::endl;
}

void Duck::_track_version(){
  //Input file stream
  std::ifstream ts_in;        
  //Output file stream       
  std::ofstream ts_out;
  //Test signature from file           
  std::string sig;
  //Test results from file                   
  std::string pas;

  //Create hash of test singature
  std::hash<std::string> hasher;
  size_t test_sig = hasher(test_signature);

  //Input stream of test signature results
  ts_in.open("notes/"+ duck_name +"_signature.txt");

  //Get signature results
  ts_in >>sig;
  ts_in >>pas;

  //Close input stream of test signature results
  ts_in.close();

  //Output stream of test signature results
  ts_out.open("notes/"+ duck_name +"_signature.txt");

  //If there is a new test signature, or a better performing file
  if(sig != std::to_string(test_sig) || (sig == std::to_string(test_sig) && stoi(pas) <= passed)){
    //Update test signature file
    ts_out <<test_sig<<std::endl;
    ts_out <<passed<<std::endl;

    //Create copy of current file into a "_mallards_pick.cpp" file
    std::string cmd1 = "touch notes/" + duck_name + "_pick.cpp";
    std::string cmd2 = "cat ../src/" + filename + ".cpp | pbcopy";
    std::string cmd3 = "pbpaste > notes/" + duck_name + "_pick.cpp";
    system(cmd1.c_str());
    system(cmd2.c_str());
    system(cmd3.c_str());
  }
  else{
    //Save current data to the file
    ts_out <<sig<<std::endl;
    ts_out <<pas<<std::endl;
  }

  //Close output stream of test signature results
  ts_out.close();
}

void Duck::take_notes(){
  //Enable logging
  file_logging = true;

  //Open log file
  log_file.open("notes/" + duck_name + "_notes.txt");
}

bool Duck::_file_exists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void Duck::_log_time_series(){
  //Get current time
  time_t t = time(0);
  struct tm * now = localtime( & t );
  
  //Append .csv file if it already exists
  if (_file_exists("notes/" + duck_name + ".csv")) {
    std::ofstream fs;
    fs.open ("notes/" + duck_name + ".csv", std::ofstream::app);
    fs <<now->tm_year + 1900<<"/"<<now->tm_mon + 1<<"/"<<now->tm_mday;
    fs <<" "<<now->tm_hour<<":"<<now->tm_min<<":"<<now->tm_sec;
    fs <<","<< total<<","<<passed<<","<<failed<<std::endl;
    fs.close();
  }
  else{//create a new file with legend if the .csv file does not exist
    std::ofstream fs;
    fs.open ("notes/" + duck_name + ".csv");
    fs <<"date,total,passed,failed"<<std::endl;
    fs <<now->tm_year + 1900<<"/"<<now->tm_mon + 1<<"/"<<now->tm_mday;
    fs <<" "<<now->tm_hour<<":"<<now->tm_min<<":"<<now->tm_sec;
    fs <<","<< total<<","<<passed<<","<<failed<<std::endl;
    fs.close();
  }
}

void Duck::end_notes(){
  //Disable logging
  file_logging = false;

  //Log time series if enabled
  if(time_series)
    _log_time_series();

  //Print final test statistics to log file
  if(total > 0){
    log_file<<"--------------------Test-Suite-Statistics--------------------"<<std::endl;
    log_file<<"TOTAL["<<total<<"] \tPASSED["<<passed<<"] \tFAILED["<<failed<<"]"<<std::endl;
  }

  //Close log file
  log_file.close();
}