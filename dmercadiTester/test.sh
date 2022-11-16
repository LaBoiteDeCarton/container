#!/bin/bash

RESET="\033[0m"
GREEN="\033[32m"
RED="\033[31m"
BOLDRED="\033[1m\033[31m"
CYAN="\033[36m"
WHITE="\033[37m"
BOLDYELLOW="\033[1m\033[33m"
BOLDWHITE="\033[1m\033[37m"

INCLUDES_PATH=../

mkdir ret 2>/dev/null

function test ()
{
	rm container 2>/dev/null
	printf $BOLDRED
	c++ -Wall -Wextra -std=c++98 -I$INCLUDES_PATH -DFT test_files/$@.cpp -o container 2>/dev/null
	if [  ! $? -eq 0 ]; then
		printf $RED"compilation failed"
		exit;
	fi
	./container >ret/ft_ret 2>ret/ft_err_ret
	c++ -Wall -Wextra -std=c++98 test_files/$@.cpp -o container 2>/dev/null
	./container >ret/std_ret 2>ret/std_err_ret
		printf $WHITE"Comparing files of $CYAN $@\n"$RESET

	diff ret/ft_ret ret/std_ret >/dev/null
	if [ $? -eq 0 ]; then
		printf "    $GREEN%s$RESET   " "✓ "
		rm ret/ft_ret ret/std_ret
	else
		printf "    $RED%s$RESET   " "✗ "
	fi

	diff ret/ft_err_ret ret/std_err_ret >/dev/null
	if [ $? -eq 0 ]; then
		printf "    $GREEN%s$RESET    " "✓ "
		rm ret/ft_err_ret ret/std_err_ret
	else
		printf "    $RED%s$RESET   " "✗ "
	fi
	rm container
	printf "\n$RESET$WHITE"
}

test vector
test stack
test map
test set

exit