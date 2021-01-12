#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>
#include <QLineEdit>

#define MaxLineNum 12
#define Load 0
#define Save 1


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //QString pathDefault = "E:/ATY/Projects/ATY/ProjectsOfEmbedded/Qt/EssayInfoGet/TestFile";
    QString pathDefault = "E:/ATY/Projects/ATY/ProjectsOfHTML/hexo/source/_posts";
    QString pathA;
    QDir dirA;

    int filesCount = 0;
    QString filesCountStr;
    QStringList filesNames;

    QFile archiveFile;
    QTextStream archiveFileText;
    QDir archiveDir;
    QString archivePath;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString lineStr[MaxLineNum];
    QString lineDeal;

    int startLine = 1;
    int endLine = 2;
    int specifiedLine = 0;
    int sl[MaxLineNum] = {0};
    int slStart[MaxLineNum] = {0};
    int slEnd[MaxLineNum] = {0};
    QLineEdit *slLE[MaxLineNum];
    QLineEdit *slStartLE[MaxLineNum];
    QLineEdit *slEndLE[MaxLineNum];

    bool DealFiles(QString fileNameRead);
    QString delimiter = ",";

//    int dataDealPosition_0 = 7;
//    int dataDealPosition_1 = 6;
//    int dataDealPosition_2 = 6;
//    int dataDealPosition_3 = 7;

private slots:
    void on_btnOpenDir_clicked();
    void on_btnOpenAr_clicked();
    void on_btnChoseDir_clicked();

    void on_btnStart_clicked();

    void on_rbtnContinuousLine_clicked();
    void on_rbtnSpecifiedLine_clicked();
    void rbtnCheck();

    void on_cbDelimiter_currentTextChanged(const QString &arg1);
    void on_leDelimiter_textChanged(const QString &arg1);

    void on_leStartLine_textChanged(const QString &arg1);
    void on_leEndLine_textChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);
    QString readLineDeal(QFile *file, int line, int startNmu, int endNum);

    void on_leSL1_textChanged(const QString &arg1);
    void on_leSLs1_textChanged(const QString &arg1);
    void on_leSLe1_textChanged(const QString &arg1);
    void on_leSL2_textChanged(const QString &arg1);
    void on_leSLs2_textChanged(const QString &arg1);
    void on_leSLe2_textChanged(const QString &arg1);
    void on_leSL3_textChanged(const QString &arg1);
    void on_leSLs3_textChanged(const QString &arg1);
    void on_leSLe3_textChanged(const QString &arg1);
    void on_leSL4_textChanged(const QString &arg1);
    void on_leSLs4_textChanged(const QString &arg1);
    void on_leSLe4_textChanged(const QString &arg1);
    void on_leSL5_textChanged(const QString &arg1);
    void on_leSLs5_textChanged(const QString &arg1);
    void on_leSLe5_textChanged(const QString &arg1);
    void on_leSL6_textChanged(const QString &arg1);
    void on_leSLs6_textChanged(const QString &arg1);
    void on_leSLe6_textChanged(const QString &arg1);
    void on_leSL7_textChanged(const QString &arg1);
    void on_leSLs7_textChanged(const QString &arg1);
    void on_leSLe7_textChanged(const QString &arg1);
    void on_leSL8_textChanged(const QString &arg1);
    void on_leSLs8_textChanged(const QString &arg1);
    void on_leSLe8_textChanged(const QString &arg1);
    void on_leSL9_textChanged(const QString &arg1);
    void on_leSLs9_textChanged(const QString &arg1);
    void on_leSLe9_textChanged(const QString &arg1);
    void on_leSL10_textChanged(const QString &arg1);
    void on_leSLs10_textChanged(const QString &arg1);
    void on_leSLe10_textChanged(const QString &arg1);
    void on_leSL11_textChanged(const QString &arg1);
    void on_leSLs11_textChanged(const QString &arg1);
    void on_leSLe11_textChanged(const QString &arg1);
    void on_leSL12_textChanged(const QString &arg1);
    void on_leSLs12_textChanged(const QString &arg1);
    void on_leSLe12_textChanged(const QString &arg1);

    void archiveDeal(bool saveAload);  //0:load, 1:save
    void on_btnSaveSetting_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
