CC = gcc
CFLAGS = -fdiagnostics-color=always -g ${SRC} -pg
SRC = ${wildcard src/*.c}
OUT = dist/disassembler
SCRIPTS = scripts
PY = python3

NORMAL_IN = test/input.txt 
NORMAL_OUT = test/compiled.riscv 
STRESS_IN = test/million_inputs.txt
STRESS_OUT = test/compiled_million_inputs.riscv
STRESS_SCRIPT = ${SCRIPTS}/million_inputs.py

all : ${OUT}

${OUT} : ${SRC}
	${CC} ${CFLAGS} -o ${OUT}	

test : ${OUT}
	${OUT} < ${NORMAL_IN} > ${NORMAL_OUT}

stress : ${OUT}
	${PY} ${STRESS_SCRIPT} > ${STRESS_IN}
	${OUT} < ${STRESS_IN} > ${STRESS_OUT}

clean:
	rm -f ${OUT}

.PHONY: all test stress clean
