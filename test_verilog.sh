#!/bin/bash
gen() {
  input="$1"
  ./9cc "$input"
}

gen "1*2+3*4;"