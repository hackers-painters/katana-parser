#!/bin/sh
#
# Copyright (c) 2015 QFish <im@qfi.sh>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# autoscan
# mv configure.scan configure.ac

if test ! -f "configure.ac"; then
  if test ! -f "configure.in"; then
    echo "autogen.sh: line $LINENO: ERROR: Missing configure.ac or configure.in"
    exit 1
  fi
fi

if test ! -f "Makefile.am"; then
  echo "autogen.sh: line $LINENO: ERROR: ERROR: Missing Makefile.am"
  exit 1
fi

if test -z "$LIBTOOLIZE" -a "`uname`" = "Darwin"; then
  if command -v "glibtoolize" >/dev/null; then
    LIBTOOLIZE=glibtoolize
  elif command -v "libtoolize" >/dev/null; then
    LIBTOOLIZE=libtoolize
  else
    echo "autogen.sh: line $LINENO: command glibtoolize or libtoolize not found"
    exit 1
  fi
fi

${LIBTOOLIZE:-libtoolize}
${ACLOCAL:-aclocal -I m4}
${AUTOCONF:-autoconf}
${AUTOHEADER:-autoheader}
${AUTOMAKE:-automake} --add-missing
