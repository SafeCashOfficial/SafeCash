
Debian
====================
This directory contains files used to package safecashd/safecash-qt
for Debian-based Linux systems. If you compile safecashd/safecash-qt yourself, there are some useful files here.

## safecash: URI support ##


safecash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install safecash-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your safecash-qt binary to `/usr/bin`
and the `../../share/pixmaps/safecash128.png` to `/usr/share/pixmaps`

safecash-qt.protocol (KDE)

