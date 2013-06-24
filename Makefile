MKDIR_P = mkdir -p

all: directories program
	
directories: bin

bin:
	${MKDIR_P} bin

program:
	g++ src/main.cc -o bin/moldynamics
	
clean:
	rm -rf bin