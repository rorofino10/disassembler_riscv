CC = gcc
DEBUG=-pg -g
CODEDIRS=src
INCDIRS=.
OPT=-O0
CFLAGS = -fdiagnostics-color=always ${DEBUG} ${OPT}

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))

BINARY=dist/disassembler

all: ${BINARY}

${BINARY}: ${OBJECTS}
	${CC} -pg -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

SCRIPTS = scripts
PY = python3

NORMAL_IN = test/input.txt 
NORMAL_OUT = test/compiled.riscv 
STRESS_IN = test/million_inputs.txt
STRESS_OUT = test/compiled_million_inputs.riscv
STRESS_SCRIPT = ${SCRIPTS}/million_inputs.py



test: ${BINARY}
	${BINARY} < ${NORMAL_IN} > ${NORMAL_OUT}

stress: ${BINARY}
	${PY} ${STRESS_SCRIPT} > ${STRESS_IN}
	${BINARY} < ${STRESS_IN} > ${STRESS_OUT}

clean:
	rm -rf ${BINARY} ${OBJECTS}

.PHONY: all test clean clean

