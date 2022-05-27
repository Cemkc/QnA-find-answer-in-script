# QnA-find-answer-in-script

Purpose of this project is to find the corresponding answers to given questions in a text.

# Benchamark results:

-13,951 word long text.

-8 questions with total of 96 words.

-Intel i5 12400F

Total time to find answers: 0.003 secs

(Algorithm's performance is nearly not affected by the length or number of questions but it will consume more memory)

# Accuracy:

(For the examples and data that was used for this project)

The algorithm was able to answer 6 out of 8 questions with %100 accuracy. The reason for the remaining 2 questions being not found is not having any solution 
for suffixes thus loss of words in the questions.
