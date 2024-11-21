CXXFLAGS:= @etc/cxxflags
LDFLAGS:= @etc/ldflags
LDLIBES:= @etc/libs
CXX:=$(shell cat etc/cxx)
list/here:=$(shell git ls-files .)
dirb:=$(notdir $(PWD))
list/up1:=$(patsubst %,$(dirb)/%,$(list/here))
exe:= cat-gem cat-gpt 
all: cat-gpt.tar $(exe)

tar: cat-gpt.tar


cat-gpt.tar: $(list/here)
	tar -cf cat-gpt.tar cat-gpt -C .. $(list/up1)

%.i: %.cc etc/cxxflags
	$(CXX) -o $@ $< $(CXXFLAGS) -E

%.o: %.i etc/cxxflags
	$(CXX) -o $@ $< $(CXXFLAGS) -c

%.o: %.S etc/cxxflags
	$(CXX) -o $@ $< $(CXXFLAGS) -S

$(exe): %: %.o
	$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LDLIBES)

