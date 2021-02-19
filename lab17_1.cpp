#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filepath , vector<string> &names , vector<int> &scores , vector<char> &grades){
    ifstream source(filepath);
    string text;
    while(getline(source , text)){
        char ctext[1000]; 
        strcpy(ctext , text.c_str());
        char format[] = "%[^:]: %d %d %d";
        char name[1000]; 
        int a , b , c , sum ;
        sscanf(ctext , format , name , &a , &b , &c);
        sum = a + b + c;
        names.push_back(name);
        scores.push_back(sum); 
        if(sum >= 80)
            grades.push_back('A');
        else if(sum >= 70)
            grades.push_back('B');
        else if(sum >= 60)
            grades.push_back('C');
        else if(sum >= 50)
            grades.push_back('D');
        else
            grades.push_back('F');
    }
}

void getCommand(string &command , string &key){
    string line;
    cout << "Please input your command: ";
    getline(cin , line);
    int L = line.length();
    int find = line.find_first_of(" ");
    command = line.substr(0 , find);
    if(find == -1)
        key = "BOBO";
    else
        key = line.substr(find + 1 , L - find);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    for(int i = 0 ; i < names.size() ; ++i){
        if(key == toUpperStr(names[i])){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(int i = 0 ; i < names.size() ; ++i){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);

    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
