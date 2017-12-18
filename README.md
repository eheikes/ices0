This is a fork of the [Icecast ices0 utility](http://www.icecast.org/ices.php), with the following changes:

* It has been modified to fix Unicode-encoded ID3 metadata. You can read the full story in the [associated blog post](http://ericheikes.com/id3-fix-for-icecast-mp3s/).
* It has username support (through `<Username>` in the XML config, or a `-U` flag), courtesy of Mikko Laine.
* The new [test-src](test-src/README.md) folder contains a debugger/test program.

Check out the [original documentation](README) for ice0 and [Icecast](http://icecast.org/) for how to build and run the utility.
