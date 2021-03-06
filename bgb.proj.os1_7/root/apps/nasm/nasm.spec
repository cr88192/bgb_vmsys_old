# $Id: nasm.spec.in,v 1.8 2003/08/29 21:03:44 hpa Exp $
Summary: The Netwide Assembler, a portable x86 assembler with Intel-like syntax
Name: nasm
Version: 0.98.38
Serial: 6432256
Release: 1
Copyright: LGPL
Group: Development/Languages
Source: ftp://download.sourceforge.net/pub/sourceforge/nasm/nasm-%{version}.tar.bz2
URL: http://nasm.sourceforge.net/
BuildRoot: /tmp/rpm-build-nasm
Prefix: /usr
BuildPrereq: perl

%package doc
Summary: Extensive documentation for NASM
Group: Development/Languages
Prereq: /sbin/install-info

%package rdoff
Summary: Tools for the RDOFF binary format, sometimes used with NASM.
Group: Development/Tools

%description
NASM is the Netwide Assembler, a free portable assembler for the Intel
80x86 microprocessor series, using primarily the traditional Intel
instruction mnemonics and syntax.

%description doc
Extensive documentation for the Netwide Assembler, NASM, in HTML,
info, PostScript and text formats.

%description rdoff
Tools for the operating-system independent RDOFF binary format, which
is sometimes used with the Netwide Assembler (NASM).  These tools
include linker, library manager, loader, and information dump.

%prep
%setup

%build
CFLAGS="$RPM_OPT_FLAGS" LDFLAGS=-s ./configure --prefix=/usr
make everything

%install
rm -rf "$RPM_BUILD_ROOT"
mkdir -p "$RPM_BUILD_ROOT"
mkdir -p "$RPM_BUILD_ROOT"/usr/bin
mkdir -p "$RPM_BUILD_ROOT"/usr/man/man1
mkdir -p "$RPM_BUILD_ROOT"/%{_infodir}
DOC="$RPM_BUILD_ROOT"/usr/doc/nasm-%{version}
mkdir -p "$DOC"
mkdir -p "$DOC"/rdoff
rm -f "$RPM_BUILD_ROOT"/usr/info/nasm.*
make INSTALLROOT="$RPM_BUILD_ROOT" \
	docdir=/usr/doc/nasm-%{version} \
	infodir=%{_infodir} \
	install_everything
gzip -9 "$RPM_BUILD_ROOT"/%{_infodir}/nasm.*
gzip -9 "$DOC"/*.txt "$DOC"/*.ps
cp AUTHORS CHANGES COPYING README TODO doc/*.doc "$DOC"
cp rdoff/README "$DOC"/rdoff
cp rdoff/doc/* "$DOC"/rdoff

%clean
rm -rf "$RPM_BUILD_ROOT"

%post doc
/sbin/install-info %{_infodir}/nasm.info.gz %{_infodir}/dir

%preun doc
if [ $1 = 0 ]; then
  /sbin/install-info --delete %{_infodir}/nasm.info.gz %{_infodir}/dir
fi

%files
%attr(-,root,root)	/usr/bin/nasm
%attr(-,root,root)	/usr/bin/ndisasm
%attr(-,root,root) %doc /usr/man/man1/nasm.1*
%attr(-,root,root) %doc /usr/man/man1/ndisasm.1*

%files doc
%attr(-,root,root) %doc %{_infodir}/nasm.info*.gz
%attr(-,root,root) %doc /usr/doc/nasm-%{version}/*

%files rdoff
%attr(-,root,root)	/usr/bin/ldrdf
%attr(-,root,root)	/usr/bin/rdf2bin
%attr(-,root,root)	/usr/bin/rdf2com
%attr(-,root,root)	/usr/bin/rdf2ihx
%attr(-,root,root)	/usr/bin/rdfdump
%attr(-,root,root)	/usr/bin/rdflib
%attr(-,root,root)	/usr/bin/rdx
%attr(-,root,root) %doc	/usr/doc/nasm-%{version}/rdoff/*
