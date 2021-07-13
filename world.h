#pragma once

template<int w, int h>
class World
{
private:
	constexpr static int widht=w,height=h;
	bool world[height][widht]={{false}};
	bool IsFree(const SDL::Point& move, const Shape& shape)
	{
		if(shape.Position().y+move.y+shape.DownIndex()>=height)return false;
		if(shape.Position().x+move.x+shape.RightIndex()>=widht)return false;
		if(shape.Position().x+move.x+shape.LeftIndex()<0)return false;
		for(uint8 y=0;y<=shape.DownIndex();++y)
			for(uint8 x=0;x<=shape.RightIndex();++x)
				if(shape[y][x]&&world[shape.Position().y+move.y+y][shape.Position().x+move.x+x])
					return false;
		return true;
	}
public:
	World()=default;
	void Put(const Shape& form)
	{
		for(uint8 y=form.UpIndex();y<=form.DownIndex();++y)
			for(uint8 x=form.LeftIndex();x<=form.RightIndex();++x)
				world[form.Position().y+y][form.Position().x+x]|=form[y][x];
	}
	bool CanFall(const Shape& shap)
	{
		return IsFree(SDL::Point(0,1), shap);
	}
	bool CanMoveLeft(const Shape& shap)
	{
        return IsFree(SDL::Point(-1,0), shap);
	}
	bool CanMoveRight(const Shape& shap)
	{
        return IsFree(SDL::Point(1,0), shap);
	}
	bool CanTurn(Shape shap)
	{
		shap.TurnLeft();
		return IsFree(SDL::Point(0,0), shap);
	}
	constexpr static uint16 Height()
	{
		return height;
	}
	constexpr static uint16 Widht()
	{
		return widht;
	}
	void FreeFullLines()
	{
        for(size_t y=0;y<height;++y)
		{
			bool remove=true;
			for(size_t x=0;x<widht&&remove;++x)
			{
				remove&=world[y][x];
			}
			if(remove)
			{
                for(size_t i=y;i>0;--i)
				{
					for(size_t x=0;x<widht;++x)
					{
                        world[i][x]=world[i-1][x];
					}
				}
			}
		}
	}
	void DrawOn(SDL::Renderer& rend)
	{
		constexpr SDL::Color dark_cyan(0,130,125,255);
		for(uint16 y=0;y<height;++y)
		{
			for(uint16 x=0;x<widht;++x)
			{
				if(world[y][x])
				{
					rend.Draw(SDL::Rect(x*40,y*40,40),dark_cyan);
				}
			}
		}
		for(uint16 i=1;i<=height;++i)
		{
			rend.Draw(SDL::Line(SDL::Point(0,i)*40, SDL::Point(widht, i)*40), SDL::Color(255,255,255));
		}
		for(uint16 i=1;i<=widht;++i)
		{
			rend.Draw(SDL::Line(SDL::Point(i,0)*40, SDL::Point(i, height)*40), SDL::Color(255,255,255));
		}
	}
};