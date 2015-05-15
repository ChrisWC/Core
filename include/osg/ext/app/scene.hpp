#include <string>

class scene
{
private:
	std::string name;
public:
	scene();
	~scene();

	virtual bool initialize();
	virtual bool start();
}
