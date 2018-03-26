# Mallard

## A lightweight software testing framework

Designed as a lightweight solution to promote test-driven development, Mallard is an easy way to deploy unit testing on software for school projects and more!

## The rational

> Test-driven development guides your work towards an end goal while ensuring all previously achieved goals are still met

### Features

* Tell Mallard to watch your code at certain points to ensure your code works as expected!
* If specified, Mallard can provide runtime error reporting for your code and provides a detailed summary of your tests after your code's execution.
* Once your program has executed, Mallard will provide a customizable log file summarizing your the test's entire run.
* Mallard can be set up to track the best performing version of your code. You can rollback your code to the best performing version at any time!
* Mallard can also generate a time-series log file so you can track your code's performance over time

### Usage

In this document, any`duck.function()` represents a call made by a `Duck` object

Sample tests:

```cpp
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
```

By using the command `./mallard run` you can run all the tests stated within the `tests/tests.cpp` file. Any logs will be generated inside the `tests/notes` folder.

Results:

```console
TEST[boolean return value] LINE[21] OUTCOME[PASSED]
TEST[boolean return value] LINE[22] OUTCOME[FAILED] REASON[recieved a value of FALSE]

TEST[integer return value] LINE[24] OUTCOME[PASSED]
TEST[integer return value] LINE[25] OUTCOME[FAILED] REASON[status code 1]

TEST[string equality] LINE[27] OUTCOME[PASSED]
TEST[string equality] LINE[28] OUTCOME[FAILED] REASON[value was 'bar' but 'foo' was expected]

TEST[integer equality] LINE[30] OUTCOME[PASSED]
TEST[integer equality] LINE[31] OUTCOME[FAILED] REASON[value was '2' but '1' was expected]

TEST[float value within threshold] LINE[33] OUTCOME[PASSED]
TEST[float value within threshold] LINE[34] OUTCOME[FAILED] REASON[value was '1.490000' but '1.500000' was expected, with a tolerance of 0.001000]
```

Adding a `duck.status()` breakpoint inside your code will output the status of that corresponding duck's tests so far.

Status:

```console
--------------------Test-Suite-Statistics--------------------
TOTAL[10]   PASSED[5]   FAILED[5]
```

### Version control

To use version control in your testing:

```cpp
//  Specify the file your duck supervises when
Duck duck("duck", "matrix.cpp");

//  Enable version control
duck.version_control = true;

//  With version control enabled, the best performing version
// of your file will be kept in tests/notes/duck_pick.cpp
```

You can rollback to the best perfoming version of your file using `./mallard rollback -duckname-`

```console
./mallard rollback duck
```

### Logging

Logging is controlled in the following fashion:

```cpp
Duck duck("duck");

//  Customization
duck.show_passes = true;
duck.show_fails = true;
duck.show_reason = true;

// Begin logging
duck.take_notes();

...

//  End logging
duck.end_notes();
```

### Setup

[See SETUP](docs/SETUP.md)

### License

[See LICENSE](docs/LICENSE.md)
