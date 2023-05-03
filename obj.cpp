#include "obj.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

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

	}
}
