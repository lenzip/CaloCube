INCLUDES = -I../include/ -I../../DataDormats/include/

lib_LTLIBRARIES = libG4Geometry.la

libG4Geometry_la_SOURCES = AerogelFactory.cc  CsICrystalFactory.cc  DetectorConstruction.cc  VolumeFactory.cc SimpleGeneratorAction.cc cuboDetectorConstruction.cc  

libG4Geometry_la_CPPFLAGS = $(AM_CPPFLAGS)

#libG4Geometry_la_LIBADD = ../../DataFormats/src/libDataFormats.la 

libG4Geometry_la_LDFLAGS = $(AM_LDFLAGS)  -shared
