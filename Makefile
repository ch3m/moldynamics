
MKDIR_P = mkdir -p

all: variables directories program

variables:
	@echo "arquitectura: $(ARCH)"
ifeq ($(ARCH),linux)
CXX := icc
BOOST_LIB := /home/ch3m/Tools/boost-install
else ifeq ($(ARCH),mac)
CXX := g++
BOOST_LIB := ../boost-install
else
CXX := g++
BOOST_LIB := ../boost-install
endif
	
	
directories: bin

bin:
	${MKDIR_P} bin

program:
	@echo "Compilador: ${CXX}"
	${CXX} -L${BOOST_LIB}/lib -lboost_filesystem -lboost_system -I${BOOST_LIB}/include src/main.cc -o bin/moldynamics
	
clean:
	rm -rf bin