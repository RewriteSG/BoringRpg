#include "EndingManager.h"
#include "Application.h"
#include "GameManager.h"
#include "string"
#include "MainMenu.h"
#include "Windows.h"
#include "Endings.h"

void EndingManager::PlayLivingRoom(void)
{
	if (GameManager::getGM()->TimeSys.TimeLoop == 1)
	{
		dialogues.push_back("TIME:??? You heard the sound of the footstep outside of your main door. ");
		dialogues.push_back("TIME:??? There was a stranger tried to open the MAIN DOOR, then you looked at the clock. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " THOUGHT: who is that at this godly hour? ");

		*time += 5;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " BANG! ");

		*time += 2;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Surprised, you swiftly turned to the main door and saw a familiar face. ");

		*time += 1;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Before you could utter a word, the stranger quickly ran forwards you. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Raising his cruel blade, and straight to your chest. ");

		*time += 3;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You fell on the ground. Your breath and heartbeat was racing with the time. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Everything went silience but the sound of tickling clock. ");

		*time += 10;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Finally your vision gradually faded off... ");
		return;
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was trying to open the MAIN DOOR. ");

	if (GameManager::getGM()->InteractionsMgr.isBarricadeSetup) 
	{
		*time += 120;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As the door barricaded. This would take some time for the killer to break into the house. ");
	}
	else 
	{
		*time += 5;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer immediately broke into the house with ease. ");
	}

	if (isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering living room, and finally found you there. ");
		return;
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering living room, and found nothing. ");

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup && GameManager::getGM()->InteractionsMgr.soapLocation == killerCurrentScene)
	{
		*time += 60;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The serial killer had stepped on the soap and fell down. This would take some time for the killer to recover. ");
	}
}

void EndingManager::PlayStoreroom(void)
{
	*time += 10;

	if (isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering storeroom, and finally found you there. ");
		return;
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering storeroom, and found nothing. ");

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup && GameManager::getGM()->InteractionsMgr.soapLocation == killerCurrentScene)
	{
		*time += 60;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Ah yes! The serial killer had stepped on your soap and fell down. This would take some time for the killer to recover. ");
	}
}

void EndingManager::PlayToilet(void)
{
	*time += 10;

	if (isPlayerFound)
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering toilet, and finally found you in toilet. ");
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering toilet, and found nothing. ");

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup && GameManager::getGM()->InteractionsMgr.soapLocation == killerCurrentScene)
	{
		*time += 60;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Ah yes! The serial killer had stepped on your soap and fell down. This would take some time for the killer to recover. ");
	}
}

void EndingManager::PlayBedroom(void)
{
	*time += 10;

	if (isPlayerFound)
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering bedroom, and finally found you in bedroom. ");
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering bedroom, and found nothing. ");

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup && GameManager::getGM()->InteractionsMgr.soapLocation == killerCurrentScene)
	{
		*time += 60;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Ah yes! The serial killer had stepped on your soap and fell down. This would take some time for the killer to recover. ");
	}
}

void EndingManager::PlayKitChen(void)
{
	*time += 10;

	if (isPlayerFound)
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering kitchen, and finally found you in kitchen. ");
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering kitchen, and found nothing. ");

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup && GameManager::getGM()->InteractionsMgr.soapLocation == killerCurrentScene)
	{
		*time += 60;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Ah yes! The serial killer had stepped on your soap and fell down. This would take some time for the killer to recover. ");
	}
}

