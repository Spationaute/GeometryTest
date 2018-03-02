#ifndef Vertex_hpp
#define Vertex_hpp
#include <iostream>
#include <string>
#include <math.h>

class Vertex
{
public:
	Vertex();
	Vertex(double x, double y, double z);
	~Vertex(){}

	double getX();
	double getY();
	double getZ();

	void set(double x, double y, double z);
	void set(std::string toScan);
	void set(double toSet[3]);

	//Vector functions
	double norm();
	double dot(Vertex& b);
	Vertex cross(Vertex& b);

	//Operators Overloads
	Vertex operator-(Vertex& b);
	Vertex operator+(Vertex& b);
	Vertex operator*(Vertex& b);
	Vertex operator/(const double& b);

	//Printing
	friend bool operator==(Vertex& a, Vertex& b);
	friend std::ostream& operator<<(std::ostream& out,Vertex& toPrint);

private:
	double x,y,z;

};

#endif