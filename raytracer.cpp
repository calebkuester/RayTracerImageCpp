#include "Camera.h"
#include "Light.h"
#include "material.h"
#include <cstring> //memset
#include <iostream>
#include <fstream>
#include <chrono>

class RayTracer{
	public:
		material* materialList[65535];
		Camera* cameraList[65535];
		Light* lightList[65535];
		std::string outputFileName = "";
		int screenWidth = 0;
		int screenHeight = 0;
		int rayDepth = 0;
		unsigned int *pixels;
		int materialCount = 0;
		unsigned long startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		short debug = 0;

		void getMaterialData(char* fileName){
			std::ifstream materialFile(fileName);
			std::string line="";
			int limit = sizeof(materialList);
			int currentMaterialIndex=0;
			std::string materialStringData;
			std::string materialArray[9];
			if(!materialFile){
				std::cout << "Material File: \""+std::string(fileName)+"\" not found. Halting"+'\n';
				exit(0);
			}
			while(std::getline(materialFile, line)){
				materialStringData = "";
				if(currentMaterialIndex>=limit){
					break;
				}
				
				if(line[0]=='#'){
					continue;
				}
				if(line.substr(0, line.find(" ")) == "newmtl"){//if the first word is "newmtl"
					for(int i = 0; line!="\n" && i<9 ; std::getline(materialFile, line)){
						materialArray[i] = line;
						i++;
					}
					for(int i=0; i<9; i++){
						materialStringData += materialArray[i]+'\n';
						
						//std::cout << materialArray[i] << std::endl;
					}
					materialList[materialCount] = new material(materialStringData, debug);
					materialCount++;
					if(debug){
						std::cout << materialStringData << std::endl;
					}
					
				}
				currentMaterialIndex += line.length();
			}
			materialFile.close();
			std::cout << "Material File: \""+std::string(fileName)+"\" Loaded"+'\n';
		}

		void getRenderedElements(char* fileName){
			std::ifstream materialFile(fileName);
			std::string line="";
			
		}

		void getSceneData(char* fileName){
			std::ifstream commandsFile(fileName);
			std::string line;
			int spaceLocations[500];
			int j;
			std::memset( spaceLocations, -1, sizeof( spaceLocations ) );

			if(!commandsFile){
				std::cout << "Commands File: \""+std::string(fileName)+"\" not found. Halting"+'\n';
				exit(0);
			}
			while(std::getline(commandsFile, line)){
				j = 0;
				if(line[0] == 'r' && line[1] == ' '){
					for(int i=1; i<(int)line.size(); i++){
						if(line[i] == ' '){
							spaceLocations[j] = i;
							j++;
						}
					}
					outputFileName = line.substr(spaceLocations[0]+1,spaceLocations[1]-2);
					screenWidth = std::stoi(line.substr(spaceLocations[1]+1,spaceLocations[2]-(spaceLocations[1]+1)));
					screenHeight = std::stoi(line.substr(spaceLocations[2]+1,spaceLocations[3]-(spaceLocations[2]+1)));
					rayDepth = std::stoi(line.substr(spaceLocations[3]+1,spaceLocations[4]-(spaceLocations[3]+1)));

					//std::cout << "1: file name: " + outputFileName << std::endl;
					//std::cout << "2: screen width: " << screenWidth << std::endl;
					//std::cout << "3: screen height: " << screenHeight << std::endl;
					// std::cout << "4: ray depth: " << rayDepth << std::endl;
				}
				
			}

		}

		void renderScene(){
			std::ofstream outputFile;
			outputFile.open("output/"+outputFileName+".ppm");
			outputFile << "P6 \n";
			outputFile << screenWidth << " \n";
			outputFile << screenHeight << " \n";
			outputFile << "255 \n";

			int sizeOfPixelArray = screenWidth*screenHeight;
			
			
			pixels = new unsigned int[sizeOfPixelArray]; //TODO: Decide which is more viable

			std::memset( pixels, 0, sizeOfPixelArray*sizeof(int) );
			
			//pixels[(y*screenHeight)+x]
			for(int y=0; y<screenHeight; y++){
				for(int x=0; x<screenWidth; x++){
					//outputFile << (char)(255) << (char)(255) << (char)(255);
					outputFile << (char)(0) << (char)(0) << (char)(0); //g b r
				}
			}

			outputFile.close();

		}
		
		~RayTracer(){
			delete pixels;
			long completionTime = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) - startTime;
			std::cout << "Program completed in " << completionTime << "ms\n";
		}
};
int main(int argc, char** argv){
	RayTracer a;
	if(argc!=5){
		std::cout << "expected usage: *program name* *material file name* *scene file name* *debug* (true or false)\n";
		exit(0);
	}
	if(argv[4][0] == 't' && argv[4][1] == 'r' && argv[4][2] == 'u' && argv[4][3] == 'e'){
		std::cout << "debug mode" << std::endl;
		a.debug=1;
	}
	a.getMaterialData(argv[1]); //first argument
	a.getRenderedElements(argv[2]);
	a.getSceneData(argv[3]);
	
	a.renderScene();
	if(a.debug){
		for(int i=0; i<a.materialCount; i++){
			std::cout << a.materialList[i]->toString() << std::endl;
		}
	}
	
}
