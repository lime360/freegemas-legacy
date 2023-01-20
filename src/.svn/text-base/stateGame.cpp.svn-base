#include "stateGame.h"
#include "log.h"
#include "game.h"
#include "resManager.h"
#include "inter.h"
#include "animation.h"

#include <cmath>
#include <algorithm>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

#define foreach BOOST_FOREACH

using boost::format;

StateGame::StateGame(Game * p) : State(p){
    lDEBUG << Log::CON("StateGame");

    // Set the initial loading state
    state = eLoading;

    // Load the loading screen
    imgLoadingBanner = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/loadingBanner.png");
    std::srand(std::clock());

}

void StateGame::init(){

    // Load the font for the timer
    fontTime = ResMgr -> getFont(Gosu::resourcePrefix() + L"media/fuentelcd.ttf", 62);

    // Load the font for the scoreboard
    fontScore = ResMgr -> getFont(Gosu::resourcePrefix() + L"media/fuentelcd.ttf", 33);

    // Load the backgorund image
    imgBoard = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/board.png");

    // Load the image for the square selector
    imgSelector = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/selector.png");    

    // Load the background image for the time
    imgTimeBackground = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/timeBackground.png");

    // Load the background image for the scoreboard
    imgScoreBackground = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/scoreBackground.png");
    
    /***************************************/
    // Temporal bitmap to create the images for the different texts
    Gosu::Bitmap bmpTemp;

    // Image for scoreboard heading
    bmpTemp = Gosu::createText(Gosu::utf8ToWstring(_("score")),
                               Gosu::resourcePrefix() + L"media/fNormal.ttf", 
                               37, 0, 190, Gosu::taCenter);
    imgScoreHeader.reset(new Gosu::Image(parent -> graphics(), bmpTemp));

    // Image for time heading
    bmpTemp = Gosu::createText(Gosu::utf8ToWstring(_("time left")),
                               Gosu::resourcePrefix() + L"media/fNormal.ttf", 
                               37, 0, 190, Gosu::taCenter);
    imgTimeHeader.reset(new Gosu::Image(parent -> graphics(), bmpTemp));


    /**************************************/
    // Buttons

    hintButton.reset(new BaseButton(parent -> graphics(),
                                    Gosu::utf8ToWstring(_("Show hint")), L"iconHint.png"));

    resetButton.reset(new BaseButton(parent -> graphics(),
                                     Gosu::utf8ToWstring(_("Reset game")), L"iconRestart.png"));

    exitButton.reset(new BaseButton(parent -> graphics(),
                                    Gosu::utf8ToWstring(_("Exit")), L"iconExit.png"));

    musicButton.reset(new BaseButton(parent -> graphics(),
                                     Gosu::utf8ToWstring(_("Turn on music")), L"iconMusic.png"));


    /**************************************/
    // Sounds
    sfxMatch1.reset(new Gosu::Sample(Gosu::resourcePrefix() + L"media/match1.ogg"));
    sfxMatch2.reset(new Gosu::Sample(Gosu::resourcePrefix() + L"media/match2.ogg"));
    sfxMatch3.reset(new Gosu::Sample(Gosu::resourcePrefix() + L"media/match3.ogg"));
    sfxSelect.reset(new Gosu::Sample(Gosu::resourcePrefix() + L"media/select.ogg"));
    sfxFall.reset(new Gosu::Sample(Gosu::resourcePrefix() + L"media/fall.ogg"));
    sfxSong.reset(new Gosu::Song(Gosu::resourcePrefix() + L"media/music1.ogg"));

    /**************************************/
    // Images for the gems
    imgWhite = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemWhite.png");
    imgRed = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemRed.png");
    imgPurple = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemPurple.png");
    imgOrange = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemOrange.png");
    imgGreen = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemGreen.png");
    imgYellow = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemYellow.png");
    imgBlue = ResMgr -> getImage (Gosu::resourcePrefix() + L"media/gemBlue.png");

    // Initial animation state
    pasoAnim = 0;

    // Steps for short animations
    totalAnim = 17;

    // Steps for long animations
    totalAnimInit = 50;

    // Steps for the hint animation
    totalAnimPista = 50;

    // Reset the hint flag
    mostrandoPista = -1;

    // Initial score multiplier
    multiplier = 1;

    // Reset the game to the initial values
    resetGame();

    //sfxSong -> play(true);
    sfxSong -> changeVolume(0.5);    
}

void StateGame::resetGame(){
    
    // Reset the score
    puntos = 0;

    // Redraw the scoreboard
    redrawScoreboard();

    // Restart the time (two minutes)
    timeStart = Gosu::milliseconds() + 2 * 60 * 1000;
}

