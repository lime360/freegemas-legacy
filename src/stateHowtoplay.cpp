#include "stateHowtoplay.h"

#include "game.h"
#include "resManager.h"
#include "inter.h"

StateHowtoplay::StateHowtoplay(Game * p) : State(p){
    lDEBUG << Log::CON("StateHowtoPlay");

    imgBackground = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/howtoScreen.png");

    fontTitle = ResMgr -> getFont(Gosu::resourcePrefix() + L"media/fuenteMenu.ttf", 58);
    fontSubtitle = ResMgr -> getFont(Gosu::resourcePrefix() + L"media/fuenteMenu.ttf", 34);
    fontBodyText.reset(new TextBlock(parent -> graphics(), Gosu::resourcePrefix() + L"media/fNormal.ttf", 31, 450));

    bodyText += Gosu::utf8ToWstring(_("The objective of the game is to swap one gem with an adjacent gem to form a horizontal or vertical chain of three or more gems."));
    bodyText += Gosu::utf8ToWstring("\n\n");
    bodyText += Gosu::utf8ToWstring(_("Click the first gem and then click the gem you want to swap it with. If the movement is correct, they will swap and the chained gems will disappear."));
    bodyText += Gosu::utf8ToWstring("\n\n");
    bodyText += Gosu::utf8ToWstring(_("Bonus points are given when more than three identical gems are formed. Sometimes chain reactions, called cascades, are triggered, where chains are formed by the falling gems. Cascades are awarded with bonus points."));

    preparedText = fontBodyText->prepareText(bodyText);
}

void StateHowtoplay::update(){ }

void StateHowtoplay::draw(){
    imgBackground -> draw(0,0,0);

    wstring titleText = Gosu::utf8ToWstring(_("How to play"));
    wstring exitText = Gosu::utf8ToWstring(_("Press escape to come back"));

    
    fontTitle -> draw(titleText, 
                      300 + 470 / 2 - fontTitle -> textWidth(titleText) / 2,
                      20, 1);

    fontTitle -> draw(titleText, 
                      300 + 470 / 2 - fontTitle -> textWidth(titleText) / 2 + 1,
                      20 + 2, 0.9,
                      1, 1, 0x44000000);

    fontSubtitle -> draw(exitText,
                         30, 550, 1);

    fontSubtitle -> draw(exitText,
                         30 + 1, 550 + 2, 0.9,
                         1, 1, 0x44000000);

    fontBodyText -> draw(preparedText, 310, 110, 1, 0xffffffff);
    fontBodyText -> draw(preparedText, 310 + 1, 110 + 2, 1 - 0.1, 0x44000000);
}

void StateHowtoplay::buttonDown(Gosu::Button B){
    if(B == Gosu::kbEscape || B == Gosu::msLeft){
        parent -> changeState("stateMainMenu");
    }
}

StateHowtoplay::~StateHowtoplay(){
    lDEBUG << Log::DES("StateHowtoPlay");
}
