#include "Polyhedron.hpp"

Polyhedron::Polyhedron(){
	name = "unamed";
}

Polyhedron::~Polyhedron(){}

void Polyhedron::loadSTL(std::string file){
	
	using namespace std;
	cout << "Loading from: " << file << endl;
	ifstream stlFile(file.c_str());
	setName(file);
	faces.clear();
	vertices.clear();

	if(stlFile.good()){
		//The regular expressions
		boost::regex vertexReg("\\s*vertex\\s*(-?\\d+.?\\d*e?[+-]?\\d*)\\s*(-?\\d+.?\\d*e?[+-]?\\d*)\\s*(-?\\d+.?\\d*e?[+-]?\\d*)");
		char readBuffer[255];
		long unsigned int count = 0;
		faces.push_back(face());
		while(!stlFile.eof()){
			boost::smatch results;
			stlFile.getline(readBuffer,255);
			std::string line = readBuffer;
			if(boost::regex_match(line, results, vertexReg)){
				Vertex temp(
							stod(results[1]),
							stod(results[2]),
							stod(results[3])
						);
				//cout << "\t" << temp << endl;
				vertices.push_back(temp);
				faces.back().push_back(vertices.size()-1);
				if(count%3==2){
					//cout << "\t" << "New Face" << endl;
					faces.push_back(face());
				}
				count++;
			}
		}
		if(faces.back().size()<3){
			//cout << "\tLast face incomplet, removing it" << endl;
			faces.pop_back();
		}
	}else{
		cout << "File "<< file <<" cannot be read." << endl;
	}
}

void Polyhedron::setName(std::string name){
	this->name = name;
}

std::string Polyhedron::getName(){
	return name;
}

void Polyhedron::addPoint(Vertex toAdd){
	vertices.push_back(toAdd);
}

void Polyhedron::addPoint(double x, double y, double z){
	vertices.push_back(Vertex(x,y,z));
}

void Polyhedron::addPoints(double toAdd[][3], uint nElem){
	for(int ii=0;ii<nElem;++ii){
		Vertex temp;
		temp.set(toAdd[ii]);
		vertices.push_back(temp);
	}
}



Vertex Polyhedron::normalOfFace(uint index){
	face target = faces[index];
	Vertex origine = vertices[target[0]];
	Vertex one = vertices[target[1]]-origine;
	Vertex two = vertices[target[2]]-origine;
	Vertex n = one.cross(two);
	return n/n.norm();
}

void Polyhedron::addFace(face toAdd){
	faces.push_back(toAdd);
}

void Polyhedron::addFace(uint* faceSet, uint nElem){
	face temp;
	for(int ii=0;ii<nElem;++ii){
		temp.push_back(faceSet[ii]);
	}
	faces.push_back(temp);
}

void Polyhedron::addFaces(uint* faceSet, uint nFaces, uint nElem){
	uint nTotal = nFaces * nElem;
	face temp;
	faces.push_back(temp);
	for(int ii=0;ii<nTotal;++ii){
		faces.back().push_back(faceSet[ii]);
		if( ii%nElem == nElem-1 && ii!=nTotal-1){
			face temp;
			faces.push_back(temp);
		}
	}
}

Vertex Polyhedron::getPoint(uint index){
	if(index>vertices.size()){
		std::cout << "Requested Vertex doesn't exist" << std::endl;
		return Vertex();
	}
	return vertices[index];
}

face Polyhedron::getFace(uint index){
	if(index>faces.size()){
		std::cout << "Requested Vertex doesn't exist" << std::endl;
		return face();
	}
	return faces[index];
}

bool Polyhedron::isInside(Vertex source){
	uint nFaces = faces.size();
	for(int ii=0;ii<nFaces;++ii){
		Vertex origine = vertices[faces[ii][0]];
		Vertex one = origine - source;
		Vertex normale= normalOfFace(ii);
		//std::cout << "Face " << ii << ": " << normale << std::endl;
		double direction = one.dot(normale);
		direction /= one.norm();
		if(direction <0 ){
			//std::cout << "Test Failed at Face: " << ii << std::endl;
			return false;
		}
	}
	return true;
}


bool Polyhedron::isFaceConnected(uint indexA , uint indexB){
	face faceA = faces[indexA];
	face faceB = faces[indexB];
	for (int ii = 0; ii < faceA.size(); ++ii)
	{
		for (int jj = ii++; jj < faceB.size(); ++jj)
		{
			if(vertices[faceA[ii]]==vertices[faceB[jj]]){
				return true;
			}
		}
	}
	return false;
}

bool Polyhedron::isConvex(){
	uint nVertices = vertices.size();
	for (int ii = 0; ii < nVertices; ++ii)
	{
		for (int jj = ii+1; jj < nVertices; ++jj)
		{
			if(!(vertices[ii]==vertices[jj])){
				Vertex middle = (vertices[jj]-vertices[ii])/2;
				middle = vertices[ii]+middle;
				//std::cout << middle << std::endl;
				if(!isInside(middle)){
					return false;
				}
			}
		}
	}
	return true;
}

bool operator==(Vertex& a, Vertex& b){
	if( abs(a.x-b.x)<1e-14 && abs(a.y-b.y)<1e-14 && abs(a.z-b.z)<1e-14){
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out,Polyhedron& toPrint){
	out << toPrint.getName() << " Vertices: " << std::endl;
	for(int ii=0;ii< toPrint.vertices.size();++ii){
		out << "\t" << toPrint.vertices[ii] << std::endl;
	}
	out << "Faces:" << std::endl;
	for (int ii = 0; ii < toPrint.faces.size(); ++ii)
	{
		out << "\t(";
		face temp = toPrint.faces[ii];
		for (int jj = 0; jj < temp.size(); ++jj)
		{
			std::string ending =(jj==temp.size()-1)?") ":", " ;
			out << temp[jj] << ending;
		}
		out << std::endl;
		/* code */
	}
	return out;
}
