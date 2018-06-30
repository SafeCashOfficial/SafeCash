SafeCash QT
=============

Setup
---------------------
SafeCash QT is the primary wallet for the SafeCash network. It downloads and, by default, stores the entire history of SafeCash transactions; depending on the speed of your computer and network connection, the synchronization process can multiple hours to complete

To download the SafeCash QT Wallet, visit [safecash.io](https://safecash.io/#download).

Running
---------------------
The following are some helpful notes on how to run SafeCash on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/safecash-qt` (GUI) or
- `bin/safecashd` (headless)

### Windows

Unpack the files into a directory, and then run safecash-qt.exe.

### OS X

Drag SafeCash to your applications folder, and then run safecash-qt.

### Need Help?

* Please visit our [forums](https://safecash.io/forum/)

Building
---------------------
The following are developer notes on how to build SafeCash on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The SafeCash repo's [root README](/README.md) contains relevant information on the development process.

License
---------------------
Distributed under the [MIT software license](/COPYING).
