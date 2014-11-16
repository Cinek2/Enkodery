#define enkoder_tyl_prawy  2 //obsluga przerwan
#define enkoder_przod_prawy 7
#define enkoder_tyl_lewy 3 //obsluga przerwan
#define enkoder_przod_lewy 8
#define przod 1
#define tyl -1

//Liczniki impulsow enkoderow:
volatile int licznik_P=0;
volatile int licznik_L=0;
//Zmienna kierunku obrotu silnika:
volatile int kierunek_P=przod;
volatile int kierunek_L=przod;
//Rozdzielczosc enkodera:(impulsow/obrot)
int rozdz=8;
//Predkosc katowa:(rad/s, z minusem-kola obracaja sie w tyl, z plusem-kola obracaja sie w przod)
double wP=0;//Kolo prawe.
double wL=0;//Kolo lewe.
//Predkosci liniowe kol:(m/s)
double vP=0;//Kolo prawe.
double vL=0;//Kolo lewe.
//Promien obrotu:
double Rob=0;
//Kat obrotu robota:(wzgledem ustalonego ukladu wspolrzednych)
double fi=0;
//Promien kol:(m):
const double R=0.05;
//Rozstaw kol(m):
const double D=0.3;
//Wspolrzedne w ukladzie(np. pomieszczeniu):
double x=0;
double y=0;
//Liczba pi:
const double pi=4*atan(1.);

void setup(){
   pinMode(enkoder_tyl_prawy,INPUT);
   pinMode(enkoder_przod_prawy,INPUT);
   pinMode(enkoder_tyl_lewy,INPUT);
   pinMode(enkoder_przod_lewy,INPUT);
   attachInterrupt(0,licz1,RISING);
   attachInterrupt(1,licz2,RISING);
   Serial.begin(9600);
}
void loop(){
  //Czytanie wartosci licznikow co sekundę:
  if(millis()%1000==0)
    {wP=2*pi*licznik_P/rozdz*kierunek_P;
    wL=2*pi*licznik_L/rozdz*kierunek_L;
    licznik_P=0;
    licznik_L=0;
    vP=wP*R;
    vL=wL*R;
    if(vP>vL)
      Rob=vP*D/(vP-vL);
    else if(vL>vP)
      Rob=vL*D/(vP-vL);
    fi=fi+(vP+vL)/(2*Rob)*1;
    x=x+(vP+vL)/2*cos(fi)*1;
    y=y+(vP+vL)/2*sin(fi)*1;
    Serial.print(x);
    Serial.print(y);
    }
    
}

void licz1()
{licznik_P++;
if(digitalRead(enkoder_przod_prawy)==LOW)
  kierunek_P=przod;
else if(digitalRead(enkoder_przod_prawy)==HIGH)
  kierunek_P=tyl;
}
void licz2()
{licznik_L++;
if(digitalRead(enkoder_przod_lewy)==LOW)
  kierunek_L=przod;
else if(digitalRead(enkoder_przod_lewy)==HIGH)
  kierunek_L=tyl;
}
