
Debian
====================
This directory contains files used to package skind/skin-qt
for Debian-based Linux systems. If you compile skind/skin-qt yourself, there are some useful files here.

## skin: URI support ##


skin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install skin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your skinqt binary to `/usr/bin`
and the `../../share/pixmaps/skin128.png` to `/usr/share/pixmaps`

skin-qt.protocol (KDE)

