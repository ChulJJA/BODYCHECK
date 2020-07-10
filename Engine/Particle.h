/*
 * Author		:Jeesoo Kim
 * File			:Particle.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Particle
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

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
	SPEEDMODE,
	MISSILE,
	WIN,
};

class ParticleGenerator
{
public:
	// Constructor
	ParticleGenerator(Object* object, GLuint amount, const char* texture_path, ParticleType type);
	// Update all particles
	void Update(float dt, Object* object, GLuint newParticles, vector2 offset = vector2(0.0f, 0.0f));
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

	GLuint lastUsedParticle = 0;
	float angle = 0;

	Vertices shape;
	Shader shader;
	Texture texture;
	material material;

	matrix3 mat_ndc;
	ParticleType m_type;

	bool red = true;
	bool green = false;
	bool blue = false;

	float theta = 15.0f;
	int circle_points = 1;
};