#include "ExampleGO.h"
#include "AIModel.h"
#include "stringHelp.h"
#include "game.h"
#include "Shader.h"
#include "Texture.h"

ExampleGO::ExampleGO()
{
}

ExampleGO::~ExampleGO()
{
}

void ExampleGO::Load(ifstream& _file)
{
	GameObject::Load(_file);
	StringHelp::String(_file, "MODEL", m_ModelName);
	StringHelp::String(_file, "TEXTURE", m_TexName);
	StringHelp::String(_file, "SHADER", m_ShaderName);

}

void ExampleGO::Tick(float _dt)
{
	GameObject::Tick(_dt);
}

void ExampleGO::PreRender()
{
	GameObject::PreRender();

	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void ExampleGO::Render()
{
	m_model->Render();
}

void ExampleGO::Init(Game* _game)
{
	m_ShaderProg = _game->GetShader(m_ShaderName)->GetProg();
	m_texture = _game->GetTexture(m_TexName)->GetTexID();
	m_model = _game->GetModel(m_ModelName);
}
