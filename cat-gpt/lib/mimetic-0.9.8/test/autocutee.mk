# cutee autogen: begin
CUTEE=./cutee
t_runners=t.version.cutee.cxx t.tokenizer.cutee.cxx t.base64.cutee.cxx t.qp.cutee.cxx t.circular_buffer.cutee.cxx t.file.cutee.cxx t.mimemessage.cutee.cxx t.composite.cutee.cxx t.directory.cutee.cxx t.fieldparam.cutee.cxx t.strutils.cutee.cxx t.rfc822.cutee.cxx t.tree.cutee.cxx t.parser.cutee.cxx t.contenttype.cutee.cxx t.utils.cutee.cxx t.codec.cutee.cxx t.find_bm.cutee.cxx t.contentdisposition.cutee.cxx 

%.cutee.cxx: $(srcdir)/%.h
	$(CUTEE) -o $@ $<


runtest.cxx: cutee
	$(CUTEE) -m -o $@

runtest-clean:
	rm -f autocutee.mk cutee *.o *.cutee.cxx runtest runtest.cxx
	touch autocutee.mk

EXTRA_PROGRAMS=runtest
runtest_SOURCES=runtest.cxx $(test_files) $(t_runners)
runtest_DEPENDENCIES=cutee autocutee.mk
# cutee autogen: end 
