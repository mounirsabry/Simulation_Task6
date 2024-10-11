#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include<vector>

using namespace std;

double Generate_normal(double mean , double sigma) ;    // dealing with seconds
void Avg (vector<double> arr) ;
const int Experiment_size = 10 ;
vector<double> time_with_Soup ;
vector<double> time_without_soup;

int main()
{
    bool take_soup = 0 ;
    double Pre_AT = 0 , AT = 0 , IAT  , Start_cash ,  pre_Cash_CT = 0 , Cashier_time , leave_cashier = 0 , salad_time , Soup_time  ;
    double temp = 0;

    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_real_distribution<double> dem(0.0, 1.0);
    for (int i = 0 ; i < Experiment_size ; i++) {
        double r = dem(gen) ;
        if(r <= 0.6)   take_soup = true ;
        else take_soup = false ;
        IAT = Generate_normal(60 , 12) ;
        AT = IAT + Pre_AT ;
        Pre_AT = AT ;
        Start_cash = max(pre_Cash_CT , AT) ; // in case eny wslt b3d elly 2bly ma 5ls
        Cashier_time = Generate_normal(40,10) ;
        leave_cashier = Start_cash + Cashier_time ;
        temp = pre_Cash_CT ;
        pre_Cash_CT = leave_cashier ;

        salad_time = Generate_normal(120,20) ;
        Soup_time = Generate_normal(60,15) ;
        time_without_soup .push_back(  Start_cash - AT  + Cashier_time + salad_time )  ;

        if (take_soup)  {
           time_with_Soup.push_back(  Start_cash - AT  + Cashier_time + salad_time +Soup_time);
        }
//        cout << "cust " << i+1 << " arrived at " << AT << endl
//        << "previous cust finished at " << temp << " .. but he took " << leave_cashier - Start_cash << " at Cashier"
//        << endl << "and had salad for " << salad_time << endl;
//        if (take_soup) cout << "\nwith soup  " << Soup_time << " , he took " << time_with_Soup[i] << endl;
//        else  cout << "\nwithout soup , he took " << time_without_soup[i] << endl;
//        cout << endl;
    }
    cout << "\nWhen taking soup : \n" ; Avg(time_with_Soup) ;
    cout << "\nWhen no Soup taken\n" ; Avg(time_without_soup) ;

    return 0;
}

double Generate_normal(double mean , double sigma)
{
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    normal_distribution<double> norm_distribution(mean,sigma);
    double number = norm_distribution(gen);
    return number ;
}

void Avg (vector<double> arr) {
    double total = 0 ;
    double minutes = 0 , seconds = 0 ;
    for (int i = 0 ; i < arr.size() ; i++){
        total += arr[i] ;
    }
    double avg = total / arr.size() ;
    minutes =(int) avg / 60 ;
    seconds = ceil( avg - minutes * 60 ) ;
    cout << "Average time is " << minutes << " minutes ,, " << seconds << " seconds\n" ;
}