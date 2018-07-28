#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SAFECASHD=${SAFECASHD:-$SRCDIR/safecashd}
SAFECASHCLI=${SAFECASHCLI:-$SRCDIR/safecash-cli}
SAFECASHTX=${SAFECASHTX:-$SRCDIR/safecash-tx}
SAFECASHQT=${SAFECASHQT:-$SRCDIR/qt/safecash-qt}

[ ! -x $SAFECASHD ] && echo "$SAFECASHD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SCASHVER=($($SAFECASHCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for safecashd if --version-string is not set,
# but has different outcomes for safecash-qt and safecash-cli.
echo "[COPYRIGHT]" > footer.h2m
$SAFECASHD --version | sed -n '1!p' >> footer.h2m

for cmd in $SAFECASHD $SAFECASHCLI $SAFECASHTX $SAFECASHQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SCASHVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SCASHVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
