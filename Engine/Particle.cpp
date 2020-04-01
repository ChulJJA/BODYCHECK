#include "Particle.h"
#include "StockShaders.hpp"
#include "Graphic.h"
#include "GL.hpp"

ParticleGenerator::ParticleGenerator(Object* obj, GLuint amount, const char* texture_path, ParticleType type)
{
	total_particles = amount;
	material.shader = &(SHADER::particles());

	const auto path = texture_path;
	m_type = type;

	if (!Can_Load_To_Texture(texture, path))
	{
		printf("Particle Texture Load Fail!?\n");
	}
	texture.SelectTextureForSlot(texture);
	material.textureUniforms["texture_to_sample"] = { &(texture) };

	Mesh square;
	square = MESH::create_box(30, { 255,255,255,255 });
	shape.InitializeWithMeshAndLayout(square, SHADER::particles_layout());

	for (GLuint i = 0; i < this->total_particles; ++i)
		this->particles.push_back(Particle());
}


void ParticleGenerator::Update(float dt, Object* object, GLuint newParticles, vector2 offset)
{
	if (object->GetComponentByTemplate<Player>() != nullptr)
	{
		switch (m_type)
		{
		case ParticleType::DASH:

			for (GLuint i = 0; i < newParticles; ++i)
			{
				int unusedParticle = this->firstUnusedParticle();
				this->respawnParticle(this->particles[unusedParticle], object, offset);
			}
			for (GLuint i = 0; i < this->total_particles; ++i)
			{
				Particle& p = this->particles[i];
				p.life -= dt * 5.0f;
				if (p.life > 0.0f)
				{
					p.position -= (p.velocity * dt);
					p.color.alpha -= dt;
				}
			}
			break;
		case ParticleType::COLLIDE:
			break;
		case ParticleType::DESTROY:
			break;
		default:
			break;
		}
	}
}

void ParticleGenerator::Draw(Object* obj)
{
	if (obj->GetComponentByTemplate<Player>() != nullptr)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		switch (m_type)
		{
		case ParticleType::DASH:
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
		case ParticleType::COLLIDE:
			break;
		case ParticleType::DESTROY:
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


GLuint lastUsedParticle = 0;
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
	printf("No dead particles\n");
	return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, Object* object, vector2 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
	particle.position = object->GetTransform().GetTranslation() + vector2(random) + offset;
	particle.color = Color4f(rColor, rColor, rColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = object->GetComponentByTemplate<Player>()->GetPlayerVelocity() * 0.5f;
}