#include <bits/stdc++.h>
#include<iostream>
#include<regex>
#include<string.h>

using namespace std;

unordered_map<string,pair<string,string>> btb_taken;
unordered_map<string,pair<string,string>> btb_not_taken;
unordered_map<string,pair<string,string>> btb_one_bit;
unordered_map<string,pair<string,string>> btb_two_bit;

unordered_map<string,bool> history_table;

unordered_map<string,bool> one_bit_state;
unordered_map<string,int> two_bit_state;

int total=0;
int not_taken = 0;
int taken = 0;
int accuracy_1bit = 0;
int accuracy_2bit = 0;

long long hexToDec(string hex) 
{   
    for (char& c : hex)
    {
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

string decToHex(long long dec)
{
    string hex = "";
    int rem;
    char ch;
    while (dec != 0)
    {
        rem = dec % 16;
        if (rem < 10)
        {
            ch = rem + 48;
        }
        else
        {
            ch = rem + 55;
        }
        hex += ch;
        dec = dec / 16;
    }
    if (hex == "")
    {
        hex += '0';
    }
    reverse(hex.begin(), hex.end());
    return ("0x" + hex);
}

vector<string> split(string s)
{
    vector<string> output;
    string token;

    istringstream iss(s);

    while (iss >> token)
    {
        output.push_back(token);
    }

    return output;
}

void always_taken(string curr_instruction, string next_instruction)
{
    vector<string> tokens1 = split(curr_instruction);
    vector<string> tokens2 = split(next_instruction);
    string PC = tokens1[2];
    string target_PC = tokens2[2];
    int actual_jump = hexToDec(target_PC) - hexToDec(PC);
    string label = tokens1[tokens1.size()-1];
    int label_jump;
    if(label[1]=='x')
    {
        label_jump = hexToDec(label);
    }
    else
    {
        label_jump = stoi(label);
    }
    if(tokens1[tokens1.size()-2] == "-") label_jump *= -1;
    if(actual_jump == label_jump) taken++;
    btb_taken[PC] = {"TAKEN",decToHex(hexToDec(PC) + label_jump)};
}

void always_not_taken(string curr_instruction, string next_instruction)
{
    vector<string> tokens1 = split(curr_instruction);
    vector<string> tokens2 = split(next_instruction);
    string PC = tokens1[2];
    string target_PC = tokens2[2];
    int actual_jump = hexToDec(target_PC) - hexToDec(PC);
    string label = tokens1[tokens1.size()-1];
    int label_jump;
    if(label[1]=='x')
    {
        label_jump = hexToDec(label);
    }
    else
    {
        label_jump = stoi(label);
    }
    if(tokens1[tokens1.size()-2] == "-") label_jump *= -1;
    if(actual_jump != label_jump) not_taken++;
    btb_not_taken[PC] = {"NOT TAKEN",decToHex(hexToDec(PC) + 4)};
}

void one_bit_predictor(string curr_instruction, string next_instruction)
{
    vector<string> tokens1 = split(curr_instruction);
    vector<string> tokens2 = split(next_instruction);
    string PC = tokens1[2];
    string target_PC = tokens2[2];
    int actual_jump = hexToDec(target_PC) - hexToDec(PC);
    string label = tokens1[tokens1.size()-1];
    int label_jump;
    if(label[1]=='x')
    {
        label_jump = hexToDec(label);
    }
    else
    {
        label_jump = stoi(label);
    }
    if(tokens1[tokens1.size()-2] == "-") label_jump *= -1;

    if(one_bit_state.find(PC)==one_bit_state.end()) one_bit_state[PC] = false;
    
    bool state = one_bit_state[PC];
    if(state)
    {
        if(actual_jump == label_jump)
        {
            accuracy_1bit++;
        }
        else
        {
            one_bit_state[PC] = false;
        }
    }
    else
    {
        if(actual_jump != label_jump)
        {
            accuracy_1bit++;
        }
        else
        {
            one_bit_state[PC] = true;
        }
    }
    if(one_bit_state[PC]) btb_one_bit[PC] = {"TAKEN",decToHex(hexToDec(PC) + label_jump)};
    else btb_one_bit[PC] = {"NOT TAKEN",decToHex(hexToDec(PC) + 4)};
}

void two_bit_predictor(string curr_instruction, string next_instruction)
{
    vector<string> tokens1 = split(curr_instruction);
    vector<string> tokens2 = split(next_instruction);
    string PC = tokens1[2];
    string target_PC = tokens2[2];
    int actual_jump = hexToDec(target_PC) - hexToDec(PC);
    string label = tokens1[tokens1.size()-1];
    int label_jump;
    if(label[1]=='x')
    {
        label_jump = hexToDec(label);
    }
    else
    {
        label_jump = stoi(label);
    }
    if(tokens1[tokens1.size()-2] == "-") label_jump *= -1;

    if(two_bit_state.find(PC)==two_bit_state.end()) two_bit_state[PC] = 0;

    int state = two_bit_state[PC];
    if(state>1)
    {
        if(actual_jump == label_jump)
        {
            accuracy_2bit++;
            two_bit_state[PC] = (state == 3)? 3 : state + 1;
        }
        else
        {
            two_bit_state[PC] -= 1;
        }
    }
    else
    {
        if(actual_jump != label_jump)
        {
            accuracy_2bit++;
            two_bit_state[PC] = (state == 0)? 0 : state - 1;
        }
        else
        {
            two_bit_state[PC] += 1;
        }
    }
    if(two_bit_state[PC] > 1) btb_two_bit[PC] = {"TAKEN",decToHex(hexToDec(PC) + label_jump)};
    else btb_two_bit[PC] = {"NOT TAKEN",decToHex(hexToDec(PC) + 4)};
}

void branch_history(string curr_instruction, string next_instruction)
{
    vector<string> tokens1 = split(curr_instruction);
    vector<string> tokens2 = split(next_instruction);
    string PC = tokens1[2];
    string target_PC = tokens2[2];
    int actual_jump = hexToDec(target_PC) - hexToDec(PC);
    string label = tokens1[tokens1.size()-1];
    int label_jump;
    if(label[1]=='x')
    {
        label_jump = hexToDec(label);
    }
    else
    {
        label_jump = stoi(label);
    }
    if(tokens1[tokens1.size()-2] == "-") label_jump *= -1;
    history_table[PC] = (actual_jump == label_jump);
}

void display(string simulation)
{
    if(simulation == "always_taken")
    {
        double accuracy =  (taken/(double)total) * 100;
        cout << "Prediction Method : " << simulation << endl;
        cout << "\nAccuracy : " << accuracy << "%" << endl;

        cout << "\nBranch Target Buffer for each Instruction (pc)" << endl;
        cout << "\nPC             Action           Target PC"<< endl;

        for (auto x : btb_taken)
        {
            cout<<x.first<<"      "<<x.second.first<<"      "<<x.second.second<<endl;
        }
    }
}

int main()
{
    string input_file = "";
    cout<<"Enter file name: ";
    cin>>input_file;
    ifstream file(input_file);

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

    regex pattern("(beq|bne|blt|ble|bgt|bge|bltu|bleu|bgtu|bgeu)");
    for(int i=0;i<size-2;i++)
    {
        if(regex_search(input[i],pattern))
        {
            always_taken(input[i],input[i+1]);
            always_not_taken(input[i],input[i+1]);
            one_bit_predictor(input[i],input[i+1]);
            two_bit_predictor(input[i],input[i+1]);
            branch_history(input[i],input[i+1]);
            total++;
        }
    }
    display("always_taken");
    display("always_not_taken");
    display("one_bit");
    display("two_bit");

    return 0;
}
