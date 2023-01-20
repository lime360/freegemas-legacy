#include "baseButton.h"

BaseButton::BaseButton(Gosu::Graphics & g, std::wstring text, std::wstring imgIconPath) : g(g){
    buttonBackground = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/buttonBackground.png");
    buttonFont = ResMgr -> getFont(Gosu::resourcePrefix() + L"media/fNormal.ttf", 29);

    if(imgIconPath != L""){
        imgIcon = ResMgr -> getImage(Gosu::resourcePrefix() + L"media/" + imgIconPath);	
    }

    changeText(text);
}

void BaseButton::changeText(std::wstring text){
    buttonText = text;
    double text_w = buttonFont -> textWidth(buttonText) / 2;

    if(imgIcon != 0){
        int espacio = 35;
        textX = Gosu::round(espacio + (buttonBackground -> width() - espacio) / 2 - text_w);
    }else{
        textX = Gosu::round(buttonBackground -> width() / 2 - text_w);
    }
}

void BaseButton::draw(int x, int y, double z){
    lastX = x;
    lastY = y;

    if(imgIcon != 0){
        imgIcon -> draw(x + 7, y, z + 0.1);
    }

    buttonFont -> draw(buttonText,
                       x + textX, y + 5, z + 0.2);

    buttonFont -> draw(buttonText,
                       x + textX + 1, y + 7, z + 0.1,
                       1,1,0x44000000);

    buttonBackground -> draw(x, y, z);
	
}

bool BaseButton::clicked(unsigned int mX, unsigned int mY){
    if(mX > lastX && mX < lastX + buttonBackground -> width() &&
       mY > lastY && mY < lastY + buttonBackground -> height()){
        return true;
    }else{
        return false;
    }
}
