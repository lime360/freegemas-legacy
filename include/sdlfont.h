/**
 * @file customFont.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Class to use custom fonts in Gosu & Linux
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
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


#ifndef _CUSTOMFONT_H_
#define _CUSTOMFONT_H_

#include "Gosu/Gosu.hpp"

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include <map>
#include <cstdio>

#include <iostream>
using namespace std;


class TextBlock{  
    Gosu::Graphics &g;
    boost::shared_ptr<Gosu::Font> font;

    int textWidth, fontLineSkip;

	vector<wstring> tokenize(const wstring & text, const wchar_t sep = L'\n'){
		vector<wstring> tokens;	

		string::size_type lastPos = text.find_first_not_of(sep, 0);
		// Find first "non-delimiter".
		string::size_type pos     = text.find_first_of(sep, lastPos);
		
		tokens.clear();
		while (string::npos != pos || string::npos != lastPos)
		{
			// Found a token, add it to the vector.
			tokens.push_back(text.substr(lastPos, pos - lastPos));

			// Skip '\n'.  Note the "not_of"
			lastPos = text.find_first_not_of(sep, pos);

			// Find next "non-delimiter"
			pos = text.find_first_of(sep, lastPos);
		}	

		return tokens;
	}

	vector<wstring> fitLines(const vector<wstring> & lines){
		vector<wstring> result;
		wstring tempString;
		vector<wstring>::const_iterator i, j, w1, w2;

		double acumWidth, currWordWidth;

		for(i = lines.begin(), j = lines.end(); i != j; ++i){
			acumWidth = 0;
			tempString = L"";
			vector<wstring> words = tokenize(*i, L' ');	

			for(w1 = words.begin(), w2 = words.end(); w1 != w2; ++w1){
				currWordWidth = font -> textWidth(*w1);
				if(acumWidth + currWordWidth <= textWidth){
					tempString += L" " + *w1;
					acumWidth += currWordWidth;
				}else{
					result.push_back(tempString);
					tempString = *w1;
					acumWidth = currWordWidth;
				}
			}	

			if(tempString != L""){
				result.push_back(tempString);
			}
			result.push_back(L"\n");
		}

		return result;
	}
	
public:

    TextBlock(Gosu::Graphics & g, const std::wstring& fontName, unsigned fontHeight, int textWidth) : g(g), textWidth(textWidth){
        font.reset(new Gosu::Font(g, fontName, fontHeight));
        fontLineSkip = fontHeight;
    }

    vector<wstring> prepareText(const std::wstring & text){
        return fitLines(tokenize(text));
    }

    void draw(const std::vector<wstring> & textLines, int x, int y, Gosu::ZPos z, Gosu::Color color){
        vector<wstring>::const_iterator i, j;
	    
	    int c = 0;
	    for(i = textLines.begin(), j = textLines.end();
	        i != j; ++i){
		    double thisLineWidth = font -> textWidth(*i);		        
			font -> draw(*i, Gosu::round(x + textWidth / 2 - thisLineWidth / 2), 
				Gosu::round(y + c++ * (fontLineSkip + 5) * 1), 
		                 z, 1, 1, color);
	    }
    }

    void draw(const std::wstring & text, int x, int y, Gosu::ZPos z, Gosu::Color color){
	    draw(fitLines(tokenize(text)), x, y, z, color);
    }
};
#endif /* _CUSTOMFONT_H_ */
