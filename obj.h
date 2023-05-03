#include <vector>
#include <string>
using namespace std;
struct Vertex {
	float pos[3];
};

struct Normal {
	float pos[3];
};

struct Material {
	int idx;
	string name;
	float ambient[4];
	float specular[4];
	float diffuse[4];
};

struct Face {
	vector<Vertex> vertices;
	Normal normal;
	Material mtl;
};

class ObjectLoader 
{
public:
	void load_obj(string filename);
	void load_mtl(string filename);
	
	vector<Face> faces;

protected:
	vector<Vertex> vertices;
	vector<Normal> normals;
	vector<Material> mtls;
};
