#include "stateMainMenu.h"

#include "game.h"
#include "log.h"

#include "resManager.h"
#include "inter.h"

template <typename T, typename R>

T clamp(T v, R bottom, R top){
    if(v > top) return top;
    if(v < bottom) return bottom;
    return v;
}

StateMainMenu::StateMainMenu(Game * p) : State(p){
    lDEBUG << Log::CON("StateMainMenu");
    
    currentTransitionState = TransitionIn;

    imgBackground = ResMgr -> getImage(Gosu::resourcePrefix() + 
                                       L"media/stateMainMenu/mainMenuBackground.png");

    imgLogo = ResMgr -> getImage(Gosu::resourcePrefix() + 
                                 L"media/stateMainMenu/mainMenuLogo.png");

    imgHighl = ResMgr -> getImage(Gosu::resourcePrefix() +
                                  L"media/stateMainMenu/menuHighlight.png");

    font = ResMgr -> getFont(Gosu::resourcePrefix() + L"media/fuenteMenu.ttf", 40);

    
    
    animationTotalSteps = 30;
    animationLogoSteps = 30;
    animationCurrentStep = 0;

    menuOptions.push_back(make_pair(Gosu::utf8ToWstring(_("Timetrial mode")), "stateGame"));
    menuOptions.push_back(make_pair(Gosu::utf8ToWstring(_("How to play?")), "stateHowtoplay"));
//    menuOptions.push_back(make_pair(L"Créditos");
    menuOptions.push_back(make_pair(Gosu::utf8ToWstring(_("Exit")), "stateQuit"));

    menuSelectedOption = 0;
    menuYStart = 350;
    menuYGap = 42;
    menuYEnd = 350 + (int) menuOptions.size() * menuYGap;

    double widthRead = 0, maxWidth = 0;

    for(size_t i = 0, s = menuOptions.size();
        i < s;
        ++i){

        widthRead = font -> textWidth(menuOptions[i].first);

        if(widthRead > maxWidth){
            maxWidth = widthRead;
        }
    }

	menuXStart = Gosu::round(800 / 2 - maxWidth / 2);
	menuXEnd = Gosu::round(menuXStart + maxWidth);

}

void StateMainMenu::update(){
    if(currentTransitionState == TransitionIn){
        animationCurrentStep ++;

        if(animationCurrentStep == animationTotalSteps){
            currentTransitionState = Active;
        }

    } else if(currentTransitionState == Active){

    } else if(currentTransitionState == TransitionOut){

    }

    int mY = (int) parent -> input().mouseY();

    if(mY >= menuYStart && mY < menuYEnd){
        menuSelectedOption = (mY - menuYStart) / menuYGap;
    }
}

void StateMainMenu::draw(){
    imgBackground -> draw(0,0,1);

    int logoAlfa = clamp( (int)(255 * (float)animationCurrentStep / animationLogoSteps),
                          0, 255);

    imgLogo -> draw(86, 0, 2, 1, 1, 
                    Gosu::Color(logoAlfa, 255, 255, 255));

    for(int i = 0, s = (int) menuOptions.size(); i < s; ++i){
		int hor = Gosu::round(800 / 2 - font -> textWidth(menuOptions[i].first) / 2);

        font -> draw(menuOptions[i].first, hor, menuYStart + i * menuYGap, 2);
        font -> draw(menuOptions[i].first, hor, menuYStart + i * menuYGap + 2, 
                     1.9, 1, 1, Gosu::Color(125, 0,0,0));
    }

    jewelAnim . draw();

    imgHighl -> draw(266, menuYStart + 5 + menuSelectedOption * menuYGap, 2);
}

void StateMainMenu::buttonDown(Gosu::Button B){
    if(B == Gosu::kbEscape){
        parent -> close();
    } 

    else if(B == Gosu::kbDown){
        if(++menuSelectedOption == (int) menuOptions.size()){
            menuSelectedOption = 0;
        }
    }

    else if(B == Gosu::kbUp){
        if(--menuSelectedOption == -1){
            menuSelectedOption = (int) menuOptions.size() - 1;
        }
    }

    else if(B == Gosu::kbReturn || B == Gosu::kbEnter){
        optionChosen();
    }

    else if(B == Gosu::msLeft){
        int mX = (int) parent -> input().mouseX();
        int mY = (int) parent -> input().mouseY();

        if(mX >= menuXStart && mX <= menuXEnd &&
           mY >= menuYStart && mY <= menuYEnd){
            optionChosen();
        }
    }
}

void StateMainMenu::optionChosen(){    
    parent -> changeState(menuOptions[menuSelectedOption].second);
}

StateMainMenu::~StateMainMenu(){
    lDEBUG << Log::DES("StateMainMenu");
}
