/*
- Чёрный экран для скриншот-ситуаций.
- Автор: timmylich.
- ВКонтакте - @timmylich, TG - @timmylich.
- Кто спиздит себе - тот пидор и за тем уже выехали.

- Данный модуль работает по принципу "подключил и забыл".
- То есть для его работы достаточно будет просто подключить его как include после основных включений.
- Для работы необходим командный процессора Pawn.CMD, адаптируйте скрипт под свой командный процессор, если у вас он другой.
- Вы можете изменить настройки скрипта с помощью define'ов.
- Не забудьте добавить команду /blind(/bs, /black, /blackscreen) в список команд в помощи вашего сервера.

- Версия: 1.0.
- Дата обновления: 12.04.2024.
- https://github.com/timmylich/blind
*/

#include <Pawn.CMD>


#if !defined blind_Time // Время чёрного экрана
	#define blind_Time 3000 
#endif


static BlindTimer[MAX_PLAYERS];
static Text:BlindTD;


public OnPlayerConnect(playerid)
{
	BlindTimer[playerid] = -1;
	
	#if defined blind_OnPlayerConnect
		return blind_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect blind_OnPlayerConnect
#if defined blind_OnPlayerConnect
	forward blind_OnPlayerConnect(playerid);
#endif


public OnGameModeInit()
{
	BlindTD = TextDrawCreate(0.000000, 0.000000, "|");
	TextDrawUseBox(BlindTD, 1);
	TextDrawBoxColor(BlindTD, 0x000000FF);
	TextDrawTextSize(BlindTD, 640.000000, 23.000000);
	TextDrawAlignment(BlindTD, 0);
	TextDrawBackgroundColor(BlindTD, 0x000000FF);
	TextDrawFont(BlindTD, 3);
	TextDrawLetterSize(BlindTD, 1.000000, 52.200000);
	TextDrawColor(BlindTD, 0x00000000);
	TextDrawSetOutline(BlindTD, 1);
	TextDrawSetProportional(BlindTD, 1);
	TextDrawSetShadow(BlindTD, 1);

	#if defined blind_OnGameModeInit
		return blind_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit blind_OnGameModeInit
#if defined blind_OnGameModeInit
	forward blind_OnGameModeInit();
#endif


CMD:blind(playerid)
{
	if(BlindTimer[playerid] != -1)
	{
		BlindTimer[playerid] = -1;
		return TextDrawHideForPlayer(playerid, BlindTD);
	}
	BlindTimer[playerid] = SetTimerEx(!"HideBlackScreenTD", blind_Time, false, !"i", playerid);
	return TextDrawShowForPlayer(playerid, BlindTD);
}
forward pc_alias_blind();
public pc_alias_blind() PC_RegAlias(!"blind", !"black", !"bs", !"blackscreen");

forward HideBlackScreenTD(playerid);
public HideBlackScreenTD(playerid)
{
	if(BlindTimer[playerid] == -1) return 0;
	TextDrawHideForPlayer(playerid, BlindTD);
	return BlindTimer[playerid] = -1;
}