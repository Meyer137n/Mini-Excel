#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QTableWidget>
#include <QKeyEvent>
#include <QModelIndexList>
#include <QClipboard>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    model = new QStandardItemModel(99,26,this);

    ui->tableView->setModel(model);
    for(int i=0; i<26; ++i)
        model->setHeaderData(i,Qt::Horizontal,QString((char)('A'+i)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent* event) {
    // If Ctrl-C typed
    if (event->key() == Qt::Key_C && (event->modifiers() & Qt::ControlModifier))
    {

        int col = ui->tableView->currentIndex().column();
        int row = ui->tableView->currentIndex().row();
        QModelIndex index=model->index(row,col);
        vl = model->data(index).toString();

    }
    // If Ctrl-V typed
    if (event->key() == Qt::Key_V && (event->modifiers() & Qt::ControlModifier))
    {

        int col = ui->tableView->currentIndex().column();
        int row = ui->tableView->currentIndex().row();
        QModelIndex index=model->index(row,col);
        model->setData(index,vl);
    }

    // If Enter typed
    if (((event->key()==Qt::Key_Enter) || (event->key()==Qt::Key_Return)))
    {

        int col = ui->tableView->currentIndex().column();
        int row = ui->tableView->currentIndex().row();
        QModelIndex index=model->index(row,col);
        QString tmp_val = model->data(index).toString();
        QString ANS="";

        QStringList esli=tmp_val.split("=ЕСЛИ");
        if (esli.size()==2)
        {
            QStringList to = esli[1].split(")то(");
            QString uslovie1 = to[0].split('(')[1];
            QString uslovie2 = to[1].split(')')[0];


            bool check=false;
            QStringList check_uslovie11 = uslovie1.split('>');
            if (check_uslovie11.size()==2)
            {
                QString colA = check_uslovie11[0][0];
                QString colB = "";
                for (int i=1; i< check_uslovie11[0].size(); ++i)
                    colB+=check_uslovie11[0][i];

                int col1 = 0;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==colA)
                        col1=i;
                int row1 = colB.toInt()-1;

                QModelIndex index1=model->index(row1,col1);
                QString tmp_val1 = model->data(index1).toString();
                colA = check_uslovie11[1][0];
                colB = "";
                for (int i=1; i< check_uslovie11[1].size(); ++i)
                    colB+=check_uslovie11[1][i];

                int col2 = 0;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==colA)
                        col2=i;
                int row2 = colB.toInt()-1;
                QModelIndex index2=model->index(row2,col2);
                QString tmp_val2 = model->data(index2).toString();

                if (tmp_val1.toInt()>tmp_val2.toInt())
                  check=true;
            }

            QStringList check_uslovie12 = uslovie1.split('<');
            if (check_uslovie12.size()==2)
            {
                QString colA = check_uslovie12[0][0];
                QString colB = "";
                for (int i=1; i< check_uslovie12[0].size(); ++i)
                    colB+=check_uslovie12[0][i];

                int col1 = 0;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==colA)
                        col1=i;
                int row1 = colB.toInt()-1;

                QModelIndex index1=model->index(row1,col1);
                QString tmp_val1 = model->data(index1).toString();
                colA = check_uslovie12[1][0];
                colB = "";
                for (int i=1; i< check_uslovie12[1].size(); ++i)
                    colB+=check_uslovie12[1][i];

                int col2 = 0;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==colA)
                        col2=i;
                int row2 = colB.toInt()-1;
                QModelIndex index2=model->index(row2,col2);
                QString tmp_val2 = model->data(index2).toString();

                if (tmp_val1.toInt()<tmp_val2.toInt())
                  check=true;
            }

            QStringList check_uslovie13 = uslovie1.split('=');
            if (check_uslovie13.size()==2)
            {
                QString colA = check_uslovie13[0][0];
                QString colB = "";
                for (int i=1; i< check_uslovie13[0].size(); ++i)
                    colB+=check_uslovie13[0][i];

                int col1 = 0;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==colA)
                        col1=i;
                int row1 = colB.toInt()-1;

                QModelIndex index1=model->index(row1,col1);
                QString tmp_val1 = model->data(index1).toString();
                colA = check_uslovie13[1][0];
                colB = "";
                for (int i=1; i< check_uslovie13[1].size(); ++i)
                    colB+=check_uslovie13[1][i];

                int col2 = 0;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==colA)
                        col2=i;
                int row2 = colB.toInt()-1;
                QModelIndex index2=model->index(row2,col2);
                QString tmp_val2 = model->data(index2).toString();

                if (tmp_val1.toInt()==tmp_val2.toInt())
                  check=true;
            }

            if (check)
            {
                double val1=0;
                double val2=0;
                QString sym="";
                QStringList li1=uslovie2.split('+');
                if (li1.size()==2)
                {
                    bool chek1=true;
                    for(int i=0; i<26; ++i)
                        if (QString((char)('A'+i))==li1[0][0])
                        {
                            chek1=false;

                            QString colB = li1[0].split(li1[0][0])[1];
                            index=model->index(colB.toInt()-1,i);
                            val1 = model->data(index).toInt();

                        }
                    if (chek1)
                        val1 = li1[0].toDouble();
                    val2 = li1[1].toDouble();
                    sym='+';
                }
                QStringList li2=uslovie2.split('-');
                if (li2.size()==2)
                {
                    bool chek1=true;
                    for(int i=0; i<26; ++i)
                        if (QString((char)('A'+i))==li2[0][0])
                        {
                            chek1=false;

                            QString colB = li2[0].split(li2[0][0])[1];
                            index=model->index(colB.toInt()-1,i);
                            val1 = model->data(index).toInt();
                        }
                    if (chek1)
                    val1 = li2[0].toDouble();
                    val2 = li2[1].toDouble();
                    sym='-';
                }
                QStringList li3=uslovie2.split('*');
                if (li3.size()==2)
                {
                    bool chek1=true;
                    for(int i=0; i<26; ++i)
                        if (QString((char)('A'+i))==li3[0][0])
                        {
                            chek1=false;

                            QString colB = li3[0].split(li3[0][0])[1];
                            index=model->index(colB.toInt()-1,i);
                            val1 = model->data(index).toInt();
                        }
                    if (chek1)
                    val1 = li3[0].toDouble();
                    val2 = li3[1].toDouble();
                    sym='*';
                }
                QStringList li4=uslovie2.split('/');
                if (li4.size()==2)
                {
                    bool chek1=true;
                    for(int i=0; i<26; ++i)
                        if (QString((char)('A'+i))==li4[0][0])
                        {
                            chek1=false;

                            QString colB = li4[0].split(li4[0][0])[1];
                            index=model->index(colB.toInt()-1,i);
                            val1 = model->data(index).toInt();

                        }
                    if (chek1)
                        val1 = li4[0].toDouble();
                    val2 = li4[1].toDouble();
                    sym='/';
                }
                QStringList li5=uslovie2.split('^');
                if (li5.size()==2)
                {
                    bool chek1=true;
                    for(int i=0; i<26; ++i)
                        if (QString((char)('A'+i))==li5[0][0])
                        {
                            chek1=false;

                            QString colB = li5[0].split(li5[0][0])[1];
                            index=model->index(colB.toInt()-1,i);
                            val1 = model->data(index).toInt();

                        }
                    if (chek1)
                        val1 = li5[0].toDouble();
                    val2 = li5[1].toDouble();
                    sym='^';
                }



                if (sym=='+')
                    ANS=QString::number(val1+val2);
                if (sym=='-')
                    ANS=QString::number(val1-val2);
                if (sym=='*')
                    ANS=QString::number(val1*val2);
                if (sym=='/')
                    ANS=QString::number(val1/val2);
                if (sym=='^')
                    ANS=QString::number(pow(val1,val2));
                if (sym!="")
                    model->setData(index,ANS);

            }

        } else if (tmp_val[0]=='='){
            double val1=0;
            double val2=0;
            QString sym="";
            QStringList li1=tmp_val.split('=')[1].split('+');
            if (li1.size()==2)
            {
                bool chek1=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li1[0][0])
                    {
                        chek1=false;

                        QString colB = li1[0].split(li1[0][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val1 = model->data(index1).toInt();

                    }
                if (chek1)
                    val1 = li1[0].toDouble();

                bool chek2=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li1[1][0])
                    {
                        chek2=false;

                        QString colB = li1[1].split(li1[1][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val2 = model->data(index1).toInt();

                    }
                if (chek2)
                    val2 = li1[1].toDouble();
                sym='+';
            }
            QStringList li2=tmp_val.split('=')[1].split('-');
            if (li2.size()==2)
            {
                bool chek1=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li2[0][0])
                    {
                        chek1=false;

                        QString colB = li2[0].split(li2[0][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val1 = model->data(index1).toInt();

                    }
                if (chek1)
                    val1 = li2[0].toDouble();

                bool chek2=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li2[1][0])
                    {
                        chek2=false;

                        QString colB = li2[1].split(li2[1][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val2 = model->data(index1).toInt();

                    }
                if (chek2)
                    val2 = li2[1].toDouble();
                sym='-';
            }
            QStringList li3=tmp_val.split('=')[1].split('*');
            if (li3.size()==2)
            {
                bool chek1=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li3[0][0])
                    {
                        chek1=false;

                        QString colB = li3[0].split(li3[0][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val1 = model->data(index1).toInt();

                    }
                if (chek1)
                    val1 = li3[0].toDouble();

                bool chek2=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li3[1][0])
                    {
                        chek2=false;

                        QString colB = li3[1].split(li3[1][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val2 = model->data(index1).toInt();

                    }
                if (chek2)
                    val2 = li3[1].toDouble();

                sym='*';
            }

            QStringList li4=tmp_val.split('=')[1].split('/');
            if (li4.size()==2)
            {
                bool chek1=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li4[0][0])
                    {
                        chek1=false;

                        QString colB = li4[0].split(li4[0][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val1 = model->data(index1).toInt();

                    }
                if (chek1)
                    val1 = li4[0].toDouble();

                bool chek2=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li4[1][0])
                    {
                        chek2=false;

                        QString colB = li4[1].split(li4[1][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val2 = model->data(index1).toInt();

                    }
                if (chek2)
                    val2 = li4[1].toDouble();
                sym='/';
            }

            QStringList li5=tmp_val.split('=')[1].split('^');
            if (li5.size()==2)
            {
                bool chek1=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li5[0][0])
                    {
                        chek1=false;

                        QString colB = li5[0].split(li5[0][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val1 = model->data(index1).toInt();

                    }
                if (chek1)
                    val1 = li5[0].toDouble();

                bool chek2=true;
                for(int i=0; i<26; ++i)
                    if (QString((char)('A'+i))==li5[1][0])
                    {
                        chek2=false;

                        QString colB = li5[1].split(li5[1][0])[1];
                        QModelIndex index1=model->index(colB.toInt()-1,i);
                        val2 = model->data(index1).toInt();

                    }
                if (chek2)
                    val2 = li5[1].toDouble();

                sym='^';
            }

            if (sym=='+')
                ANS=QString::number(val1+val2);
            if (sym=='-')
                ANS=QString::number(val1-val2);
            if (sym=='*')
                ANS=QString::number(val1*val2);
            if (sym=='/')
                ANS=QString::number(val1/val2);
            if (sym=='^')
                ANS=QString::number(pow(val1,val2));
            if (sym!="")
                model->setData(index,ANS);
        }
    }
}

void MainWindow::on_action_2_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Сохранить", QDir::rootPath(), "CSV File (*.csv)");
    if (filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream xout(&file);
    const int rowCount = model->rowCount();
    const int colCount = model->columnCount();
    for (int ix = 0; ix < rowCount; ++ix)
    {
        xout << getValueAt(ix,0);
        for (int jx = 1; jx <colCount; ++jx)
        {
            xout << "; " << getValueAt(ix,jx);
        }
        xout << "\n";
    }
    file.flush();
    file.close();
}

void MainWindow::on_action_3_triggered()
{
    auto filename = QFileDialog::getOpenFileName(this,"Открыть", QDir::rootPath(),"CSV File (*.csv)");
    if (filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream xin(&file);
    int ix =0;
    while (!xin.atEnd())
    {
        model->setRowCount(ix);
        auto line = xin.readLine();
        auto values = line.split(";");
        const int colCount = values.size();
        model->setColumnCount(colCount);
        for (int jx = 0; jx < colCount; ++jx)
        {
            setValueAt(ix,jx, values.at(jx));
        }
        ++ix;
    }
    file.close();
}

void MainWindow::setValueAt(int ix, int jx, const QString &value)
{
    if (!model->item(ix,jx)){
        model->setItem(ix,jx, new QStandardItem(value));
    } else {
        model->item(ix,jx)->setText(value);
    }

}

QString MainWindow::getValueAt(int ix, int jx)
{
    if (!model->item(ix,jx)){
        return "";
    }
    return model->item(ix, jx)->text();
}


void MainWindow::on_action_10_triggered()
{
    model->removeRows(ui->tableView->currentIndex().row(), 1);
}


void MainWindow::on_action_9_triggered()
{
    model->removeColumns(ui->tableView->currentIndex().column(), 1);
}


void MainWindow::on_action_7_triggered()
{
    int row = ui->tableView->currentIndex().row();
    model->insertRows(row, 1);

    QModelIndex in = model->index(row, 1);
    ui->tableView->setCurrentIndex(in);
}


void MainWindow::on_action_6_triggered()
{
    int col = ui->tableView->currentIndex().column();
    model->insertColumns(col, 1);

    QModelIndex in = model->index(col, 1);
    ui->tableView->setCurrentIndex(in);
}












