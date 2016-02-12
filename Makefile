# CXX=g++
# CC=g++
FSTPATH=/Users/neubig/usr
LDFLAGS=-g -O3 -lfst -ldl -std=c++0x -I${FSTPATH}/include -L${FSTPATH}/lib

all: latticelm latticetm

latticelm: latticelm.h pylm.h lexfst.h ${ADDLD}
	${CXX} -o latticelm mainlatticelm.cc ${LDFLAGS}

latticetm: latticetm.h mainlatticetm.cc ${ADDLD}
	${CXX} -o latticetm mainlatticetm.cc ${LDFLAGS}

clean:
	rm -f latticelm
	rm -f latticetm
