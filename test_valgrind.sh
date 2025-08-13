#!/bin/bash

# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   test_valgrind.sh                                   :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025/08/11 22:00:00 by wojti             #+#    #+#             #
#   Updated: 2025/08/11 22:00:00 by wojti            ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

# Kolory dla output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Zmienne
MINISHELL_PATH="./minishell"
VALGRIND_LOG_DIR="valgrind_logs"
TIMEOUT=10
PASSED=0
FAILED=0
TOTAL=0

# Tworzenie katalogu na logi
mkdir -p $VALGRIND_LOG_DIR

echo -e "${BLUE}=== COMPREHENSIVE VALGRIND TESTS FOR MINISHELL ===${NC}"
echo -e "${YELLOW}Testing with timeout: ${TIMEOUT}s${NC}"
echo ""

# Funkcja do uruchamiania pojedynczego testu
run_valgrind_test() {
    local test_name="$1"
    local command="$2"
    local log_file="$VALGRIND_LOG_DIR/${test_name}.log"
    
    echo -n -e "${YELLOW}[$((TOTAL+1))] Testing: ${test_name}${NC} ... "
    
    # Uruchomienie z Valgrindem
    timeout $TIMEOUT valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --log-file="$log_file" \
        --suppressions=./readline.supp \
        $MINISHELL_PATH <<< "$command" >/dev/null 2>&1
    
    local exit_code=$?
    
    # Sprawdzenie czy był timeout
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}TIMEOUT${NC}"
        echo "TIMEOUT after ${TIMEOUT}s" >> "$log_file"
        FAILED=$((FAILED+1))
    else
        # Sprawdzenie błędów Valgrind
        if grep -q "ERROR SUMMARY: 0 errors" "$log_file" && \
           grep -q "definitely lost: 0 bytes" "$log_file"; then
            echo -e "${GREEN}PASS${NC}"
            PASSED=$((PASSED+1))
        else
            echo -e "${RED}FAIL${NC}"
            FAILED=$((FAILED+1))
        fi
    fi
    
    TOTAL=$((TOTAL+1))
}

# ===== TESTY PODSTAWOWE =====
echo -e "${BLUE}=== BASIC COMMANDS ===${NC}"

run_valgrind_test "echo_simple" "echo hello"
run_valgrind_test "echo_multiple_args" "echo hello world test"
run_valgrind_test "echo_with_quotes" "echo 'hello world'"
run_valgrind_test "echo_empty" "echo"
run_valgrind_test "pwd_simple" "pwd"
run_valgrind_test "env_simple" "env"
run_valgrind_test "exit_simple" "exit"
run_valgrind_test "exit_with_code" "exit 42"

# ===== TESTY REDIREKCJI =====
echo -e "${BLUE}=== REDIRECTIONS ===${NC}"

# Przygotowanie plików testowych
echo "test content line 1" > test_input.txt
echo "test content line 2" >> test_input.txt

run_valgrind_test "redirect_output" "echo hello > output_test.txt"
run_valgrind_test "redirect_append" "echo world >> output_test.txt"
run_valgrind_test "redirect_input" "cat < test_input.txt"
run_valgrind_test "redirect_multiple" "cat < test_input.txt > output_copy.txt"

# ===== TESTY PIPE =====
echo -e "${BLUE}=== PIPES ===${NC}"

run_valgrind_test "pipe_simple" "echo hello | cat"
run_valgrind_test "pipe_multiple" "echo hello world | cat | cat"
run_valgrind_test "pipe_with_redirect" "echo test | cat > pipe_output.txt"
run_valgrind_test "pipe_complex" "ls | grep mini | head -5"

# ===== TESTY HEREDOC =====
echo -e "${BLUE}=== HEREDOC ===${NC}"

run_valgrind_test "heredoc_simple" "cat << EOF
hello world
test line
EOF"

run_valgrind_test "heredoc_with_pipe" "cat << END | cat
line 1
line 2
END"

