#pragma once
#include <GL/glew.h>
#include "Component.hpp"
#include "vector2.hpp"
#include "Shader.hpp"
#include "Graphic.h"
#include "Color4f.hpp"
#include "Vertices.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Image.hpp"
#include "Physics.h"
#include "Component_Player.h"
#include "ObjectManager.h"

//class ParticleSystem : public Component
//{
//public:
//	// Constructor
//	ParticleSystem(Object* obj, unsigned int amount);
//	//// Update all particles
//	//void Update(GLfloat dt, Object& object, GLuint newParticles, vector2 offset = vector2(0.0f, 0.0f));
//	//// Render all particles
//	//void Draw();
//	bool Can_Load_To_Texture(Texture& texture, const char* file_path);
//	void Init(Object* obj) override;
//	void Update(float dt) override;
//private:
//
//	float random = ((rand() % 100) - 50) / 70.0f;
//	float lifetime;
//	Object* particle_handler;
//	unsigned int particle_amount;
//	Shader shader;
//	Vertices shape;
//	material material;
//	Texture texture;
//	Image image;
//	// Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
//	//GLuint firstUnusedParticle();
//	// Respawns particle
//	//void respawnParticle(Particle& particle, Object& object, vector2 offset = vector2(0.0f, 0.0f));
//
//	float seconds = 0;
//	int width = 1280, height = 720;
//};

struct Particle {
	vector2 position, velocity;
	Color4f color;
	float life;

	Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};

enum class ParticleType
{
	DASH,
	COLLIDE,
	DESTROY
};

class ParticleGenerator
{
public:
	// Constructor
	ParticleGenerator(Object* object, GLuint amount, const char* texture_path, ParticleType type);
	// Update all particles
	void Update(GLfloat dt, Object* object, GLuint newParticles, vector2 offset = vector2(0.0f, 0.0f));
	// Render all particles
	void Draw(Object* object);
	bool Can_Load_To_Texture(Texture& texture, const char* file_path);
	void SetProjectionMatrix(Object* obj);
private:
	GLuint firstUnusedParticle();
	void respawnParticle(Particle& particle, Object* object, vector2 offset = vector2(0.0f, 0.0f));

	int total_particles;
	int alive_particles;
	std::vector<Particle> particles;

	Vertices shape;
	Shader shader;
	Texture texture;
	material material;

	matrix3 mat_ndc;
	ParticleType m_type;


};