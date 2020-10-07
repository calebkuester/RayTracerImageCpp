#ifndef LIGHT_H
#define LIGHT_H
#include <string>
#include <iostream>

class Light{
	public:
		Light* parseData();
		Light();
		Light(std::string s);
	private:
		std::string stringData;
};
#endif
