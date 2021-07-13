#pragma once

#include <tuple>

using namespace std;

class Shape
{
public:
	using Form=bool[4][4];
private:
	static void CopyArray(const Form& src, Form& dst)
	{
		for(size_t y=0;y<4;++y)
		{
			for(size_t x=0;x<4;++x)
			{
				dst[y][x]=src[y][x];
			}
		}
	}
	Form form={{false}};
	uint8 upindex;
	uint8 downindex;
	uint8 leftindex;
	uint8 rightindex;
	SDL::Point pos;
	void ComputeIndex()
	{
		downindex=0;
		rightindex=0;
		upindex=3;
		leftindex=3;
		for(size_t y=0;y<4;++y)
		{
			for(size_t x=0;x<4;++x)
			{
				if(form[y][x])downindex=y;
				if(form[y][x]&&y<upindex)upindex=y;
				if(form[y][x]&&x>rightindex)rightindex=x;
				if(form[y][x]&&x<leftindex)leftindex=x;
			}
		}
	}
public:
	Shape(const Form& init, SDL::Point pos)
	{
		this->pos=pos;
		CopyArray(init, form);
		ComputeIndex();
	}
	Shape& operator=(const Form& init)
	{
		CopyArray(init, form);
		ComputeIndex();
		return *this;
	}
	void GoDown()
	{
		++pos.y;
	}
	void GoLeft()
	{
		--pos.x;
	}
	void GoRight()
	{
        ++pos.x;
	}
	void TurnLeft()
	{
		Form tmp_array;
		CopyArray(form, tmp_array);
		for(size_t y=0;y<4;++y)
			for(size_t x=0;x<4;++x)
				form[x][3-y]=tmp_array[y][x];
		ComputeIndex();
	}
	const bool* operator[](size_t i)const
	{
		return form[i];
	}
	const Form& GetArray()const
	{
        return form;
	}
	uint8 DownIndex()const
	{
		return downindex;
	}
	uint8 UpIndex()const
	{
		return upindex;
	}
	uint8 RightIndex()const
	{
		return rightindex;
	}
	uint8 LeftIndex()const
	{
		return leftindex;
	}
	SDL::Point Position()const
	{
		return pos;
	}
	void GoTo(const SDL::Point& newpos)
	{
		pos=newpos;
	}
	void DrawOn(SDL::Renderer& rend)const
	{
		constexpr SDL::Color red(255,0,0,255);
		for(uint8 y=0;y<4;++y)
		{
			for(uint8 x=0;x<4;++x)
			{
				if(form[y][x])
				{
					rend.Draw(SDL::Rect(SDL::Point(pos.x+x,pos.y+y)*40,40,40), red);
				}
			}
		}
	}
};