void StateGame::redrawScoreboard(){
    Gosu::Bitmap temporal = Gosu::createText(
        boost::lexical_cast<wstring>(puntos),  // Text of the bitmap
        Gosu::resourcePrefix() + L"media/fuentelcd.ttf",   // Font of the bitmap
        33, // Font size
        0,  // Font flags
        190,  // Text width
        Gosu::taRight); // Text alignment

    txtPuntos.reset(new Gosu::Image(parent -> graphics(), temporal)); // reset the image
}

void StateGame::playMatchSound(){
    if(multiplier == 1){
        sfxMatch1 -> play(0.25);
    }else if(multiplier == 2){
        sfxMatch2 -> play(0.25);
    }else{
        sfxMatch3 -> play(0.25);
    }
}

void StateGame::createFloatingScores(){

    // For each match in the group of matched squares
    foreach(Match & m, groupedSquares){

        // Create a new floating score image
        scoreSet.push_back(FloatingScore(parent -> graphics(),
                                         m.size() * 5 * multiplier,
                                         m.midSquare().x,
                                         m.midSquare().y, 8));

        // Create a new particle system for it to appear over the square
        for(size_t i = 0, s = m.size(); i < s; ++i){
            particleSet.push_back(SistemaParticulas(& parent -> graphics(),
                                                    50, 150, 
                                                    241 + m[i].x * 65 + 32, 
                                                    41 + m[i].y * 65 + 32, 60, 0.5));

        }

        puntos += m.size() * 5 * multiplier;       
    }

    redrawScoreboard();
}
void StateGame::update(){

    /*
      Before doing anything else, we have to show, at least once, the loading
      screen. After the first draw event, we'll jump to the eFirstFlip state, where
      init() will be called and the resources will start to load
    */

    if(state == eLoading)
        return;

    if(state == eFirstFlip){

        // Call init to start loading resources
        init();

        // Switch to the main game state
        state = eInicialGemas;

        // Then stop computing the rest of the logic
        return;
    }

    
    // Compute the remaining time
    double remainingTime = (timeStart - Gosu::milliseconds()) / 1000;
	
    // If there's some remaining time, compute the string for the time board
    if(remainingTime >= 0){
        int minutes = int(remainingTime / 60);
        int seconds = int(remainingTime - minutes * 60);
        txtTime = boost::lexical_cast<string>(minutes) + 
            (seconds < 10 ? ":0" : ":") + 
            boost::lexical_cast<string>(seconds);
    }

    // If there's no time left and we're not in a final state
    else if(remainingTime < 0 && state != eTimeFinished && state != eShowingScoreTable){

        // End the game
        state = eTimeFinished;

        // Take the gems out of the screen
        gemsOutScreen();
    }

    // Remove the hidden floating score 
    scoreSet.erase(remove_if(scoreSet.begin(), scoreSet.end(), 
                             boost::bind<bool>(&FloatingScore::ended, _1)), scoreSet.end());

    // Remove the hiden particle systems
    particleSet.erase(remove_if(particleSet.begin(), 
                                particleSet.end(), 
                                boost::bind<bool>(&SistemaParticulas::ended, _1)), 
                      particleSet.end());

    // Initial game state
    if(state == eInicialGemas){

        // If animation ended
        if(++pasoAnim == totalAnimInit){
            
            // Switch to next state (waiting for user input)
            state = eEspera;
            board.endAnimations();

            // reset animation step counter
            pasoAnim = 0;
        }
    }

    // In the waiting state, the multiplier must be zero
    else if(state == eEspera){
        multiplier = 0;
    }

    // In this state, the pair of selected gems are swapping
    else if(state == eGemasCambiando){	

        // When animation ends
        if(++pasoAnim == totalAnim){

            // Switch to the next state (gems start to disappear)
            state = eGemasDesapareciendo;

            // Swap the gems in the board
            board.swap(selectedSquareFirst.x, selectedSquareFirst.y,
                       selectedSquareSecond.x, selectedSquareSecond.y);

            // Increase the multiplier
            ++multiplier;

            // Play matching sound
            playMatchSound();

            // Create floating scores for the matching group
            createFloatingScores();

            // Reset animation step counter
            pasoAnim = 0;
        }
    }

    // In this state, the swapping gems are fading
    else if(state == eGemasDesapareciendo){

        // When animation ends
        if(pasoAnim++ == totalAnim){

            // Switch to the next state (new gems fall to their position)
            state = eGemasNuevasCayendo;

            // Redraw the score board with new points
            redrawScoreboard();

            // Delete the squares that were matched in the board
            for(size_t i = 0; i < groupedSquares.size(); ++i){
                for(size_t j = 0; j < groupedSquares[i].size(); ++j){
                    board.del(groupedSquares[i][j].x,
                              groupedSquares[i][j].y);
                }
            }

            // Calculate fall movements
            board.calcFallMovements();

            // Apply changes to the board...
            board.applyFall();

            // Fill empty spaces
            board.fillSpaces();

            // Reset animation step counter
            pasoAnim = 0;
        }
    }

    // In this state, new gems are falling
    else if(state == eGemasNuevasCayendo){

        // When animation ends
        if(pasoAnim++ == totalAnim){

            // Play the fall sound fx
            sfxFall -> play(0.3);

            // Switch to the next state (waiting state)
            state = eEspera;

            // Reset animation counter
            pasoAnim = 0;

            // Reset animation variables
            board.endAnimations();

            // Check if there are matching groups
            groupedSquares = board.check();

            // If there are...
            if(! groupedSquares.empty()){

                // Increase the score multiplier
                ++multiplier;

                // Create the floating scores
                createFloatingScores();

                // Play matching sound
                playMatchSound();

                // Go back to the gems-fading state
                state = eGemasDesapareciendo;
            }

            // If there are neither current solutions nor possible future solutions
            else if(board.solutions().empty()){

                // Make the board disappear
                state = eDesapareceBoard;
                gemsOutScreen();

            }
        }
    }

    // In this state, the board is disappearing because there were no possible movements
    else if(state == eDesapareceBoard){

        // When animation ends
        if(++pasoAnim == totalAnimInit){

            // Switch to the initial state
            state = eInicialGemas;

            // Generate a brand new board
            board.generate();

            // Reset animation counter
            pasoAnim = 0;
        }
    }

    // In this state, the time has finished, so we need to create a ScoreBoard
    else if(state == eTimeFinished){

        // When animation ends
        if(++pasoAnim == totalAnimInit){

            // Create a new score table
            scoreTable.reset(new ScoreTable(parent, puntos));

            // Switch to the following state
            state = eShowingScoreTable;
			 
            // Reset animation counter
            pasoAnim = 0;
        }
    }

    // Whenever a hint is being shown, decrease its controlling variable
    if(mostrandoPista != -1) 
        mostrandoPista --;

}



