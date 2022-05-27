#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include "HashT.h"


int main(){

    clock_t begin = (double)clock();

    HashT questionWordHash;
    HashT stopWordHash;

    std::ifstream ts_question("questions.txt");
    std::ifstream ts_script("the_truman_show_script.txt");
    std::ifstream stopWords("stopwords.txt");

    while (!stopWords.eof()) {
        std::string hold;
        stopWords >> hold;
        stopWordHash.insert(hold, 0);
    }

    int questionNum = 1;
    while (!ts_question.eof()) {

        std::string hold;
        ts_question >> hold;

        for (int i = 0; i < hold.size(); i++) {
            hold[i] = tolower(hold[i]);
            if ((int(hold[i]) < 97 || int(hold[i]) > 122) && int(hold[i]) != 39) {
                hold.erase(hold.begin() + i);
            }
        }

        if (!stopWordHash.search(hold)) {
            questionWordHash.insert(hold, questionNum);
        }

        if (ts_question.peek() == '\n' || ts_question.peek() == '\r') {
            questionNum++;
        }

    }
    //Hash Tables are Ready.

    int seqFound = 0;
    int questionNumm = 0;
    int filePtr = 0;
    bool flag = true;
    bool end_of_sentence = false;
    std::string answer[10];
    int corr_answer_q[10];
    int truman_count = 0;
    int ques_word_cont[8] = { 0 };
    std::string tempAnswerCont;
    int answerIndx = 0;

    while (!ts_script.eof()) {
        std::string hold;
        ts_script >> hold;
        for (int i = 0; i < hold.size(); i++) {
            hold[i] = tolower(hold[i]);
            if ((int(hold[i]) < 48 || int(hold[i]) > 122) && int(hold[i]) != 39) {
                if (hold[i] == '.') {
                    end_of_sentence = true;
                }
                hold.erase(hold.begin() + i);
            }
        }
        tempAnswerCont += hold + " ";


        if (questionWordHash.search(hold)) {
            if (hold == "truman") {
                truman_count++;
            }
            if (truman_count < 2) {
                ques_word_cont[questionWordHash.getQnum(hold) - 1]++;
            }

        }

        if (end_of_sentence) {
            int maximum = ques_word_cont[0];
            int maxQuestionWords = 0;
            for (int i = 1; i < 8; i++) {
                if (ques_word_cont[i] > maximum) {
                    maximum = ques_word_cont[i];
                    maxQuestionWords = i;
                }
            }
            if (maximum > 2) {
                answer[answerIndx] = tempAnswerCont;
                corr_answer_q[answerIndx] = maxQuestionWords + 1;
                answerIndx++;
            }
            end_of_sentence = false;
            tempAnswerCont.clear();
            truman_count = 0;
            for (int i = 0; i < 8; i++) {
                ques_word_cont[i] = 0;
            }
        }
    }

    for (int i = 0; i < answerIndx; i++) {
        std::string hold;
        std::string temp;
        int iterator = 0;

        for (int j = 0; j < answer[i].size(); j++) {
            if (answer[i][j] == ' ') {
                hold = answer[i].substr(iterator, j - iterator);
                if (!questionWordHash.search(hold) && !stopWordHash.search(hold)) {
                    temp += hold + " ";
                }
                iterator = j + 1;
            }
        }

        if (temp.empty()) {
            temp = "Truman";
        }

        answer[i] = temp;
        temp.clear();
    }

    for (int i = 0; i < answerIndx; i++) {
        std::cout << answer[i] << " :: " << corr_answer_q[i] << std::endl;
    }

    clock_t end = (double)clock();
    double elapsed = (end - begin) / (double)CLOCKS_PER_SEC;
    std::cout << "Time Elapsed:" << elapsed << "seconds";

    return 0;
}
