#pragma once
class Location
{
	private:

	int locdata[2][2];

	public:

	Location()
	{
		locdata[0][1] = -1;
		locdata[0][0] = -1;
		locdata[1][1] = -1;
		locdata[1][0] = -1;
	}

	Location(int xfrom, int yfrom, int xto, int yto)
	{
		locdata[0][1] = xfrom;
		locdata[0][0] = yfrom;
		locdata[1][1] = xto;
		locdata[1][0] = yto;
	}

	void assignAll( int xfrom = -1, int yfrom = -1, int xto = -1, int yto = -1)
	{
		locdata[0][1] = xfrom;
		locdata[0][0] = yfrom;
		locdata[1][1] = xto;
		locdata[1][0] = yto;
	}

	int fromx()
	{
		return locdata[0][1];
	};
	int fromy()
	{
		return locdata[0][0];
	};
	int tox()
	{
		return locdata[1][1];
	};
	int toy()
	{
		return locdata[1][0];
	};

	bool isAssigned( int temp )
	{
		return temp != -1;
	}

	void operator= ( Location *input )
	{
		input->locdata[0][1] = fromx();
		input->locdata[0][0] = fromy();
		input->locdata[1][1] = tox();
		input->locdata[1][0] = toy();
	}
};