// state.h --- Clase base state

// Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>

// Autor: José Tomás Tocino García

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.

#ifndef _STATE_H_
#define _STATE_H_

#include <Gosu/Gosu.hpp>
#include <iostream>

#include "log.h"

using namespace std;

class Game;

/**
 * @class State
 * 
 * @brief Base clase for the game states.
 *
 * This abstract class holds the methods that the main class (Game) will
 * call. Each state should implement these methods as needed.
 *
*/

class State{
protected:
    /**
     * @brief Reference to the game's main class
     *
     * It's used when we have to switch states (calling #Game::changeState(),
     * access the graphics system (using Game::graphics()), etc.
    **/
    Game * parent;
public:
    /** 
     * Default constructor. It receives a pointer to the game's main class.
     * 
     */
    State(Game * p);

    /// Control logic happens here
    virtual void update() = 0;

    /// Drawing operations happen here
    virtual void draw() = 0;

    /// Triggers when a key is pressed
    virtual void buttonDown(Gosu::Button){};

    /// Triggers when a key is released
    virtual void buttonUp(Gosu::Button){};

    /// Default destructor
    virtual ~State();
};

#endif /* _STATE_H_ */
