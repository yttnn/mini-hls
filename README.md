# 9cc
https://www.sigbus.info/compilerbook

## めも
- `make test`で実行
- step6
  - `- -10 = 10`になることを初めてしった。。。あまりにもはずい
- step7,8
  - この時点での文法は
  ```
  expr       = equality
  equality   = relational ("==" relational | "!=" relational)*
  relational = add ("<" add | "<=" add | ">" add | ">=" add)*
  add        = mul ("+" mul | "-" mul)*
  mul        = unary ("*" unary | "/" unary)*
  unary      = ("+" | "-")? primary
  primary    = num | "(" expr ")"
  ```
  - ファイル分割も行う
  - step8以降は`9cc.c`の利用をしないため`old`へ退避