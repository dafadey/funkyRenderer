# funky renderer

## What for, Carl?
This is an attempt to smooth edges of geometry on postprocessing in pixel shader.<br>

The basic idea is to used rasterization *pure* 2d output like color buffe (regual rasterized image but not shaded), z(depth)-buffer and normal mapping to produce smooth image, basically to add facets. The idea is very simple: having normal mapping you do not need any smoothing in 3d space, normal mapping represents 3 components of normal vector for each fragment (pixel) which you can use to smooth by bluring normal mapping image in a 2d buffer. That is it! <br>

Simple? It looks so, but there are some problems on *falling* edges. If edge is not continous (i.e. threre is a gap in z-buffer on that edge) you have to be very accurate with smoothing, otherwise result will look really weird. sortf guling something that outght to have a distance. <br>
Anyway all that stuff is actually processed in a second stage fragment shader, while in host code you need just to run two stage rendering (i.e. first render your 3d VBO+VAO to texture and then render your texture to some flat quad covering the screen)

## Build
As simple as
```
make
```
Outght to be crossplatform, but was tested only on Linux, sorry...

## Run
```
./funky
```
Yep, all sample data is hardcoded, refer to main.cpp
Three STL files are used as input. Colors are set in main.cpp.

## Pictures
Sometimes your view is degenerated you get blind flat output, in that case this method alows to draw lines for *falling* edges:
![This is an image](https://github.com/dafadey/funkyRenderer/blob/main/example1.png)
For arbitrary view, you get falling edges and facets, more shades more 3d experience especially for Manhattan geometries:
![This is an image](https://github.com/dafadey/funkyRenderer/blob/main/example2.png)
Method does not try to pretend that everything is smooth. Want your sharp edges - zoom to it:
![This is an image](https://github.com/dafadey/funkyRenderer/blob/main/example3.png)

# A little more thechnical details on the scheme:
![This is an image](https://github.com/dafadey/funkyRenderer/blob/main/doc.svg)
