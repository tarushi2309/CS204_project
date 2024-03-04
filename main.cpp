#include <iostream>
#include <unordered_map>
#include <fstream> 
#include <string> 
using namespace std;
int main()
{
    unordered_map<string,vector<string>>R_format;
    unordered_map<string,vector<string>>S_format;
    unordered_map<string,vector<string>>U_format;

    R_format["add"]={"0110011","000","0000000"};
    R_format["and"]={"0110011","111","0000000"};
    R_format["or"]={"0110011","110","0000000"};
    R_format["sll"]={"0110011","001","0000000"};
    R_format["slt"]={"0110011","010","0000000"};
    R_format["sra"]={"0110011","101","0100000"};
    R_format["srl"]={"0110011","101","0000000"};
    R_format["sub"]={"0110011","000","0100000"};
    R_format["xor"]={"0110011","100","0000000"};
    R_format["mul"]={"0110011","000","0000001"};
    R_format["div"]={"0110011","100","0000001"};
    R_format["rem"]={"0110011","110","0000001"};

    S_format["sb"]={"0100011","000"};
    S_format["sw"]={"0100011","010"};
    S_format["sd"]={"0100011","011"};
    S_format["sh"]={"0100011","001"};

    U_format["auipc"]={"0010111"};
    U_format["lui"]={"0110111"};

    ifstream file("input_file.asm"); 
    string line; 
    vector<string>input;
    unordered_map<string,int>label_pc;
    if (file.is_open()) 
    {  
        int c=0;
        while (getline(file, line)) 
        {
            c++;
            input.push_back(line);
            string label="";
            for(int i=0;i<line.length();i++)
            {
                if(line[i]!=' ')
                {
                    label=label+line[i];
                }
                else
                {
                    if(R_format.find(label)==R_format.end()&&S_format.find(label)==S_format.end()&&SB_format.find(label)==SB_format.end()&&I_format.find(label)==I_format.end()&&U_format.find(label)==U_format.end()&&UJ_format.find(label)==UJ_format.end()&&label!=".data"&&label!=".text")
                    {
                        label_pc[label]=c;
                    }
                    break;

                }
            }
        }  
        file.close(); 
    } 

}
