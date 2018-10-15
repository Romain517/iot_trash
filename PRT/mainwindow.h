#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void addPoint();
    void plot();
    void warning();


public slots:
    void addPoint();
    void erase();


private:
    Ui::MainWindow *ui;
    QStringList qv_y_string;
    QVector<double> qv_x,qv_y;
    QString data;
};

#endif // MAINWINDOW_H
