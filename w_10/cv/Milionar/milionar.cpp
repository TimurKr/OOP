#include <random>       // std::default_random_engine
#include <chrono>
#include <QMessageBox>
#include "milionar.h"
#include "./ui_milionar.h"

void Question::load(std::istream& input_file)
{
    std::string aux;

    std::getline(input_file, question);
    for (int i = 0; i < 4; i++) {
        std::getline(input_file, options[i]);
    }
    std::getline(input_file, aux);
    aux = options[0];
    shuffle(options.begin(), options.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

    for (int i = 0; i < 4; i++) {
        if (options[i] == aux) {
            correct_index = i;
            break;
        }
    }
}



Milionar::Milionar(QWidget *parent) : QMainWindow(parent), ui(new Ui::Milionar)
{
    ui->setupUi(this);

    option_buttons = {ui->opt1, ui->opt2, ui->opt3, ui->opt4};

    std::ifstream input_file("/Users/timurkramar/Library/CloudStorage/OneDrive-Personal/MPM/OOP/OOP/w_10/cv/Milionar/questions.txt");
    if (! input_file.is_open() ) {
        throw 1;
    }

    for (int i = 0; i < 10; i++) {
        questions[i].load(input_file);
    }

    player.setName("");
    in_game = false;

}

Milionar::~Milionar()
{
    delete ui;
}


void Milionar::load_question(unsigned int index)
{
    if (index == 10) {
        on_endGame_clicked();
        return;
    }
    ui->question->setPlainText(QString::fromStdString(questions[index].getQuestion()));
    ui->opt1->setText(QString::fromStdString(questions[index].getOptions()[0]));
    ui->opt2->setText(QString::fromStdString(questions[index].getOptions()[1]));
    ui->opt3->setText(QString::fromStdString(questions[index].getOptions()[2]));
    ui->opt4->setText(QString::fromStdString(questions[index].getOptions()[3]));
    for (int i = 0; i<4; i++) {
        option_buttons[i]->setAutoExclusive(false);
        option_buttons[i]->setChecked(false);
        option_buttons[i]->setAutoExclusive(true);
        option_buttons[i]->setEnabled(true);
    }

    joker_in_use = false;
    active_question = index;

    for (int i = 0; i<4; i++) {
        option_buttons[i]->setChecked(false);
    }

//    on_difficulty_activated(ui->difficulty->currentIndex());
}

void Milionar::activate_joker()
{
    if (joker_in_use) { return; }
    unsigned int one = rand() % 4;
    while (one == questions[active_question].getCorrectIndex()) {
        one = rand() % 4;
    }

    unsigned int two = rand() % 4;
    while (one == two || two == questions[active_question].getCorrectIndex()) {
        two = rand() % 4;
    }

    option_buttons[one]->setEnabled(false);
    option_buttons[two]->setEnabled(false);

    for (int i = 0; i<4; i++) {
        option_buttons[i]->setAutoExclusive(false);
        option_buttons[i]->setChecked(false);
        option_buttons[i]->setAutoExclusive(true);
    }

    joker_in_use = true;
}



void Milionar::on_difficulty_activated(int index)
{
    if (index == 0) {
        ui->joker1->setEnabled(true);
        ui->joker2->setEnabled(true);
        ui->joker3->setEnabled(true);
    } else if (index == 1) {
        ui->joker1->setEnabled(true);
        ui->joker2->setEnabled(true);
        ui->joker3->setEnabled(false);
    } else if (index == 2) {
        ui->joker1->setEnabled(true);
        ui->joker2->setEnabled(false);
        ui->joker3->setEnabled(false);
    }
}

void Milionar::on_newGame_clicked()
{
    if (! in_game) {

        if (ui->name->text().toStdString() == "") {
            ui->statusbar->showMessage("Zadajte meno!");
            return;
        }
        player.setName(ui->name->text().toStdString());

    }

    if (ui->randomOrder->isChecked()) {
        shuffle (questions.begin(), questions.end(), std::default_random_engine());
    }

    ui->statusbar->showMessage("Spúšťam hru...");
    in_game = true;

    player.setScore(0);
    ui->score->setValue(player.Score());

    ui->endGame->setEnabled(true);
    ui->difficulty->setEnabled(false);
    ui->randomOrder->setEnabled(false);
    ui->newGame->setEnabled(false);

    load_question(0);
}

void Milionar::on_endGame_clicked()
{
    player.changeScore((10 - active_question) * 0.5);
    in_game = false;
    ui->endGame->setEnabled(false);
    ui->difficulty->setEnabled(true);
    ui->randomOrder->setEnabled(true);
    ui->newGame->setEnabled(false);

    ui->opt1->setEnabled(false);
    ui->opt2->setEnabled(false);
    ui->opt3->setEnabled(false);
    ui->opt4->setEnabled(false);

    QMessageBox msgBox;
    msgBox.setText(QString("The game is over, %1.\nYou have earned %2 points").arg(
                       QString::fromStdString(player.Name()),
                       QString::number(player.Score())));
    msgBox.exec();
}

void Milionar::on_joker1_clicked()
{
    if (joker_in_use) return;
    activate_joker();
    ui->joker1->setEnabled(false);
}

void Milionar::on_joker2_clicked()
{
    if (joker_in_use) return;
    activate_joker();
    ui->joker2->setEnabled(false);
}

void Milionar::on_joker3_clicked()
{
    if (joker_in_use) return;

    activate_joker();
    ui->joker3->setEnabled(false);
}

void Milionar::on_submit_clicked()
{
    unsigned int answer_index = 0;
    QMessageBox msgBox;

    while (true) {
        if (option_buttons[answer_index]->isChecked()) break;
        answer_index++;
        if (answer_index == 4) {

            msgBox.setText(QString("Nezadali ste žiadnu možnosť."));
            msgBox.exec();
            return;
        }
    }

    if (answer_index == questions[active_question].getCorrectIndex()) {
        player.changeScore(1);
        msgBox.setText(QString("Správne, máte %1 bodov.").arg(QString::number(player.Score())));
    } else {
        player.changeScore(-1);
        msgBox.setText(QString("Nesprávne, máte %1 bodov.").arg(QString::number(player.Score())));
    }
    msgBox.exec();

    ui->score->setValue(player.Score());
    load_question(active_question + 1);
}

void Milionar::on_skip_clicked()
{
    player.changeScore(-0.5);
    ui->score->setValue(player.Score());

    QMessageBox msgBox;
    msgBox.setText(QString("Preskočili ste otázku, máte %1 bodov.").arg(QString::number(player.Score())));
    msgBox.exec();

    load_question(active_question + 1);
}
