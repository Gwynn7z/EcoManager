#include "EcoManagerGameModeBase.h"
#include "Manager.h"
#include "ManagerHUD.h"


AEcoManagerGameModeBase::AEcoManagerGameModeBase()
{
	DefaultPawnClass = AManager::StaticClass();
	HUDClass = AManagerHUD::StaticClass();
}
