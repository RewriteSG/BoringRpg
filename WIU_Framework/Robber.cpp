#include "Robber.h"
#include "RobberSprite.h"
#include "RobberDownSprite.h"
#include "TimeSystem.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "Application.h"
#include <iostream>
#include "RobberDownSprite.h"
//#include <chrono>
//#include <thread>





Robber* Robber::robberInstance = nullptr;

Robber::Robber()
{
	Start();
    robberInstance = this;
}
Robber::Robber(Vector2 toPos)
{
	Start();
	*GetPosition() = toPos;
	//GetPosition() = toPos;

}
void Robber::Start()
{
   
    GetPosition()->SetXandY(3, 3);
    if (IsRobberDead == false) {
        SetSprite(new RobberSprite());

    }
    else if (IsRobberDead==true) {
        SetSprite(new RobberDownSprite());
    }
 
  
}
void Robber::Update()
{
   // if (IsRobberDead && !dynamic_cast<RobberDownSprite*>(GetSprite())) {

        //SetSprite(new RobberDownSprite());
       // GameManager::getGM()->robberDown = true;
   // }
    //else if(!IsRobberDead)
        if (IsRobberDead == false) {
            MoveTowardsPlayer(*GameManager::getGM()->player);
        }
    
    
 
	/*switch (steps)
	{
	case 0:
	
		*GetPosition() = Vector2(7, 7);
		break;
	
	steps++;*/
}
void Robber::Collided(GameObject* collision)
{
   
	//HealingGlobe* healGlobe = dynamic_cast<HealingGlobe*>(collision);
	//if (healGlobe) 
	//{
	//	ObjectManager::getObjectManager()->DestroyObject(collision);
	//	SetHealth(GetHealth() + healGlobe->GetHeal());
	//	*GetPosition() = *collision->GetPosition();
	//}
	//Weapon* wpn = dynamic_cast<Weapon*>(collision);
	//if (wpn)
	//{
	//	collision->SetActive(false);
	//	SetAttackDamage(GetAttackDamage() + wpn->GetDamageIncrease());
	//	SetWeaponHeld(wpn);
	//	*GetPosition() = *collision->GetPosition();
	//}
}

void Robber::OnDestroyed()
{
     
}

    void Robber::MoveTowardsPlayer(Player & player)
    {

        if (IsRobberDead == false) {
         /*   using namespace std::this_thread;
            using namespace std::chrono;
            srand(static_cast<unsigned int>(time(0)));*/

            Vector2 playerPos = player.GetPosition(true);


            Vector2 RobberDirection;

            //sleep_for(nanoseconds(10));
          //   // sleep_until(system_clock::now() + seconds(1));
            


            int distX = position.GetX() - playerPos.GetX();
            int distY = position.GetY() - playerPos.GetY();
            if (distX> 1) {
                RobberDirection.SetXandY(-1, 0);
                GameManager::getGM()->TimeSys.increaseRobberTime(20);
            }
            else if (distX < -1) {
                RobberDirection.SetXandY(1, 0);
                GameManager::getGM()->TimeSys.increaseRobberTime(20);
            }
            else if (distY > 1) {
                RobberDirection.SetXandY(RobberDirection.GetX(), -1);
                GameManager::getGM()->TimeSys.increaseRobberTime(20);

            }
            else if (distY < -1) {
                RobberDirection.SetXandY(RobberDirection.GetX(), 1);
                GameManager::getGM()->TimeSys.increaseRobberTime(20);
            }
              
            else {
                RobberDirection.SetXandY(0, 0);  //dont move

            }

            // Update robber's position in respect to direction
            position += RobberDirection;

        }
    }
