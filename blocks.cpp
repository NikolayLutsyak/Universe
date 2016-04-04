#include <iostream>
#include <cmath>
#include <vector>

#define  FIELD_SIZE1 10
#define  FIELD_SIZE2 10
#define ELEMENTS_AMOUNT 10
#define GRAVITY_CONST =1
#define TIME_CONST =1

weight[ELEMENTS_AMOUNT]={1,1,1,1,1,1,1,1,1,1};

struct comp // состав
{
	float element[ELEMENTS_AMOUNT];
};

class intvector
{
	public:
	int x;
	int y;
}

class floatvector
{
	public:
	float x;
	float y;
	float abs();
}

floatvector::abs()
{
	return sqrt(x^2+y^2);
};

struct star
{
public:
 intvector coord;// координаты
 comp composition;//состав
 floatvector speed;
 void step();
};

class gas
{
public:
comp composition[ELEMENTS_AMOUNT];
floatvector speed[ELEMENTS_AMOUNT];
};

class cell
{
intvector coord; 
public:
gas gase;
vector<star> stars;
int amount_of_stars;
void init(intvector coord);
void step( float mass[FIELD_SIZE1][FIELD_SIZE2] );
};

class field
{
	private:
	cell cells[FIELD_SIZE1][FIELD_SIZE2];
	public:
	float mass[][];
	void init();
	void step();
	void print();
};
