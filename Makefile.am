AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing
ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = -I${top_srcdir}/src -I${top_builddir}/src

bin_PROGRAMS = journal2riemann

#cc `pkg-config --cflags --libs libsystemd` -o test test.c /usr/local/lib/libriemann-client.a /usr/lib/x86_64-linux-gnu/libprotobuf-c.a

journal2riemann_SOURCES = src/main.c
journal2riemann_LDADD = @RIEMANN_CLIENT_LIBS@ @LIBSYSTEMD_LIBS@
journal2riemann_CFLAGS = @RIEMANN_CLIENT_CFLAGS@ @LIBSYSTEMD_CFLAGS@
