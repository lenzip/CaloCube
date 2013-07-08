INCLUDES = -I../include/

lib_LTLIBRARIES = libDataFormats.la 

libDataFormats_la_SOURCES = CaloCubeDictionary.cxx Crystal.cc Shower.cc Particle.cc GlobalEvent.cc

libDataFormats_la_CPPFLAGS = $(AM_CPPFLAGS)

libDataFormats_la_LDFLAGS = $(AM_LDFLAGS)  -shared

CaloCubeDictionary.cxx: ../include/Particle.h ../include/Ref.h ../include/Position.h ../include/Crystal.h ../include/Shower.h LinkDef.h
	rootcint -f $@ -c $(AM_CPPFLAGS) $(INCLUDES) -p $^

clean:
	rm -f CaloCubeDictionary.cxx CaloCubeDictionary.h 

.PHONY: clean
