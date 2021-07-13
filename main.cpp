#include "objsdl/objsdl.h"
#include "mylibraries/random.h"

#include "shape.h"
#include "world.h"

using namespace std;

int main()try
{
	SDL::Window screen("Tetris", SDL::Rect(SDL::Window::UndefinedPos, 400, 600));
	SDL::Renderer rend(screen);
	Random random(time(0));
	Shape::Form shapes[]={
		{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},//#
		{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},//Line
		{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},//Letter L
		{{0,0,1,0},{0,0,1,0},{0,1,1,0},{0,0,0,0}} //Reversed L
	};
	World<10, 15> world;
    uint8 sleep=100;
	Shape active(shapes[1], SDL::Point(world.Widht()/2-2, -1));
	for(uint8 i=0;!SDL::events::Quit();++i)
	{
		if(i%5==0)
		{
			for(auto& event: SDL::events::Handler())
			{
				if(event.Type()==SDL::events::Type::Keydown)
				{
					if(event.Keyboard().Key==SDL::Keycode::Up&&world.CanTurn(active))
					{
						active.TurnLeft();
					}
					else if(event.Keyboard().Key==SDL::Keycode::Left&&world.CanMoveLeft(active))
					{
						active.GoLeft();
					}
					else if(event.Keyboard().Key==SDL::Keycode::Right&&world.CanMoveRight(active))
					{
						active.GoRight();
					}
					else
					{
						if(event.Keyboard().Key==SDL::Keycode::Down)
						{
							++i;
						}
						continue;
					}
					SDL::events::Flush(SDL::events::Type::Keydown);
					break;
				}
			}
			constexpr SDL::Color BGcol(255,255,0);
			rend.Repaint(BGcol);
			active.DrawOn(rend);
			world.DrawOn(rend);
			rend.Show();
			if(!world.CanFall(active))
			{
				world.Put(active);
				active=shapes[random.Next(func::Size(shapes))];
				active.GoTo(SDL::Point(world.Widht()/2-2, -1));
				world.FreeFullLines();
				rend.Repaint(BGcol);
				active.DrawOn(rend);
				world.DrawOn(rend);
				rend.Show();
				if(!world.CanFall(active))
				{
					SDL::MessageBox::Show("Tetris", "Konec hry");
					break;
				}
			}
			active.GoDown();
		}
		SDL::Wait(sleep);
		if(i==255)--sleep;
	}
	return 0;
}
catch(SDL::Error& err)
{
	err.Show();
	return 0;
}
catch(exception& exc)
{
	SDL::MessageBox::Show("Exception",exc.what());
	return 0;
}