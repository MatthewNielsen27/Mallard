#include <iostream>
#include <string>
#include <fstream>

using namespace::std;

string make_string = "CC=g++\nCFLAGS=-I.\n\n#All source files used by main test file\n_SRC = duck.cpp\nSRC= $(patsubst %,../src/%,$(_SRC))\n\n#Name of main test file\nMAIN = tests.cpp\n\ntests: $(MAIN) $(SRC)\n\tg++ -o $@ $^ $(CFLAGS)";

void initiate(){
  system("mkdir tests");
  system("mkdir tests/notes");
  system("mkdir src");
  system("mkdir include");
  system("mkdir lib");
  system("mkdir docs");
  system("touch .gitignore");
  ofstream f;
  f.open("tests/tests.cpp");
  f <<"//This file can be used to run all your tests\n\n//Please add duck.hpp to this folder"<<endl;
  f << "#include \"../include/duck.hpp\"\n\nusing namespace::std;\n"<<endl;
  f << "int main(){\n\n//Start off with creating a duck of your own!\nDuck quacky(\"quacky\");\n"<<endl;
  f << "//Now configure your Duck however you like\n//Type './mallard help config' for a full list of commands\n"<<endl;
  f << "quacky.show_passes = true;\n\n//Now write some tests\n//Type './mallard help usage' for a full list of comands\n"<<endl;
  f << "quacky.watch(true,\"sample test\",__LINE__);\n\n//Show the status of tests\nquacky.status();\n\nreturn 0;\n}"<<endl;
  f.close();
  //Create the makefile
  f.open("tests/makefile");
  f <<make_string<<endl;
  f.close();
}

int main(int argc, const char *argv[]){
  if(argc > 1){
    string base_param = string(argv[1]);
    if(base_param == "init"){
      initiate();
    }else if(base_param == "run"){ //Work on mallard functionality
      system("cd tests && make && ./tests");
    }else if(base_param == "rollback"){
      if(argc > 3){
        string duckname = string(argv[2]);
        string filename = string(argv[3]);
        string cmd1 = "cat tests/notes/" + duckname + "_pick.cpp | pbcopy";
        string cmd2 = "pbpaste > src/" + filename;
        system(cmd1.c_str());
        system(cmd2.c_str()); 
      }else{
        cerr <<"Error: insufficient command-line arguments"<<endl;
        cerr <<"Expecting: ./mallard rollback duckname file_to_be_rolled_back"<<endl;
      }
    }else if(base_param == "help" ){
      if(argc > 2){
        string second_param = string(argv[2]);
        if(second_param == "config"){
          cout<<"# Current customization supported by Mallard:"<<endl;
          cout<<"## GENERAL CONFIGURATIONS"<<endl;
          cout<<"* [BOOLEAN] show_passes - if passed tests will be displayed to the console"<<endl;
          cout<<"* [BOOLEAN] show_fails - if failed tests will be displayed to the console"<<endl;
          cout<<"* [BOOLEAN] show_reason - if the reason for failed tests will be displayed to the console"<<endl;
          cout<<"* [BOOLEAN] file_logging - if file logging is enabled"<<endl;
          cout<<"* [BOOLEAN] time_series - if a time-series file log is generated"<<endl;
          cout<<"* [BOOLEAN] version_control - save the best performing version of your file"<<endl;
          cout<<"\n# Example usage\nDuck quacky(\"quacky\",\"usage_file.cpp\");\nquacky.show_fails = true;\nquacky.time_series = true;"<<endl;
        }else if(second_param == "usage"){
         cout<<"# Current commands supported by Mallard:"<<endl; 
         cout<<"## WATCHPOINTS"<<endl;
         cout<<"* [INTEGER EQUALITY] void watch(int expected, int actual, string test_name, int line)"<<endl;
         cout<<"* [FLOAT EQUALITY] void watch(float expected, float actual, float tolerance, string test_name, int line)"<<endl;
         cout<<"* [STRING EQUALITY] void watch(string expected, string actual, string test_name, int line)"<<endl;
         cout<<"* [INTEGER RETURN] void watch(int result, string test_name, int line)"<<endl;
         cout<<"* [BOOLEAN RETURN] void watch(bool result, string test_name, int line)"<<endl;
         cout<<"\n## LOGGING"<<endl;
         cout<<"void take_notes()"<<endl;
         cout<<"void end_notes()"<<endl;
         cout<<"void status()"<<endl;
         cout<<"\n# Example usage\nDuck quacky(\"quacky\",\"usage_file.cpp\");"<<endl;
         cout<<"quacky.take_notes();\n\nquacky.watch(validate(username,password),\"Successful login test\",__line__);"<<endl;
         cout<<"\nquacky.status();\nquacky.end_notes();"<<endl;
        }
      }else{
        cout<<"# MALLARD CONSOLE COMMANDS"<<endl;
        cout<<"## General purpose commands"<<endl;
        cout<<"help config - see how to manage mallard configuations"<<endl;
        cout<<"help usage - see how to use mallard"<<endl;
        cout<<"init - restore mallard directories"<<endl;
        cout<<"run - run mallard test suite"<<endl;
        cout<<"rollback duck_name usage_file - rollback to best performing version of your usage file"<<endl;
      }
    }
    return 0;
  }else{
    cerr<<"Error: Expecting a command line argument"<<endl;
    cerr<<"Please enter './mallard help' into the command line for a list of all command line arguments"<<endl;
    return 1;
  }
}