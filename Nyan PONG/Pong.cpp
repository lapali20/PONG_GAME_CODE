#include "Pong.h"
#define PADDLE_HEIGHT 120
#define PADDLE_WIDTH 20
#define winningscore 6
Pong::Pong()
{
    gWindow = NULL;
    winSurface = NULL;
    winTexture = NULL;
    dash = NULL;
    dashTex = NULL;
    renderer = SDL_CreateRenderer(gWindow, -1, 0);
    Nyan_Song = NULL;
    paddleOpp = true;
    scoreP1 = 0;
    scoreP2 = 0;
    scoreDisplayP1.setRect(1);
    scoreDisplayP2.setRect(2);

}

Pong::~Pong()
{
    SDL_FreeSurface(winSurface);
    SDL_FreeSurface(dash);
}

void Pong::runGame()
{
        int colorChangeP1 = 0;
        int colorChoiceP1 = 0;

        bool timerSet = false;

        int colorChangeP2 = 0;
        int colorChoiceP2 = 0;

        SDL_Surface* BgSurface = NULL;
        SDL_Texture* Bg = NULL;

        BgSurface = SDL_LoadBMP("images/nyanbg.bmp");

        Bg = SDL_CreateTextureFromSurface(renderer, BgSurface);

        Nyan_Song = NULL;
        Nyan_Song = Mix_LoadMUS("sounds/NyanTheSong.mp3");

        quit = false;

        SDL_Event gameEvents;
        SDL_Event NyanBGM;

        dash = SDL_LoadBMP("images/dash.bmp");
        SDL_Rect dashRect;
        dashRect.y = 0;
        dashRect.x = 374;
        dashRect.h = 52;
        dashRect.w = 43;
        dashTex = SDL_CreateTextureFromSurface(renderer,dash);

        playerOne.setWidth(PADDLE_WIDTH);
        playerOne.setHeight(PADDLE_HEIGHT);
        playerOne.setPosX(0);
        playerOne.setPosY(230);

        playerTwo.setWidth(PADDLE_WIDTH);
        playerTwo.setHeight(PADDLE_HEIGHT);
        playerTwo.setPosX(SCREEN_WIDTH - 20);
        playerTwo.setPosY(230);

        Ball Nyan(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 8, -4);

        Nyan.ballSurf = SDL_LoadBMP("images/nyanBall.bmp");
        Nyan.ballTex = SDL_CreateTextureFromSurface(renderer, Nyan.ballSurf);

        setPaddles(paddleOpp);

        while( !quit )
        {
            while(SDL_PollEvent(&NyanBGM) != 0)
            {
                if(NyanBGM.type == SDL_QUIT)
                {
                    quit = true;
                }
                processInput(NyanBGM);
            }

            playerOne.move(SCREEN_HEIGHT, gameEvents);

            if (playerTwo.AIControlled)
            {
                playerTwo.moveAI(SCREEN_HEIGHT, Nyan.hitBox.y);
            }
            else
            {
                playerTwo.move(SCREEN_HEIGHT, gameEvents);
            }

            SDL_RenderCopy(renderer, Bg, NULL, NULL);
            SDL_RenderCopy(renderer,dashTex, NULL, &dashRect);

            scoreDisplayP1.setImage(scoreP1, renderer);
            scoreDisplayP2.setImage(scoreP2, renderer);
            scoreDisplayP1.displayScore(renderer);
            scoreDisplayP2.displayScore(renderer);

            colorChange(colorChangeP1, colorChoiceP1);

            SDL_RenderFillRect(renderer, &playerOne.hitBox);
            SDL_RenderDrawRect(renderer, &playerOne.hitBox);

            colorChange(colorChangeP2, colorChoiceP2);

            SDL_RenderFillRect(renderer, &playerTwo.hitBox);
            SDL_RenderDrawRect(renderer, &playerTwo.hitBox);

            int ballMove = Nyan.move(SCREEN_HEIGHT, SCREEN_WIDTH, playerOne, playerTwo);

            SDL_RenderCopy(renderer, Nyan.ballTex, NULL, &Nyan.hitBox);


            if(ballMove == 1)
            {
                scoreP1++;
                SDL_Delay(1000);
            }
            if(ballMove == 2)
            {
                scoreP2++;
                SDL_Delay(1000);

            }

            if(scoreP1 == winningscore || scoreP2 == winningscore)
            {
                if (scoreP1 == winningscore)
                {
                    winSurface = SDL_LoadBMP("images/p1win.bmp");
                    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
                    SDL_RenderCopy(renderer, winTexture, NULL, NULL);
                    quit = true;
                }
                else if (scoreP2 == winningscore)
                {
                    winSurface = SDL_LoadBMP("images/p2win.bmp");
                    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
                    SDL_RenderCopy(renderer, winTexture, NULL, NULL);
                    quit = true;
                }

            }

            SDL_RenderPresent(renderer);
		}

		SDL_Delay(1000);

		SDL_FreeSurface(BgSurface);

	closeGame();
}

