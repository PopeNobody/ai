CXXFLAGS:= @etc/cxxflags
LDFLAGS:= @etc/ldflags
LDLIBES:= @etc/libs
CXX:=$(shell cat etc/cxx)
LIST:=$(shell git ls-files)

all: cat-gpt ../cat-gpt.tar

tar: ../cat-gpt.tar


../cat-gpt.tar: $(LIST)
	tar -cf ../cat-gpt.tar -C .. cat-gpt $(git ls-files)

%.i: %.cc etc/cxxflags
	$(CXX) -o $@ $< $(CXXFLAGS) -E

%.o: %.i etc/cxxflags
	$(CXX) -o $@ $< $(CXXFLAGS) -c

%.o: %.S etc/cxxflags
	$(CXX) -o $@ $< $(CXXFLAGS) -S

cat-gpt: cat-gpt.o
	$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LDLIBES)

