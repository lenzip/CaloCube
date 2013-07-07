#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(CaloCube, 0.1, piergiulio.lenzi@cern.ch)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE(dist-bzip2)
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AM_INIT_AUTOMAKE

## Work out library suffix for the build
RAW_LIB_EXTN=$(echo "$shrext_cmds" | sed -e 's/^\.//')
LIB_SUFFIX=\\\"$shrext_cmds\\\"
AC_SUBST(RAW_LIB_EXTN)
AC_SUBST([LIB_SUFFIX])

AC_ARG_WITH([root-incpath], AC_HELP_STRING(--with-root-incpath, 
                             path to directory containing root headers),
                             [with_root_incpath=$withval], [with_root_incpath=check])
AC_ARG_WITH([root-libpath], AC_HELP_STRING(--with-root-libpath, 
                            path to directory containing root libraries),
                            [with_root_libpath=$withval], [with_root_libpath=check])
AC_ARG_WITH([geant], AC_HELP_STRING(--with-geant, 
                            path to directory containing geant base installation),
                            [with_geant=$withval], [with_geant=check])


AC_CHECK_PROG([ROOTCONFIG], [root-config], yes, no)
if test "x$with_root_incpath" = "xcheck"; then
  if test "$ROOTCONFIG" = "no"; then
    AC_MSG_ERROR("root-config not found")
  else ROOTCPPFLAGS=$(root-config --cflags)
  fi
else AC_SUBST([ROOTCPPFLAGS], ["-I"$with_root_incpath])  
fi


if test "x$with_root_libpath" = "xcheck"; then
  if test "$ROOTCONFIG" = "no"; then
    AC_MSG_ERROR("root-config not found")
  else ROOTLDFLAGS=$(root-config --libs)
  fi
else AC_SUBST(ROOTLDFLAGS, ["-L"$with_root_libpath" -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lz -pthread -lm -ldl -rdynamic"])  
fi

if test "x$with_geant" = "xcheck"; then
  AC_CHECK_PROG([GEANTCONFIG], [geant4-config], yes, no)
  if test "$GEANTCONFIG" = "no"; then
    AC_MSG_ERROR("geant4-config not found in the path and you did not specify a location where to find it.")
  fi
  G4CONFIGCOMMAND="geant4-config"
else
  AC_CHECK_FILE(${with_geant}/bin/geant4-config, 
                G4CONFIGCOMMAND="${with_geant}/bin/geant4-config", 
                AC_MSG_ERROR("${with_geant}/bin/geant4-config does not exist."))
fi  
GEANTLDFLAGS=$($G4CONFIGCOMMAND --libs)
GEANTCPPFLAGS=$($G4CONFIGCOMMAND --cflags)

AM_CPPFLAGS="-fPIC"
AM_CPPFLAGS="$AM_CPPFLAGS $ROOTCPPFLAGS $GEANTCPPFLAGS"

AC_SUBST(AM_CPPFLAGS)

AM_LDFLAGS="$AM_LDFLAGS $ROOTLDFLAGS -lMathCore $GEANTLDFLAGS"

AC_SUBST(AM_LDFLAGS)

AC_CONFIG_FILES([Makefile
                 DataFormats/Makefile
                 DataFormats/src/Makefile
                 DataFormats/include/Makefile
                 G4Geometry/Makefile
                 G4Geometry/src/Makefile
                 G4Geometry/include/Makefile
                 Application/Makefile
                 Application/src/Makefile
                 Application/include/Makefile
                 Main/Makefile])
AC_OUTPUT
