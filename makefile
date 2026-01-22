CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

OBJS = main.o Node.o Hashtable.o vigenere.o cipher.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f a.out *.o *.gch *.dSYM main rawdata.txt encrypteddata.txt
