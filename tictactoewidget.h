#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>

class QPushButton; // forward declaration

namespace Ui {
class TicTacToeWidget;
}



class TicTacToeWidget : public QWidget
{
    Q_OBJECT

public:

    enum Player {
        Invalid, Player1, Player2, Draw
    };


    explicit TicTacToeWidget(QWidget *parent = 0);
    ~TicTacToeWidget();

    void initNewGame();
    Player currentPlayer() const { return m_currentPlayer; }
    void setCurrentPlayer(Player p) {
        if(m_currentPlayer == p)
            return;
        m_currentPlayer = p;
        emit currentPlayerChanged(p);
    }




signals:
    void currentPlayerChanged(Player);
    void gameOver(TicTacToeWidget::Player);


public slots:
    void handleButtonClick(int);

private:
    void setUpBoard();
    TicTacToeWidget::Player checkWinCondition(int row, int col);

private:
    Ui::TicTacToeWidget *ui;

    QList<QPushButton*> board;
    Player m_currentPlayer;
};

#endif // TICTACTOEWIDGET_H
