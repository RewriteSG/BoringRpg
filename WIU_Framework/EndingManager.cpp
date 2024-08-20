#include "EndingManager.h"
#include "Application.h"
#include "GameManager.h"
#include "string"

void EndingManager::PlayLivingRoom(void)
{
	dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was trying to open the MAIN DOOR. ");
	if (GameManager::getGM()->InteractionsMgr.isBarricadeSetup) {
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

	if (GameManager::getGM()->InteractionsMgr.isSoapSetup)
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
}

void EndingManager::PlayToilet(void)
{
	*time += 10;

	if (isPlayerFound)
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering toilet, and finally found you in toilet. ");
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering toilet, and found nothing. ");

	if ((GameManager::getGM()->InteractionsMgr.isPlayerHidden && isPlayerWithKiller) && !hasWeapon)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, he went back to check again, and finally found you. ");
		isPlayerFound = true;
	}
}

void EndingManager::PlayBedroom(void)
{
	*time += 10;

	if (isPlayerFound)
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering bedroom, and finally found you in bedroom. ");
	else
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " The killer was entering bedroom, and found nothing. ");

	if ((GameManager::getGM()->InteractionsMgr.isPlayerHidden && isPlayerWithKiller) && !hasWeapon)
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
	if (playerGotBothWeapon)
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
					for (int ch = 0; ch < dialogues[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(j) - 1].length(); ++ch)
						ui->CreateText(" ", Vector2(ch, yPos));

				ui->CreateText(dialogues[j], Vector2(0, yPos));
				yPos++;
			}

			dialogueIndex++;
		}
		ui->CreateOptionUI(Vector2(0, 10), false);
		ui->GetOptionUI()->AddOption(new std::string("Metal Pan"));
		ui->GetOptionUI()->AddOption(new std::string("Knife"));

		int choosenItem = 0;
		if (!isPlayerFound)
			choosenItem = ui->PickDialogue(Vector2(0, 10), "THOUGHT: I guess the killer unable to see me. What should I do next? (use knife to kill him? or use metal pan to knock him down?)");
		else
			choosenItem = ui->PickDialogue(Vector2(0, 10), "THOUGHT: Shit! The killer found me in the " + killerCurrentScene + ". What should I do next ? (use knife to kill him? or use metal pan to knock him down?)");

		switch (choosenItem)
		{
		case 0:
			MentalPanEnding();
			GameManager::getGM()->InteractionsMgr.hasKnife = false;
			break;
		case 1:
			KnifeEnding();
			GameManager::getGM()->InteractionsMgr.hasMetalPan = false;
			break;
		}
	}
}

void EndingManager::MentalPanEnding(void)
{
	if (!isPlayerFound)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You were carefully moving behind of the killer to try to gave him a swing on the head. ");
		if (!GameManager::getGM()->InteractionsMgr.hasDuctTape)
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

			ui->CreateOptionUI(Vector2(0, 10), false);
			ui->GetOptionUI()->AddOption(new std::string("Run"));
			ui->GetOptionUI()->AddOption(new std::string("Hide"));
			int choosenItem = ui->PickDialogue(Vector2(0, 10), "I had successfully knocked down this killer. What should I do next?");
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As the blow from the metal pan was weak, the killer had recovered and stood up. ");
			switch (choosenItem)
			{
			case 0:
				dialogues.push_back(TimeSystem::GetTimeinString(*time) + " After witnessed that, you were so afraid and quickly ran for your life.");
				dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the serial killer was still able to catch up to you.");
				break;
			case 1:
				dialogues.push_back(TimeSystem::GetTimeinString(*time) + " After witnessed that, you were so afraid and hid away from the killer.");
				dialogues.push_back(TimeSystem::GetTimeinString(*time) + " However, the serial killer was still able to find to you.");
				break;
			}
			isPlayerFound = true;
		}
		else
		{
			*time += 30;
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " As he was being knock out, you used your duct tape to tie him up. Then you was calmly waiting for police on the sofa. ");
			isWeaponUse = true;
		}
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
		if (!isPoliceCame)
		{
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You were slowly moving behind the killer, and gave him a critical stab on his back. ");
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " In that moment, you was standing over your target, your blade stained with deep crimson of freshly spilled blood. ");

			*time += 60;
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " After waiting for a minute to calm youself down, you decided to the police for asssistance. ");
			isWeaponUse = true;
		}
	}
}

