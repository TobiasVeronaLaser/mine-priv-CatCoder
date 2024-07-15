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
void calculate(ifstream *input_file, ofstream *output_file);
vector get_start_pos(string input, vector dim);
vector get_dimension(string input);
bool move_lawn(char **lawn, vector pos, vector dim, string input, unsigned valid_position_count);

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

        calculate(&input_file, &output_file);
        
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

void calculate(ifstream *input_file, ofstream *output_file){
    unsigned n;
    *input_file >> n;
    for(unsigned i = 0; i < n; i++){
        long long width = 2, height = 3;
        *input_file >> width;
        *input_file >> height;
        cout << width << " " << height << "\n";
        char **lawn = (char **)malloc(height * sizeof(*lawn));  
        for(long long y = 0; y < height; y++){
            string input_row;
            *input_file >> input_row;
            char *row = (char*)malloc(width * sizeof(*row));
            for(long long x = 0; x < width; x++){
                row[x] = input_row[x];
            }
            lawn[y] = row;
        }
        string input;
        *input_file >> input;
        vector dim = get_dimension(input);
        vector current_pos = get_start_pos(input, dim);
        // cout << current_pos.x << " " << current_pos.y << "\n";
        
        
        *output_file << (move_lawn(lawn, current_pos, dim, input, width * height - 1) ?  "VALID" : "INVALID") << "\n";
        cout << "\nwrote\n\n";
        for(long long y = 0; y < height; y++){
            free(lawn[y]);
        }
        free(lawn);
    }
}

// TODO: What if lawn moves to the left and to the right over or up and down
vector get_start_pos(string input, vector dim){
    vector current_vec = {0, 0}, min_vec = {0, 0}, max_vec = {0, 0};
    for(unsigned i = 0; i < input.length(); i++){
        add_direction(&current_vec, char_to_direction(input[i]), 1);
        set_greater(&current_vec.x, &max_vec.x);
        set_greater(&current_vec.y, &max_vec.y);
        set_smaller(&current_vec.x, &min_vec.x);
        set_smaller(&current_vec.y, &min_vec.y);
        // cout << current_vec.x << " " << current_vec.y << "\n";
    }

    vector output = {0, 0};
    if(min_vec.x < 0){
        output.x = -min_vec.x;
    }else if(max_vec.x > dim.x){
        output.x = dim.x - 1 -max_vec.x6
    }
    return output;
}

vector get_dimension(string input){
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

bool move_lawn(char **lawn, vector pos, vector dim, string input, unsigned valid_position_count){
    unsigned counter = 1;
    lawn[pos.y][pos.x] = '0';
    for(unsigned j = 0; j < input.length(); j++){
            add_direction(&pos, char_to_direction(input[j]), 1);
            if(pos.x < 0 || pos.y < 0 || pos.x >= dim.x || pos.y >= dim.y){
                return false;
            }
            for(unsigned y = 0; y < dim.y; y++){
                for(unsigned x = 0; x < dim.x; x++){
                    cout << lawn[y][x];
                }
                cout << "\n";
            }
            cout << pos.y << " " << pos.x << "\n";
            switch(lawn[pos.y][pos.x]){
                case 'X': 
                    cout << "tree\n";
                    return false;
                case '0':
                    cout << "double\n";
                    return false;
                case '.':
                    break;
                default:
                    cout << "Invalid value";
                    return false;
            }
            counter++;
            lawn[pos.y][pos.x] = '0';
        }
    return counter == valid_position_count;
}