#pragma once

#include <fstream>
#include <iostream>

#include "geo.h"
#include "timer.h"

geo readSTL(const char* filename) {
	timer t("reading complete in ");
	geo g;
	std::ifstream inf(filename, std::ios_base::binary);
	//skip header
	inf.seekg(80);
	uint32_t ntris;
	inf.read((char*)&ntris, sizeof(ntris));
	std::cout << "reading " << ntris << " triangles from " << filename << '\n'; 
	g.points.resize(ntris*3);
	for(int i=0; i<ntris; i++) {
	  float n[3];
	  float v1[3];
	  float v2[3];
	  float v3[3];
	  inf.read((char*)n, sizeof(float)*3);
	  inf.read((char*)v1, sizeof(float)*3);
	  inf.read((char*)v2, sizeof(float)*3);
	  inf.read((char*)v3, sizeof(float)*3);
	  uint16_t junk;
	  inf.read((char*)&junk, sizeof(junk));
	  g.points[i*3] = vec3{v1[0],v1[1],v1[2]};
	  g.points[i*3+1] = vec3{v2[0],v2[1],v2[2]};
	  g.points[i*3+2] = vec3{v3[0],v3[1],v3[2]};
	  g.push_back(triangle{&g.points[i*3], &g.points[i*3+1], &g.points[i*3+2]});
	}
	return g;
}
