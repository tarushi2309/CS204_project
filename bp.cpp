#include <bits/stdc++.h>
#include<iostream>
#include<regex>

using namespace std;

long long hexToDec(string hex) 
{   
    for (char& c : hex) {
        c = toupper(c);
    }
    int len = hex.size(); 

    long long base = 1; 
    long long dec = 0; 
 
    for (int i = len - 1; i >= 0; i--) 
    { 
        if (hex[i] >= '0' && hex[i] <= '9')
        { 
            dec += (int(hex[i]) - 48) * base; 
            base = base * 16; 
        } 
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        { 
            dec += (int(hex[i]) - 55) * base; 
            base = base * 16; 
        } 
    } 
    return dec; 
}
int always_taken(unordered_map<string,vector<pair<int,string>>> trace)
{
    int taken=0;
    for(auto itr:trace)
    {
        for(auto it:trace[itr.first])
        {
            if(it.first==1)
            taken++;
        }
    }
    return taken;
}
int one_bit(unordered_map<string,vector<pair<int,string>>> trace,unordered_map<string,bitset<1>> &one_bit_history)
{
    int acc=0;
    for(auto itr:trace)
    {
        string PC=itr.first;
        for(auto it:trace[PC])
        {
            if(it.first==one_bit_history[PC].count())
            acc++;
            else
            one_bit_history[PC]=it.first;
        }
    }
    return acc;
}
int main()
{
    ifstream file("input_file.txt");

    vector<string>input;
    string line;
    long long count = 0; 
    if (file.is_open()) 
    {  
        while (getline(file, line) && count<1000000) 
        {
            input.push_back(line);
            count++;
        } 

        file.close(); 
    }
    int size = input.size();

    unordered_map<string,vector<pair<int,string>>> trace;
    unordered_map<string,bitset<1>> one_bit_history;
    int total=0;
    regex pattern("(beq|bne|blt|ble|bgt|bge|bltu|bleu|bgtu|bgeu|jal|j|jalr|jr|ret|call|tail)");
    for(int i=0;i<size-1;i++)
    {
        if(regex_search(input[i],pattern))
        {
            string PC = input[i].substr(10,10);
            string target = input[i+1].substr(10,10);
            int branch_taken = 0;
            long long PC_dec = hexToDec(PC);
            long long target_dec = hexToDec(target);
            long long jump = target_dec-PC_dec;
            if(jump!=4) branch_taken = 1;
            trace[PC].push_back(make_pair(branch_taken,target));
            one_bit_history[PC]=0;
            total++;
        }
    }

    //always taken
    int taken1=always_taken(trace);
    double acc1=(double)taken1/total*100;
    cout<<"accuracy of always taken : "<<acc1<<endl;
    //1 bit
    int taken2=one_bit(trace,one_bit_history);
    double acc2=(double)taken2/total*100;
    cout<<"accuracy of 1-bit branch predictor : "<<acc2<<endl;
    return 0;
}
