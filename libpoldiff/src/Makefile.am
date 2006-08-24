lib_LIBRARIES = libpoldiff.a

poldiffso_DATA = @libpoldiff_soname@
poldiffsodir = $(libdir)

AM_CFLAGS = @DEBUGCFLAGS@ @WARNCFLAGS@ @PROFILECFLAGS@ @SELINUX_CFLAGS@ \
	@APOL_CFLAGS@ @QPOL_CFLAGS@ -I$(srcdir)/../include -fpic
AM_LDFLAGS = @DEBUGLDFLAGS@ @WARNLDFLAGS@ @PROFILELDFLAGS@

libpoldiff_a_SOURCES = \
	poldiff.c \
	bool_diff.c bool_internal.h \
	class_diff.c class_internal.h \
	user_diff.c user_internal.h \
	poldiff_internal.h
libpoldiff_a_DEPENDENCIES = $(top_builddir)/libapol/src/libapol.so

libpoldiff_so_OBJS = $(patsubst %.c,%.o,$(filter %.c,$(libpoldiff_a_SOURCES)))
LIBPOLDIFF_SONAME = @libpoldiff_soname@

dist_noinst_DATA = libpoldiff.map

$(poldiffso_DATA): $(libpoldiff_so_OBJS) libpoldiff.map
	$(CC) -shared -o $@ $(libpoldiff_so_OBJS) $(AM_LDFLAGS) $(LDFLAGS) -Wl,-soname,$(LIBPOLDIFF_SONAME),--version-script=$(srcdir)/libpoldiff.map,-z,defs $(top_builddir)/libqpol/src/libqpol.so $(top_builddir)/libapol/src/libapol.so
	$(LN_S) -f $@ libpoldiff.so

$(top_builddir)/libapol/src/libapol.so:
	$(MAKE) -C $(top_builddir)/libapol/src $(notdir $@)

$(top_builddir)/libqpol/src/libqpol.so:
	$(MAKE) -C $(top_builddir)/libqpol/src $(notdir $@)

install-data-hook:
	cd $(DESTDIR)$(poldiffsodir) && $(LN_S) -f $(poldiffso_DATA) libpoldiff.so

mostlyclean-local:
	-rm -rf *.gcno *.gcda *.gprof *.gcov libpoldiff.so $(poldiffso_DATA)

uninstall-local:
	-rm -rf $(poldiffsodir)/libpoldiff.so