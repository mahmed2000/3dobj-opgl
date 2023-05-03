#include "obj.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <regex>
#include <iostream>

void ObjectLoader::load_mtl(string filename) {
	string tmp;
	ifstream f(filename);
	int mtl_idx = -1;
	while (getline(f, tmp)) {
		if (tmp.rfind("newmtl", 0) == 0) {
			mtl_idx += 1;
			mtls.push_back(*(new Material));
			mtls.back().name = tmp.substr(tmp.rfind(' ') + 1);
		} else if (tmp[0] == 'K') {
			float* target_list;
			switch (tmp[1]) {
				case 'a':
					target_list = mtls.back().ambient;
					break;
				case 'd':
					target_list = mtls.back().diffuse;
					break;
				case 's':
					target_list = mtls.back().specular;
					break;
				default:
					continue;
			};
			char delim = ' ';
			char *token = strtok(const_cast<char*>(tmp.c_str()), &delim);
			for (int i = 0; i < 3; i++) {
				token = strtok(NULL, &delim);
				target_list[i] = atof(token);
			};
			target_list[3] = 1.0f;
		};
	};
};

void ObjectLoader::load_obj(string filename) {
	string tmp;
	ifstream f(filename);
	while (getline(f, tmp)) {
		Material* mtl_ptr;
		if (tmp[0] == 'v') {
			float* target_list;
			switch (tmp[1]) {
				case ' ':
					vertices.push_back(*(new Vertex));
					target_list = vertices.back().pos;
					break;
				case 'n':
					normals.push_back(*(new Normal));
					target_list = normals.back().dir;
					break;
				default:
					continue;
			};
			char delim = ' ';
			char *token = strtok(const_cast<char*>(tmp.c_str()), &delim);
			for (int i = 0; i < 3; i++) {
				token = strtok(NULL, &delim);
				target_list[i] = atof(token);
			};

		} else if (tmp.rfind("usemtl", 0) == 0) {
			mtl_ptr = get_mtl_ptr(tmp.substr(tmp.find(' ') + 1));
		} else if (tmp[0] == 'f') {
			faces.push_back(*(new Face));
			faces.back().mtl = mtl_ptr;
			regex re("f (\\d*)//(\\d*) (\\d*)//(\\d*) (\\d*)//(\\d*)");
			smatch match;
			regex_search(tmp, match, re);
			for (int i = 1; i < 7; i++) {
				if (i % 2 == 0) {
					faces.back().normals.push_back(&(normals[stoi(match.str(i)) - 1]));
				} else {
					faces.back().vertices.push_back(&(vertices[stoi(match.str(i)) - 1]));
				};
			};
		};
	};
};

Material*  ObjectLoader::get_mtl_ptr(string mtl_name) {
	for (int i = 0; i < mtls.size(); i++) {
		if (mtls[i].name == mtl_name) {
			return &(mtls[i]);
		};
	};
};
