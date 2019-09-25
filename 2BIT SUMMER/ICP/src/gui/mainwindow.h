/**
 * @file 	mainwindow.h
 * @brief 	header file for main GUI
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QLabel>
#include <list>
#include <QWidget>
#include <QTimer>
#include "clickablelabel.h"
#include "../square.hpp"
#include "../chess.hpp"
#include <vector>
#include <QListWidgetItem>

#define SELECT 0
#define MOVE 1

namespace Ui {
class MainWindow;
}

/**
 *	@brief Main window class from Qt
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     *	@brief Shows available moves on board
     *  @param availableMoves list of available moves
     */
    void show_available_moves(std::list<Square> availableMoves);

    /**
     *	@brief restores colors of board
     */
    void restore_board_colors();

    /**
     *	@brief initialize board and figures
     */
    void init_board();

    /**
     *	@brief Aux method for storing labels for figures
     *  @param l pointer to label
     *  @param row row of board
     *  @param col col of board
     */
    void set_board(ClickableLabel *l, int row, int col);

    /**
     *	@brief returns selected label with figure
     *  @param row row of board
     *  @param col col of board
     *  @return label with figure
     */
    ClickableLabel *get_board(int row, int col);

    /**
     *	@brief Aux method for storing widgets
     *  @param w pointer to widget
     *  @param row row of board
     *  @param col col of board
     */
    void set_field(QWidget *w, int row, int col);

    /**
     *	@brief returns selected widget
     *  @param row row of board
     *  @param col col of board
     *  @return widget of board
     */
    QWidget *get_field(int row, int col);

private slots:
    void FieldSelected();

    void on_LoadButton_clicked();

    void on_StartButton_clicked();

    void perform_move();

    void on_StopButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_PrevButton_clicked();

    void on_PlayButton_clicked();

    void on_ReplayButton_clicked();

    void on_UndoButton_clicked();

    void onListItemClicked(QListWidgetItem*);

private:
    /**
     *	@brief pointer to ui basics
     */
    Ui::MainWindow *ui;
    /**
     *	@brief game class instance for game logic
     */
    Chess *game;
    /**
     *	@brief game board
     */
    ClickableLabel *board[8][8];
    /**
     *	@brief game board fields
     */
    QWidget *fields[8][8];
    /**
     *	@brief timer handler
     */
    QTimer *timer;
    /**
     *	@brief default timeout for timer handler
     */
    int timeout = 1000;
    /**
     *	@brief id of the game
     */
    int gameId;
    /**
     *	@brief turn counter
     */
    int turns = 1;
    /**
     *	@brief player indicator
     */
    int player;
    /**
     *	@brief moves counter
     */
    int moves;
    /**
     *	@brief end game flag
     */
    bool gameEnd = false;
    /**
     *	@brief start game flag
     */
    bool gameStart = true;
    /**
     *	@brief replay flag
     */
    bool replayOn = false;
    /**
     *	@brief vector for available moves
     */
    std::vector<Square> undo_history;
};



#endif // MAINWINDOW_H