void EndingManager::PickWeaponOption(void)
{
	if (playerGotBothWeapon)
	{
		ContinueDialogue();
		ui->GetOptionUI()->AddOption(new std::string("Metal Pan"));
		ui->GetOptionUI()->AddOption(new std::string("Knife"));
		ui->GetOptionUI()->AddOption(new std::string("Hide"));

		int choosenItem = 0;
		if (!isPlayerFound)
			choosenItem = ui->PickDialogue(Vector2(0, 10), "THOUGHT: I guess the killer unable to see me. What should I do next? (use knife to kill him? or use metal pan to knock him down? or continue to hide)");
		else
			choosenItem = ui->PickDialogue(Vector2(0, 10), "THOUGHT: Shit! The killer found me in the " + killerCurrentScene + ". What should I do next ? (use knife to kill him? or use metal pan to knock him down?)");

		switch (choosenItem)
		{
		case 0:
			MetalPanEnding();
			GameManager::getGM()->InteractionsMgr.hasKnife = false;
			break;
		case 1:
			KnifeEnding();
			GameManager::getGM()->InteractionsMgr.hasMetalPan = false;
			break;
		case 2:
			HideAction();
		}
	}
}

void EndingManager::MetalPanEnding(void)
{
	if (!isPlayerFound)
	{
		if (!playerGotBothWeapon)
		{
			ContinueDialogue();
			ui->GetOptionUI()->AddOption(new string("Use Metal Pan"));
			ui->GetOptionUI()->AddOption(new string("Hide"));
			int chooseItem = ui->PickDialogue(Vector2(0, 10), "Since the killer did not see me. What should I do next? (use metal pan to knock him down? or continue to hide?)");

			if (chooseItem == 0)
				MetalPanAction();
			else
				HideAction();
		}
		else
			MetalPanAction();
	}
	else
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You charged forward insanely like a bear to try to knock down this serial killer with your metal pan. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the killer dodged it. ");
	}
}

void EndingManager::KnifeEnding(void)
{
	if (isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You charged forward insanely like a bear to try to slash this serial killer with your knife. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the killer dodged it. ");
	}
	else
	{
		isPoliceCame = GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops;
		if (!playerGotBothWeapon)
		{
			ContinueDialogue();
			ui->GetOptionUI()->AddOption(new string("Use Knife"));
			ui->GetOptionUI()->AddOption(new string("Hide"));
			int chooseItem = ui->PickDialogue(Vector2(0, 10), "Since the killer did not see me. What should I do next? (use knife to kill him? or continue to hide?)");

			if (chooseItem == 0)
				KnifeAction();
			else
				HideAction();
		}
		else
			KnifeAction();
	}
}

void EndingManager::MetalPanAction(void)
{
	std::string locationYouHid = (GameManager::getGM()->InteractionsMgr.isHidInCloset) ? "closet" : " toilet";
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " At the moment the killer was about to leave, you was gently opening " + locationYouHid + " door. ");

	*time += 5;
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " And slowly moving behind of the killer to give him a strike on his head. ");
	ContinueDialogue();

	ui->GetOptionUI()->AddOption(new std::string("Run"));
	ui->GetOptionUI()->AddOption(new std::string("Hide"));
	if (GameManager::getGM()->InteractionsMgr.hasDuctTape)
		ui->GetOptionUI()->AddOption(new std::string("Use Duct Tape"));

	int choosenItem = ui->PickDialogue(Vector2(0, 10), "I had successfully knocked him down this killer. What should I do next?");

	switch (choosenItem)
	{
	case 0:
		*time += 30;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As the blow from the metal pan was weak, the killer had recovered and stood up. ");

		*time += 10;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As you were running, the killer was still able to catch up to you.");
		isPlayerFound = true;
		break;
	case 1:
		*time += 30;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As the blow from the metal pan was weak, the killer had recovered and stood up. ");

		*time += 10;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As you were hiding, the killer was still able to find to you.");
		isPlayerFound = true;
		break;
	case 2:
		*time += 10;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As he was being knock out, you used your duct tape to tie him up. Then you was calmly waiting for police on the sofa. ");
		isWeaponUse = true;
		break;
	}
}

void EndingManager::KnifeAction(void)
{
	std::string locationYouHid = (GameManager::getGM()->InteractionsMgr.isHidInCloset) ? "closet" : " toilet";
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " At the moment the killer was about to leave, you was gently opening " + locationYouHid + " door. ");

	*time += 5;
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " And slowly moving behind the killer to give him a critical stab on his back. ");

	*time += 2;
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " In that moment, you was standing over your target, your blade stained with deep crimson of freshly spilled blood. ");

	*time += 60;
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " After waiting for a minute to calm youself down, you decided to the police for asssistance. ");
	isWeaponUse = true;
}

