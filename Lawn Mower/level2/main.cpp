#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

enum Direction{W, D, S, A, DIRECTION_COUNT};

struct vector{
    long long x;
    long long y;
};

Direction char_to_direction(char c);
vector *add_direction(vector *vec, Direction direction, long long step_size);
void set_greater(long long *source, long long *target);
void set_smaller(long long *source, long long *target);
vector calculate(string input);

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
        long long row_direction_count;
        input_file >> row_direction_count;
        for(unsigned j = 0; j < row_direction_count; j++){
            string row;
            input_file >> row;
            vector dimensions = calculate(row);
            output_file << dimensions.x << " " << dimensions.y << "\n";
            // cout << row << "\n";
        }
        output_file.close();
        input_file.close();
        cout << "Successfully wrote from \"" << argv[i] << "\" to \"" << output_file_name << "\"!\n";
    }
    return EXIT_SUCCESS;
}

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


vector *add_direction(vector *vec, Direction direction, long long step_size){
    switch(direction){
        case W:
            vec->y -= step_size;
            break;
        case S:
            vec->y += step_size;
            break;
        case A:
            vec->x -= step_size;
            break;
        case D:
            vec->x +=step_size;
            break;
        default: 
            break;
    }
    return vec;
}

void set_greater(long long *source, long long *target){
    if(*source > *target){
        *target = *source;
    }
}

void set_smaller(long long *source, long long *target){
    if(*source < *target){
        *target = *source;
    }
}

vector calculate(string input){
    vector current_vec = {0, 0}, min_vec = {0, 0}, max_vec = {0, 0};
    for(unsigned i = 0; i < input.length(); i++){
        add_direction(&current_vec, char_to_direction(input[i]), 1);
        set_greater(&current_vec.x, &max_vec.x);
        set_greater(&current_vec.y, &max_vec.y);
        set_smaller(&current_vec.x, &min_vec.x);
        set_smaller(&current_vec.y, &min_vec.y);
        // cout << current_vec.x << " " << current_vec.y << "\n";
    }
    vector output = {max_vec.x - min_vec.x + 1, max_vec.y - min_vec.y + 1};
    return output;
}