void StateGame::draw(){
    // If we're still loading resources, just show the loading screen
    if(state == eLoading || state == eFirstFlip){
        state = eFirstFlip;
        imgLoadingBanner -> draw(156, 200, 2);
        return;
    }

    // Draw the background image
    imgBoard -> draw(0,0,1);

    // Vertical initial position for the buttons
    int vertButStart = 360;

    // Draw the buttons
    hintButton -> draw(17, vertButStart, 2);
    resetButton -> draw(17, vertButStart + 47, 2);
    musicButton -> draw(17, vertButStart + 47 * 2, 2);
    exitButton -> draw(17, 538, 2);

    // Draw the score 
    imgScoreBackground -> draw(17, 124, 2);
    imgScoreHeader -> draw(17, 84, 3, 1, 1, Gosu::Color(0xffa0a9ff));
    imgScoreHeader -> draw(18, 85, 2, 1, 1, Gosu::Color(0x66000000));

    fontScore -> draw(boost::lexical_cast<wstring>(puntos), 
                      197 - fontScore ->textWidth(boost::lexical_cast<wstring>(puntos)),
                      127, 2, 1, 1,
                      Gosu::Color(0xff4ec1be));

    // Draw the time
    imgTimeBackground -> draw(17, 230, 2);
    imgTimeHeader -> draw(17, 190, 3, 1, 1, Gosu::Color(0xffa0a9ff));
    imgTimeHeader -> draw(18, 191, 2, 1, 1, Gosu::Color(0x66000000));

    fontTime -> draw(Gosu::utf8ToWstring(txtTime), 
                     190 - fontTime ->textWidth(Gosu::utf8ToWstring(txtTime)),
                     232, 2, 1, 1,
                     Gosu::Color(0xff4ec1be));

    // Draw each score little messages
    std::for_each(scoreSet.begin(), 
                  scoreSet.end(), 
                  boost::bind(&FloatingScore::draw, _1));

    // Draw each particle system
    std::for_each(particleSet.begin(), 
                  particleSet.end(), 
                  boost::bind(&SistemaParticulas::draw, _1));

    // Starting position for the squares
    int posX = 241, 
        posY = 41;

    // Generic pointer for drawing the squares
    boost::shared_ptr<Gosu::Image> img;

    // If we're not in the final screen (showing the scores)
    if(state != eShowingScoreTable){

        // Go through all of the squares
        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){

                // Check the type of each square and
                // save the proper image in the img pointer

                switch(board.squares[i][j]){
                case sqWhite:
                    img = imgWhite;
                    break;

                case sqRed:
                    img = imgRed;
                    break;

                case sqPurple:
                    img = imgPurple;
                    break;

                case sqOrange:
                    img = imgOrange;
                    break;

                case sqGreen:
                    img = imgGreen;
                    break;

                case sqYellow:
                    img = imgYellow;
                    break;

                case sqBlue:
                    img = imgBlue;
                    break;

                case sqEmpty:
                    img.reset();
                    break;
                } // fin switch

                // Now, if img is not NULL (there's something to draw)
                if(img != NULL){
                    // Default positions
                    float imgX = posX + i * 65;
                    float imgY = posY + j * 65;

                    // Default color
                    Gosu::Color imgColor = 0xffffffff;
                    
                    // In the initial state, the gems fall vertically
                    // decreasing its speed
                    if(state == eInicialGemas){
                        imgY = Animacion::easeOutQuad(
                            float(pasoAnim),
                            float(posY + board.squares[i][j].origY * 65),
                            float(board.squares[i][j].destY * 65),
                            float(totalAnimInit));                            
                    }

                    // In the ending states, gems fall vertically, 
                    // increasing their speed
                    else if(state == eDesapareceBoard || state == eTimeFinished){
                        imgY = Animacion::easeInQuad(
                            float(pasoAnim),
                            float(posY + board.squares[i][j].origY * 65),
                            float(board.squares[i][j].destY * 65),
                            float(totalAnimInit));
                    }

                    else if((state == eEspera || 
                             state == eGemaMarcada ||
                             state == eGemasNuevasCayendo)
                            &&
                            board.squares[i][j].mustFall)
                    {
                        imgY = Animacion::easeOutQuad(
                            float(pasoAnim),
                            float(posY + board.squares[i][j].origY * 65),
                            float(board.squares[i][j].destY * 65),
                            float(totalAnim));
                    }                    

                    // When two gems are switching
                    else if(state == eGemasCambiando){
                        if(i == selectedSquareFirst.x && 
                           j == selectedSquareFirst.y){

                            imgX = Animacion::easeOutQuad(
                                float(pasoAnim),
                                float(posX + i * 65),
                                float((selectedSquareSecond.x - selectedSquareFirst.x) * 65),
                                float(totalAnim));

                            imgY = Animacion::easeOutQuad(
                                float(pasoAnim),
                                float(posY + j * 65),
                                float((selectedSquareSecond.y - selectedSquareFirst.y) * 65),
                                float(totalAnim));

                        }

                        else if(i == selectedSquareSecond.x && 
                                j == selectedSquareSecond.y){

                            imgX = Animacion::easeOutQuad(
                                float(pasoAnim),
                                float(posX + i * 65),
                                float((selectedSquareFirst.x - selectedSquareSecond.x) * 65),
                                float(totalAnim));

                            imgY = Animacion::easeOutQuad(
                                float(pasoAnim),
                                float(posY + j * 65),
                                float((selectedSquareFirst.y - selectedSquareSecond.y) * 65),
                                float(totalAnim));

                        }
                    }

                    else if(state == eGemasDesapareciendo){
                        // Desaparición de las gemas ganadoras

                        if(groupedSquares.matched(coord(i,j))){

                            imgColor = Gosu::Color(int(255 * (1 -(float)pasoAnim/totalAnim)), 
                                                   255, 255, 255);
                        }
                    }

                    // Finally draw the image
                    img -> draw(imgX, imgY, 3, 1, 1, imgColor);

                } // Fin if (img != NULL)
                
                img.reset();
            }
        }

        // Get the mouse position
        int mX = (int) parent -> input().mouseX();
        int mY = (int) parent -> input().mouseY();

        // If the mouse is over a gem
        if(overGem(mX, mY) ){

            // Draw the selector over that gem
            imgSelector -> draw( 241 + getCoord(mX, mY).x * 65,
                                 41 + getCoord(mX, mY).y * 65,
                                 4);
        }

        // If a gem was previously clicked
        if(state == eGemaMarcada){

            // Draw the tinted selector over it
            imgSelector -> draw(241 + selectedSquareFirst.x * 65,
                                41 + selectedSquareFirst.y * 65,
                                4, 1, 1,
                                Gosu::Color(0xffff0000));
        }

        // If a hint is being shown
        if(mostrandoPista != -1){
            // Get the opacity percentage
            float p1 = (float)mostrandoPista / totalAnimPista;

            float pX1 = 241 + coordPista.x * 65 - imgSelector -> width() * (2 - p1) / 2 + 65 / 2;
            float pY1 = 41 + coordPista.y * 65 - imgSelector -> height() * (2 - p1) / 2 + 65 / 2;

            imgSelector -> draw(pX1, pY1,
                                3, 2 - p1, 2 - p1,
                                Gosu::Color(int(p1 * 255), 0, 255, 0));

        }
    }else{
        scoreTable -> draw(241 + (65 * 8) / 2 - 150  , 105, 3);
    }
}

