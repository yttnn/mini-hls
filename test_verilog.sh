#!/bin/bash
gen() {
  input="$1"
  ./9cc "$input"
}

gen "foo = 5 + 4; var = 5; val = foo + var;"