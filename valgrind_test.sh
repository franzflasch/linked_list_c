#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./linked_list_test
