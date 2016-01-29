# Read Picture
This program is used to read picture

# How to Build

## Use Makefile
```
make
```

## Use CMake
```
mkdir build
cd build
cmake ..
make
```

# How to Use pkg-config

## Shell
```
pkg-config --cflags opencv
pkg-config --libs opencv
```

# Add opencv include and lib to Makefile
```
$(shell pkg-config --cflags opencv)
$(shell pkg-config --libs opencv)
```

# Add opencv include and lib to QT project file (.pro)
```
CONFIG += link_pkgconfig
PKGCONFIG += opencv
```
