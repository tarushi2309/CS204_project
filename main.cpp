#include <iostream>
#include <unordered_map>
#include <fstream> 
#include <string> 
#include <ctype.h>
#include <bitset>
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

    //creating an unordered_map to store I_format basic instruction codes (opcode and funct3)
    unordered_map<string,vector<string>> I_format;
    //adding addi instruction 
    vector<string> addi;
    addi.push_back("0010011");//opcode
    addi.push_back("000");//funct3
    I_format["addi"] = addi;

    //adding andi instruction 
    vector<string> andi;
    andi.push_back("0010011");//opcode
    andi.push_back("111");//funct3
    I_format["andi"] = andi;

    //adding ori instruction 
    vector<string> ori;
    ori.push_back("0010011");//opcode
    ori.push_back("110");//funct3
    I_format["ori"] = ori;

    //adding lb instruction 
    vector<string> lb;
    lb.push_back("0000011");//opcode
    lb.push_back("000");//funct3
    I_format["lb"] = lb;

    //adding lh instruction 
    vector<string> lh;
    lh.push_back("0000011");//opcode
    lh.push_back("001");//funct3
    I_format["lh"] = lh;

    //adding lw instruction 
    vector<string> lw;
    lw.push_back("0000011");//opcode
    lw.push_back("010");//funct3
    I_format["lw"] = lw;

    //adding ld instruction 
    vector<string> ld;
    ld.push_back("0000011");//opcode
    ld.push_back("011");//funct3
    I_format["ld"] = ld;

    //adding jalr instruction 
    vector<string> jalr;
    jalr.push_back("1100111");//opcode
    jalr.push_back("000");//funct3
    I_format["jalr"] = jalr;

    /*
        for(auto x: I_format)
    {
        cout<<x.first<<endl;
        for(auto y: x.second)
        {
            cout<<y<<endl;
        }
    }
    */

    //creating an unordered_map to store SB_format basic instruction codes (opcode and funct3)
    unordered_map<string,vector<int>>SB_format;

    //adding sb instruction 
    vector<string> sb;
    sb.push_back("0100011");//opcode
    sb.push_back("000");//funct3
    I_format["sb"] = sb;

    //adding sh instruction 
    vector<string> sh;
    sh.push_back("0100011");//opcode
    sh.push_back("001");//funct3
    I_format["sh"] = sh;

    //adding sw instruction 
    vector<string> sw;
    sw.push_back("0100011");//opcode
    sw.push_back("010");//funct3
    I_format["sw"] = sw;

    //adding sd instruction 
    vector<string> sd;
    sd.push_back("0100011");//opcode
    sd.push_back("011");//funct3
    I_format["sd"] = sd;

    //creating an unordered_map to store UJ_format basic instruction codes (opcode)
    unordered_map<string,string>UJ_format;
    UJ_format["jal"] = "1101111";

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
    unordered_map<string,vector<string>> I_format;
    vector<string> input;
    int size = input.size();
    string data = ".data";
    string text = ".text";
    auto it_data = find(input.begin(),input.end(),data);
    auto it_text = find(input.begin(),input.end(),text);
    int start = 0;
    //finding the text segment
    if(it_data != input.end())
    {
        int i = 0;
        while(input[i]!=text) i++;
        start = i+1;
    }
    else if (input[start]==text) start = start+1;
    // program counter
    int PC = 0;
    //reading the instructions line by line
    for(int i=start;i<size;i++)
    {
        string line = input[i];
        int j =0;
        if(line[j] == ' ') j++;
        string instruction = "";
        while(line[j]!= ' ')
        {
            instruction += line[j];
            j++;
        }
        if(I_format.find(instruction)!=I_format.end())
        {
            //getting opcode
            string opcode = I_format[instruction][0];

            //getting funct3
            string funct3 = I_format[instruction][1];

            //getting rs1
            j++;
            int reg = 0;
            while(line[j]!=',')
            {
                if(isdigit(line[j]))
                {
                    reg = reg*10 + (int(line[j]-'0'));
                }
                j++;
            }
            bitset<5> rs1_bits(reg);
            string rs1 = rs1_bits.to_string();

            //getting rd
            j++;
            reg = 0;
            while(line[j]!=',')
            {
                if(isdigit(line[j]))
                {
                    reg = reg*10 + (int(line[j]-'0'));
                }
                j++;
            }
            bitset<5> rd_bits(reg);
            string rd = rd_bits.to_string();

            //getting immediate value
            j++;
            int immed = 0;
            int neg = 0;
            while(line[j]!='\n')
            {
                if(isdigit(line[j]))
                {
                    immed = immed*10 + (int(line[j]-'0'));
                }
                if(line[j]=='-')
                {
                    neg = 1;
                }
                j++;
            }
            if(neg==1) immed *= -1;
            
        }

    }
    return 0;
}
