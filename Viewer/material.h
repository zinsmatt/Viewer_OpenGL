#ifndef MATERIAL_H
#define MATERIAL_H


class Material
{
private:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shininess;
public:
	Material() ;
	~Material();
	void apply() const;

	void setAmbient(float r, float g, float b, float a) { ambient[0]=r; ambient[1]=g; ambient[2]=b; ambient[3]=a; }
	void setDiffuse(float r, float g, float b, float a) { diffuse[0]=r; diffuse[1]=g; diffuse[2]=b; diffuse[3]=a; }
	void setSpecular(float r, float g, float b, float a) { specular[0]=r; specular[1]=g; specular[2]=b; specular[3]=a; }
	void setEmission(float r, float g, float b, float a) { emission[0]=r; emission[1]=g; emission[2]=b; emission[3]=a; }
	void setShininess(float val) { shininess = val; }

	const float* getAmbient() { return ambient; }
	const float* getDiffuse() { return diffuse; }
	const float* getSpecular() { return specular; }
	const float* getEmission() { return emission; }
	float getShininess() { return shininess; }

};

#endif // MATERIAL_H
