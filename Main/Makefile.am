INCLUDES = -I../DataFormats/include/ -I../G4Geometry/include -I../Application/include

bin_PROGRAMS = simulate 

simulate_LDADD = ../DataFormats/src/libDataFormats.la ../G4Geometry/src/libG4Geometry.la ../Application/src/libApplication.la

simulate_SOURCES = simulate.cc

simulate_CPPFLAGS = $(AM_CPPFLAGS) -g

simulate_LDFLAGS = $(AM_LDFLAGS)

