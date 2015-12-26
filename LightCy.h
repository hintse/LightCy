#ifndef LIGHTCY_H
#define LIGHTCY_H

#include "glutMaster.h"
#include "PlasmaFractal.h"
#include "Timer.h"
#include "Player.h"
#include "Camera.h"
#include "Terrain.h"
#include "Types.h"
#include "Message.h"

/* class representing the game window */
class LightCy : public GlutWindow
{
	public:
		/* constructor */
		LightCy(GlutMaster& glutMaster);
		
		/* destructor */
		~LightCy();
		
		/* begin callback functions for GLUT */
		void CallBackDisplayFunc(void);
		void CallBackReshapeFunc(int w, int h);
		void CallBackIdleFunc(void);
		void CallBackKeyboardFunc(unsigned char key, int x, int y);
		void CallBackSpecialFunc(int key, int x, int y);   
		/* end callback functions for GLUT */
	
	private:
		/* initialise opengl */
		void initialise_opengl();
		
		/* initialise glut */
		void initialise_glut();
		
		/* compile the terrain into a opengl display list
		   for better performance */
		void compile_terrain();

		/*	initialise the objects in the game */
		void initialise_game();
		
		/* reset the game the the initial state */
		void reset_game();
		
		/* check if a player lost.  return the distance the
		   player lost by (how much the player crashed).  we
		   need the distance to resolve draws */
		float check_lost(const Player& p) const;
		
		/* update the start countdown timer */
		void update_start_countdown(float dt);
		
		/* update the state of the game */
		void update_game_state(float dt);

		/* handle to glutmaster */
		GlutMaster* glutmaster_;
		
		/* terrain (i.e. landscape) */
		Terrain terrain_;
		
		/* the players in the game */
		std::vector<Player> players_;
		
		/* cameras following the players */
		std::vector<Camera> cameras_;
		
		/* messages to be displayed on the screen for each player */
		std::vector<Message> messages_;
		
		/* rudimentary timer for the game*/
		Timer timer_;

		/* current window height */
		float window_height_ = 600.0f;
		
		/* current window width */
		float window_width_ = 800.0f;
		
		/* is the game running? */		
		bool game_running_ = false;
		
		/* are we in the start menu? (only true when application
		   starts, false once the first game starts */
		bool in_start_menu_ = true;		
		
		/* time left on countdown timer */
		float start_countdown_ = 0.0f;
		
		/* map width */
		static constexpr auto map_size_x = 512;
		
		/* map height */
		static constexpr auto map_size_y = 512;
		
		/* time to countdown before game starts */
		static constexpr auto start_countdown_time = 3.5f;
		
};

#endif

