# Makefile
#
# Project ArbCall
# by. FridaDEV
#

# Environment
LD  := -Ddebug -lc
SRC := src/main.c src/arbcall.c
OUT := out/poc

# Targets
all: compile

compile:
	@if [ -d out ]; then rm -rf out; fi
	@mkdir out
	clang -o $(OUT) $(LD) $(SRC)
