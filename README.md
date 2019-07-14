# color-segmentation-example

Example for color segmentation.

## Build

0. You need to install essential libraries before building:

- `OpenCV`
- `libtclap-dev`

1. Build

```bash
$ cd /path/to/this/repo
$ mkdir build && cd build
$ cmake .. & make -j
```

## Arguments

```bash
USAGE:

   ./color_segmentation  [-d <string>] [--] [--version] [-h]


Where:

   -d <string>,  --device <string>
     path to camera device

   -h,  --help
     Displays usage information and exits.


   Color segmentation for live video stream
```
