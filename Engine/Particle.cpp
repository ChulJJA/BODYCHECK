/*
 * Author		:Jeesoo Kim
 * File			:Particle.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Particle
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Particle.h"

#include "Component_Missile.h"
#include "StockShaders.hpp"
#include "UsefulTools.hpp"
#include "Graphic.h"
#include "GL.hpp"

ParticleGenerator::ParticleGenerator(Object* obj, GLuint amount, const char* texture_path, ParticleType type)
{
	total_particles = amount;
	material.shader = &(SHADER::particles());

	const auto path = texture_path;
	m_type = type;
	Mesh square;

	if (!Can_Load_To_Texture(texture, path))
	{
		printf("Particle Texture Load Fail!?\n");
	}

	texture.SelectTextureForSlot(texture);
	material.textureUniforms["texture_to_sample"] = { &(texture) };

	switch (m_type)
	{
	case ParticleType::SPEEDMODE:
		square = MESH::create_box(120, { 255,255,255,255 });
		shape.InitializeWithMeshAndLayout(square, SHADER::particles_layout());
		break;
	case ParticleType::COLLIDE:

		square = MESH::create_box(100, { 255,255,255,255 });
		shape.InitializeWithMeshAndLayout(square, SHADER::particles_layout());
		break;
	case ParticleType::DASH:
		square = MESH::create_box(120, { 255,255,255,255 });
		shape.InitializeWithMeshAndLayout(square, SHADER::particles_layout());
		break;
	case ParticleType::MISSILE:
		square = MESH::create_box(120, { 255,255,255,255 });
		shape.InitializeWithMeshAndLayout(square, SHADER::particles_layout());
		break;
	case ParticleType::WIN:
		square = MESH::create_box(120, { 255,255,255,255 });
		shape.InitializeWithMeshAndLayout(square, SHADER::particles_layout());
		break;
	default:
		break;
	}

	for (GLuint i = 0; i < this->total_particles; ++i)
		this->particles.push_back(Particle());
}


void ParticleGenerator::Update(float dt, Object* object, GLuint newParticles, vector2 offset)
{
	if (object->GetComponentByTemplate<Player>() != nullptr || object->GetComponentByTemplate<Missile>() != nullptr)
	{
		for (GLuint i = 0; i < newParticles; ++i)
		{
			int unusedParticle = this->firstUnusedParticle();
			this->respawnParticle(this->particles[unusedParticle], object, offset);
		}

		switch (m_type)
		{
		case ParticleType::SPEEDMODE:

			for (GLuint i = 0; i < this->total_particles; ++i)
			{
				Particle& p = this->particles[i];
				p.life -= dt * 5.0f;
				if (p.life > 0.0f)
				{
					p.position -= (p.velocity * dt);
					p.color.alpha -= dt * 2.5f;
				}
			}
			break;
		case ParticleType::COLLIDE:
			for (GLuint i = 0; i < this->total_particles; ++i)
			{
				Particle& p = this->particles[i];
				p.life -= dt * 4.0f;
				if (p.life > 0.0f)
				{
					p.position.x += p.velocity.x * object->GetScale().x * 1.5f;
					p.position.y += p.velocity.y * object->GetScale().y * 1.5f;
					p.color.alpha -= dt * 2.5f;
				}
			}
			break;
		case ParticleType::DASH:
			for (GLuint i = 0; i < this->total_particles; ++i)
			{
				Particle& p = this->particles[i];
				p.life -= dt * 5.0f;
				if (p.life > 0.0f)
				{
					p.position -= (p.velocity * dt);
					p.color.alpha -= dt * 2.5f;
				}
			}
		case ParticleType::MISSILE:
			for (GLuint i = 0; i < this->total_particles; ++i)
			{
				Particle& p = this->particles[i];
				p.life -= dt * 5.0f;
				if (p.life > 0.0f)
				{
					p.position -= (p.velocity * dt);
					p.color.alpha -= dt * 2.5f;
				}
			}
		case ParticleType::WIN:
			for (GLuint i = 0; i < this->total_particles; ++i)
			{
				Particle& p = this->particles[i];
				p.life -= dt * 5.0f;
				if (p.life > 0.0f)
				{
					p.position -= object->GetTransform().GetTranslation();
					p.position = rotate_by(15, p.position);
					p.position += object->GetTransform().GetTranslation();
					p.color.alpha -= dt * 2.0f;
				}
			}
			break;
		default:
			break;
		}
	}
}

void ParticleGenerator::Draw(Object* obj)
{
	if (obj->GetComponentByTemplate<Player>() != nullptr || obj->GetComponentByTemplate<Missile>() != nullptr)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		material.shader->Select(*(material.shader));
		switch (m_type)
		{
		case ParticleType::SPEEDMODE:
			for (Particle particle : this->particles)
			{
				if (particle.life > 0.0f)
				{
					material.vectorUniforms["offset"] = particle.position;
					material.color4fUniforms["color"] = particle.color;

					matrix3 result = MATRIX3::build_identity();
					result *= MATRIX3::build_translation({ particle.position.x, particle.position.y }) *
						MATRIX3::build_rotation(obj->GetTransform().GetRotation()) *
						MATRIX3::build_scale({ obj->GetScale().x , obj->GetScale().y });
					matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
					mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
					mat_ndc *= result;
					material.matrix3Uniforms["to_ndc"] = mat_ndc;
					GL::draw(shape, material);
					GL::end_drawing();
				}
			}
			break;
		case ParticleType::COLLIDE:
			for (Particle particle : this->particles)
			{
				if (particle.life > 0.0f)
				{
					material.vectorUniforms["offset"] = particle.position;
					material.color4fUniforms["color"] = particle.color;

					matrix3 result = MATRIX3::build_identity();
					result *= MATRIX3::build_translation({ particle.position.x, particle.position.y }) * MATRIX3::build_rotation(0.0f) * MATRIX3::build_scale({ 1.0f,1.0f });
					matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
					mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
					mat_ndc *= result;
					material.matrix3Uniforms["to_ndc"] = mat_ndc;
					GL::draw(shape, material);
					GL::end_drawing();
				}
			}
			break;
		case ParticleType::DASH:
			for (Particle particle : this->particles)
			{
				if (particle.life > 0.0f)
				{
					material.vectorUniforms["offset"] = particle.position;
					material.color4fUniforms["color"] = particle.color;

					matrix3 result = MATRIX3::build_identity();
					result *= MATRIX3::build_translation({ particle.position.x, particle.position.y }) *
						MATRIX3::build_rotation(obj->GetTransform().GetRotation()) *
						MATRIX3::build_scale({ obj->GetScale().x - 1.f, obj->GetScale().y - 1.f });
					matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
					mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
					mat_ndc *= result;
					material.matrix3Uniforms["to_ndc"] = mat_ndc;
					GL::draw(shape, material);
					GL::end_drawing();
				}
			}
		case ParticleType::MISSILE:
			for (Particle particle : this->particles)
			{
				if (particle.life > 0.0f)
				{
					material.vectorUniforms["offset"] = particle.position;
					material.color4fUniforms["color"] = particle.color;
					
					matrix3 result = MATRIX3::build_identity();
					result *= MATRIX3::build_translation({ particle.position.x, particle.position.y }) *
						MATRIX3::build_rotation(obj->GetTransform().GetRotation()) *
						MATRIX3::build_scale({ obj->GetScale().x - 0.2f, obj->GetScale().y- 0.6f });
					matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
					mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
					mat_ndc *= result;
					material.matrix3Uniforms["to_ndc"] = mat_ndc;
					GL::draw(shape, material);
					GL::end_drawing();
				}
			}
		case ParticleType::WIN:
			for (Particle particle : this->particles)
			{
				if (particle.life > 0.0f)
				{
					material.vectorUniforms["offset"] = particle.position;
					material.color4fUniforms["color"] = particle.color;

					matrix3 result = MATRIX3::build_identity();
					result *= MATRIX3::build_translation({ particle.position.x, particle.position.y }) *
						MATRIX3::build_rotation(obj->GetTransform().GetRotation()) *
						MATRIX3::build_scale({ obj->GetScale().x - 0.5f, obj->GetScale().y - 0.5f });
					matrix3 mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
					mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
					mat_ndc *= result;
					material.matrix3Uniforms["to_ndc"] = mat_ndc;
					GL::draw(shape, material);
					GL::end_drawing();
				}
			}
			break;
		default:
			break;
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

bool ParticleGenerator::Can_Load_To_Texture(Texture& texture, const char* file_path)
{
	const bool is_okay = texture.LoadFromPNG(file_path);
	if (!is_okay)
	{
	}
	return is_okay;
}

void ParticleGenerator::SetProjectionMatrix(Object* obj)
{
	matrix3 result = MATRIX3::build_identity();
	result *= MATRIX3::build_translation({ obj->GetTransform().GetTranslation().x, obj->GetTransform().GetTranslation().y }) * MATRIX3::build_rotation(0.0f) * MATRIX3::build_scale({ 1.0f,1.0f });

	mat_ndc = Graphic::GetGraphic()->Get_View().Get_Camera_View().GetCameraToNDCTransform();
	mat_ndc *= Graphic::GetGraphic()->Get_View().Get_Camera().WorldToCamera();
	mat_ndc *= result;
	material.matrix3Uniforms["to_ndc"] = mat_ndc;
}

GLuint ParticleGenerator::firstUnusedParticle()
{
	for (GLuint i = lastUsedParticle; i < this->total_particles; ++i) {
		if (this->particles[i].life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, Object* object, vector2 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	if (m_type == ParticleType::SPEEDMODE)
	{
		if (red)
		{
			green = true;
			red = false;
			particle.color = Color4f(1.f, 0.f, 0.f, 1.f);
		}
		else if (green)
		{
			blue = true;
			green = false;
			particle.color = Color4f(0.f, 1.f, 0.f, 1.f);
		}
		else if (blue)
		{
			blue = false;
			red = true;
			particle.color = Color4f(0.f, 0.f, 1.f, 1.f);
		}

		particle.position = object->GetTransform().GetTranslation() + offset;
		particle.life = 1.0f;
		particle.velocity = object->GetComponentByTemplate<Player>()->GetPlayerVelocity() + vector2(random);
	}
	else if (m_type == ParticleType::COLLIDE || m_type == ParticleType::DASH)
	{
		GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
		particle.color = Color4f(rColor, rColor, rColor, 1.0f);

		particle.position = object->GetTransform().GetTranslation() + offset;
		particle.life = 1.0f;
		particle.velocity = object->GetComponentByTemplate<Player>()->GetPlayerVelocity() + vector2(random);
	}
	else if (m_type == ParticleType::MISSILE)
	{
		GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
		particle.color = Color4f(rColor, rColor, rColor, 1.0f);
		particle.position = object->GetTransform().GetTranslation() + offset;
		particle.life = 1.0f;
		particle.velocity = object->GetComponentByTemplate<Physics>()->GetVelocity() + vector2(random);
	}
	else if (m_type == ParticleType::WIN)
	{
		GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
		particle.color = Color4f(rColor, rColor, rColor, 1.0f);
		particle.position = object->GetTransform().GetTranslation() + offset;
		particle.life = 1.0f;
		particle.velocity = object->GetComponentByTemplate<Player>()->GetPlayerDirection() * 2 + vector2(0, random);
	}
}