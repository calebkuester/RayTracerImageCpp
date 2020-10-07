#include <string>
#include "material.h"
#include <iostream>
#include <sstream>

/*
*Example of material input as string:
*newmtl blue
*Ka 1.000000000000 1.000000000000 1.000000000000	//ambient reflection
*Kd 0.1 0.1 0.9					//difuse reflection
*Ks 0.5 0.15 0.35 					//specular reflection
*Ns 100 						//specular exponent
*n1 1.000000000000
*Tr 1.000000000000
*Kr 1
*Krf 1
*/

std::string materialString = "";

material::material(std::string materialData, short debug){
	materialString = materialData;
	this->ka = setColor("Ka ", "Kd ", debug);//ka
	this->kd = setColor("Kd ", "Ks ", debug);//kd
	this->ks = setColor("Ks ", "Ns ", debug);//ks
}

struct material::Color* material::setColor(std::string beginString, std::string endString, short debug){
	std::string newmtl = "newmtl ";
	int newmtlLength = newmtl.length();
	materialName = materialString.substr(newmtlLength, materialString.find('\n')-newmtlLength);
	material::Color *kdColor = new material::Color{};
	std::string beginningPart = beginString;
	int begin = materialString.find(beginString)+beginString.length();
	int end = materialString.find(endString);
	int length = end-begin;
	std::string colorStringData = materialString.substr(begin, length);
	int firstSpace = colorStringData.find(" ");
	int secondSpace = colorStringData.substr(firstSpace+1, colorStringData.length()-(firstSpace+1)).find(" ")+firstSpace+1;
	std::string rString = colorStringData.substr(0, firstSpace);
	std::string gString = colorStringData.substr(firstSpace+1, secondSpace-(firstSpace));
	std::string bString = colorStringData.substr(secondSpace+1, materialString.length()-(secondSpace+1));
	if(debug){
		std::cout << beginString << " found: " << firstSpace << " " << secondSpace << " " << rString << " " << gString << " " << bString;
		std::cout << rString << std::endl;
		std::cout << gString << std::endl;
		std::cout << bString;
		std::cout << beginString << " found:     " << colorStringData << std::endl;
	}
	kdColor->r = stod(rString);
	kdColor->g = stod(gString);
	kdColor->b = stod(bString);
	return kdColor;
}

void material::setTr(std::string materialData){
	materialData = materialData;
}
void material::setNs(std::string materialData){
	materialData = materialData;
}
void material::setN1(std::string materialData){
	materialData = materialData;
}
void material::setKr(std::string materialData){
	materialData = materialData;
}
void material::setKrf(std::string materialData){
	materialData = materialData;
}

material::Color* material::getKa(){
	return this->ka;
}

material::Color* material::getKd(){
	return this->kd;
}

material::Color* material::getKs(){
	return this->ks;
}

material::Color* getTr(std::string stringData){
	stringData = stringData;
	material::Color *c = new material::Color();
	return c;
}

material::Color* getNs(std::string stringData){
	stringData = stringData;
	material::Color *c = new material::Color();
	return c;
}

material::Color* getN1(std::string stringData){
	stringData = stringData;
	material::Color *c = new material::Color();
	return c;
}

material::Color* getKr(std::string stringData){
	stringData = stringData;
	material::Color *c = new material::Color();
	return c;
}

material::Color* getKrf(std::string stringData){
	stringData = stringData;
	material::Color *c = new material::Color();
	return c;
}
std::string material::toString(){
	std::ostringstream oss;
	oss << this->materialName << '\n';
	oss << "ka: " << std::to_string(this->getKa()->r) << " " << std::to_string(this->getKa()->g) << " " << std::to_string(this->getKa()->b)<< '\n';
	oss << "kd: " << std::to_string(this->getKd()->r) << " " << std::to_string(this->getKd()->g) << " " << std::to_string(this->getKd()->b)<< '\n';
	oss << "ks: " << std::to_string(this->getKs()->r) << " " << std::to_string(this->getKs()->g) << " " << std::to_string(this->getKs()->b)<< '\n';
	return oss.str();
}

