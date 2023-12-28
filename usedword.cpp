#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>
#include <set>
#include <iterator>
int main(){
   
    //Initializes object f. Change filename to suit your needs.
    std::fstream f("pg100.txt");
    
    //Create string line, use getline function to get input from f
    //and output it line by line
    std::string line; 

    //Create new map, which has the key as a string, and the amount as word_count.
    std::map<std::string, int > word_count;
    
    //Excluded words list
    std::set<std::string> excluded_words {"s", ":", ",", ".", "Γ", "Ç", "Ö"};
   
    while(std::getline(f,line)){
        std::transform(line.begin(), line.end(), line.begin(),
        [](unsigned char c){ return std::tolower(c); });
    

        // Remove excluded words from the line
        for (const auto& excluded_word : excluded_words) {
            auto found = line.find(excluded_word);
            while (found != std::string::npos) {
                line.erase(found, excluded_word.length());
                found = line.find(excluded_word);
            }
        }

        //Want to access each word individually
        auto index = excluded_words.begin();

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
        
        std::ranges::sort(vp, [](const auto& e, const auto& e2){return e.second < e2.second;});

        for(const auto& v: vp){
            std::cout << v.first << " : " << v.second << std::endl;
        }

        if (!vp.empty()) {
        // The last element in the sorted vector has the highest frequency
        const auto& most_common_word = vp.back().first;
        std::cout << "The most common word in this script is: " << most_common_word << std::endl;
        
        } 
        else {
        std::cout << "No words found in the script." << std::endl;
        }
    

    return 0;
}