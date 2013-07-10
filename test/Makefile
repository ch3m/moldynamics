
MKDIR_P = mkdir -p

all: variables directories program

variables:
ifeq ($(ARCH),linux)
CXX := icc
BOOST_LIB := /home/ch3m/Tools/boost-install
FLAGS := -O3
else ifeq ($(ARCH),mac)
CXX := g++
BOOST_LIB := ../../boost-install
FLAGS := -O3
else
ARCH := none
CXX := g++
BOOST_LIB := ../../boost-install
FLAGS := -O3
endif


testing:
	@echo "Making test"
	${CXX} -L${BOOST_LIB}/lib -lboost_unit_test_framework -I${BOOST_LIB}/include unit_test.cpp -o ../bin/moldynamics_test
	../bin/moldynamics_test

clean:
	rm -rf bin
