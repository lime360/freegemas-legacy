/**
 * @file stateMainMenu.h
 * 
 * @author José Tomás Tocino García
 * @date 2011
 *
 * Copyright (C) 2011 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _STATEMAINMENU_H_
#define _STATEMAINMENU_H_

#include <Gosu/Gosu.hpp>

#include "state.h"
#include "resManager.h"
#include "jewelGroupAnim.h"
#include "sdlfont.h"

#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include <utility>
using namespace std;

class Game;

/**
 * @class StateMainMenu
 *
 * @brief State for the main menu
 *
 * It manages the buttons of the main menu. The menu items are largely
 * dynamic. Also, there's an additional class that manages the animations of the
 * group of jewels that appear for decoration.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class StateMainMenu : public State{
public:

    /// Creates a new StateMainMenu
    StateMainMenu(Game * p);

    /// It controls the animations and the transitions
    void update();

    /// Draws the different elements
    void draw();

    /**
     * @brief It gets called whenever the user presses a button.
     *
     * The user can press Up, Down and Return to select the menu entries, as
     * well as the mouse.
     * 
     */
    void buttonDown(Gosu::Button B);

    ~StateMainMenu();

private:

    /// Possible states of the transition
    enum transitionState{ TransitionIn,
			  Active,
			  TransitionOut };

    /// Current transition state
    transitionState currentTransitionState;

    /// Current step of the animation
    int animationCurrentStep;

    /// Logo animation's total steps
    int animationLogoSteps;

    /// General animation's total steps
    int animationTotalSteps;
			  
    /// Image for the background
    boost::shared_ptr<Gosu::Image> imgBackground;

    /// Image for the logo
    boost::shared_ptr<Gosu::Image> imgLogo;

    /// Image for the higlight of the menu entry
    boost::shared_ptr<Gosu::Image> imgHighl;

    /// Font for the menu entries
    boost::shared_ptr<Gosu::Font> font;

    /// Class for the animation of the decorating jewels
    JewelGroupAnim jewelAnim;

    /// Current highlighted option
    int menuSelectedOption;

    /// List of menu options.
    /// 
    /// The first element of the pair represents the caption of the menu
    /// entry. The second element holds the name of the state to load when the
    /// user presses that menu option.
    vector<pair<wstring, string> > menuOptions;

    /// It gets executed when the user choses an option. It changes the state
    ///  to the proper one.
    void optionChosen();
    
    /// @{
    /// @name Coordinates of the menu elements
    int menuYStart, menuYEnd, menuYGap;
    int menuXStart, menuXEnd;
    /// @}

};

#endif /* _STATEMAINMENU_H_ */