bool StateGame::overGem(int mX, int mY){
    return (mX > 241 && mX < 241 + 65 * 8 &&
            mY > 41 && mY < 41 + 65 * 8);
}

coord StateGame::getCoord(int mX, int mY){
    return coord((mX - 241) / 65 , 
                 (mY - 41) / 65 );
}

bool StateGame::checkClickedSquare(int mX, int mY){
    selectedSquareSecond = getCoord(mX, mY);

    bool returnValue = false;

    // Si es una gema CONTIGUA
    if(abs(selectedSquareFirst.x - selectedSquareSecond.x) 
       + abs(selectedSquareFirst.y - selectedSquareSecond.y) == 1){ 

        Board temporal = board;
        temporal.swap(selectedSquareFirst.x, selectedSquareFirst.y,
                      selectedSquareSecond.x, selectedSquareSecond.y);

        groupedSquares = temporal.check();

        // SI ES UN MOVIMIENTO GANADOR
        if(! groupedSquares.empty()){
            state = eGemasCambiando;
            returnValue = true;
        }else{
            returnValue = false;
        }
    }

    return returnValue;
}

void StateGame::buttonUp (Gosu::Button B){
    if(B == Gosu::msLeft){
        clicking = false;

        if(state == eGemaMarcada){
            int mX = (int) parent -> input().mouseX();
            int mY = (int) parent -> input().mouseY();

            coord res = getCoord(mX, mY);

            if(!(res == selectedSquareFirst)){
                checkClickedSquare(mX, mY);
            }
        }
    }
}

