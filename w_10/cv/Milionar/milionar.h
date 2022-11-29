#ifndef MILIONAR_H
#define MILIONAR_H

#include "QtWidgets/qradiobutton.h"
#include <QMainWindow>
#include <fstream>
#include <string>
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class Milionar; }
QT_END_NAMESPACE

class Player
{
private:
    std::string name;
    double score;

public:
    Player() {}
    ~Player() {}

    void setName(std::string n) { name = n; }
    std::string Name() { return name; }
    void setScore(double i) { score = i; }
    void changeScore(double diff) { score += diff; }
    double Score() { return score; }
};


class Question
{
private:
    std::string question;
    std::array<std::string, 4> options;
    unsigned int correct_index;

public:
    enum exceptions {OutOfRangeOption};

    Question() {}
    ~Question() {}

    std::string getQuestion() { return question; }
    std::array<std::string, 4> getOptions() { return options; }
    std::string getCorrectAnswer() { return options[correct_index]; }
    unsigned int getCorrectIndex() { return correct_index; }

    void load(std::istream& input_file);
};


class Milionar : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Milionar *ui;
    Player player;
    std::array<Question, 10> questions;
    unsigned int active_question;
    bool in_game;
    bool joker_in_use;
    std::array<QRadioButton *, 4> option_buttons;

public:
    Milionar(QWidget *parent = nullptr);
    ~Milionar();

    void load_question(unsigned int index);


private slots:
    void on_newGame_clicked();
    void on_endGame_clicked();
    void on_difficulty_activated(int index);

    void activate_joker();
    void on_joker1_clicked();
    void on_joker2_clicked();
    void on_joker3_clicked();

    void on_submit_clicked();
    void on_skip_clicked();

};
#endif // MILIONAR_H
