#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFile"
#include "QFileDialog"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateWordFreq(QString text, QString delimeter)
{
    QStringList words=text.split(delimeter);

    for(auto word : words)
    {
        m_word_set[word]++;
    }
    QList<int> word_count_list=m_word_set.values();
    std::sort(word_count_list.rbegin(),word_count_list.rend());

    int text_len=words.length();
    int word_len=word_count_list.length();

    int rate20=word_len/5;

    int size80=0;
    for(int i=0;i<rate20;i++)
    {
        size80+=word_count_list[i];
    }

    double rate =(double)size80/(double)text_len;
    //qDebug()<<"Total Word Count  :" << text_len;
    ui->lblTotalWordCnt->setText(QString::number(text_len));
    //qDebug()<<"Unique Word Count :" << word_len;
    ui->lblUniqueWord->setText(QString::number(word_len));
    //qDebug()<<"The rate is :%"<<rate*100;
    ui->lblRatio->setText("%"+QString::number(rate*100));

}

void MainWindow::on_calcButton_clicked()
{
    m_word_set.clear();
    calculateWordFreq(m_text);
}

void MainWindow::on_fileBtn_clicked()
{
    on_btnlClear_clicked();
    if(m_lastPath.isEmpty())
        m_lastPath= QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), m_lastPath, tr("Text Files (*.txt *.pdf *.doc)"));
    QFile *file =new QFile(fileName);
    QFileInfo *f_info=new QFileInfo(fileName);
    m_lastPath=f_info->absolutePath();
    ui->lblFileName->setText(f_info->baseName());

    if(file->open(QIODevice::ReadWrite))
    {
        m_text=file->readAll();
    }

}

void MainWindow::on_btnlClear_clicked()
{
    ui->lblFileName->clear();
    ui->lblRatio->clear();
    ui->lblTotalWordCnt->clear();
    ui->lblUniqueWord->clear();

}
