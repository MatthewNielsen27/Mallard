#include <iostream>
#include <unordered_map>
#include <ctime>
#include <fstream>
#include <string>
#include "../include/duck.hpp"

using namespace::std;

Duck::Duck(string duckname){
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

Duck::Duck(string duckname, string hostname){
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

void Duck::watch(int expected, int actual, string test_name, int line){
  total++;
  test_signature += test_name;
  if(expected != actual){
    failed++;
    if(show_fails || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[value was '" + to_string(actual) + "' but '" + to_string(expected) + "' was expected]";

      if(show_fails)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;  
    }
  } 
}

float Duck::_fabs(float val){
  return val >= 0 ? val : -1 * val; 
}

bool Duck::_within_range(float expected, float actual, float tolerance){
  return (_fabs(expected - actual) <= _fabs(tolerance));
}

void Duck::watch(float expected, float actual, float tolerance, string test_name, int line){
  total++;
  test_signature += test_name;
  if(!_within_range(expected, actual, tolerance)){
    failed++;
    if(show_fails || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[value was '" + to_string(actual) + "' but '" + to_string(expected) + "' was expected, with a tolerance of " + to_string(tolerance) + "]";

      if(show_fails)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;  
    }
  } 
}

void Duck::watch(string expected, string actual, string test_name, int line){
  total++;
  test_signature += test_name;
  if(expected != actual){
    failed++;
    if(show_fails || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[value was '" + actual + "' but '" + expected + "' was expected]";

      if(show_fails)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;  
    }
  }
}

void Duck::watch(int result, string test_name, int line){
  total++;
  test_signature += test_name;
  if(result){
    failed++;
    if(show_fails || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[status code " + to_string(result) + "]";

      if(show_fails)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;  
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;
    }
  }
}

void Duck::watch(bool result, string test_name, int line){
  total++;
  test_signature += test_name; 
  if(!result){
    failed++;
    //Only create message if logging is enabled
    if(show_fails || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[FAILED]";
      if(show_reason)
        message += " REASON[recieved a value of FALSE]";

      if(show_fails)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;    
    }
  }
  else{
    passed++;
    if(show_passes || file_logging){
      string message = "TEST[" + test_name + "] LINE[" + to_string(line) + "] OUTCOME[PASSED]";

      if(show_passes)
        cout<<message<<endl;
      if(file_logging)
        log_file<<message<<endl;   
    }
  }
}

void Duck::status(){
  //If version control is enabled
  if(version_control)
    _track_version();

  //Output current test suite statistics
  cout <<"--------------------Test-Suite-Statistics--------------------"<<endl;
  cout <<"TOTAL["<<total<<"] \tPASSED["<<passed<<"] \tFAILED["<<failed<<"]"<<endl;
}

void Duck::_track_version(){
  //Input file stream
  ifstream ts_in;        
  //Output file stream       
  ofstream ts_out;
  //Test signature from file           
  string sig;
  //Test results from file                   
  string pas;

  //Create hash of test singature
  hash<string> hasher;
  size_t test_sig = hasher(test_signature);

  //Input stream of test signature results
  ts_in.open("mallard_notes/"+ duck_name +"_signature.txt");

  //Get signature results
  ts_in >>sig;
  ts_in >>pas;

  //Close input stream of test signature results
  ts_in.close();

  //Output stream of test signature results
  ts_out.open("mallard_notes/"+ duck_name +"_signature.txt");

  //If there is a new test signature, or a better performing file
  if(sig != to_string(test_sig) || (sig == to_string(test_sig) && stoi(pas) <= passed)){
    //Update test signature file
    ts_out <<test_sig<<endl;
    ts_out <<passed<<endl;

    //Create copy of current file into a "_mallards_pick.cpp" file
    string cmd1 = "touch mallard_notes/" + duck_name + "_pick.cpp";
    string cmd2 = "cat src/" + filename + ".cpp | pbcopy";
    string cmd3 = "pbpaste > mallard_notes/" + duck_name + "_pick.cpp";
    system(cmd1.c_str());
    system(cmd2.c_str());
    system(cmd3.c_str());
  }
  else{
    //Save current data to the file
    ts_out <<sig<<endl;
    ts_out <<pas<<endl;
  }

  //Close output stream of test signature results
  ts_out.close();
}

void Duck::take_notes(){
  //Enable logging
  file_logging = true;

  //Open log file
  log_file.open("mallard_notes/" + duck_name + "_notes.txt");
}

bool Duck::_file_exists(string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void Duck::_log_time_series(){
  //Get current time
  time_t t = time(0);
  struct tm * now = localtime( & t );
  
  //Append .csv file if it already exists
  if (_file_exists("mallard_notes/" + duck_name + ".csv")) {
    fstream fs;
    fs.open ("mallard_notes/" + duck_name + ".csv", fstream::app);
    fs <<now->tm_year + 1900<<"/"<<now->tm_mon + 1<<"/"<<now->tm_mday;
    fs <<" "<<now->tm_hour<<":"<<now->tm_min<<":"<<now->tm_sec;
    fs <<","<< total<<","<<passed<<","<<failed<<endl;
    fs.close();
  }
  else{//create a new file with legend if the .csv file does not exist
    ofstream fs;
    fs.open ("mallard_notes/" + duck_name + ".csv");
    fs <<"date,total,passed,failed"<<endl;
    fs <<now->tm_year + 1900<<"/"<<now->tm_mon + 1<<"/"<<now->tm_mday;
    fs <<" "<<now->tm_hour<<":"<<now->tm_min<<":"<<now->tm_sec;
    fs <<","<< total<<","<<passed<<","<<failed<<endl;
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
    log_file<<"--------------------Test-Suite-Statistics--------------------"<<endl;
    log_file<<"TOTAL["<<total<<"] \tPASSED["<<passed<<"] \tFAILED["<<failed<<"]"<<endl;
  }

  //Close log file
  log_file.close();
}