bool Pong::initialize()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " <<  SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!" << endl;
		}

		//Create window
		gWindow = SDL_CreateWindow( "Nyan Pong!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(renderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
//				//if(!( IMG_Init( imgFlags ) & imgFlags))
//				{
//					cout << "SDL_image could not initialize! SDL_image Error: " <<  IMG_GetError() << endl;
//					success = false;
//				}
				//Initialize SDL_mixer
				if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
				{
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
                    success = false;
                }
			}
		}
	}
	return success;
}

void Pong::closeGame()
{
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	renderer = NULL;

    Mix_FreeMusic(Nyan_Song);
    Nyan_Song = NULL;

	Mix_Quit();
	SDL_Quit();
}

void Pong::processInput(SDL_Event& e)
{
    playerOne.handleEvent(e);

    if (!playerTwo.AIControlled)
    {
        playerTwo.handleEventP2(e);
    }

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_m:
            if(Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(Nyan_Song, -1);
            }
            else
            {
                if( Mix_PausedMusic() == 1)
                {
                    Mix_ResumeMusic();
                }
                else
                {
                    Mix_PauseMusic();
                }
            }
            break;
        case SDLK_p:
            paddleOpp = !paddleOpp;
            setPaddles(paddleOpp);
            break;
        case SDLK_q:
            quit = true;
        }
    }
}

void Pong::setPaddles(bool isAI)
{
    if (isAI)
    {
        playerTwo.AIControlled = true;
        playerTwo.speed = 8;
    }
    else
    {
        playerTwo.AIControlled = false;
        playerTwo.speed = 12;
    }
}

void Pong::colorChange(int& change, int& choice)
{
    if (change == 10)
    {
        switch (choice)
        {
        case 0: //red
            SDL_SetRenderDrawColor( renderer, 255, 51, 51, 0 );
            choice++;
            change = 0;
            break;
        case 1: //orange
            SDL_SetRenderDrawColor( renderer, 255, 153, 51, 0 );
            choice++;
            change = 0;
            break;
        case 2: //yellow
            SDL_SetRenderDrawColor( renderer, 255, 255, 51, 0 );
            choice++;
            change = 0;
            break;
        case 3: //light-green
            SDL_SetRenderDrawColor( renderer, 153, 255, 51, 0 );
            choice++;
            change = 0;
            break;
        case 4: //green
            SDL_SetRenderDrawColor( renderer, 51, 255, 51, 0 );
            choice++;
            change = 0;
            break;
        case 5: //light-blue
            SDL_SetRenderDrawColor( renderer, 51, 255, 255, 0 );
            choice++;
            change = 0;
            break;
        case 6: //blue
            SDL_SetRenderDrawColor( renderer, 51, 51, 255, 0 );
            choice++;
            change = 0;
            break;
        case 7: //purple
            SDL_SetRenderDrawColor( renderer, 204, 0, 204, 0 );
            choice = 0;
            change = 0;
            break;
        case 8: //pink
            SDL_SetRenderDrawColor( renderer, 204, 0, 204, 0 );
            choice = 0;
            change = 0;
            break;
        default: //if error pink, cause why not
            SDL_SetRenderDrawColor( renderer, 255, 192, 203, 0 );
            choice = 0;
        }
    }
    change++;
}

