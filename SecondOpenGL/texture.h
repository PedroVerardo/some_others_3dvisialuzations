#include <iostream>
#include "state.h"

class Texture;
using TexturePtr = std::shared_ptr<Texture>;

class Texture:public Appearance {
unsigned int m_tex;
std::string m_varname;

	protected :
		Texture(const std::string& varname , const std::string& filename);
		//Texture(const std::string& varname , int width, int height);
		//Texture(const std::string& varname , const glm::vec3& texel);
	public :
		static TexturePtr PtrMake(const std::string& varname , const std::string& filename);
		//static Texture PtrMake(const std::string& varname , int width, int height);
		//static Texture PtrMake(const std::string& varname , const glm::vec3 & texel);
		virtual ~Texture();
		unsigned int GetTexId() const;
		virtual void Load(StatePtr st);
		virtual void Unload(StatePtr st);
};