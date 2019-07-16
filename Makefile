CC:=clang++
CFLAGS:=-O3

# Detect which operating system we're currently building for.
ifeq ($(OS), Windows_NT)
	CFLAGS += -fopenmp
else
	# Likely a *nix system. Give me the OS name with uname.
	UNAME := $(shell uname -s)
	ifeq ($(UNAME), Darwin)
		# Apple clang is dumb and doesn't include support for fopenmp by default, apparently.
		CFLAGS += -Xpreprocessor -fopenmp -lomp
	else
		CFLAGS += -fopenmp
	endif
endif

all:
	$(CC) main.cpp -o raytracer $(CFLAGS)
