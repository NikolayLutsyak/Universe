#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

#define  FIELD_SIZE1 2
#define  FIELD_SIZE2 4
#define ELEMENTS_AMOUNT 10
#define GRAVITY 1
#define TIME 1
#define DIFFUSION 0.01

#define mH 1
#define mHe 4
#define mLi 7
#define mBe 9
#define mB 11
#define mC 12
#define mN 14
#define mO 16
#define mF 19
#define mNe 20

int weight[ELEMENTS_AMOUNT]={mH,mHe,mLi,mBe,mB,mC,mN,mO,mF,mNe};

struct comp // состав
{
    float element[ELEMENTS_AMOUNT];
};

class intvector
{
    public:
    int x;
    int y;
};

class floatvector
{
    public:
    float x;
    float y;
    float abs();
    float abs3();
};

float floatvector::abs()
{
    return sqrt(x*x+y*y);
};

float floatvector::abs3()
{
    return abs()*abs()*abs();
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
comp composition;
floatvector speed[ELEMENTS_AMOUNT];
};

class cell
{
private:
    intvector coord_;
public:
    float mass_;
    gas gase_;
    std::vector<star> stars;
    int amount_of_stars_;
    void init(intvector coord, gas gase);
    void step( floatvector Force[FIELD_SIZE1][FIELD_SIZE2] );
};

void cell::init(intvector coord, gas gase)
{
    coord_ = coord;
    amount_of_stars_ = 0;
    gase_ = gase;
    mass_ = 0;
    int i;
    for (i=0; i<ELEMENTS_AMOUNT; i++)
        mass_+=(gase.composition.element[i]*weight[i]);
};

class field
{
    public:
    cell cells[FIELD_SIZE1][FIELD_SIZE2];
    field();
    void init(const char * filename);
    void export_to(const char *filename);
    void step();
    void print();
};

void field::print()
{
    cout<<"got";
}

field::field()
{
    intvector coord;
    gas gase;

    int k;
    for(k=0;k<ELEMENTS_AMOUNT;k++)
    {
        gase.speed[k].x=0;
        gase.speed[k].y=0;
        gase.composition.element[k] = 0;
    }
    int i,j;
    for(i=0;i<FIELD_SIZE1;i++)
        for(j=0;j<FIELD_SIZE2;j++)
        {
            coord.x = i;
            coord.y = j;
            cells[i][j].init(coord, gase);
        }
};

void field::init(const char *filename)
{
    ifstream inFile;
    inFile.open(filename);
    intvector coord;
    gas gase;
    string temp;

    int i,j,k;
    for (i=0; i<FIELD_SIZE1; i++)
    {
        for (j=0; j<FIELD_SIZE2; j++)
        {
            coord.x = i;
            coord.y = j;

            for(k=0; k<3*ELEMENTS_AMOUNT; k++)
            {
                if(k==0)
                    inFile >> temp;//для комментов и номеров клеток

                if(k<ELEMENTS_AMOUNT)         
                    inFile >> gase.composition.element[k]; //первая строка - массы

                if((k>=ELEMENTS_AMOUNT)&&(k<2*ELEMENTS_AMOUNT))
                    inFile >> gase.speed[k%ELEMENTS_AMOUNT].x;// вторая - координата скорости по x

                if((k>=2*ELEMENTS_AMOUNT)&&(k<3*ELEMENTS_AMOUNT))
                    inFile >> gase.speed[k%ELEMENTS_AMOUNT].y; // третья - скорость по y
            }
            cells[i][j].init(coord,gase);
        }
    }
};


void field::export_to(const char * filename)
{
    int i,j,k;
    ofstream outFile;
    outFile.open(filename);
    gas gase;

    for (i=0; i<FIELD_SIZE1; i++)
    {
        for (j=0; j<FIELD_SIZE2; j++)
        {
            gase = cells[i][j].gase_;
            for(k=0; k<3*ELEMENTS_AMOUNT; k++)
            {
                if(k<ELEMENTS_AMOUNT)
                    outFile << gase.composition.element[k]<<" "; //первая строка - массы
                if (k==ELEMENTS_AMOUNT)
                    outFile<<endl;
                if((k>=ELEMENTS_AMOUNT)&&(k<2*ELEMENTS_AMOUNT))
                    outFile << gase.speed[k%ELEMENTS_AMOUNT].x<<" ";// вторая - координата скорости по x
                if(k==2*ELEMENTS_AMOUNT)
                    outFile<<endl;
                if((k>=2*ELEMENTS_AMOUNT)&&(k<3*ELEMENTS_AMOUNT))
                    outFile << gase.speed[k%ELEMENTS_AMOUNT].y<<" "; // третья - скорость по y
            }
            outFile<<endl<<endl;
        }
    }
};

int main(){

    field  f = field();

    string in = "input.txt";
    string out = "output.txt";

    f.init(in.c_str());
    f.export_to(out.c_str());
    return 0;
}

//Пофиксить считывание, если файл кончился.
//Совпадение ввода ввывода
//Синхронизацию.
//Экземпляры 10 на 10 две штуки разных.
