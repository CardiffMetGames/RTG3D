#pragma once
#include "GameObject.h"
class Model;

class ExampleGO :
    public GameObject
{
public:
    ExampleGO();
    ~ExampleGO();

    //load me from the file
    virtual void Load(ifstream& _file);

    //update _window allows for Keyboard access
    virtual void Tick(float _dt);

    //render this object
    virtual void PreRender();
    virtual void Render();

    virtual void Init(Scene* _scene);

protected:

    string m_ShaderName, m_TexName, m_ModelName;

    GLuint m_texture;
    Model* m_model;
};

