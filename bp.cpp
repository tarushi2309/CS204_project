#include<bits/stdc++.h>
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

    regex pattern("(beq|bne|blt|ble|bgt|bge|bltu|bleu|bgtu|bgeu|jal|j|jalr|jr|ret|call|tail)");
    for(int i=0;i<size;i++)
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
        }
    }

    for(auto x:trace)
    {
        cout<<x.first<<endl;
        for(auto y:x.second)
        {
            cout<<y.first<<" ";
            cout<<y.second<<endl;
        }
        cout<<endl;
    }

    return 0;
}