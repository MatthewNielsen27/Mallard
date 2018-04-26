#!/bin/bash
if (($1 == 'run'))
then
  cd tests && make && ./tests
fi
