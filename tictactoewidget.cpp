#include "tictactoewidget.h"
#include "ui_tictactoewidget.h"

#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TicTacToeWidget)
{
    ui->setupUi(this);
    setUpBoard();
}

TicTacToeWidget::~TicTacToeWidget()
{
    delete ui;
}

void TicTacToeWidget::initNewGame()
{
    for (int i=0;i<9;++i) board.at(i)->setText(" ");
}

void TicTacToeWidget::handleButtonClick(int index)
{
    if(index < 0 || index >= board.size()) return; // out of bounds check

    QPushButton *button = board.at(index);
    if(button->text() != " ")   // invalid move
        return;

    button->setText(currentPlayer() == Player1 ? "X" : "O");
    Player winner = checkWinCondition(index / 3, index % 3);
    if(winner == Invalid) {
        setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
        return;
    } else {
        emit gameOver(winner);
    }
}

TicTacToeWidget::Player TicTacToeWidget::checkWinCondition(int row, int col)
{
    return Player::Invalid;
}

void TicTacToeWidget::setUpBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    QSignalMapper *mapper = new QSignalMapper(this);


    QFont font;
    font.setPointSize(48);
    font.setBold(true);
    font.setWeight(75);





    for (int row = 0; row < 3; ++row) {
        for (int col=0; col < 3; ++col) {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum,
                                  QSizePolicy::Minimum);
            button->setText(" ");
            button->setFont(font);
            gridLayout->addWidget(button, row, col);
            board.append(button);
            mapper->setMapping(button, board.count()-1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
            //connect(button, &QPushButton::clicked, mapper, &QSignalMapper::map);
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this,
            SLOT(handleButtonClick(int)));
    setLayout(gridLayout);
}
