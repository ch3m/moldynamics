/**      
 * A detailed description of the class.
 * 
 * @short A short description of the class
 * @author Name of the author
 * @version version
 * @since version
 * @see something
 */

#ifndef TIMER_h
#define TIMER_h
#include <ctime>
#include <iostream>
#include <time.h>

#define SECONDS 1
#define MINUTES 2
#define HOURS   3

using namespace std;

class Timer{
public:
    //Put Public variables

    //Constructors & destructor
    Timer() {
      Timer1Units = SECONDS;
    }
    ~Timer(void) {
    }

    //some funtion
    void StartTimer1() {
        ST1=clock();
    }
    void EndTimer1(int units) {
        ET1=clock();
        Timer1Units = units;
        Timer1 = TimeDiff(ET1,ST1);
    }
    double TimeDiff(clock_t e, clock_t b){
        //regresa en segundos, minutos u horas, si la opcion no es valida regresa segundos
        double ticks = e - b;
        double diff = ticks / CLOCKS_PER_SEC;
        switch(Timer1Units){
                case SECONDS: return diff;
                case MINUTES: return diff / 60;
                case HOURS  : return diff / 60 / 60;
                default     : return diff;
        }
    }
    void PrintT1(){
        switch(Timer1Units){
        case SECONDS:   cout << "Elepsed Time:\t\t" << Timer1 << " (seg)" << endl;
                            break;
        case MINUTES:   cout << "Elepsed Time:\t\t" << Timer1 << " (min)" << endl;
                    break;
        case HOURS  :   cout << "Elepsed Time:\t\t" << Timer1 << " (hrs)" << endl; 
                    break;
        default     :   cout << "Elepsed Time:\t\t" << Timer1 << " (seg)" << endl;
                    break;
        }
    }
    void PrintDate(){
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        cout << "The current date/time is: " << asctime (timeinfo);
    }

protected:
private:
    clock_t ST1;
    clock_t ET1;  
    int Timer1Units;
    double Timer1;
};

#endif
