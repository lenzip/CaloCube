INCLUDES = -I../include/ -I../../DataFormats/include/ -I../../G4Geometry/include/

lib_LTLIBRARIES = libApplication.la

libApplication_la_SOURCES = EventAction.cc  RunAction.cc  StackingAction.cc  SteppingAction.cc 

libApplication_la_CPPFLAGS = $(AM_CPPFLAGS)

#libApplication_la_LIBADD = ../../DataFormats/src/libDataFormats.la

libApplication_la_LDFLAGS = $(AM_LDFLAGS) -L../../DataFormats/src/.libs/ -lDataFormats -shared
