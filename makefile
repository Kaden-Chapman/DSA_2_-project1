CXX=g++
CXXFLAGS=-std=c++14 -Wall -g

main: main.o Node.o Hashtable.o vignere.o cipher.o vignere.o
	$(CXX) -o $@ $^

	%.0:o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) a.out *.o *.gch *.dSYM main rawData.txt encrypted.txt 

	