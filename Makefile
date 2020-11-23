CXX=clang++-9
CXXFLAGS=-std=c++2a 

edf: EDF_policy.cpp
	$(CXX) $(CXXFLAGS) EDF_policy.cpp -o edf

bd: BD_policy.cpp
	$(CXX) $(CXXFLAGS) BD_policy.cpp -o bd

clean:
	rm -f *.o demo bd  edf