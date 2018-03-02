#include <iostream>
#include "Vertex.hpp"
#include "Polyhedron.hpp"
#include <stdlib.h>

using namespace std;
int main(int argc, char const *argv[])
{
	if(argc<4){
		cout << "The program need four arguments ";
		cout << "the path of the stl file ";
		cout << "and three floating point number has arguments" << endl;
		cout << "eg:" << endl;
		cout << "\ttestShape cube.stl 50 50 50" << endl;
		return 0;
	}

	string path = argv[1];
	Vertex testPoint(atof(argv[2]),atof(argv[3]),atof(argv[4]));
	cout << "Input Point:" << endl;
	cout << testPoint <<endl;

	Polyhedron cube;
	cube.setName("Test Geometry");
	cube.loadSTL(path);

	//Set The points inside the geometry
	/*double points[][3]={
			{0,0,0},
			{5,0,0},
			{0,6,0},
			{0,0,7}
		};
	cube.addPoints(points,4);
	//Define the faces
	uint faces[] ={
		0,2,1,
		1,2,3,
		0,3,2,
		0,1,3
	};
	cube.addFaces(faces,4,3);
    */

	cout << cube << endl;

	
	if(cube.isInside(testPoint)){
		cout << "Point inside" << endl;
	}else{
		cout << "Point outside" << endl;
	}

	if(cube.isConvex()){
		cout << "Geometry is is Convex" << endl;
	}else{
		cout << "Geometry is NOT convex" << endl;
	}
	return 0;
}