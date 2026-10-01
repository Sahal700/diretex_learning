/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can 255istribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			mobileX = mobileX - 1;
	} 
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			mobileX = mobileX + 1;
	}
	
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
			mobileY = mobileY - 1;
	}
	
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		
			mobileY = mobileY + 1;
	}
	

	mobileX = clampScreenX(mobileX);
	mobileY = clampScreenY(mobileY);
	
	colliding = overlapingTest(fixed0X, fixed0Y, mobileX, mobileY) ||
				overlapingTest(fixed1X, fixed1Y, mobileX, mobileY) ||
				overlapingTest(fixed2X, fixed2Y, mobileX, mobileY) ||
				overlapingTest(fixed3X, fixed3Y, mobileX, mobileY);

	//isShapeChanged = wnd.kbd.KeyIsPressed(VK_SHIFT);
}

void Game::ComposeFrame()
{
	drawBox(fixed0X, fixed0Y, 0, 255, 0);
	drawBox(fixed1X, fixed1Y, 0, 255, 0);
	drawBox(fixed2X, fixed2Y, 0, 255, 0);
	drawBox(fixed3X, fixed3Y, 0, 255, 0);


	if (colliding) {
		drawBox(mobileX, mobileY, 255, 0, 0);
	}
	else {
		drawBox(mobileX, mobileY, 255, 255, 255);
	}


}

void Game::drawBox(int x, int y, int r, int g, int b) {

	gfx.PutPixel(x - 5, y - 3, r, g, b);
	gfx.PutPixel(x - 5, y - 4, r, g, b);
	gfx.PutPixel(x - 5, y - 5, r, g, b);
	gfx.PutPixel(x - 4, y - 5, r, g, b);
	gfx.PutPixel(x - 3, y - 5, r, g, b);
	gfx.PutPixel(x + 5, y + 3, r, g, b);
	gfx.PutPixel(x + 5, y + 4, r, g, b);
	gfx.PutPixel(x + 5, y + 5, r, g, b);
	gfx.PutPixel(x + 4, y + 5, r, g, b);
	gfx.PutPixel(x + 3, y + 5, r, g, b);
	gfx.PutPixel(x - 5, y + 3, r, g, b);
	gfx.PutPixel(x - 5, y + 4, r, g, b);
	gfx.PutPixel(x - 5, y + 5, r, g, b);
	gfx.PutPixel(x - 4, y + 5, r, g, b);
	gfx.PutPixel(x - 3, y + 5, r, g, b);
	gfx.PutPixel(x + 5, y - 3, r, g, b);
	gfx.PutPixel(x + 5, y - 4, r, g, b);
	gfx.PutPixel(x + 5, y - 5, r, g, b);
	gfx.PutPixel(x + 4, y - 5, r, g, b);
	gfx.PutPixel(x + 3, y - 5, r, g, b);
}

bool Game::overlapingTest(int box0X, int box0Y, int box1X, int box1Y)
{
	int mobileLeft = box0X - 5, mobileRight = box0X + 5, mobileTop = box0Y - 5, mobileDown = box0Y + 5;
	int fixedLeft = box1X - 5, fixedRight = box1X + 5, fixedTop = box1Y - 5, fixedBottom = box1Y + 5;

	return (mobileLeft <= fixedRight && mobileRight >= fixedLeft) && (mobileTop <= fixedBottom && mobileDown >= fixedTop);
}

int Game::clampScreenX(int x)
{
	int left = x - 5;
	int right = x + 5;
	if (left < 0) {
		return 5;
	}
	if (right >= gfx.ScreenWidth) {
		return gfx.ScreenWidth - 6;
	}

	return x;
	
}
int Game::clampScreenY(int y)
{
	int top = y - 5;
	int bottom= y + 5;
	if (top < 0) {
		return 5;
	}
	if (bottom >= gfx.ScreenHeight) {
		return gfx.ScreenHeight - 6;
	}
	return y;
}
