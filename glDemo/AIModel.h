#pragma once
#include "Model.h"
class AIMesh;

class AIModel :
    public Model
{
public:
    AIModel();
    ~AIModel();

    void Load(ifstream& _file);

protected:
    AIMesh* m_AImesh;
};

