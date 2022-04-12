#pragma once
class Location
{
	private:

	int locdata[2][2];

	public:

	//constructors
	
	Location( int xfrom = -1, int yfrom = -1, int xto = -1, int yto = -1 )
	{
		locdata[0][1] = xfrom;
		locdata[0][0] = yfrom;
		locdata[1][1] = xto;
		locdata[1][0] = yto;
	}

	Location( const Location &toCopyFrom )
	{
		locdata[0][1] = toCopyFrom.locdata[0][1];
		locdata[0][0] = toCopyFrom.locdata[0][0];
		locdata[1][1] = toCopyFrom.locdata[1][1];
		locdata[1][0] = toCopyFrom.locdata[1][0];
	}



	void assignAll( int xfrom = -1, int yfrom = -1, int xto = -1, int yto = -1)
	{
		locdata[0][1] = xfrom;
		locdata[0][0] = yfrom;
		locdata[1][1] = xto;
		locdata[1][0] = yto;
	}


	//getters:

	//gets x location that piece is coming from
	int fx()
	{
		return locdata[0][1];
	};
	//gets y location that piece is coming from
	int fy()
	{
		return locdata[0][0];
	};
	//gets x location that piece is going to
	int tx()
	{
		return locdata[1][1];
	};
	//gets y location that piece is going to
	int ty()
	{
		return locdata[1][0];
	};


	//helpers
	bool isAssigned( int temp )
	{
		return temp != -1;
	}

	bool inBounds(std::string toorfrom)//true for checking to, false for checking from
	{
		if ( toorfrom == "FROM" )
		{
			return (
				locdata[0][1] > -1 && locdata[0][1] < 8 &&
				locdata[0][0] > -1 && locdata[0][0] < 8
				);

		}
		if( toorfrom == "TO" )
		{
			return (
				locdata[1][1] > -1 && locdata[1][1] < 8 &&
				locdata[1][0] > -1 && locdata[1][0] < 8
				);
		}
		return false;
	}

	//copy operator reassignment
	void operator= ( Location *input )
	{
		input->locdata[0][1] = fx();
		input->locdata[0][0] = fy();
		input->locdata[1][1] = tx();
		input->locdata[1][0] = ty();
	}
};