# Blind CMD
English | [Русский](README.ru.md)

# What is this?

This module adds the `/blind` command to the server along with its aliases `/bs`, `/black`, `/blackscreen`. When the command is executed, the player's screen turns black for a specified duration. This is useful for roleplay players to cut text from the chat and create screenshot situations.

To make the script work, simply include it after the main includes.
```pawn
#include <blind>
```

Demo video:
[![Watch the video](https://img.youtube.com/vi/tBqWAklIL9s/maxresdefault.jpg)](https://youtu.be/tBqWAklIL9s)

Author - timmylich. | [VKontakte](vk.com/timmylich) | [Telegram](t.me/timmylich)

# Compatibility and Configuration
The script requires `Pawn.CMD` to function, but you can easily adapt it for other command processors. You just need to modify the `CMD:blind` declaration.

The duration of the black screen is controlled by the following definition:
```pawn
#define blind_Time(%0) 3000
```
`%0` defines the player ID, allowing you to extract a custom duration set by the player if necessary.