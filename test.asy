import palette;

file inf = input("Zbuffer.dat").word();

real[] raw = inf;

write("found " + string(raw.length) + " words");

int nx = floor(raw[0]);
int ny = floor(raw[1]);

real[][] img = new real[nx][ny];

for(int j=0;j<ny;++j) {
  for(int i=0;i<nx;++i) {
    img[i][j] = raw[2+i+j*nx];
  }
}

picture p;
image(p, img, (0,0), (nx,ny), BWRainbow());
write("range is " + string(min(img)) + "--" + string(max(img)));
add(p.fit());
