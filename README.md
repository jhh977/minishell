# Minishell

A simple Unix shell implementation in C, recreating basic bash functionality as part of the 42 curriculum.

```
 _____ _____ _____ _____ _____ _____ _____ __    __    
|     |     |   | |     |   __|  |  |   __|  |  |  |   
| | | |-   -| | | |  |  |__   |     |   __|  |__|  |__ 
|_|_|_|_____|_|___|_____|_____|__|__|_____|_____|_____|
```

## 📋 Table of Contents
- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Testing](#testing)
- [Known Issues](#known-issues)
- [Project Structure](#project-structure)
- [Authors](#authors)

## 🎯 About

Minishell is a project from the 42 school curriculum that challenges students to create their own shell. This implementation includes:
- Command execution with PATH resolution
- Built-in commands implementation
- Pipe and redirection handling
- Environment variable management
- Signal handling

## ✨ Features

### Core Features
- ✅ Interactive prompt
- ✅ Command execution from PATH
- ✅ Executable with relative/absolute paths
- ✅ Command history (↑/↓ arrows)
- ✅ Exit status (`$?`)

### Built-in Commands
| Command | Description | Example |
|---------|-------------|---------|
| `echo` | Print text with optional `-n` flag | `echo -n "Hello"` |
| `cd` | Change directory | `cd /path` or `cd ..` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variables | `export VAR=value` |
| `unset` | Remove environment variables | `unset VAR` |
| `env` | Display environment | `env` |
| `exit` | Exit shell with status code | `exit 42` |

### Redirections
| Type | Syntax | Description |
|------|--------|-------------|
| Input | `< file` | Read from file |
| Output | `> file` | Write to file (truncate) |
| Append | `>> file` | Append to file |
| Heredoc | `<< DELIMITER` | Read until delimiter |

### Advanced Features
- **Pipes**: Chain commands with `|`
- **Quotes**: 
  - Single quotes `'...'` prevent expansion
  - Double quotes `"..."` allow variable expansion
- **Environment Variables**: Access with `$VAR` or `$?`
- **Signal Handling**:
  - `Ctrl-C`: New prompt (does not exit)
  - `Ctrl-D`: Exit shell
  - `Ctrl-\`: Ignored

## 🚀 Installation

### Compilation
```bash
# Clone the repository
git clone git@vogsphere.42beirut.com:vogsphere/intra-uuid-35c7963e-809f-46c8-961f-a74aee853d23-7014643-jhijazi
cd minishell

# Compile
make

# Run
./minishell
```

### Makefile Rules
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

## 💻 Usage

### Basic Commands
```bash
minishell$ ls -la
minishell$ pwd
minishell$ echo "Hello World"
minishell$ cat file.txt
```

### Using Pipes
```bash
minishell$ ls -l | grep ".c"
minishell$ cat file.txt | grep "search" | wc -l
minishell$ echo "test" | cat -e
```

### Redirections
```bash
# Output redirection
minishell$ echo "Hello" > output.txt
minishell$ ls -l >> output.txt

# Input redirection
minishell$ wc -l < input.txt

# Heredoc
minishell$ cat << EOF
> Line 1
> Line 2
> EOF
```

### Environment Variables
```bash
# Set variables
minishell$ export MY_VAR="Hello"
minishell$ export PATH=/usr/bin:/bin

# Use variables
minishell$ echo $MY_VAR
Hello

minishell$ echo $USER
aawad

# Check exit status
minishell$ ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
minishell$ echo $?
2

# Display all environment
minishell$ env

# Remove variables
minishell$ unset MY_VAR
```

### Quotes
```bash
# Single quotes (literal string)
minishell$ echo 'Hello $USER'
Hello $USER

# Double quotes (with expansion)
minishell$ echo "Hello $USER"
Hello aawad

# Mixed
minishell$ echo 'Single' "Double" Normal
Single Double Normal
```

## 📚 Built-in Commands

### `echo [-n] [string ...]`
Print arguments to standard output
```bash
minishell$ echo Hello World
Hello World

minishell$ echo -n "No newline"
No newlineminishell$ 

minishell$ echo -nnn "Multiple n flags"
Multiple n flagsminishell$
```

### `cd [path]`
Change the current working directory
```bash
minishell$ cd /tmp          # Absolute path
minishell$ cd ..            # Parent directory
minishell$ cd ~             # Home directory
minishell$ cd               # Home directory (no args)
minishell$ cd relative/path # Relative path
```

### `pwd`
Print the current working directory
```bash
minishell$ pwd
/home/aawad/minishell
```

### `export [VAR[=value] ...]`
Set or display environment variables
```bash
# Display all exported variables
minishell$ export
declare -x HOME="/home/aawad"
declare -x PATH="/usr/bin:/bin"
declare -x USER="aawad"

# Export with value
minishell$ export VAR=value
minishell$ export GREETING="Hello World"

# Export without value (declare only)
minishell$ export VAR

# Multiple exports
minishell$ export A=1 B=2 C=3
```

### `unset [VAR ...]`
Remove environment variables
```bash
minishell$ unset VAR
minishell$ unset VAR1 VAR2 VAR3
```

### `env`
Display all environment variables
```bash
minishell$ env
SHELL=/bin/bash
HOME=/home/aawad
USER=aawad
PATH=/usr/bin:/bin
...
```

### `exit [n]`
Exit the shell with optional status code
```bash
minishell$ exit           # Exit with last status
minishell$ exit 0         # Exit with status 0
minishell$ exit 42        # Exit with status 42
minishell$ exit 256       # Exit with status 0 (256 % 256)

# Error cases
minishell$ exit abc       # Error: numeric argument required
minishell$ exit 1 2 3     # Error: too many arguments (doesn't exit)
```

## 🧪 Testing

### Basic Functionality Test
```bash
./minishell

# Test built-ins
minishell$ pwd
minishell$ cd ..
minishell$ pwd
minishell$ cd -
minishell$ echo -n "test"
minishell$ echo $USER
minishell$ export TEST=123
minishell$ echo $TEST
minishell$ unset TEST

# Test execution
minishell$ ls -la
minishell$ /bin/echo "absolute path"
minishell$ cat /etc/passwd | grep root

# Test redirections
minishell$ echo "test" > file.txt
minishell$ cat < file.txt
minishell$ ls >> file.txt
minishell$ cat << EOF
heredoc test
EOF

# Test quotes
minishell$ echo "Hello $USER"
minishell$ echo 'Hello $USER'

# Test pipes
minishell$ ls | wc -l
minishell$ cat file.txt | grep pattern | sort

# Test exit status
minishell$ ls
minishell$ echo $?
minishell$ ls nonexistent
minishell$ echo $?

# Test signals
# Press Ctrl-C (should show new prompt)
# Press Ctrl-\ (should do nothing)
# Press Ctrl-D (should exit)

# Exit
minishell$ exit
```

### Complex Test Cases
```bash
# Multiple pipes
minishell$ cat file.txt | grep "a" | sort | uniq | wc -l

# Multiple redirections
minishell$ < input.txt cat | grep "test" > output.txt

# Mixed quotes and variables
minishell$ echo "User: $USER, Home: $HOME"
minishell$ echo 'User: $USER' "Home: $HOME"

# Export multiple variables
minishell$ export A=1 B=2 C=3
minishell$ echo "$A $B $C"

# Heredoc with pipes
minishell$ cat << EOF | grep "line"
first line
second line
EOF

# Complex command
minishell$ export PATH=/bin:/usr/bin
minishell$ echo "Files:" && ls | wc -l
```

### Memory Check (Valgrind)
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

# Inside valgrind session:
minishell$ echo test
minishell$ ls | grep .c
minishell$ export VAR=test
minishell$ exit
```

## ⚠️ Known Issues

### Current Bugs
1. **Segmentation fault**: When doing `export a` followed by `Ctrl-D` (being investigated)
   - Workaround: Use `exit` command instead of `Ctrl-D`

### Not Implemented
- ❌ Logical operators (`&&`, `||`)
- ❌ Wildcards (`*`, `?`)
- ❌ Backslash escaping (`\`)
- ❌ Background processes (`&`)
- ❌ Command substitution (`` `...` `` or `$(...)`)
- ❌ Special variables (`$$`, `$!`, `$_`)
- ❌ Subshells (`(...)`)
- ❌ Brace expansion (`{a,b,c}`)

### Limitations
- Only simple quotes and double quotes are handled
- Variable expansion in heredoc is not implemented
- Exit status is limited to 0-255 range
- No support for aliases or functions

## 📁 Project Structure

```
minishell/
├── Makefile                      # Build configuration
├── minishell.h                   # Header file
├── main.c                        # Main loop and initialization
├── copy_envp.c                   # Environment copying and freeing
│
├── Parsing & Tokenization:
├── tokenization.c                # Main tokenization logic
├── tokenization_helper.c         # Tokenization utilities
├── tokenization_quotes.c         # Quote handling in tokens
├── token.c                       # Token creation and management
├── add_word.c                    # Word addition to tokens
├── parser.c                      # Main parser
├── parse_checker.c               # Parse validation
├── cmd_helper.c                  # Command structure helpers
├── redirs_handler.c              # Redirection parsing
├── local_var_helper.c            # Local variable expansion
├── free_functions_parsing.c      # Parsing memory cleanup
│── signals.c                     # Signal setup and handling
├── signals_helper.c              # Signal helper functions
|
|
├── Execution:
├── execute_command_child.c       # Child process execution
├── execute_single_cmd.c          # Single command execution
├── handel_single_execution.c     # Single command helper
│── Built-in Commands:
├── built_in_command1.c           # pwd, echo, cd, env
├── built_in_command2.c           # exit, unset
├── built_in_command3.c           # export
├── built_in_execution.c          # Built-in dispatcher
├── built_in_redirection.c        # Save/restore file descriptor
├── Pipes:
├── pipline_command.c             # Pipe creation and management
├── pipline_execute.c             # Pipeline utilities
├── wait_execute_pipeline.c       # Pipeline execution and waiting
├── handel_redirection1.c         # Input redirections
├── handel_redirection2.c         # Output redirections
├── heredoc.c                     # Heredoc implementation
├── remove_add_env.c              # Add/remove environment variables
├── find_path.c                   # Find executables in PATH
├── find_path_utils.c             # Path utilities
├── free_child_processes.c        # Cleanup functions
│
└── libft/                        # Custom C library
    ├── ft_*.c                    # String, memory, output functions
    └── libft.h                   # Library header
```

## 👥 Authors

- **aawad** - [GitHub Profile](https://github.com/awadanthony33-collab)
- **jhijazi** - [GitHub Profile](https://github.com/jhh977)

*42 School - Minishell Project*

## 📝 Notes

### Development Tips
- Always test with valgrind to check for memory leaks
- Use `Ctrl-D` carefully due to known issue
- Test edge cases: empty commands, multiple spaces, special characters
- Compare behavior with bash for reference

### Debugging
```bash
# Compile with debug flags
make DEBUG=1

# Run with valgrind
valgrind --leak-check=full -q ./minishell

#Run with valgrind and supp.supp file to check witout readline leaks
valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp -q  ./minishell

# Run with gdb
gdb -tui ./minishell
```

---

**⚠️ This is an educational project and should not be used in production environments.**

*Last updated: January 2026*