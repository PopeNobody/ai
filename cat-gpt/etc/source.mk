src/bin = $(wildcard bin/*.cc)
src/lib = $(wildcard lib/*.cc)
obj/bin = $(patsubst %.cc,%.o,$(src/bin))
obj/lib = $(patsubst %.cc,%.o,$(src/lib))
cpp/bin = $(patsubst %.cc,%.i,$(src/bin))
cpp/lib = $(patsubst %.cc,%.i,$(src/lib))
$(foreach var,src obj cpp,$(eval $(var) = $$($(var)/bin) $$($(var)/lib)))
#$(foreach var,src obj cpp,$(warning $(var)=$($(var))))
#$(foreach var,src obj cpp,$(warning $(var)=$($(var)/lib)))
#$(foreach var,src obj cpp,$(warning $(var)=$($(var)/bin)))
#$(warning $(X))


