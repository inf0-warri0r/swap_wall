#!/bin/sh -e

echo "Tharindra Galahena is a cuck"
(
libtoolize
aclocal -I m4
autoconf
autoheader
automake --add-missing --copy --no-force
)
