#  Copyright (c) 2000-2017, Parallels International GmbH
# Copyright (c) 2017-2019 Virtuozzo International GmbH. All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#  Our contact details: Virtuozzo International GmbH, Vordergasse 59, 8200
#  Schaffhausen, Switzerland.

include $(top_srcdir)/paths.am

AM_CPPFLAGS = -Wall -I$(top_srcdir)/include -I$(top_srcdir)/lib \
	      -DSBINDIR=\"$(sbindir)\" \
	      -DPKGCONFDIR=\"$(pkgconfdir)\" \
	      -DPKGLIBDIR=\"$(pkglibdir)\"

#sbin_PROGRAMS = test
noinst_PROGRAMS = test

VZCTL_LIBS = $(top_builddir)/lib/libvzctl2.la -lpthread


test_SOURCES = test.c test_config.c test_vzctl.c
test_LDADD = $(VZCTL_LIBS) $(UTIL_LIBS)