void Pong::showHome()
{
    SDL_Event eHome;
    if( !initialize() )
	{
		cout << "Failed to initialize!"  << endl;
	}
	else
	{
        SDL_Surface* icon = SDL_LoadBMP("images/nyanIcon.bmp");
	    SDL_SetWindowIcon(gWindow, icon);
        SDL_Surface* HomeBgSurface = NULL; //background surface
        SDL_Texture* HomeBg = NULL; //background

        HomeBgSurface = SDL_LoadBMP("images/Menu.bmp");
        HomeBg = SDL_CreateTextureFromSurface(renderer, HomeBgSurface);

        Nyan_Song = NULL;
        Nyan_Song = Mix_LoadMUS("sounds/NyanTheSong.mp3");

        SDL_RenderCopy(renderer, HomeBg, NULL, NULL);
        SDL_RenderPresent(renderer);
		//Delay end of game to show who won

		//Free surfaces
        //Main loop flag
        bool quitHome = false;

        while(!quitHome){
        if(SDL_WaitEvent(&eHome) == 0){
            continue;
        }
        if(eHome.type == SDL_QUIT){
            quitHome = true;
        }
        if(eHome.type == SDL_MOUSEBUTTONDOWN){
            if(eHome.button.button == SDL_BUTTON_LEFT){
                if(eHome.button.x >=15 && eHome.button.x<=220 && eHome.button.y >= 250 && eHome.button.y <=400)
                {
                    runGame();
                    quitHome = true;
                }
                else if (eHome.button.x >=280 && eHome.button.x<=480 && eHome.button.y >= 340 && eHome.button.y <=450)
                {
                    showTutorial();
                }
                else if (eHome.button.x >=545 && eHome.button.x<=745 && eHome.button.y >= 450 && eHome.button.y <=550)
                {
                    closeGame();
                }
                }
            }
            else{
                continue;
            }
        }
        SDL_RenderCopy(renderer, HomeBg, NULL, NULL);
        SDL_RenderPresent(renderer);

		//Free surfaces
		SDL_FreeSurface(HomeBgSurface);
		SDL_FreeSurface(icon);
	}
	//Close SDL
	closeGame();
}

void Pong::showTutorial()
{
        SDL_Event eTutorial;

        SDL_Surface* TutorialBgSurface = NULL; //background surface
        SDL_Texture* TutorialBg = NULL; //background

        TutorialBgSurface = SDL_LoadBMP("images/Tutorial.bmp");
        TutorialBg = SDL_CreateTextureFromSurface(renderer, TutorialBgSurface);

        SDL_RenderCopy(renderer, TutorialBg, NULL, NULL);
        SDL_RenderPresent(renderer);

        bool quitTutorial = false;

        while(!quitTutorial)
        {
            if(SDL_WaitEvent(&eTutorial) == 0)
            {
                continue;
            }
            if(eTutorial.type == SDL_QUIT)
            {
                quitTutorial = true;
            }
            if(eTutorial.type == SDL_MOUSEBUTTONDOWN)
            {
                if(eTutorial.button.button == SDL_BUTTON_LEFT)
                {
                    if(eTutorial.button.x >=310 && eTutorial.button.x<=480 && eTutorial.button.y >= 520 && eTutorial.button.y <=580)
                    {
                        runGame();
                        quitTutorial = true;
                    }
                }
            }
            else
            {
                continue;
            }
        }
        SDL_RenderCopy(renderer, TutorialBg, NULL, NULL);
        SDL_RenderPresent(renderer);
}

//void Pong::replay()
//{
//        SDL_Event eReplay;
//
//        SDL_Surface* ReplayBgSurface = NULL; //background surface
//        SDL_Texture* ReplayBg = NULL; //background
//
//        ReplayBgSurface = SDL_LoadBMP("images/p2win.bmp");
//        ReplayBg = SDL_CreateTextureFromSurface(renderer, ReplayBgSurface);
//
//        SDL_RenderCopy(renderer, ReplayBg, NULL, NULL);
//        SDL_RenderPresent(renderer);
//
//        bool quitReplay = false;
//
//        while(!quitReplay)
//        {
//            if(SDL_WaitEvent(&eReplay) == 0)
//            {
//                continue;
//            }
//            if(eReplay.type == SDL_QUIT)
//            {
//                quitReplay = true;
//            }
//            if(eReplay.type == SDL_MOUSEBUTTONDOWN)
//            {
//                if(eReplay.button.button == SDL_BUTTON_LEFT)
//                {
//                    if(eReplay.button.x >=310 && eReplay.button.x<=480 && eReplay.button.y >= 520 && eReplay.button.y <=580)
//                    {
//                        closeGame();
//                        quitReplay = true;
//                    }
//                }
//            }
//            else
//            {
//                continue;
//            }
//        }
//        SDL_RenderCopy(renderer, ReplayBg, NULL, NULL);
//        SDL_RenderPresent(renderer);
//}
