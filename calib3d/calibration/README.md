# Calibration
This is a camera calibration program.

# How to Use
camera calibration
```
./calibration -w=9 -h=6 -n=20 -o=camera.yml

```

images calibration (read from image list)
```
./calibration -w=9 -h=6 -n=20 -o=camera.yml image_list.xml

```
-su show undistorted images after calibration

use asymmetric circles
```
./calibration -w=4 -h=11 -pt=acircles
```
