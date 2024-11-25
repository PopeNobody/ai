#!/bin/bash

cfg=()
add() { 
  (( $# == 2 )) && set -- "$1=$2"

  cfg+=("$@");
}
#  `configure' configures this package to adapt to many kinds of systems.
#  
#  Usage: ./configure [OPTION]... [VAR=VALUE]...
#  
#  To assign environment variables (e.g., CC, CFLAGS...), specify them as
#  VAR=VALUE.  See below for descriptions of some of the useful variables.
#  
#  Defaults for the options are specified in brackets.
#  
#  Configuration:
#    -h, --help              display this help and exit
#        --help=short        display options specific to this package
#        --help=recursive    display the short help of all the included packages
#    -V, --version           display version information and exit
#    -q, --quiet, --silent   do not print `checking ...' messages
add  --cache-file config.cache
#    -C, --config-cache      alias for `--cache-file=config.cache'
#    -n, --no-create         do not create output files
#add  --srcdir                            # find the sources in DIR [configure dir or `..']
#  
#  Installation directories:
add  --prefix $(cd ../.. && pwd)                           # install architecture-independent files in PREFIX
#                            [/usr/local]
#add  --exec-prefix                       # install architecture-dependent files in EPREFIX
#                            [PREFIX]
#  
#  By default, `make install' will install all the files in
#  `/usr/local/bin', `/usr/local/lib' etc.  You can specify
#  an installation prefix other than `/usr/local' using `--prefix',
#  for instance `--prefix=$HOME'.
#  
#  For better control, use the options below.
#  
#  Fine tuning of the installation directories:
#add  --bindir                            # user executables [EPREFIX/bin]
#add  --sbindir                           # system admin executables [EPREFIX/sbin]
#add  --libexecdir                        # program executables [EPREFIX/libexec]
#add  --sysconfdir                        # read-only single-machine data [PREFIX/etc]
#add  --sharedstatedir                    # modifiable architecture-independent data [PREFIX/com]
#add  --localstatedir                     # modifiable single-machine data [PREFIX/var]
#add  --libdir                            # object code libraries [EPREFIX/lib]
#add  --includedir                        # C header files [PREFIX/include]
#add  --oldincludedir                     # C header files for non-gcc [/usr/include]
#add  --datarootdir                       # read-only arch.-independent data root [PREFIX/share]
#add  --datadir                           # read-only architecture-independent data [DATAROOTDIR]
#add  --infodir                           # info documentation [DATAROOTDIR/info]
#add  --localedir                         # locale-dependent data [DATAROOTDIR/locale]
#add  --mandir                            # man documentation [DATAROOTDIR/man]
#add  --docdir                            # documentation root [DATAROOTDIR/doc/PACKAGE]
#add  --htmldir                           # html documentation [DOCDIR]
#add  --dvidir                            # dvi documentation [DOCDIR]
#add  --pdfdir                            # pdf documentation [DOCDIR]
#add  --psdir                             # ps documentation [DOCDIR]
#  
#  Program names:
#add  --program-prefix                    # prepend PREFIX to installed program names
#add  --program-suffix                    # append SUFFIX to installed program names
#add  --program-transform-name            # run sed PROGRAM on installed program names
#  
#  System types:
#add  --build                             # configure for building on BUILD [guessed]
#add  --host                              # cross-compile to build programs to run on HOST [BUILD]
#add  --target                            # configure for building compilers for TARGET [HOST]
#  
#  Optional Features:
#add  --disable-option-checking           # ignore unrecognized --enable/--with options
#add  --disable-FEATURE                   # do not include FEATURE (same as --enable-FEATURE=no)
#add  --enable-FEATURE                    # include FEATURE [ARG=yes]
#add  --disable-dependency-tracking       # speeds up one-time build
#add  --enable-dependency-tracking        # do not reject slow dependency extractors
#add  --enable-shared                     # build shared libraries [default=yes]
add  --enable-static                     # build static libraries [default=yes]
#add                                      #  --enable-fast-install[=PKGS]
#                            optimize for fast installation [default=yes]
#add  --disable-libtool-lock              # avoid locking (might break parallel builds)
#add  --enable-debug                      # enables debug symbols default=2
#add  --enable-profile                    # enables profiling
#  
#  Optional Packages:
#add  --with-PACKAGE                      # use PACKAGE [ARG=yes]
#add  --without-PACKAGE                   # do not use PACKAGE (same as --with-PACKAGE=no)
#add  --with-pic                          # try to use only PIC/non-PIC objects [default=use
#                            both]
#add  --with-gnu-ld                       # assume the C compiler uses GNU ld [default=no]
#add  --with-stlport                      # use STLport
#add  --with-stlport-includes             # where the STLport includes are
#add  --with-stlport-libraries            # where STLport library is installed
#add  --with-stlport-libname              # STLport lib base name
#  
#  Some influential environment variables:
#    CC          C compiler command
#    CFLAGS      C compiler flags
#    LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
#                nonstandard directory <lib dir>
#    LIBS        libraries to pass to the linker, e.g. -l<library>
#    CPPFLAGS    (Objective) C/C++ preprocessor flags, e.g. -I<include dir> if
#                you have headers in a nonstandard directory <include dir>
#    CPP         C preprocessor
#    CXX         C++ compiler command
#    CXXFLAGS    C++ compiler flags
#    CXXCPP      C++ preprocessor
#  
#  Use these variables to override the choices made by `configure' or to help
#  it to find libraries and programs with nonstandard names/locations.
#  
#  Report bugs to the package provider.

./configure "${cfg[@]}";
