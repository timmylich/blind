/*
 - This module adds the `/blind` command to the server along with its aliases `/bs`, `/black`, `/blackscreen`.
 - When the command is executed, the player's screen turns black for a specified duration.
 - This is useful for roleplay players to cut text from the chat and create screenshot situations.

 - This include works on a Plug and Play principle.
 - In other words, to make it work, you just need to include it as an include right after the main includes (a_samp or open.mp and Pawn.CMD).
 - You can customize the scriptТs settings using a set of defines.
 - Pawn.CMD must be enabled to work, but you can adapt the module for other command processors.

 - Version: 1.1.
 - Date: 08.10.2024.
 - GitHub Repo: https://github.com/timmylich/blind

 - Connect with author:
 - VKontake: https://vk.com/timmylich
 - Telegram: https://t.me/timmylich
*/


#include <Pawn.CMD>


/*
[EN] The duration of the black screen.
 - `%0` defines the player ID, allowing you to extract a custom duration set by the player if necessary.
[RU] ¬рем€, на которое по€вл€етс€ чЄрный экран.
 - `%0` - определ€ет ID игрока, с помощью которого в случае надобности вы можете извлечь индивидуальное врем€ срабатывани€, установленное игроком.
*/
#if !defined blind_Time
	#define blind_Time(%0) 3000 
#endif


static BlindTimer[MAX_PLAYERS];
static Text:BlindTD;


// OnPlayerConnect hook
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


// OnGameModeInit hook
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

// Pawn.CMD
CMD:blind(playerid)
{
	if(BlindTimer[playerid] != -1)
	{
		BlindTimer[playerid] = -1;
		return TextDrawHideForPlayer(playerid, BlindTD);
	}
	BlindTimer[playerid] = SetTimerEx(!"HideBlackScreenTD", blind_Time(playerid), false, !"i", playerid);
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