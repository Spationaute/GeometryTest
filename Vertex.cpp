#include "Vertex.hpp"

Vertex::Vertex(){
	set(0, 0, 0);
}
Vertex::Vertex(double x, double y, double z){
	set(x, y, z);
}

double Vertex::getX(){
	return x;
}
double Vertex::getY(){
	return y;
}
double Vertex::getZ(){
	return z;
}

void Vertex::set(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vertex::set(double toSet[3]){
	this->x = toSet[0];
	this->y = toSet[1];
	this->z = toSet[2];
}

double Vertex::norm(){
	return sqrt( x*x + y*y + z*z);
}

double Vertex::dot(Vertex& b){
	return (x * b.getX() + y * b.getY() + z * b.getZ());
}

Vertex Vertex::cross(Vertex& b){
	return Vertex( y*b.z - b.y*z, z*b.x - b.z*x, x*b.y - b.x*y);
}

Vertex Vertex::operator-(Vertex& b){
	return Vertex(x - b.getX(), y - b.getY(), z - b.getZ());
}	

Vertex Vertex::operator+(Vertex& b){
	return Vertex(x + b.getX(), y + b.getY(), z + b.getZ());
}

Vertex Vertex::operator*(Vertex& b){
	return Vertex(x * b.getX(), y * b.getY(), z * b.getZ());
}

Vertex Vertex::operator/(const double& b){
	return Vertex( x/b, y/b, z/b);
}

std::ostream& operator<<(std::ostream& out,Vertex& toPrint){
	out << "( " << toPrint.x << ", ";
	out << toPrint.y << ", ";
	out << toPrint.z << " )";
	return out;
}