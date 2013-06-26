CXX = g++
MKDIR_P = mkdir -p

all: directories program
	
directories: bin

bin:
	${MKDIR_P} bin

program:
	${CXX} -L../boost-install/lib -lboost_filesystem -lboost_system -I../boost-install/include src/main.cc -o bin/moldynamics
	
clean:
	rm -rf bin