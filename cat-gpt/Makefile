
CXXFLAGS:= -ggdb3 
LDFLAGS:= -Wl,--verbose
LDLIBES:= -lcurl -lboost_program_options

%.i: %.cc
	g++ -o $@ $< $(CXXFLAGS) -E

cat-gpt: cat-gpt.cc
	@echo test
	g++ -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LDLIBES)

