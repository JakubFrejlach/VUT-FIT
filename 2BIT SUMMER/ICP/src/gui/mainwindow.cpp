/**
 * @file 	mainwindow.cpp
 * @brief 	main GUI implementation
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "clickablelabel.h"
#include <QSignalMapper>
#include <list>
#include <QFileDialog>
#include <QMessageBox>
#include "../enums.hpp"
#include "../chess.hpp"
#include "../chess.cpp"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->game = new Chess();
    ui->UndoButton->setEnabled(false);
    ui->StartButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
    ui->PrevButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
    ui->PlayButton->setEnabled(false);
    ui->ReplayButton->setEnabled(false);
    connect(ui->NextButton, SIGNAL(clicked()), this, SLOT(perform_move()));
}

void MainWindow::init_board()
{
    for (int i = 1; i <= 8; i++)
    {
       for (int j = 1; j <= 8; j++)
       {
           QWidget *w = new QWidget();
           w->setFixedWidth(60);
           w->setFixedHeight(60);

           if(i % 2 != 0)
           {
               if(j % 2 != 0)
               {
                   w->setStyleSheet("background-color:white;");
               }
               else
               {
                   w->setStyleSheet("background-color:grey;");
               }
           }
           else
           {
               if(j % 2 != 0)
               {
                   w->setStyleSheet("background-color:grey;");
               }
               else
               {
                   w->setStyleSheet("background-color:white;");
               }
           }

           ClickableLabel *label = new ClickableLabel();
           QHBoxLayout *layout = new QHBoxLayout();
           layout->addWidget(label);
           label->setScaledContents(true);
           label->set_cord(i - 1, j - 1);
           w->setLayout(layout);

           ui->gridLayout_2->addWidget(w, i, j, 1, 1, 0);
           this->set_board(label, i - 1, j - 1);
           this->set_field(w, i - 1, j - 1);
       }
    }

    for(int i = 0; i <= 7; i++)
    {
        this->get_board(1, i)->set_figure(":/images/black-pawn.png");
    }
    this->get_board(0, 0)->set_figure(":/images/black-rook.png");
    this->get_board(0, 7)->set_figure(":/images/black-rook.png");
    this->get_board(0, 1)->set_figure(":/images/black-knight.png");
    this->get_board(0, 6)->set_figure(":/images/black-knight.png");
    this->get_board(0, 2)->set_figure(":/images/black-bishop.png");
    this->get_board(0, 5)->set_figure(":/images/black-bishop.png");
    this->get_board(0, 3)->set_figure(":/images/black-queen.png");
    this->get_board(0, 4)->set_figure(":/images/black-king.png");


    for(int i = 0; i <= 7; i++)
    {
        this->get_board(6, i)->set_figure(":/images/white-pawn.png");
    }
    this->get_board(7, 0)->set_figure(":/images/white-rook.png");
    this->get_board(7, 7)->set_figure(":/images/white-rook.png");
    this->get_board(7, 1)->set_figure(":/images/white-knight.png");
    this->get_board(7, 6)->set_figure(":/images/white-knight.png");
    this->get_board(7, 2)->set_figure(":/images/white-bishop.png");
    this->get_board(7, 5)->set_figure(":/images/white-bishop.png");
    this->get_board(7, 3)->set_figure(":/images/white-queen.png");
    this->get_board(7, 4)->set_figure(":/images/white-king.png");
}

void MainWindow::set_board(ClickableLabel *l, int row, int col)
{
    this->board[row][col] = l;
}

ClickableLabel *MainWindow::get_board(int row, int col)
{
    return this->board[row][col];
}

void MainWindow::set_field(QWidget *w, int row, int col)
{
    this->fields[row][col] = w;
}

QWidget *MainWindow::get_field(int row, int col)
{
    return this->fields[row][col];
}

void MainWindow::FieldSelected()
{
    Square place;
    Square auxPlace;
    std::list<Square> availableMoves;
    static int gameState = SELECT;
    static ClickableLabel *selectedLabel;

    ClickableLabel* pLabel = qobject_cast<ClickableLabel*>(sender());
    if (pLabel)
    {
        if(gameState == SELECT)
        {
            place = pLabel->get_cord();
            availableMoves= this->game->get_available_moves(this->gameId, place);
            if(!availableMoves.empty())
            {
                this->show_available_moves(availableMoves);
                selectedLabel = pLabel;
                gameState = MOVE;
                ui->UndoButton->setEnabled(false);
            }
        }
        else if(gameState == MOVE)
        {
           Move move;
           place = selectedLabel->get_cord();
           auxPlace = pLabel->get_cord();
           availableMoves = this->game->get_available_moves(this->gameId, place);

           for(auto &m : availableMoves)
           {
              if(m.row == auxPlace.row && m.col == auxPlace.col)
              {
                  place.figure = board[place.row][place.col]->get_figure();
                  auxPlace.figure = board[auxPlace.row][auxPlace.col]->get_figure();
                  this->undo_history.push_back(place);
                  this->undo_history.push_back(auxPlace);
                  move.set_new_place(auxPlace);
                  move.set_previous_place(place);
                  move.set_gameId(this->gameId);
                  move.set_turn_number(this->turns);


                  this->game->move(&move, true, player);
                  Move *currentMove = this->game->get_move(gameId, turns, player);
                  player = this->game->change_player(gameId);
                  if(player == WHITE)
                  {
                      turns++;
                  }

                  int state = this->game->is_end(gameId);
                  if(state == WHITE_WIN)
                  {
                      QMessageBox::information(this, tr("Game finished!"), tr("WHITE WON, CONGRATZ"));
                      this->gameEnd = true;
                  }
                  else if(state == BLACK_WIN)
                  {
                      QMessageBox::information(this, tr("Game finished!"), tr("BLACK WON, CONGRATZ"));
                      this->gameEnd = true;
                  }
                  else if(state == DRAW)
                  {
                      QMessageBox::information(this, tr("Game finished!"), tr("IT'S A DRAW, SHAME!"));
                      this->gameEnd = true;
                  }

                  currentMove->generate_notation(player == WHITE ? BLACK : WHITE);
                  ui->listWidget->addItem(QString::number(++this->moves) + ". " +QString::fromStdString(currentMove->get_notation()));
                  pLabel->set_figure(selectedLabel->get_figure());
                  selectedLabel->set_figure("");
                  selectedLabel = NULL;
                  gameState = SELECT;
                  this->restore_board_colors();
                  ui->UndoButton->setEnabled(true);
              }
           }
        }
    }
}

void MainWindow::restore_board_colors()
{
    for (int i = 0; i <= 7; i++)
    {
       for (int j = 0; j <= 7; j++)
       {
           if(i % 2 != 0)
           {
               if(j % 2 != 0)
               {
                   this->fields[i][j]->setStyleSheet("background-color:white;");
               }
               else
               {
                   this->fields[i][j]->setStyleSheet("background-color:grey;");
               }
           }
           else
           {
               if(j % 2 != 0)
               {
                   this->fields[i][j]->setStyleSheet("background-color:grey;");
               }
               else
               {
                   this->fields[i][j]->setStyleSheet("background-color:white;");
               }
           }
       }
    }
}

void MainWindow::show_available_moves(std::list<Square> availableMoves)
{
    for(Square m: availableMoves)
    {
        this->fields[m.row][m.col]->setStyleSheet("background-color:green;");
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoadButton_clicked()
{
    ui->UndoButton->setEnabled(false);
    ui->StartButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
    ui->PrevButton->setEnabled(false);
    ui->NextButton->setEnabled(false);

    for(int i=ui->listWidget->count(); i > 0; i--)
    {
       ui->listWidget->takeItem(i - 1);
    }

    this->init_board();
    this->undo_history.clear();
    this->gameId = this->game->start();
    QString f = QFileDialog::getOpenFileName(this, tr("Open file"));
    std::string fileName = f.toUtf8().constData();
    if(!this->game->load_game(fileName,gameId))
    {
        QMessageBox::information(this, tr("Failed to load!"), tr("WRONG NOTATION!"));
        return;
    }

    std::list<Move> moves= this->game->get_history_by_gameId(gameId);
    int aux_counter = 1;
    for(auto &m : moves)
    {
        ui->listWidget->addItem(QString::number(aux_counter++) + ". " +QString::fromStdString(m.get_notation()));
    }

    this->player = WHITE;
    this->gameEnd = false;
    this->replayOn = false;
    this->gameStart = true;
    this->timer = NULL;
    this->moves = 0;
    this->turns = 1;
    ui->StartButton->setEnabled(true);
    ui->StopButton->setEnabled(true);
}

void MainWindow::on_StartButton_clicked()
{
    if(!replayOn && !this->gameEnd)
    {
        disconnect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                    this, SLOT(onListItemClicked(QListWidgetItem*)));
        ui->NextButton->setEnabled(false);
        ui->PrevButton->setEnabled(false);
        replayOn = true;
        this->timer = new QTimer();
        connect(this->timer, SIGNAL(timeout()), this, SLOT(perform_move()));
        this->timer->start(this->timeout);
    }
}

void MainWindow::on_StopButton_clicked()
{
    if(replayOn)
    {
        connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                    this, SLOT(onListItemClicked(QListWidgetItem*)));
        if(!this->gameEnd)
        {
            ui->NextButton->setEnabled(true);
        }
        ui->PlayButton->setEnabled(true);
        ui->PrevButton->setEnabled(true);
        this->timer->stop();
        replayOn = false;
    }
}

void MainWindow::on_UndoButton_clicked()
{
    if(!this->undo_history.empty())
    {
        this->game->undo(this->gameId, &player, &turns);
        Square aux = this->undo_history.back();
        this->undo_history.pop_back();
        this->board[aux.row][aux.col]->set_figure(aux.figure);
        aux = this->undo_history.back();
        this->undo_history.pop_back();
        this->board[aux.row][aux.col]->set_figure(aux.figure);

        this->game->clear_moves_after_turn_number(this->gameId, this->turns, this->player);

        for(int i=ui->listWidget->count(); i > 0; i--)
        {
           ui->listWidget->takeItem(i - 1);
        }

        std::list<Move> moves= this->game->get_history_by_gameId(gameId);
        int aux_counter = 1;
        for(auto &m : moves)
        {
            ui->listWidget->addItem(QString::number(aux_counter++) + ". " +QString::fromStdString(m.get_notation()));
        }
        this->moves--;

        this->gameEnd = false;
    }
}


void MainWindow::on_PrevButton_clicked()
{
    if(!this->undo_history.empty())
    {
        ui->NextButton->setEnabled(true);
        this->game->undo(this->gameId, &player, &turns);
        Square aux = this->undo_history.back();
        this->undo_history.pop_back();
        this->board[aux.row][aux.col]->set_figure(aux.figure);
        aux = this->undo_history.back();
        this->undo_history.pop_back();
        this->board[aux.row][aux.col]->set_figure(aux.figure);

        if(!--this->moves)
        {
            ui->listWidget->clearFocus();
            ui->listWidget->clearSelection();
        }
        else
        {
            ui->listWidget->item(this->moves - 1)->setSelected(true);
            ui->listWidget->setFocus();
        }

        this->gameEnd = false;
    }
}

void MainWindow::perform_move()
{
    if(this->moves == this->game->get_number_of_moves(gameId))
    {
        return;
    }

    ui->listWidget->item(this->moves++)->setSelected(true);
    ui->listWidget->setFocus();
    if(gameStart)
    {
        player = this->game->get_player(gameId);
        gameStart = false;
        turns = 1;
    }

    if(turns <= this->game->get_total_turns(gameId) && !this->gameEnd)
    {
        Move *currentMove = this->game->get_move(gameId, turns, player);

        currentMove->set_gameId(gameId);
        this->game->move(currentMove, false, player);
        if(this->game->get_error_status(gameId))
        {
            QMessageBox::information(this, tr("Failed to perform move!"), tr("FORBIDDEN MOVE!"));
            return;
        }
        Square prev = currentMove->get_previous_place();
        Square next = currentMove->get_new_place();
        prev.figure = board[prev.row][prev.col]->get_figure();
        next.figure = board[next.row][next.col]->get_figure();
        this->undo_history.push_back(prev);
        this->undo_history.push_back(next);
        board[next.row][next.col]->set_figure(board[prev.row][prev.col]->get_figure());
        board[prev.row][prev.col]->set_figure("");

        this->game->replay_check_promotion(gameId, currentMove);

        player = this->game->change_player(gameId);
        if(player == WHITE)
        {
            turns++;
        }

        int state = this->game->is_end(gameId);
        if(state == WHITE_WIN)
        {
            QMessageBox::information(this, tr("Game finished!"), tr("WHITE WON, CONGRATZ"));
            this->timer->stop();
            ui->NextButton->setEnabled(false);
            this->gameEnd = true;
            emit ui->StopButton->clicked();
        }
        else if(state == BLACK_WIN)
        {
            QMessageBox::information(this, tr("Game finished!"), tr("BLACK WON, CONGRATZ"));
            this->timer->stop();
            ui->NextButton->setEnabled(false);
            this->gameEnd = true;
            emit ui->StopButton->clicked();
        }
        else if(state == DRAW)
        {
            QMessageBox::information(this, tr("Game finished!"), tr("IT'S A DRAW, SHAME!"));
            this->timer->stop();
            ui->NextButton->setEnabled(false);
            this->gameEnd = true;
            emit ui->StopButton->clicked();
        }

        if(this->game->get_number_of_moves(gameId) < turns * 2 && player == BLACK)
        {
          this->timer->stop();
        }
   }

}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if(replayOn)
    {
        this->timer->setInterval(position);
    }
    this->timeout = position;

}


void MainWindow::on_PlayButton_clicked()
{
    disconnect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListItemClicked(QListWidgetItem*)));
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            connect(this->board[i][j], SIGNAL(clicked()), this, SLOT(FieldSelected()));
        }
    }
    ui->UndoButton->setEnabled(true);
    ui->StartButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
    ui->PrevButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
    ui->PlayButton->setEnabled(false);
    ui->ReplayButton->setEnabled(true);

    this->game->clear_moves_after_turn_number(this->gameId, this->turns, this->player);

    for(int i=ui->listWidget->count(); i > 0; i--)
    {
       ui->listWidget->takeItem(i - 1);
    }

    std::list<Move> moves= this->game->get_history_by_gameId(gameId);
    int aux_counter = 1;
    for(auto &m : moves)
    {
        ui->listWidget->addItem(QString::number(aux_counter++) + ". " +QString::fromStdString(m.get_notation()));
    }
}

void MainWindow::on_ReplayButton_clicked()
{
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListItemClicked(QListWidgetItem*)));
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            disconnect(this->board[i][j], SIGNAL(clicked()), this, SLOT(FieldSelected()));
        }
    }
    ui->UndoButton->setEnabled(false);
    ui->StartButton->setEnabled(true);
    ui->StopButton->setEnabled(true);
    ui->PrevButton->setEnabled(true);
    ui->PlayButton->setEnabled(true);
    ui->ReplayButton->setEnabled(false);

    if(!this->gameEnd)
    {
        ui->NextButton->setEnabled(true);
    }
}

void MainWindow::onListItemClicked(QListWidgetItem *)
{
    std::string aux = ui->listWidget->currentItem()->text().toUtf8().constData();
    std::stringstream ss;
    for(auto &c : aux)
    {
        if(isdigit(c))
        {
            ss << c;
        }
        else
        {
           break;
        }
    }
    int moveNumber;
    ss >> moveNumber;
    while(moveNumber > this->moves)
    {
        this->perform_move();
    }
    while(moveNumber < this->moves)
    {
        this->on_PrevButton_clicked();
    }
}
