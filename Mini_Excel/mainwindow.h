#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int first=0;
    int tmp=1;
    QString vl="";
    void keyPressEvent(QKeyEvent* event);


private slots:
    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

private:
    void setValueAt(int ix, int jx, const QString &value);
    QString getValueAt(int ix, int jx);

    Ui::MainWindow *ui;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
