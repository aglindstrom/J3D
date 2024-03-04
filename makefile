CC = g++
BIN = ./bin
OUT = ./out

all: directories quadratic rand sine makegrid j3D exec
	
directories:
	mkdir $(BIN)
	mkdir $(OUT)

quadratic: quadratic.cpp
	$(CC) -o $(BIN)/$@ $^

rand: rand.cpp
	$(CC) -o $(BIN)/$@ $^

sine: sine.cpp
	$(CC) -o $(BIN)/$@ $^

makegrid: makegrid.cpp
	$(CC) -o $(BIN)/$@ $^

j3D: j3D.cpp
	$(CC) -o $(BIN)/$@ $^

clean:
	rm -rf $(BIN)
	rm -rf $(OUT)

exec: 
	$(BIN)/quadratic -x 40 -y 40 | $(BIN)/makegrid -x 40 | $(BIN)/j3D -d -x -35.26 -y 54.74 -z 45 | jgraph | convert -density 600 - $(OUT)/quad.jpg
	$(BIN)/rand -x 40 -y 40 | $(BIN)/makegrid -x 40 | $(BIN)/j3D -d -x -35.26 -y 54.74 -z 45 | jgraph | convert -density 600 - $(OUT)/rand.jpg
	$(BIN)/sine -x 40 -y 40 -s 4 | $(BIN)/makegrid -x 40 | $(BIN)/j3D -d -x -35.26 -y 54.74 -z 45 | jgraph | convert -density 600 - $(OUT)/sin.jpg
