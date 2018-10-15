#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCustomPlot *customPlot = ui->widget;

    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->yAxis->setRange(0, 150);

    customPlot->xAxis->setLabel("Temps");
    customPlot->yAxis->setLabel("Taux de remplissage de la poubelle (%)");

    //connect(ui->refreshBt,SIGNAL(clicked(bool)),this,SLOT(plot()));
    connect(ui->refreshBt,SIGNAL(clicked(bool)),this,SLOT(addPoint()));
    connect(ui->eraseBt,SIGNAL(clicked(bool)),this,SLOT(erase()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::erase()
{
    QFile fichier("data.txt");

    if(fichier.open(QIODevice::WriteOnly))
        {
             fichier.flush();
             fichier.close();
        }

}



void MainWindow::addPoint()
{
    QFile fichier("data.txt"); //   !!!!!!!!!!!!!!!!!!! ATTENTION AU CHEMIN !!!!!!!! A mettre dans "build" en dehors de debug et release !

    if(fichier.open(QIODevice::ReadOnly))
        {
             data = fichier.readAll();
             fichier.close();
        }

    qv_x.clear();
    qv_y.clear();

    data.remove('\n');
    data.remove('\r');

    qv_y_string=data.split(";");//.append(y);

    double lg_poubelle = 50.0;
    for(int a=0;a<qv_y_string.size();a++)
    {
        double measure = (qv_y_string.at(a)).toDouble();
        double taux = ((lg_poubelle-measure)/(lg_poubelle))*100.0;
        qv_y.append(taux);
    }

    if(qv_y.last()>=90)
    {
        warning();
    }


    for(int i=0;i<qv_y.size();i++)
    {
        qv_x.append(i);
    }

    this->plot();
}

void MainWindow::plot()
{
    ui->widget->graph(0)->setData(qv_x,qv_y);
    ui->widget->graph(0)->rescaleKeyAxis();
    ui->widget->replot();
    ui->widget->update();

}

void MainWindow::warning()
{
    //QMessageBox::critical(this, "Attention !", "Le taux de remplissage de la poubelle a dépassé le seuil de 90%, il faut aller la vider");
}
