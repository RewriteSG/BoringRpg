#include "TimeSystem.h"
#include "string"
#include "GameManager.h"
#include "InventoryManager.h"
#include "InteractionsManager.h"
#include "UI.h"
#include "windows.h"
#include "Scene.h"
TimeSystem::TimeSystem()
{
	TimeLoop = 0;
	lastTimeChecked = 0;
	TimeTaken = 0;
	RobberTime = 300;
	TimeLimitForCops = 480;
	increasedTime = false;
	lastTimeChecked = 0;
}

void TimeSystem::CountLoop(void)
{
	TimeLoop++;
	AnimateClockRewinding();
	TimeTaken = 0;
	lastTimeChecked = 0;
	GameManager::getGM()->LoopStarted = false;
	GameManager::getGM()->inventory = InventoryManager();
	GameManager::getGM()->InteractionsMgr = InteractionsManager();
	increasedTime = false;
}
void TimeSystem::CountLoop( bool)
{
	TimeLoop++;
	TimeTaken = 0;
	lastTimeChecked = 0;
	GameManager::getGM()->LoopStarted = false;
	GameManager::getGM()->inventory = InventoryManager();
	GameManager::getGM()->InteractionsMgr = InteractionsManager();
	increasedTime = false;
}
void TimeSystem::increaseTimeTaken(int time)
{

	UI* ui = GameManager::getGM()->gameUI;
	TimeTaken += time;
	if (!increasedTime) {

		InteractionsManager::LastTimeChecked = false;
		GameManager::getGM()->objManager.displayObjectives();
	}
	increasedTime = true;
	if (TimeLoop > 1)
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You took " + std::to_string(time) + " seconds to do this.");
}
void TimeSystem::increaseTimeTaken(int time, bool)
{
	TimeTaken += time;
	if (increasedTime)
		InteractionsManager::LastTimeChecked = false;
}
void TimeSystem::checkedTime(int time)
{
	InteractionsManager::LastTimeChecked = true;
	lastTimeChecked = TimeTaken;
	increasedTime = false;
}
void TimeSystem::increaseRobberTime(int time) {
	RobberTime += time;
}

int TimeSystem::GetLastTimeChecked() const
{
	return lastTimeChecked;
}

std::string TimeSystem::GetTimeinString(int time)
{
	int minute = time / 60;
	int second = time % 60;
	std::string toReturn;
	toReturn += "TIME: 00:";
	std::string minuteStr = ((minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute)) + ":";
	std::string secondStr = (second < 10) ? "0" + std::to_string(second) : std::to_string(second);

	toReturn += minuteStr + secondStr; 
	return toReturn;
}