void EndingManager::HideAction(void)
{
	std::string locationYouHid = (GameManager::getGM()->InteractionsMgr.isHidInCloset) ? "in closet." : " in toilet.";
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You chose to remain quiet while hiding " + locationYouHid);
	hasWeapon = false;
}

void EndingManager::ContinueDialogue(void)
{
	int index = dialogueIndex;
	for (int i = dialogueIndex; i < dialogues.size(); ++i)
	{
		ui->PrintDialogue(Vector2(), dialogues[i]);
		index++;

		int yPos = -index;
		for (int j = 0; j < index; ++j)
		{
			if (j != 0)
				for (int ch = 0; ch < dialogues[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(j) - 1].length(); ++ch)
					ui->CreateText(" ", Vector2(ch, yPos));

			ui->CreateText(dialogues[j], Vector2(0, yPos));
			yPos++;
		}

		dialogueIndex++;
	}
}

EndingManager::EndingManager(void)
{
	ui = nullptr;
	killerCurrentScene = "";
	isPlayerFound = false;
	isPlayerGetKilled = false;
	isPlayerWithKiller = false;
	isWeaponUse = false;
	dialogueIndex = 0;
	time = nullptr;
	ui = nullptr;
	hasWeapon = false;
	isPoliceCame = false;
	playerGotBothWeapon = false;
	endingNum = 0;
}

void EndingManager::Start(void)
{
	Vector2 uiPos = Vector2(Application::numberOfColumns / 2 - 100, Application::numberOfRows / 2);
	ui = new UI(uiPos, 0, 150);
	ui->CreateOptionUI(Vector2(0, 10), false);

	killerCurrentScene = "";
	isPlayerFound = false;
	isPlayerGetKilled = false;
	isPlayerWithKiller = false;
	isWeaponUse = false;
	dialogueIndex = 0;
	endingNum = 0;

	hasWeapon = GameManager::getGM()->InteractionsMgr.hasKnife || GameManager::getGM()->InteractionsMgr.hasMetalPan;
	playerGotBothWeapon = GameManager::getGM()->InteractionsMgr.hasKnife && GameManager::getGM()->InteractionsMgr.hasMetalPan;
	time = &GameManager::getGM()->TimeSys.TimeTaken;
	Update();
}

