mkdir -p build
cd build
cmake .. \
    -G "Visual Studio 12 2013 Win64" \
    -DOpenCV_DIR:PATH=c:/opencv/build
