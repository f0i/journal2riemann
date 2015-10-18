AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing

INCLUDES = -I$(top_srcdir)

bin_PROGRAMS = journal2riemann

#cc `pkg-config --cflags --libs libsystemd` -o test test.c /usr/local/lib/libriemann-client.a /usr/lib/x86_64-linux-gnu/libprotobuf-c.a

journal2riemann_SOURCES = main.c
journal2riemann_LDADD = @ELEMENTARY_LIBS@
journal2riemann_CFLAGS = @ELEMENTARY_CFLAGS@
