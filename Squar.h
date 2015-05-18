#pragma once
class Squar
{
	public:
		Squar ( );
		~Squar ( );

		struct Color
		{ 
			int R, G, B;
		};

		void Draw ( int x1, int y1, int x2, int y2, Color col, bool token = false );

	private:

};

