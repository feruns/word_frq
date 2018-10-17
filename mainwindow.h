#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void calculateWordFreq(QString text , QString delimeter=" ");

private slots:
    void on_calcButton_clicked();
    void on_fileBtn_clicked();

    void on_btnlClear_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString,int> m_word_set;
    QByteArray m_text;
    QString m_lastPath;
};

#endif // MAINWINDOW_H
