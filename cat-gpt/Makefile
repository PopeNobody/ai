MAKEFLAGS+= -rR -j
CXX:=$(shell cat etc/cxx)
ARC:=$(shell cat etc/arc)
all:

exe:= bin/cat-gpt bin/cat-gem bin/mmap_array_test
lib:= lib/libcat-gpt.a

include etc/source.mk $(wildcard */*.d)

all: $(exe)

tar:

cat-gpt.tar:
	tar -cf ../cat-gpt.tar -C .. cat-gpt $(git ls-files)

clean:
	rm -f $(cpp) $(exe) $(obj)



$(lib): $(obj/lib)
	ar -r $@ $(obj/lib)

$(cpp): %.i: %.cc etc/cppflags etc/cxxflags 
	$(CXX) -o $@ $< @etc/cppflags @etc/cxxflags -E

$(obj): %.o: %.cc etc/cppflags etc/cxxflags 
	$(CXX) -o $@ $< @etc/cppflags @etc/cxxflags -c

$(exe): %: %.o etc/lnkflags etc/libs lib/libcat-gpt.a $(lib)
	$(CXX) -o $@ $< @etc/cxxflags @etc/lnkflags @etc/libs $(lib)
