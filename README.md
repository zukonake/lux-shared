# lux-shared
See IDEAS.md to see what this is about.

# Building
```
mkdir build
cd build
cmake ..
make
```

## Versioning
major version is one that breaks all backward compatibility
minor version is one that maintains backward compatibility with all other minor versions
patch version is a version that does not change the compatibility

current version number can be found in cmake file

shared library - A.B.C
  * A - major version
  * B - minor version
  * C - patch number
client version - A.B.C
  * A - major version of shared library supported
  * B - highest minor version of shared library supported
  * C - patch number
server version - A.B.C
  * A - major version of shared library supported
  * B - highest minor version of shared library supported
  * C - patch number

In other words, for shared, client and server to be compatible, they need to have the same major version, the other versions do not matter, but a newest compatible version should be preferred anyway.
