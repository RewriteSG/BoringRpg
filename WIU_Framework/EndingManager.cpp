#include "EndingManager.h"
#include "Application.h"
#include "GameManager.h"
#include "string"

void EndingManager::PlayLivingRoom(void)
{
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As the door barricaded. This would take some time for the killer to broke into the house. ");

	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was trying to open the MAIN DOOR. ");
	if (GameManager::getGM()->InteractionsMgr.isBarricadeSetup) {
		*time += 60;
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As the door barricaded. This would take some time for the killer to broke into the house. ");
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

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup)
	{
		time += 120;
		dialogues.push_back("The serial killer had stepped on the soap and fell down. This would take some time for the killer to recover. ");
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
}

void EndingManager::PlayToilet(void)
{
	*time += 10;

	if (isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering toilet, and finally found you in toilet. ");
		return;
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering toilet, and found nothing. ");

	PickWeaponOption();

	if (GameManager::getGM()->InteractionsMgr.isPlayerHidden && !(GameManager::GameManager::getGM()->InteractionsMgr.hasKnife || GameManager::GameManager::getGM()->InteractionsMgr.hasMetalPan) && !isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, he went back to check again, and finally found you. ");
		isPlayerFound = true;
	}
}

void EndingManager::PlayBedroom(void)
{
	*time += 10;

	if (isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering bedroom, and finally found you in bedroom. ");
		return;
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering bedroom, and found nothing. ");

	PickWeaponOption();

	if (GameManager::getGM()->InteractionsMgr.isPlayerHidden && !(GameManager::GameManager::getGM()->InteractionsMgr.hasKnife || GameManager::GameManager::getGM()->InteractionsMgr.hasMetalPan) && !isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, he went back to check again, and finally found you. ");
		isPlayerFound = true;
	}
}

void EndingManager::PlayKitChen(void)
{
	*time += 10;

	if (isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering kitchen, and finally found you in kitchen. ");
		return;
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering kitchen, and found nothing. ");
}

void EndingManager::PickWeaponOption(void)
{
	if (GameManager::getGM()->InteractionsMgr.hasMetalPan && GameManager::getGM()->InteractionsMgr.hasKnife && !isPlayerFound)
	{
		int index = 0;
		for (std::string text : dialogues)
		{
			ui->PrintDialogue(Vector2(), text);
			index++;

			int yPos = -index;
			for (int j = 0; j < index; ++j)
			{
				if (j != 0)
					for (int ch = 0; ch < dialogues[j - 1].length(); ++ch)
						ui->CreateText(" ", Vector2(ch, yPos));

				ui->CreateText(dialogues[j], Vector2(0, yPos));
				yPos++;
			}

			dialogueIndex++;
		}

		ui->CreateOptionUI(Vector2(0, 10), false);
		ui->GetOptionUI()->AddOption(new std::string("Metal Pan"));
		ui->GetOptionUI()->AddOption(new std::string("Knife"));
		int choosenItem = ui->PickDialogue(Vector2(0, 10), "THOUGHT: I think the killer unable to find me. What should I do next? (use knife to kill him? or use metal pan to knock him down?)");
		switch (choosenItem)
		{
		case 0:
			MentalPanEnding();
			GameManager::getGM()->InteractionsMgr.hasKnife = false;
			isPlayerFound = true;
			break;
		case 1:
			GameManager::getGM()->InteractionsMgr.hasMetalPan = false;
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You was standing over your target, and in that moment your blade stained with deep crimson of freshly spilled blood. ");
			isWeaponUse = true;
			break;
		}
	}

}

void EndingManager::MentalPanEnding(void)
{
	if (!GameManager::getGM()->InteractionsMgr.hasDuctTape)
	{
		ui->CreateOptionUI(Vector2(0, 10), false);
		ui->GetOptionUI()->AddOption(new std::string("Run"));
		ui->GetOptionUI()->AddOption(new std::string("Hide"));
		int choosenItem = ui->PickDialogue(Vector2(0, 10), "I had successfully knocked the killer. What should I do next?");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " But the blow from the metal pan is weak, the killer has recovered and stood up");
		switch (choosenItem)
		{
		case 0:
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Seeing this, you are afraid and ran for your life.");
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the serial killer was still able to catch up to you.");
			break;

		case 1:
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Seeing this, you are afraid and hide away from the killer.");
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the serial killer was still able to find to you.");
			break;
		}
	}
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You used your duct tape to tide him up. Then you was waiting for police on the sofa. ");
}

void EndingManager::Start(void)
{
	//GameManager::getGM()->InteractionsMgr.hasKnife = true;
	GameManager::getGM()->InteractionsMgr.hasMetalPan = true;
	//GameManager::getGM()->InteractionsMgr.isPlayerHidden = true;
	GameManager::getGM()->InteractionsMgr.hasDuctTape = true;

	ui = nullptr;
	killerCurrentScene = "";
	isPlayerFound = false;
	isPlayerGetKilled = false;
	isPlayerWithKiller = false;
	isWeaponUse = false;
	dialogueIndex = 0;
	playerGotBothWeapon = GameManager::getGM()->InteractionsMgr.hasKnife && GameManager::getGM()->InteractionsMgr.hasMetalPan;

	time = &GameManager::getGM()->TimeSys.TimeTaken;

	Update();
}

void EndingManager::Update(void)
{
	system("CLS");
	Vector2 uiPos = Vector2(Application::numberOfColumns / 2 - 100, Application::numberOfRows / 2);
	ui = new UI(uiPos, 0, 200);

	for (int i = 0; i < 5; ++i)
	{

		killerCurrentScene = SceneManager::GetSceneName(i);
		isPlayerWithKiller = GameManager::getGM()->whatScenePlayerIn == killerCurrentScene;

		if (isPlayerWithKiller && !GameManager::getGM()->InteractionsMgr.isPlayerHidden)
			isPlayerFound = true;

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

		if (isPlayerFound || isWeaponUse)
			break;
	}

	if (GameManager::getGM()->InteractionsMgr.hasMetalPan && !playerGotBothWeapon && !isPlayerFound)
	{
		int index = 0;
		for (std::string text : dialogues)
		{
			ui->PrintDialogue(Vector2(), text);
			index++;

			int yPos = -index;
			for (int j = 0; j < index; ++j)
			{
				if (j != 0)
					for (int ch = 0; ch < dialogues[j - 1].length(); ++ch)
						ui->CreateText(" ", Vector2(ch, yPos));

				ui->CreateText(dialogues[j], Vector2(0, yPos));
				yPos++;
			}

			dialogueIndex++;
		}

		MentalPanEnding();
	}

	if (GameManager::getGM()->InteractionsMgr.hasMetalPan && !playerGotBothWeapon && isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You charged forward insanely to try to knock this serial killer with your metal pan. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the killer dodged it. ");
	}

	if (GameManager::getGM()->InteractionsMgr.hasKnife && !playerGotBothWeapon && isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You charged forward insanely to try to slash this serial killer with your knife. ");
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the killer dodged it. ");
	}

	if ((isPlayerFound && !GameManager::getGM()->InteractionsMgr.hasCalledTheCops)
		|| (GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken < GameManager::getGM()->TimeSys.TimeLimitForCops))
		dialogues.push_back("[BREAKING NEWS]: A 25-years-old man was tragically found dead at BLK 243 Kranji Street yesterday around 12:" + to_string(*time / 60) + " AM, prompting police to launch a homicide investigation. If you found any suspicious, please contact us at 999. ");
	else if (GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops)
		dialogues.push_back("[BREAKING NEWS]: The serial killer was arrested by the police. A 25-years-old man successfully defended himself by attempting with well-preapred measures until police arrived");
	else if(!isPlayerFound && GameManager::getGM()->InteractionsMgr.hasMetalPan && GameManager::getGM()->InteractionsMgr.hasDuctTape)
		dialogues.push_back("[BREAKING NEWS]: The serial killer was captured by a 25-years-old man. The police immediately arrived to the crime scene to arrest that serial killer. ");
	else if (!isPlayerFound && GameManager::getGM()->InteractionsMgr.hasKnife)
		dialogues.push_back("[BREAKING NEWS]: The serial killer had been killed at BLK 243 Kranji Street in " + killerCurrentScene + ". Suspect claimed that it was just self defence, but police still caught him for further investigation. ");

	int index = dialogueIndex;
	for (int i = dialogueIndex; i < dialogues.size(); ++i)
	{
		ui->PrintDialogue(Vector2(), dialogues[i]);
		index++;

		int yPos = -index;
		for (int j = 0; j < index; ++j)
		{
			if (j != 0)
				for (int ch = 0; ch < dialogues[j - 1].length(); ++ch)
					ui->CreateText(" ", Vector2(ch, yPos));

			ui->CreateText(dialogues[j], Vector2(0, yPos));
			yPos++;
		}
	}
}

void EndingManager::Exit()
{
	dialogues.clear();
	GameManager::getGM()->TimeSys.TimeLoop++;
	SceneManager::LoadScene("LivingRoomScene");

}