void TimeSystem::AnimateClockRewinding()
{
	const char* ClockImages[4] = {R"(@@&####################################################################&###################################&@@
@G:                                        .^^^^^^^^^^^^^^^^^^^^^^^^^^                                     :G@
@G:                                 ~7!!!!!5&@&&&&&&&&&&&&&&&&&&&&&&@#J!!!!!!^                             :G@
@G:                           ~JJ??YB@&&&&&BP5PPPGB#######BPPPPPPPPP5P#&&&&@@#J??^                         :G@
@G:                       ~Y55G&&#&#P5PPPG#&&&&&&@@GYYYYYYP#&&&&&&&&##GPPPPGB##@@#Y^                       :G@
@G:                     ~P&@@BGPPPPG#@&@@BJ?JJJJJJ?~^^^^^^~?JJJJJJ?J#@@&@#GPPPPGBB#BP~                     :G@
@G:                   ~G@@&GPPPP#@@#J!777!^^^^^^^^^^~~~~~~^^^^^^^^^^!777!J#@@#PPPPPGB#G~                   :G@
@G:                   7&@GPPB@@&@&J~^^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^~J&@&@@#PPPGG&B~                 :G@
@G:                 !#&GPPPG&@Y^^~^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~^^J&@@#GPPPG@B^               :G@
@G:               ^#@GPPPG#@@B?^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~^^J#@@#GPG&B7.              :G@
@G:             .^?B#GPPB@&G?^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~~~~~~~~~~~~^^?B@@BP5G@B^             :G@
@G:             :#@GPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~~~~~~^^?57^^~~~~~~~~~~~~^^?PBBGG@B:             :G@
@G:           .75BBGPPG#GY7~^~~~~~~~~~~~~~~~~~~~~~~~^^!5Y!^^~~^^?PPY7^^~~~~~~~~~~~~~^:~G@BPBB57.           :G@
@G:           :G@BPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^7&#!^^^^?G@@Y:^~~~~~~~~~~~~~~~^^~G@BPPB@G:           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7&#!^^^^5@G7~^^~~~~~~~~~~~~~~~^^~G@BPPB@G.           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7&#!:^J&P!^^^~~~~~~~~~~~~~~~~~^^~G@BPPPPB&5.         :G@
@G:           ^G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7##7?&@&5^^~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@@#5~^~~~~~~~~~~~~~~~~~~~~~^^~5&@@GPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^!PBBY~^^~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@P^:~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@&P?~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~JPBBGPPB@P.         :G@
@G:         .P@BPPPPPPGG&@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPG#@@P.         :G@
@G:         .P@BPPPPPPPP#@P^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~5#BGPPPB@B!.          :G@
@G:           ^G@BPPPPPP#@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5&@@BPPG&@@P.           :G@
@G:           .P&BPPPPPPPP#@Y^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5@@@BPPPPB@B^             :G@
@G:             :B@GPPPPPP#&P7~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~!P@@&BPPPPG@@&5:             :G@
@G:             ^B@#GPPPPPPP&@G???~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~?J?5&@&BPPPPPB#BY:               :G@
@G:             .7G@@#GPPPPPB##&@@PYYY5?^:^^^^^^^^^^^^^^^^^^^^^^^^:^?55YY5#&&#PPPPPGB##GJ:                 :G@
@G:                !5@@&&#BPPPPPGB#####BPPPPPPPPPPPPPPPPPPPPPPPPPPPPB####BP5PPPPPB&@@G7.                   :G@
@G:                 .~!!5@@&&&@&&#GPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBGPPPPG#&&&&@@P!!!.                     :G@
@G:                      ^^^^^:~G@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@B~:^^^.                         :G@
@@&#############################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######&#######################&@@
                          

)",R"(@@&####################################################################&###################################&@@
@G:                                        .^^^^^^^^^^^^^^^^^^^^^^^^^^                                     :G@
@G:                                 ~7!!!!!5&@&&&&&&&&&&&&&&&&&&&&&&@#J!!!!!!^                             :G@
@G:                           ~JJ??YB@&&&&&BP5PPPGB#######BPPPPPPPPP5P#&&&&@@#J??^                         :G@
@G:                       ~Y55G&&#&#P5PP5G#&&&&&&@@GYYYYYYP#&&&&&&&&##GPPPPGB##@@#Y^                       :G@
@G:                     ~P&@@BGPPPPG#@&@@GJ?JJJJJJ?~^^^^^^~?JJJJJJ?J#@@&&#GPPPPGBB#BP~                     :G@
@G:                   ~G@@&GPPPP#@@#J!777!^^^^^^^^^^~~~~~~^^^^^^^^^^!777!J#@@#PPPPPGB#G~                   :G@
@G:                   7&@GPPB@@&@&J~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^~J&@&@@#PPPGG&B~                 :G@
@G:                 !#&GPPPG&@Y^^~^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~~~~~~^^^~^^J&@@#GPPPG@B^               :G@
@G:               ^#@GPPPG#@@B?^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^!7!^^~~~~~~~~~~^^J#@@#GPG&B7.              :G@
@G:             .^?B#GPPB@&G?^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~:^P@5^^~~~~~~~~~~~~^^?B@@BP5G@B^             :G@
@G:             :#@GPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~~^^!YPP?^^~~~~~~~~~~~~~~^^?PBBGG@B:             :G@
@G:           .75BBGPPG#GY7~^~~~~~~~~~~~~~~~~~~~~~~~^^!5Y!^^75&@5^:~~~~~~~~~~~~~~~~~^:~G@BPBB57.           :G@
@G:           :G@BPPPPB@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^7&#!::J@#?!^^~~~~~~~~~~~~~~~~~~^~G@BPPB@G:           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7&#!7B@@P^^~~~~~~~~~~~~~~~~~~~~^~G@BPPB@G.           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7##!?@B!^~^~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB&5.         :G@
@G:           ^G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@@@P~^~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G~:^~~~~~~~~~~~~~~~~~~~~~~~^~5&@@GPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^!PBB5~^^~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@P^:~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@&P?~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~JPBBGPPB@P.         :G@
@G:         .P@BPPPPPPGG&@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPG#@@P.         :G@
@G:         .P@BPPPPPPPP#@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~5#BGPPPB@B!.          :G@
@G:           ^G@BPPPPPP#@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~5&@@BPPG&@@P.           :G@
@G:           .P&BPPPPPPPP#@Y^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5@@@BPPPPB@B^             :G@
@G:             :B@GPPPPPP#&P7~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~!P@@&BPPPPG@@&5:             :G@
@G:             ^B@#GPPPPPPP&@G???~^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~?J?5&@&BPPPPPB#BY:               :G@
@G:             .7G@@#GPPPPPB##&@@PYYY5?^:^^^^^^^^^^^^^^^^^^^^^^^^:^?55YY5#&&#PPPPPGB##GJ:                 :G@
@G:                !5@@&&#BPPPPPGB#####BPPPPPPPPPPPPPPPPPPPPPPPPPPPPB####BP5PPPPPB&@@G7.                   :G@
@G:                 .~!!5@@&&&@&&#GPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBGPPPPG#&&&&@@P!!!.                     :G@
@G:                      ^^^^^:~G@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@B~:^^^.                         :G@
@@&#############################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######&#######################&@@

                                
)", R"(@@&####################################################################&###################################&@@
@G:                                        .^^^^^^^^^^^^^^^^^^^^^^^^^^                                     :G@
@G:                                 ~7!!!!!5&@&&&&&&&&&&&&&&&&&&&&&&@#J!!!!!!^                             :G@
@G:                           ~JJ??YB@&&&&&BP5PPPGB#######BPPPPPPPPP5P#&&&&@@#J??^                         :G@
@G:                       ~Y55G&&#&#P5PPPG#&&&&&&@@GYYYYYYP#&&&&&&&&##GPPPPGB##@@#Y^                       :G@
@G:                     ~P&@@BGPPPPG#@&@@BJ?JJJJJJ?~^^^^^^~?JJJJJJ?J#@@&@#GPPPPGBB#BP~                     :G@
@G:                   ~G@@&GPPPP#@@#J!777!^^^^^^^^^^~~~~~~^^^^^^^^^^!777!J#@@#PPPPPGB#G~                   :G@
@G:                   7&@GPPB@@&@&J~^^^^^^^~~~~~~~~~~~~~~~^^^~~~~~~^^^^^^^~J&@&@@#PPPGG&B~                 :G@
@G:                 !#&GPPPG&@Y^^~^^^~~~~~~~~~~~~~~~~~~~^^~!~~^~~~~~~~~~~^^^~^^J&@@#GPPPG@B^               :G@
@G:               ^#@GPPPG#@@B?^^^~~~~~~~~~~~~~~~~~~~~~~^^J@G~^~~~~~~~~~~~~~^~~^^J#@@#GPG&B7.              :G@
@G:             .^?B#GPPB@&G?^^~~~~~~~~~~~~~~~~~~~~~~~~~^^J@G~^~~~~~~~~~~~~~~~~~~^^?B@@BP5G@B^             :G@
@G:             :#@GPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^^^J@G~^~~~~~~~~~~~~~~~~~~~~^^?PBBGG@B:             :G@
@G:           .75BBGPPG#GY7~^~~~~~~~~~~~~~~~~~~~~~~~^^!5Y^?@B~^~~~~~~~~~~~~~~~~~~~~~^:~G@BPBB57.           :G@
@G:           :G@BPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^7&@BPJ7~^~~~~~~~~~~~~~~~~~~~~~^^~G@BPPB@G:           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G~:^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPB@G.           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB&5.         :G@
@G:           ^G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@&5~^^~~~~~~~~~~~~~~~~~~~~~~^^~5&@@GPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^!PP~:^~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@P^:~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@&P?~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~JPBBGPPB@P.         :G@
@G:         .P@BPPPPPPGG&@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPG#@@P.         :G@
@G:         .P@BPPPPPPPP#@P^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~5#BGPPPB@B!.          :G@
@G:           ^G@BPPPPPP#@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5&@@BPPG&@@P.           :G@
@G:           .P&BPPPPPPPP#@Y^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5@@@BPPPPB@B^             :G@
@G:             :B@GPPPPPP#&P7~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~!P@@&BPPPPG@@&5:             :G@
@G:             ^B@#GPPPPPPP&@G???~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~?J?5&@&BPPPPPB#BY:               :G@
@G:             .7G@@#GPPPPPB##&@@PYYY5?^:^^^^^^^^^^^^^^^^^^^^^^^^:^?55YY5#&&#PPPPPGB##GJ:                 :G@
@G:                !5@@&&#BPPPPPGB#####BPPPPPPPPPPPPPPPPPPPPPPPPPPPPB####BP5PPPPPB&@@G7.                   :G@
@G:                 .~!!5@@&&&@&&#GPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBGPPPPG#&&&&@@P!!!.                     :G@
@G:                      ^^^^^:~G@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@B~:^^^.                         :G@
@@&#############################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######&#######################&@@
                          


)", R"(@@&####################################################################&###################################&@@
@G:                                        .^^^^^^^^^^^^^^^^^^^^^^^^^^                                     :G@
@G:                                 ~7!!!!!5&@&&&&&&&&&&&&&&&&&&&&&&@#J!!!!!!^                             :G@
@G:                           ~JJ??YB@&&&&&BP5PPPGB#######BPPPPPPPPP5P#&&&&@@#J??^                         :G@
@G:                       ~Y55G&&#&#P5PPPG#&&&&&&@@GYYYYYYP#&&&&&&&&##GPPPPGB##@@#Y^                       :G@
@G:                     ~P&@@BGPPPPG#@&@@BJ?JJJJJJ?~^^^^^^~?JJJJJJ?J#@@&@#GPPPPGBB#BP~                     :G@
@G:                   ~G@@&GPPPP#@@#J!777!^^^^^^^^^^~~~~^^^^^^^^^^^^!777!J#@@#PPPPPGB#G~                   :G@
@G:                   7&@GPPB@@&@&J~^^^^^^^~~~~~~~~~~~^^?#G!^^~~~~~^^^^^^^~J&@&@@#PPPGG&B~                 :G@
@G:                 !#&GPPPG&@Y^^~^^^~~~~~~~~~~~~~~~~~^^?&B!^^~~~~~~~~~~~^^^~^^J&@@#GPPPG@B^               :G@
@G:               ^#@GPPPG#@@B?^^^~~~~~~~~~~~~~~~~~~~~^^?&B!^^~~~~~~~~~~~~~~^~~^^J#@@#GPG&B7.              :G@
@G:             .^?B#GPPB@&G?^^~~~~~~~~~~~~~~~~~~~~~~~^:7&B!^^~~~~~~~~~~~~~~~~~~~^^?B@@BP5G@B^             :G@
@G:             :#@GPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~^^~?P@B!^^~~~~~~~~~~~~~~~~~~~~~^^?PBBGG@B:             :G@
@G:           .75BBGPPG#GY7~^~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^:~G@BPBB57.           :G@
@G:           :G@BPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPB@G:           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPB@G.           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB&5.         :G@
@G:           ^G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~5&@@GPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^!PBB5~^^~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@P^:~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@&P?~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~JPBBGPPB@P.         :G@
@G:         .P@BPPPPPPGG&@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPG#@@P.         :G@
@G:         .P@BPPPPPPPP#@P^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~5#BGPPPB@B!.          :G@
@G:           ^G@BPPPPPP#@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5&@@BPPG&@@P.           :G@
@G:           .P&BPPPPPPPP#@Y^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5@@@BPPPPB@B^             :G@
@G:             :B@GPPPPPP#&P7~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~!P@@&BPPPPG@@&5:             :G@
@G:             ^B@#GPPPPPPP&@G???~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~?J?5&@&BPPPPPB#BY:               :G@
@G:             .7G@@#GPPPPPB##&@@PYYY5?^:^^^^^^^^^^^^^^^^^^^^^^^^:^?55YY5#&&#PPPPPGB##GJ:                 :G@
@G:                !5@@&&#BPPPPPGB#####BPPPPPPPPPPPPPPPPPPPPPPPPPPPPB####BP5PPPPPB&@@G7.                   :G@
@G:                 .~!!5@@&&&@&&#GPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBGPPPPG#&&&&@@P!!!.                     :G@
@G:                      ^^^^^:~G@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@B~:^^^.                         :G@
@@&#############################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######&#######################&@@
                                
                             
)"};
int delay = 500;
for (int i = 0; i < 4; i++)
{
	Scene::DrawASCII_Art(ClockImages[i], 0, 0, 7);
	Sleep(delay);
	Scene::ClearASCII_Art(0, 0, 7);
	//Scene::ClearASCII_Art(0, 0, 7);
}
}
