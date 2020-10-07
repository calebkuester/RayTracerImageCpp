#include "Light.h"

Light::Light() : stringData("") {}

Light::Light(std::string s) : stringData(s) {
	parseData();
}

Light* Light::parseData(){
	Light* retVal = new Light();
	std::cout << "light created: "+stringData << std::endl;
	return retVal;
}
