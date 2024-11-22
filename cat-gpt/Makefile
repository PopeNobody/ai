CXX:=$(shell cat etc/cxx)
dirb:=$(notdir $(PWD))
exe:= bin/cat-gem bin/cat-gpt 
src:= $(wildcard src/*.cc)
obj:= $(patsubst src/%.cc,obj/%.o,$(src))

all: $(exe)
$(src):

$(obj): obj/%.o: src/%.cc etc/cxxflags
	$(CXX) @etc/cxxflags -o $@ $< -c  

$(exe): bin/%: obj/%.o
	$(CXX) -o $@ $< @etc/cxxflags @etc/lnkflags @etc/libs


