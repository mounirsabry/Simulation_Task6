#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

const int Experiment_size = 5 ;

double Generate_normal(double mean, double sigma) ;     // dealing with seconds
void Avg (vector<double> arr) ;
int Available_salad ();
int Available_soup ();

vector<double> time_with_Soup ; // time spent
vector<double> time_without_soup;
double Salad_server [4] = {0.0, 0.0, 0.0, 0.0}, Soup_server [2] = {0.0, 0.0} ;

int main()
{
    bool take_soup = 0;
    double Pre_AT = 0, AT = 0, IAT, Start_cash,  pre_Cash_CT = 0, Cashier_time, leave_cashier = 0, salad_time, Soup_time  ;
    double cash_WT, service_WT, Arrive_at_server, salad_WT, soup_WT;
    double temp = 0, soup_CT = 0, salad_CT = 0, start_Salad, start_soup;
    int available_salad, available_soup ;

    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_real_distribution<double> dem(0.0, 1.0);
    for (int i = 0 ; i < Experiment_size ; i++)
    {
//        cout << "---------------------" << Salad_server[0]/60.0 << " / " << Salad_server[1]/60.0
        //<< " / " << Salad_server[2]/60.0 << " / " << Salad_server[3]/60.0 << "---------------------\n" ;
        double r = dem(gen);
        if(r <= 0.6)
            take_soup = true ;
        else
            take_soup = false ;
        IAT = Generate_normal(60, 12) ;
        AT = IAT + Pre_AT ;
        Pre_AT = AT ;
        Start_cash = max(pre_Cash_CT, AT) ; // in case eny wslt b3d elly 2bly ma 5ls
        cash_WT = Start_cash - AT ;
        Cashier_time = Generate_normal(40,10) ;
        leave_cashier = Start_cash + Cashier_time ;
        temp = pre_Cash_CT ;
        pre_Cash_CT = leave_cashier ;
        Arrive_at_server = leave_cashier ;

        if(i == 0)
        {
            for (int j = 0;  j < 4 ; j++)
            {
                Salad_server[j] = leave_cashier ;
            }
        }
        available_salad = Available_salad();
        start_Salad = max(Salad_server[available_salad], Arrive_at_server) ;
//        cout << "----- Available salad is : " << available_salad << endl;
//        start_Salad = Salad_server[available_salad] ;
        salad_WT = start_Salad - Arrive_at_server;
        salad_time = Generate_normal(120,20);
        salad_CT = start_Salad + salad_time;
        Salad_server[available_salad] = salad_CT;
        if (i == 0)
        {
            for (int j = 0 ; j < 2 ; j++)
            {
                Soup_server[j] = salad_CT;
            }
        }


        if (take_soup)
        {
            Soup_time = Generate_normal(60,15) ;
            available_soup = Available_soup();
            start_soup = max(Soup_server[available_soup], salad_CT);
            soup_WT = start_soup - salad_CT ;

            soup_CT = salad_CT + soup_WT + Soup_time;
            Soup_server[available_soup] = soup_CT;
            time_with_Soup.push_back( soup_CT - AT );

        }
        else
        {
            time_without_soup.push_back( salad_CT - AT )  ;

        }

//        cout <<"------------------------------------------\n" << "1- cust " << i+1 << " arrived at " << AT/60.0 << endl
//             << "2- he waited bfore cashier : " << cash_WT/60.0 << " ,, and started cash at : " << Start_cash/60.0 << endl
//             << "3- he started salad at : " << start_Salad /60.0<< endl
//             << "4- he took " << Cashier_time/60.0 << " at Cashier"
//             << endl << "5- waited for salad : " << salad_WT/60.0 << " ,, and had salad for " << salad_time/60.0 << endl
//             << "6- he left salad at : " << salad_CT/60.0 << endl;
//        if (take_soup)
//            cout << "7- with soup , he waited : " << soup_WT/60.0 << "\n8- he started soup at : " << start_soup/60.0 <<
//                 " and took : " << Soup_time/60.0 << endl <<
//                 "9- so total time is : " << time_with_Soup.back()/60.0
//                 << " ,, he left soup at : " << soup_CT/60.0 ;
//        else
//            cout << "\n7- without soup , he took total" << time_without_soup.back()/60.0 << endl
//                 << "8- he left at : " << salad_CT/60.0;
//        cout << endl;


    }
    cout << "\nWhen taking soup : \n" ;
    Avg(time_with_Soup) ;
    cout << "\nWhen no Soup taken\n" ;
    Avg(time_without_soup) ;

    return 0;
}

double Generate_normal(double mean, double sigma)
{
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    normal_distribution<double> norm_distribution(mean,sigma);
    double number = norm_distribution(gen);
    return number ;
}

void Avg (vector<double> arr)
{
    double total = 0 ;
    double minutes = 0, seconds = 0 ;
    for (int i = 0 ; i < arr.size() ; i++)
    {
        total += arr[i] ;
    }
    double avg = total / arr.size() ;
    minutes =(int) avg / 60 ;
    seconds = ceil( avg - minutes * 60 ) ;
    cout << "Average time is " << minutes << " minutes ,, " << seconds << " seconds\n" ;
}

int Available_salad ()
{
    double Minimum = INT_MAX ;
    int available_soon ;
    for (int i = 0 ; i < 4 ; i++)
    {
        if (Minimum > Salad_server[i])
        {
            Minimum = Salad_server[i] ;
            available_soon = i ;
        }

    }
    return available_soon ;

}

int Available_soup ()
{
    double Minimum = INT_MAX ;
    int available_soon = 0;
    for (int i = 0 ; i < 2 ; i++)
    {
        if (Minimum > Salad_server[i])
        {
            Minimum = Salad_server[i] ;
            available_soon = i ;
        }

    }
    return available_soon ;
}