void EndingManager::Update(void)
{
	system("CLS");

	if(!GameManager::getGM()->InteractionsMgr.isPlayerSucide && GameManager::getGM()->TimeSys.TimeLoop > 0)
	for (int i = 0; i < 5; ++i)
	{

		killerCurrentScene = SceneManager::GetSceneName(i);
		isPlayerWithKiller = GameManager::getGM()->whatScenePlayerIn == killerCurrentScene;

		isPoliceCame = GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops;
		isPlayerFound = isPlayerWithKiller && !GameManager::getGM()->InteractionsMgr.isPlayerHidden;

		switch (i)
		{
		case 0:
			PlayLivingRoom();
			break;
		case 1:
			PlayStoreroom();
			break;
		case 2:
			PlayToilet();
			break;
		case 3:
			PlayBedroom();
			break;
		case 4:
			PlayKitChen();
			break;
		}

		if (isPlayerWithKiller)
		{
			if (!playerGotBothWeapon)
			{
				if (GameManager::getGM()->InteractionsMgr.hasMetalPan && 
					(killerCurrentScene != SceneManager::GetSceneName(SceneManager::BEDROOM) 
					|| killerCurrentScene != SceneManager::GetSceneName(SceneManager::TOILET)))
					MetalPanEnding();

				if (GameManager::getGM()->InteractionsMgr.hasKnife)
					KnifeEnding();
			}
			else
				PickWeaponOption();
		}

		if ((GameManager::getGM()->InteractionsMgr.isPlayerHidden && isPlayerWithKiller) && !hasWeapon)
		{
			*time += 7;
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, he went back to check again, and finally found you. ");
			isPlayerFound = true;
		}

		isPoliceCame = GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops;

		if (isPoliceCame)
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Finally, the police arrived on time and provided you assistance. ");

		if (isPlayerFound || isWeaponUse || isPoliceCame)
			break;
	}

	if (GameManager::getGM()->TimeSys.TimeLoop == 0)
	{
		dialogues.push_back("TIME:??? You heard a noise outside of your house but you were too tired to bother it.   ");
		dialogues.push_back("TIME:??? So you chose to continue to sleep. ");
		dialogues.push_back("TIME:??? While you were enjoying your dream, you felt a sudden pain behind your back. ");
		dialogues.push_back("TIME:??? The pain was not only once but continuously, and until you fell into eternal dream... ");
	}

	if (GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops || (GameManager::getGM()->InteractionsMgr.hasDuctTape && GameManager::getGM()->InteractionsMgr.hasMetalPan))
	{
		dialogues.push_back("[BREAKING NEWS]: The serial killer was arrested by the police. A 25-year-old man successfully defended himself by attempting with well-preapred measures until police arrived. ");
		Endings::isunlocked[Endings::ARRESTED] = true;
		endingNum = 3;
	}
	else if (!isPlayerFound && GameManager::getGM()->InteractionsMgr.hasKnife && !GameManager::getGM()->InteractionsMgr.isPlayerSucide)
	{
		dialogues.push_back("[BREAKING NEWS]: The serial killer had been killed at BLK 243 Chicken Street in the " + killerCurrentScene + ". Suspect claimed that it was just self defence, but police still caught him for further investigation. ");
		Endings::isunlocked[Endings::KILLER_KILLED] = true;
		endingNum = 4;
	}
	else if (GameManager::getGM()->InteractionsMgr.isPlayerSucide)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You raised your blade, and stabbed yourself without any hesitation. ");
		dialogues.push_back("[BREAKING NEWS]: A 25-year-old man was found dead in " + GameManager::getGM()->whatScenePlayerIn + " at at BLK 243 Chicken Street. It was suspected to be a suicide case, but police was still on working for further investigation. ");
		Endings::isunlocked[Endings::SUICIDE] = true;
		endingNum = 2;
	}
	else if (GameManager::getGM()->InteractionsMgr.isPlayerSleeping)
	{
		dialogues.push_back("[BREAKING NEWS]: A 25-year-old man was found dead in " + GameManager::getGM()->whatScenePlayerIn + " at at BLK 243 Chicken Street. The dead body was discovered on his bed with multiple stab wounds on his back. ");
		Endings::isunlocked[Endings::SLEEPING] = true;
		endingNum = 5;
	}
	else
	{
		dialogues.push_back("[BREAKING NEWS]: A 25-year-old man was tragically found dead in the " + killerCurrentScene + " at BLK 243 Chicken Street yesterday around 12:" + to_string(*time / 60) + " AM, prompting police to launch a homicide investigation. If you find any suspicious, please contact us at 999. ");
		Endings::isunlocked[Endings::GOT_KILLED] = true;
		endingNum = 1;
	}

	ContinueDialogue();
	
	system("CLS");
	((Endings*)SceneManager::endingsPage)->ShowEnding(endingNum - 1);
	Sleep(1500);

	Exit();
}

void EndingManager::Exit()
{
	system("CLS");
	dialogues.clear();
	GameManager::getGM()->TimeSys.CountLoop(0);
	
	if (endingNum == 3 || endingNum == 4)
	{
		if(endingNum == 3)
			ui->PrintDialogue(Vector2(), "Congratulation, you got a best ending!");

		if (endingNum == 4)
			ui->PrintDialogue(Vector2(), "Unfortunately not a best ending, but at least you're survied!");

		ui->CreateText("Returning to main menu...");
		Sleep(1500);
		SceneManager::LoadScene(SceneManager::mainMenu);
	}
	else
		SceneManager::LoadScene("LivingRoomScene");
	SceneManager::prevScene = "";

	delete ui;
}
