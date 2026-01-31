CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17


testbst: intbst.cpp testbst.cpp
	$(CXX) $(CXXFLAGS) intbst.cpp testbst.cpp -o testbst


clean:
	rm -f testbst
