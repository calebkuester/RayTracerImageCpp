#ifndef MATERIAL_H
#define MATERIAL_H
class material{
	public :
		struct Color{
			double r;
			double g;
			double b;
		};
		material();
		material(std::string, short);
		Color* getKa();
		Color* getKd();
		Color* getKs();
		Color* getTr(std::string);
		Color* getNs(std::string);
		Color* getN1(std::string);
		Color* getKr(std::string);
		Color* getKrf(std::string);
		struct material::Color* setColor(std::string, std::string, short int);
		void setTr(std::string);
		void setNs(std::string);
		void setN1(std::string);
		void setKr(std::string);
		void setKrf(std::string);
		std::string toString();
	private :
		std::string materialName;
		double tr; //transparency (alpha)
		//if the tr value is 0.2, then the final total illumination is 0.2*(isub(a)+isub(d)+isub(spec)+isub(refl))+0.8*isub(refr)
		int ns; //shininess
		double n1; //reflractive index
		double kr; //attenuation for the reflection component
		double krf; //attenuation for the refraction component
		struct material::Color *ka;/*ambient reflection color*/
		struct material::Color *kd;/*diffuse reflection color*/
		struct material::Color *ks;/*specular reflection color*/
		
};
#endif
