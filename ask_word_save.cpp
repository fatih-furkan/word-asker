#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#define MAX_WORD 10000 //can be changed according to needs

using namespace std;

//a function for printing all of the words and meanings
void all(string words[], string meanings[], int count) {
    for(int i = 0; i<count; i++) {
        cout << words[i] << " - " << meanings[i] << endl;
    }
}

int main() {

    //open the file
    ifstream myFile;
    myFile.open("example.txt");

    //if cannot open finish the program
    if(myFile.is_open() == 0) {
        cout << "File cannot found";
        return 1;
    }

    //initializations
    char ch;
    string words[MAX_WORD];
    string meanings[MAX_WORD];
    int w = 0;      //stands for word
    int m = 0;      //stands for meaning
    int wm = 0;     //0 for w, 1 for m
    int sep_lock = 0;
    int line_count = 0;
    int last_line = -1; // shows last line that ' - ' sequence is capted

    while(myFile.get(ch)) {

        //this part is a bit complicated to understand, it is better to start from if(sep_lock == 0) statement and go upwards.
        //the logic is, we search for a specific sequence of characters: ' - '. And for that i created a lock that contains 3 steps.
        if(sep_lock == 2) {
            if(ch == ' ') {
                sep_lock = 3;
            }
            else sep_lock = 0;
        }

        if(sep_lock == 1) {
            if(ch == '-') sep_lock = 2;
            else sep_lock = 0;
        }

        if(sep_lock == 0) {
            if(ch == ' ') sep_lock = 1;
        }        

        if(ch != '\n') {
            //if what we add is a word, append it to the words array's last word
            if(wm == 0){
                words[w].append(1, ch);
            }
            
            //if it is a meaning, then append it to meanings array's last meaning
            else {
                meanings[m].append(1, ch);
            }
        }

        //if ' - ' sequence is obteined we pass from word to meaning or from meaning to word. wm is for that.
        //last_line != line_count inequality is for avoiding the situation that 2 ' - ' sequence take place in a line
        if(sep_lock == 3) {

            if(last_line == line_count) {
                sep_lock = 0;
            }

            else {
                wm = 1;
                //remove ' - ' sequence from the word
                for(int i = 0; i<3; i++) {
                    words[w].pop_back();
                }

                w++;
                sep_lock = 0;
                last_line = line_count;
            }
        }

        //when we read the new line character, if it were reading a word, it stars to reading a new word,
        //if it were reading a meaning, it starts to read a new word anyway.
        if(ch == '\n') {

            if(wm == 0) {
                w++;
            }

            else wm = 0;

            m++;
            line_count++;
        }
    }

    //print all word meaning pairs
    //all(words, meanings, w);

    srand(time(0));

    //prints a random word and after the user has pressed on enter, reveals the meaning, right after that prints a new word.
    //Don't has an option to quit.
    // the second while is for being sure that the word is not an empty array
    while(1) {
        int num = rand() % w;
        while(words[num] == "") {
            num = rand() % w;
        }

        cout << words[num];
        cin.ignore();
        cout << meanings[num] << endl << endl;
    }

    return 0;
}