void StateGame::buttonDown (Gosu::Button B){
    if(B == Gosu::kbEscape){
        parent -> changeState("stateMainMenu");
    }

    else if(B == Gosu::msLeft){ // Se pulsó el ratón
        clicking = true;

        int mX = (int) parent -> input().mouseX();
        int mY = (int) parent -> input().mouseY();

        if(exitButton -> clicked(mX, mY)){
            parent -> changeState("stateMainMenu");
        }

        else if(hintButton -> clicked(mX, mY)){
            showHint();
        }

        else if(musicButton -> clicked(mX, mY)){
            if(sfxSong -> playing()){
                musicButton -> changeText(Gosu::utf8ToWstring(_("Turn on music")));
                sfxSong -> stop();
            }else{
                musicButton -> changeText(Gosu::utf8ToWstring(_("Turn off music")));
                sfxSong -> play(true);
            }	    
        }
        else if (resetButton -> clicked(mX, mY)){
            state = eDesapareceBoard;
            gemsOutScreen();
            resetGame();
	    
        }
        else if(overGem(mX, mY)){ // Si se pulsó sobre una gema
            sfxSelect -> play(0.3);

            if(state == eEspera){ // Si no hay ninguna gema marcada
                state = eGemaMarcada;
                selectedSquareFirst.x = getCoord(mX, mY).x;
                selectedSquareFirst.y = getCoord(mX, mY).y;
            }

            else if(state == eGemaMarcada){ // Si ya había una gema marcada
                if(!checkClickedSquare(mX, mY)){
                    selectedSquareFirst.x = -1;
                    selectedSquareFirst.y = -1;
                    state = eEspera;		    
                }
            }
        }
    }

    else if(B == Gosu::kbH){
        showHint();
    }

    if(state == eShowingScoreTable){
        scoreTable -> buttonDown(B);
    }
}

void StateGame::showHint(){
    vector<coord> posibilidades = board.solutions();
    coordPista = posibilidades[0];
    mostrandoPista = totalAnimPista;   
}

void StateGame::gemsOutScreen(){
    for(int x = 0; x < 8; ++x){
        for(int y = 0; y < 8; ++y){
            board.squares[x][y].mustFall = true;
            board.squares[x][y].origY = y;
            board.squares[x][y].destY = int(9 + Gosu::random(1,7));
        }
    }
}
StateGame::~StateGame(){
    lDEBUG << Log::DES("StateGame");
}


