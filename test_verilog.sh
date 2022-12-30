#!/bin/bash
gen() {
  input="$1"
  ./9cc "$input"
}

gen "foo = -2 + 5; var = 4 * 2; hoge = foo + var; foo = 3;"