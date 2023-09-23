# 🐚 Simple Shell

A simple re-implementation of a UNIX command interpreter (SHELL).  
It is made as a part of ALX SE program.

## 💎 Our Team

- [Ahmed Hamed](https://github.com/AhmedHamed3699)
- [Ahmed Hosny](https://github.com/photoncodes)
  
## 🔧 How To Use

#### Everything is compiled by
  
  ```bash
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
  ```

#### Shell Works In Two Modes

- Interactive mode, which can be run using `./hsh`
- Non-interactive mode
  - With an input file, like this `./hsh filename`
  - By redirecting, like this `echo "ls" | ./hsh`

## 🌟 Our Shell Features

- Commands can be written with its full path or just its names
- You can pass whatever arguments to the command
- Shell can handle errors properly
- There are some builtins that we implemented ourselves
  - `exit` with status code
  - `env`, `setenv` and `unsetenv`
  - `cd` and `alias`
- You can use commands separator `;`
- `&&` and `||` operators are handled
- Comments can be used
- Variable Replacement is supported

