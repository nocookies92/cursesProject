/* =============================================================================
 * Aaron Gross
 * cursesProject
 * renamed SpankWagon, my friend's idea.
 *
 * Credits: 
 * Programming - Aaron Gross
 * Level design, story & dialogue, director of creativity - Jason Pepper
 * Comic relief - Jack Hafer
 * 3/4/14
 * V1.0 
 * =============================================================================
 */

#include <stdio.h>
#include <curses.h>
#include "definitions.h"
#include "state.h"
#include "update.h"
#include "mainMenu.h"
#include "game.h"
#include "battle.h"

void initialize();
void render();
void gamePause();
void cleanup();

bool notReadyToQuit();

int tick = 0;

char titleBanner[] = {"\
SSSSS PPPPP   A   N   N K  K W     W   A    GGG   OOO  N   N\
S     P   P  A A  NN  N K K  W  W  W  A A  G     O   O NN  N\
SSSSS PPPPP A   A N N N KK   W W W W A   A G  G  O   O N N N\
    S P     AAAAA N N N K K  W W W W AAAAA G   G O   O N N N\
SSSSS P     A   A N  NN K  K WW   WW A   A GGGG   OOO  N  NN"};

WINDOW *w;

int main(int argc, char *argv[])
{
	initialize();

	// main game loop
	while(notReadyToQuit())
	{
		update();
		render();
		gamePause();

		tick++;
		if(tick == TICS_PER_SEC)
		{
			tick = 0;
		}
	}

	cleanup();

	return 0;
}

void initialize()
{
	w = initscr(); // init a curses window

	start_color(); // call so can use colors
	int i, j, k = 0; // counter variables
	for(i = 0; i < 8; i++) // initialize all 64 color pairs
	{
		for(j = 0; j < 8; j++)
		{
			if(k) // skip cp #1; already defined as black and white
			{
				init_pair(k, colors[i], colors[j]);
			}
			k++;
		}
	}

	/*
	 * These two lines make it so that getch() doesn't need to wait 
	 * for a character to be entered for getch() to return.
	 * This allows the game to update and render even when there is no input
	 * Also put as: call getch() without blocking
	 */
	cbreak(); // put terminal in c break mode
	nodelay(w, TRUE); // don't wait for enter to read char

	noecho(); // turn off key echoing
	keypad(w, TRUE); // allow getch() to detect non-character key presses

	curs_set(0); // hide the cursor

	initMenu(4);
	initTitle(60, 5, titleBanner);
	initMenuChoice(GAME, "Play Game");
	initMenuChoice(INSTRUCTIONS, "Instructions");
	initMenuChoice(OPTIONS, "Options");
	initMenuChoice(QUIT, "Quit");

	initGame();

	setState(MAIN_MENU);
}

void render() 
{
	clear();
	switch(getState())
	{
		case MAIN_MENU:
			renderMainMenu();
			break;
		case GAME:
			renderGame();
			break;
		case BATTLE:
			renderBattle();
			break;
		case INSTRUCTIONS:
			renderInstructions();
			break;
		case OPTIONS:
			renderOptions();
			break;
		case STATUS:
			renderStatus();
			break;
		default:
			break;
	}
	refresh(); // call curses's refresh funct to update screen
}

void gamePause() 
{
	napms(DELAY); // from curses.h, sleeps for n milliseconds
}

void cleanup()
{
	curs_set(1); // set cursor back to being visible
	cleanupMenu();
	cleanupGame();
	clear();
	refresh();
	delwin(w);
    	endwin();
}

bool notReadyToQuit()
{
	if(state)
	{
		return TRUE;
	} else 
	{
		return FALSE;
	}
}
