#!/bin/bash
gen() {
  input="$1"
  ./9cc "$input"
}

gen "foo = 5 * 4;"