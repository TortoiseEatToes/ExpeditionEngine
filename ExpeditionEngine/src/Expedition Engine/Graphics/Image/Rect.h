#ifndef Rect_h
#define Rect_h

class Rect
{
public:
	// Constructors
	Rect(float x, float y, float width, float height);
	Rect();
	//Rect(Rect&&) = delete;
	//Rect(const Rect&) = delete;
	//const Rect& operator = (Rect&&) = delete;
	//const Rect& operator = (const Rect&) = delete;
	~Rect();

	// Clear method
	void clear();

	// Structure data, public
	float x;
	float y;
	float width;
	float height;
};

#endif Rect_h