# ===== TESTY ZMIENNYCH ŚRODOWISKOWYCH =====
echo -e "${BLUE}=== ENVIRONMENT VARIABLES ===${NC}"

run_valgrind_test "export_simple" "export TEST_VAR=hello"
run_valgrind_test "export_multiple" "export VAR1=test VAR2=hello"
run_valgrind_test "unset_simple" "unset PATH"
run_valgrind_test "env_expansion" "echo \$HOME"
run_valgrind_test "env_expansion_quotes" "echo '\$HOME'"

# ===== TESTY CD =====
echo -e "${BLUE}=== CD COMMANDS ===${NC}"

mkdir -p test_dir
run_valgrind_test "cd_relative" "cd test_dir"
run_valgrind_test "cd_absolute" "cd /tmp"
run_valgrind_test "cd_home" "cd"
run_valgrind_test "cd_parent" "cd .."
run_valgrind_test "cd_nonexistent" "cd nonexistent_dir"

# ===== TESTY QUOTES =====
echo -e "${BLUE}=== QUOTES ===${NC}"

run_valgrind_test "single_quotes" "echo 'hello world'"
run_valgrind_test "double_quotes" "echo \"hello world\""
run_valgrind_test "mixed_quotes" "echo 'hello' \"world\""
run_valgrind_test "quotes_with_vars" "echo \"Hello \$USER\""
run_valgrind_test "empty_quotes" "echo '' \"\""

# ===== TESTY BŁĘDÓW =====
echo -e "${BLUE}=== ERROR HANDLING ===${NC}"

run_valgrind_test "command_not_found" "nonexistent_command"
run_valgrind_test "invalid_option" "ls --invalid-option"
run_valgrind_test "permission_denied" "cat /root/.bashrc"
run_valgrind_test "syntax_error_pipe" "echo hello |"
run_valgrind_test "syntax_error_redirect" "echo hello >"

# ===== TESTY KOMPLEKSOWE =====
echo -e "${BLUE}=== COMPLEX TESTS ===${NC}"

run_valgrind_test "complex_pipeline" "echo hello | cat | cat | cat"
run_valgrind_test "complex_redirect" "echo test > temp.txt && cat temp.txt"
run_valgrind_test "complex_heredoc_pipe" "cat << EOF | grep hello
hello world
test line
hello again
EOF"

run_valgrind_test "complex_env_export" "export TEST=hello && echo \$TEST"
run_valgrind_test "complex_cd_pwd" "cd /tmp && pwd && cd - && pwd"

# ===== TESTY STRESS =====
echo -e "${BLUE}=== STRESS TESTS ===${NC}"

# Długie komendy
run_valgrind_test "long_echo" "echo $(printf 'a%.0s' {1..1000})"
run_valgrind_test "many_pipes" "echo test | cat | cat | cat | cat | cat"

# Wiele argumentów
long_args="echo"
for i in {1..100}; do
    long_args="$long_args arg$i"
done
run_valgrind_test "many_arguments" "$long_args"

# ===== PODSUMOWANIE =====
echo ""
echo -e "${BLUE}=== SUMMARY ===${NC}"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "${YELLOW}Total:  $TOTAL${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed! No memory leaks detected.${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed. Check logs in $VALGRIND_LOG_DIR/${NC}"
    echo ""
    echo "Failed tests details:"
    for log in $VALGRIND_LOG_DIR/*.log; do
        if grep -q "ERROR SUMMARY: [^0]" "$log" || grep -q "definitely lost: [^0]" "$log" || grep -q "TIMEOUT" "$log"; then
            echo -e "${RED}  - $(basename "$log" .log)${NC}"
        fi
    done
    exit 1
fi

# Czyszczenie plików testowych
rm -f test_input.txt output_test.txt output_copy.txt pipe_output.txt temp.txt
rm -rf test_dir
