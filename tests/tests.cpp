//This file can be used to run all your tests

//Please add duck.hpp to this folder
#include "../include/duck.hpp"

using namespace::std;

int main(){

//Start off with creating a duck of your own!
Duck duck("duck");

//Now configure your Duck however you like
//Type './mallard help config' for a full list of commands

duck.show_passes = true;

//Now write some tests
//Type './mallard help usage' for a full list of comands

duck.watch(true, "boolean return value",__LINE__);
duck.watch(false, "boolean return value", __LINE__);

duck.watch(0, "integer return value", __LINE__);
duck.watch(1, "integer return value", __LINE__);

duck.watch("foo", "foo", "string equality", __LINE__);
duck.watch("foo", "bar", "string equality", __LINE__);

duck.watch(1, 1, "integer equality", __LINE__);
duck.watch(1, 2, "integer equality", __LINE__);

duck.watch(1.5, 1.5, 0.01, "float value within threshold", __LINE__);
duck.watch(1.5, 1.49, 0.001, "float value within threshold", __LINE__);

//Show the status of tests
duck.status();

return 0;
}
