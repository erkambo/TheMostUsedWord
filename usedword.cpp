#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <map>
#include <vector>
int main(){
   
    //Initializes object f. Change filename to suit your needs.
    std::fstream f("pg100.txt");
    
    //Create string line, use getline function to get input from f
    //and output it line by line
    std::string line; 

    //Create new map, which has the key as a string, and the amount as word_count.
    std::map<std::string, int > word_count;
    while(std::getline(f,line)){
       
        //Want to access each word individually
        auto split = line | std::ranges::views::split(' ');

        
        for (auto m: split){
            //Create a new string from the range  obtained from the split variable.
            auto mstr = std::string(m.begin(), m.end());
        
            if(word_count.find(mstr) != word_count.end()){ //Found Word
                word_count[mstr] += 1;
            }
            else{
                word_count[mstr] = 1; //set to 1 if there is only 1 of the word.
            }
        }
    }


        std::vector < std::pair<std::string,int>> vp;
        //Push all the elements in map to vector vp

        for (auto e: word_count){
            vp.push_back(e);
        }
        
        std::ranges::sort(vp, [](auto e, auto e2){return e.second < e2.second;});

        for(auto v: vp){
            std::cout << v.first << " : " << v.second << std::endl;
        }


    return 0;
}