EndingManager::EndingManager(void)
{
	endingNum = 0;
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
}

void EndingManager::Start(void)
{
	ui = nullptr;
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
	Vector2 uiPos = Vector2(Application::numberOfColumns / 2 - 100, Application::numberOfRows / 2);
	ui = new UI(uiPos, 0, 150);

	for (int i = 0; i < 5 && !GameManager::getGM()->InteractionsMgr.isPlayerSucide; ++i)
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

				if (GameManager::getGM()->InteractionsMgr.hasMetalPan)
					MentalPanEnding();

				if (GameManager::getGM()->InteractionsMgr.hasKnife)
					KnifeEnding();
			}
			else
				PickWeaponOption();
		}

		isPoliceCame = GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops;

		if (isPoliceCame)
			dialogues.push_back(TimeSystem::GetTimeinString(*time) + " Fortunately, the police arrived on time and provided you assistance. ");

		if (isPlayerFound || isWeaponUse || isPoliceCame)
			break;
	}

	if (GameManager::getGM()->InteractionsMgr.hasCalledTheCops && GameManager::getGM()->TimeSys.TimeTaken >= GameManager::getGM()->TimeSys.TimeLimitForCops && !hasWeapon)
	{
		dialogues.push_back("[BREAKING NEWS]: The serial killer was arrested by the police. A 25-year-old man successfully defended himself by attempting with well-preapred measures until police arrived. ");
		endingNum = 2;
	}
	else if (!isPlayerFound && GameManager::getGM()->InteractionsMgr.hasKnife && !GameManager::getGM()->InteractionsMgr.isPlayerSucide)
	{
		dialogues.push_back("[BREAKING NEWS]: The serial killer had been killed at BLK 243 Chicken Street in the " + killerCurrentScene + ". Suspect claimed that it was just self defence, but police still caught him for further investigation. ");
		endingNum = 3;
	}
	else if (GameManager::getGM()->InteractionsMgr.isPlayerSucide)
	{
		dialogues.push_back(TimeSystem::GetTimeinString(*time) + " You raised your blade, and stabbed yourself without any hesitation. ");
		dialogues.push_back("[BREAKING NEWS]: A 25-year-old man was found dead in " + GameManager::getGM()->whatScenePlayerIn + " at at BLK 243 Chicken Street. It was suspected to be a suicide case, but police was still on working for further investigation. ");
		endingNum = 4;
	}
	else if (GameManager::getGM()->InteractionsMgr.isPlayerSleeping)
	{
		dialogues.push_back("[BREAKING NEWS]: A 25-year-old man was found dead in " + GameManager::getGM()->whatScenePlayerIn + " at at BLK 243 Chicken Street. The dead body was discovered on his bed with multiple stab wounds on his back. ");
		endingNum = 6;
	}
	else
	{
		dialogues.push_back("[BREAKING NEWS]: A 25-year-old man was tragically found dead in the " + killerCurrentScene + " at BLK 243 Chicken Street yesterday around 12:" + to_string(*time / 60) + " AM, prompting police to launch a homicide investigation. If you find any suspicious, please contact us at 999. ");
		endingNum = 1;
	}

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
	}

	Exit();
}

void EndingManager::Exit()
{
	dialogues.clear();
	GameManager::getGM()->TimeSys.CountLoop(0);
	SceneManager::prevScene = "";
	SceneManager::LoadScene("LivingRoomScene");
}

int EndingManager::EndingUnlock(void) const
{
	return endingNum;
}
