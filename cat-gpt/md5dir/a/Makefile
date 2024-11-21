CXXFLAGS:= -ggdb3 -O0
CPPFLAGS:= -I.
LD_FLAGS:= -static
CXX:=g++
LD:=g++
exe:= md5dir
all_src:= $(wildcard *.cc)
all_obj:= $(all_src:.cc=.o)
exe_obj:= $(exe:=.o)
lib_obj:= $(filter-out $(exe_obj),$(all_obj))
lib:= liblib.a

#$(foreach x, lib lib_obj exe_obj all_obj all_src, $(warning $x=$($x)))

LD_LIBS:= -Wl,-start-group -lboost_system -lboost_filesystem 
LD_LIBS+= $(lib)
LD_LIBS+= -Wl,-end-group

test: all
	./md5dir

all: $(exe)

$(exe): $(lib)

$(exe): %: %.o
	$(CXX) $(LD_FLAGS) $(CXXFLAGS) -o $@ $< $(LD_LIBS) 

$(lib): $(lib_obj)
	ar r $@ $(lib_obj)

%.i: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< -E

$(src): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< -c

clean:
	rm -f *.a *.o *.i md5dir tags
