#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

#define  FIELD_SIZE1 4
#define  FIELD_SIZE2 4
#define ELEMENTS_AMOUNT 10
#define GRAVITY 1
#define TIME 1
#define DIFFUSION 0.01
#define SLEEP_STEP 100
#define SLEEP_ALL 1000
#define SIGMA 2
#define SIZE 10

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

struct color
{
    int r;
    int g;
    int b;
    int br;
};

color colors[ELEMENTS_AMOUNT]={{0,0,200, 255},
                               {200,200,0,150},
                               {150,150,150,255},
                               {220,220,220,255},
                               {90,10,10,255},
                               {10,10,10, 255},
                               {92,250,242,255},
                               {118,255,122,255},
                               {255,233,16,255},
                               {51,204,255,255}};

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

gas zero_gase;

class cell
{
private:
    intvector coord_;
public:
    float mass_;
    gas gase_;
    color c;
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
    int i,r,g,b,br, m;
    r=0;
    g=0;
    b=0;
    br=0;
    m=0;
    for (i=0; i<ELEMENTS_AMOUNT; i++)
    {
        mass_+=(gase.composition.element[i]*weight[i]);
        r += gase_.composition.element[i]*colors[i].r;
        g += gase_.composition.element[i]*colors[i].g;
        b += gase_.composition.element[i]*colors[i].b;
        br += gase_.composition.element[i]*colors[i].br;
        m+=gase.composition.element[i];
    }
    c.r=r/m;
    c.g=g/m;
    c.b=b/m;
    c.br=br/m;
}

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
void field::step()
{
    cout<<"Шажок"<<endl;
}

void field::print()
{
    //Здесь будет код Эдика...
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
    int flag = 1;

    int i,j,k;
    for (i=0; i<FIELD_SIZE1; i++)
    {
        if(!flag)
            break;
        for (j=0; j<FIELD_SIZE2; j++)
        {
            for(k=0; k<3*ELEMENTS_AMOUNT; k++)
            {
                if(k==0)
                {
                    if(!(inFile >> coord.x))
                        flag = 0;//для комментов и номеров клеток
                    inFile >> coord.y;
                }

                if(k<ELEMENTS_AMOUNT)
                    inFile >> gase.composition.element[k]; //первая строка - массы

                if((k>=ELEMENTS_AMOUNT)&&(k<2*ELEMENTS_AMOUNT))
                    inFile >> gase.speed[k%ELEMENTS_AMOUNT].x;// вторая - координата скорости по x

                if((k>=2*ELEMENTS_AMOUNT)&&(k<3*ELEMENTS_AMOUNT))
                    inFile >> gase.speed[k%ELEMENTS_AMOUNT].y; // третья - скорость по y
            }
            if (flag)
                cells[i][j].init(coord,gase);
            else break;
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
                if (k==0)
                    outFile<<i+1<<" "<<j+1<<endl;
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

void paint(field f, int flag)
{
    /* какой-то код*/
    cout<<"Рисунок"<<endl;

    return;
}

int main(){

    field  f = field();
    string a;

    string in = "input.txt";
    string out = "output.txt";

    f.init(in.c_str());
    f.export_to(out.c_str());

    /*int i;

    for(i=0;i<5;i++)
    {
        using namespace std::chrono;

        thread thr2 = thread(paint,f, 0);
        thr2.join();

        auto start = high_resolution_clock::now();

        f.step();

        auto end = high_resolution_clock::now();
        duration<double, std::milli> elapsed = end-start;
        int duration = elapsed.count();

        while(duration<SLEEP_ALL)
        {
            this_thread::sleep_for(chrono::milliseconds(SLEEP_STEP));
            duration+=SLEEP_STEP;
        }

    }*/

    return 0;
}


//Экземпляры 10 на 10 две штуки разных.
