#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

enum Direction{W, D, S, A, DIRECTION_COUNT};

Direction char_to_direction(char c){
    switch(c){
        case 'W':
        case 'w':
            return W;
        case 'D':
        case 'd':
            return D;
        case 'S':
        case 's':
            return S;
        case 'A':
        case 'a':
            return A;
        default:
            return DIRECTION_COUNT;
    }
}

map<Direction, size_t> calculate(string input){
    map<Direction, size_t> output;
    for(size_t i = 0; i < DIRECTION_COUNT; i++){
        output[(Direction)i] = 0;
    }
    for(size_t i = 0; i < input.length(); i++){
        output[char_to_direction(input[i])]++;
    }
    return output;
}

int main(int argc , char ** argv){
    if(argc < 3){
        cout << "Missing argument\nExpected \"main \"";
        return EXIT_FAILURE;
    }
    string output_ending = argv[1];
    for(int i = 2; i < argc; i++){
        ifstream input_file;
        input_file.open(argv[i]);
        if(!input_file.is_open()){
            cout << "Input file \"" << argv[i] << "\" not open!\n";
            continue;
        }
        string output_file_name = argv[i];
        output_file_name.replace(output_file_name.end() - 2, output_file_name.end(), output_ending);
        //cout << output_file_name << "\n";
        ofstream output_file;
        output_file.open(output_file_name);
        if(!output_file.is_open()){
            // cout << "Output file \"" << output_file_name << "\" not open!\n";
            input_file.close();
            continue;
        }
        size_t row_direction_count;
        input_file >> row_direction_count;
        for(size_t j = 0; j < row_direction_count; j++){
            string row;
            input_file >> row;
            map<Direction, size_t> direction_counter = calculate(row);
            for(size_t k = 0; k < DIRECTION_COUNT; k++){
                output_file << direction_counter[(Direction)k] << " ";
            }
            output_file << "\n";
            // cout << row << "\n";
        }
        output_file.close();
        input_file.close();
        cout << "Successfully wrote from \"" << argv[i] << "\" to \"" << output_file_name << "\"!\n";
    }
    return EXIT_SUCCESS;
}