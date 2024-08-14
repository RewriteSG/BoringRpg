#include "Robber.h"
#include "RobberSprite.h"
#include "TimeSystem.h"
#include "GameManager.h"
#include <chrono>
#include <thread>
#include <iostream>
Robber::Robber()
{
	Start();
    //robberInstance = this;
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
	SetSprite(new RobberSprite()); 
}
void Robber::Update()
{

    MoveTowardsPlayer(*GameManager::getGM()->player);
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
void Robber::MoveTowardsPlayer(Player& player) 
{
  

    //using namespace std::this_thread;
    //using namespace std::chrono;
    //srand(static_cast<unsigned int>(time(0)));



    Vector2 playerPos = player.GetPosition(true);
    Vector2 RobberDirection;

    if (position.GetX() < playerPos.GetX()) {
      RobberDirection.SetXandY(1, 0);  //move right
      //GameManager::getGM()->TimeSys.increaseRobberTime(20);
     /* sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));*/
    }
    else if (position.GetX() > playerPos.GetX()) {
      RobberDirection.SetXandY(-1, 0); //move left
      //GameManager::getGM()->TimeSys.increaseRobberTime(20);
    /*  sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));*/
    }
    else {
      RobberDirection.SetXandY(0, 0);  //dont move
      
    }

    if (position.GetY() < playerPos.GetY()) {
      RobberDirection.SetXandY(RobberDirection.GetX(), 1);  //move down
      //GameManager::getGM()->TimeSys.increaseRobberTime(20);
     /* sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));*/
    }
    else if (position.GetY() > playerPos.GetY()) {
      RobberDirection.SetXandY(RobberDirection.GetX(), -1); //move up
      //GameManager::getGM()->TimeSys.increaseRobberTime(20);
     /* sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));*/
    }

    // Update robber's position in respect to direction
    position += RobberDirection;

  
}