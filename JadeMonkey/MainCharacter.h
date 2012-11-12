#include "InputComponent.h"
#include "CameraComponent.h"
#include "GameEntity.h"

class MainCharacter : public GameEntity
{
public :
	MainCharacter(Game* game, InputComponent* input, CameraComponent* camera);
	int virtual Initialize(void) override;
	int virtual Update(long time) override;
private:
	InputComponent* _input;
	CameraComponent* _camera;
};