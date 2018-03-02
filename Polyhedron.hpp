#ifndef Polyhedron_HPP
#define Polyhedron_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include "Vertex.hpp"
#include <string>
#include <boost/regex.hpp>

typedef unsigned int uint;
typedef std::vector<uint> face;

class Polyhedron
{
public:
	Polyhedron();
	~Polyhedron();

	void loadSTL(std::string file);

	void setName(std::string name);
	std::string getName();

	void addPoint(Vertex toAdd);
	void addPoint(double x, double y, double z);
	void addPoints(double toAdd[][3], uint nElem);

	void addFace(face toAdd);
	void addFace(uint* faceSet,uint nElem);
	//If all faces are the same dimension:
	void addFaces(uint* faceSet, uint nFaces, uint nElem);

	Vertex getPoint(uint index);
	face getFace(uint index);
	//This fonction suppose that all points
	//of the face are in one plan
	Vertex normalOfFace(uint index);
	bool isInside(Vertex source);
	bool isFaceConnected(uint indexA , uint indexB);
	//Only work is all faces are triangle
	bool isConvex();

	friend std::ostream& operator<<(std::ostream& out,Polyhedron& toPrint);


private:
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<face> faces;
};

#endif