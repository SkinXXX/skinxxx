
Debian
====================
This directory contains files used to package skinxxxd/skinxxx-qt
for Debian-based Linux systems. If you compile skinxxxd/skinxxx-qt yourself, there are some useful files here.

## skinxxx: URI support ##


skinxxx-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install skinxxx-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your skinqt binary to `/usr/bin`
and the `../../share/pixmaps/skinxxx128.png` to `/usr/share/pixmaps`

skinxxx-qt.protocol (KDE)

