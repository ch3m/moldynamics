
MKDIR_P = mkdir -p

all: variables directories program

variables:
ifeq ($(ARCH),linux)
CXX := icc
BOOST_LIB := /home/ch3m/Tools/boost-install
FLAGS := -O3
else ifeq ($(ARCH),mac)
CXX := g++
BOOST_LIB := ../boost-install
FLAGS := -O3
else
ARCH := none
CXX := g++
BOOST_LIB := ../boost-install
FLAGS := -O3
endif
	
	
directories: bin

bin:
	${MKDIR_P} bin

program:
	@echo "arquitectura: $(ARCH)"
	@echo "Compilador: ${CXX}"
	${CXX} ${FLAGS} -L${BOOST_LIB}/lib -lboost_filesystem -lboost_system -I${BOOST_LIB}/include src/main.cc -o bin/moldynamics
	
clean:
	rm -rf bin
