#include "Globals.h"
#include "Scene.h"

class Loop
{
public:
    Loop();

    void Run();
    
private:

    void Init();

    void AI();

    void Score();

    void Collision();

    void Update();

    void Draw();

    Scene scene;

    float gameTimer;

    bool didPlayerScore = false;
    bool didOpponenetScore = false;
    
};