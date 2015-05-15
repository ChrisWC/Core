#include <iostream>
#include <string>

template <typename T>
struct color
{
	T red;
	T blue;
	T green;
	T alpha;
}

class type
{
	std::string name; //name

	std::string texture;
	std::String normal_map;

	float color[4]; //color

	color ambience;
	color diffusion;
	color specular;
	color emission;
	color shininess;
}
