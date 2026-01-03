#!/usr/bin/env bash

SHELL_BIN=${1:-bash}   # use ./minishell to test your shell
TMP_OUT=/tmp/ms_test_out
TMP_ERR=/tmp/ms_test_err

run_test() {
    local cmd="$1"
    local expected_code="$2"

    echo "TEST: [$cmd]"
    echo "$cmd" | $SHELL_BIN >"$TMP_OUT" 2>"$TMP_ERR"
    local code=$?

    printf "  exit code: %s (expected %s)\n" "$code" "$expected_code"
    printf "  stderr: %s\n" "$(cat $TMP_ERR | head -n 1)"
    echo
}

# REDIRECTIONS
run_test "<<<" 2
run_test "<<<<<<<<<<<<<<<<" 2
run_test ">" 2
run_test ">>" 2

# PATH / DIRECTORY
run_test "/" 126
run_test "//" 126
run_test "/." 126
run_test "/./../../../../.." 126
run_test "///////" 126

# BACKSLASH
run_test "\\" 127
run_test "\\\\" 127
run_test "\\\\\\\\" 127

# METACHARACTERS
run_test "-" 127
run_test "|" 2
run_test "| hola" 2
run_test "||" 2
run_test "|||||" 2
run_test "&&" 2
run_test "&&&&&" 2
run_test ";" 2
run_test ";;;;;" 2

# PARENTHESES
run_test "()" 2
run_test "( ( ) )" 2
run_test "( ( ( ( ) ) ) )" 2

# QUOTES
run_test "\"\"" 127
run_test "\"hola\"" 127
run_test "'hola'" 127
run_test "''" 127

# GLOBBING (BONUS)
run_test "*" 127
run_test "*/*" 127

# DOT
run_test "." 2
run_test ".." 127

# TILDE
run_test "~" 126

# ASSIGNMENTS
run_test "ABC=hola" 0
run_test "4ABC=hola" 127

# WORDS
run_test "hola" 127
run_test "hola que tal" 127
run_test "Makefile" 127
