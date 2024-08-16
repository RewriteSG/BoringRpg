#include "EndingManager.h"
#include "GameManager.h"
#include "InteractionsManager.h"
void EndingManager::EndingUnlocked(TYPEOUTCOME ending)
{

}
void EndingManager::Start(void)
{
	ui = GameManager::getGM()->gameUI;

	//In living room:
	//If robber see player ->  player get killed
	//else
	//    (killer step on nail) ? increase time : enter the store room


	//In store room: 
	//if player inside -> player get killed
	
	//In toilet:
	//if player is there
	//		if player setup soup
	//			then killer get fall down -> player get killed
	//		if player setup soup + pan
	//			then killer get fall down -> knock down by the pan -> then get caught by police
	//		else nothing
	//			then player get killed
	//else if player not there
	//      if player setup soup
	//			then killer get fall down -> player get killed
	//		if player setup soup + pan
	//			then killer get fall down -> knock down by the pan -> then get caught by police
	//		else nothing
	//			then killer go another room

	//In Kitchen:
	//If player is there
	//    then player inside -> player get killed
	//else if player is not there
	
	Update();
}

void EndingManager::Update(void)
{
	while (!isEndingEnded)
	{
		// if(GameManager::getGM()->InteractionMgr.IsSleeping){
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Robber breaks in and snaps your neck hehe");
		EndingUnlocked(SleepingEnding);
		//}
		
		switch (typeOfEnding)
		{
		case 0:

			break;
		case 1:
			break;
		case 2:
			break;
		}
	}
}

void EndingManager::Exit()
{
}
