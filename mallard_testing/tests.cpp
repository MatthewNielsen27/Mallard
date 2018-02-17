//This file can be used to run all your tests

//Please add duck.hpp to this folder
#include "include/duck.hpp"

using namespace::std;

int main(){

//Start off with creating a duck of your own!
Duck quacky("quacky");

//Now configure your Duck however you like
//Type './mallard help config' for a full list of commands

quacky.show_passes = true;

//Now write some tests
//Type './mallard help usage' for a full list of comands

quacky.watch(true,"sample test",__LINE__);

//Show the status of tests
quacky.status();

return 0;
}
