#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Blog Statistics - MZ");

    QLabel *site = new QLabel();
    site->setContentsMargins(0,0,20,0);
    site->setOpenExternalLinks(true);
    site->setText("<a style='font-size:20px;' href=\"https://mengze.top\">mengze.top</a>");
    ui->statusBar->addPermanentWidget(site);

    ui->lblName->setText("Dir Path.");
    ui->lblNumDealing->setText("0");
    ui->lblNumCut->setText("/");
    ui->lblNumAll->setText("0");


    slLE[0] = ui->leSL1;
    slLE[1] = ui->leSL2;
    slLE[2] = ui->leSL3;
    slLE[3] = ui->leSL4;
    slLE[4] = ui->leSL5;
    slLE[5] = ui->leSL6;
    slLE[6] = ui->leSL7;
    slLE[7] = ui->leSL8;
    slLE[8] = ui->leSL9;
    slLE[9] = ui->leSL10;
    slLE[10] = ui->leSL11;
    slLE[11] = ui->leSL12;
    slStartLE[0] = ui->leSLs1;
    slStartLE[1] = ui->leSLs2;
    slStartLE[2] = ui->leSLs3;
    slStartLE[3] = ui->leSLs4;
    slStartLE[4] = ui->leSLs5;
    slStartLE[5] = ui->leSLs6;
    slStartLE[6] = ui->leSLs7;
    slStartLE[7] = ui->leSLs8;
    slStartLE[8] = ui->leSLs9;
    slStartLE[9] = ui->leSLs10;
    slStartLE[10] = ui->leSLs11;
    slStartLE[11] = ui->leSLs12;
    slEndLE[0] = ui->leSLe1;
    slEndLE[1] = ui->leSLe2;
    slEndLE[2] = ui->leSLe3;
    slEndLE[3] = ui->leSLe4;
    slEndLE[4] = ui->leSLe5;
    slEndLE[5] = ui->leSLe6;
    slEndLE[6] = ui->leSLe7;
    slEndLE[7] = ui->leSLe8;
    slEndLE[8] = ui->leSLe9;
    slEndLE[9] = ui->leSLe10;
    slEndLE[10] = ui->leSLe11;
    slEndLE[11] = ui->leSLe12;


    archivePath = archiveDir.currentPath();
    archiveFile.setFileName(archivePath + '/' + "Archive.txt");
    archiveFileText.setDevice(&archiveFile);
    ui->leArchive->setText(archiveFile.fileName());
    if(archiveFile.exists())
    {
        ui->statusBar->showMessage("Archive File Exists.", 5000);
        //qDebug()<<"Archive File Exists.";
        archiveDeal(Load);
    }
    else
    {
        pathA = pathDefault;
        ui->statusBar->showMessage("Archive File Not Exists!", 5000);
    }
    ui->leChoseDir->setText(pathA);
    ui->lblName->setText(pathA);
    dirA.setPath(pathA);

    rbtnCheck();

    ui->gbContinuousLine->setTitle(QString("Continuous Line - %1 Max")\
                                   .arg(MaxLineNum));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenDir_clicked()
{
    QDesktopServices::openUrl(QUrl(pathA));
}

void MainWindow::on_btnOpenAr_clicked()
{
    QDesktopServices::openUrl(QUrl(archivePath));
}


void MainWindow::on_btnChoseDir_clicked()
{
//    pathA = QFileDialog::getOpenFileName(this,
//                                         tr("Open Dir..."),
//                                         "E:/ATY/Projects/ATY/ProjectsOfEmbedded/Qt/EssayInfoGet/TestFile",
//                                         tr("MarkDown (*.md);;" "Text (*.txt);;" "AllFile (*.*)"));
    pathA = QFileDialog::getExistingDirectory(this,
                                              tr("Open Dir..."),
                                              pathDefault,
                                              QFileDialog::ShowDirsOnly);

    if(pathA.isEmpty())
        ui->lblName->setText("No Dir!");
    else
    {
        ui->leChoseDir->setText(pathA);
        ui->lblName->setText(pathA);
        dirA.setPath(pathA);
    }
}

void MainWindow::on_btnStart_clicked()
{
    QFile fileData(pathA + "/" + "_0_Data.txt");
    fileData.open(QFile::WriteOnly | QFile::Truncate);
    fileData.close();

    QStringList filtersA;
    filtersA<<QString("*.md");
    dirA.setFilter(QDir::Files | QDir::NoSymLinks);
    dirA.setNameFilters(filtersA);

    filesCount = dirA.count();
    filesCountStr = QString::number(filesCount);
    if(filesCount <= 0)
    {
        ui->lblNumAll->setText("0");
        ui->statusBar->showMessage("No Files!", 5000);
    }
    else
    {
        ui->lblNumAll->setText(filesCountStr);
        ui->statusBar->showMessage("Get " + filesCountStr + " Files!", 5000);
        ui->progressBar->setMaximum(filesCount);
        ui->lblName->setText(dirA[0]);

        for(int i=0; i < filesCount; i++)
        {
            ui->lblNumDealing->setText(QString::number(i));
            ui->progressBar->setValue(i);
            ui->lblName->setText(dirA[i]);

            filesNames.append(dirA[i]);

            if(!DealFiles(dirA[i]))
                break;

            ui->lblNumDealing->setText(QString::number(i+1));
            ui->progressBar->setValue(i+1);
        }
        ui->lblName->setText(pathA + "/" + "_0_Data.txt");
    }
}

bool MainWindow::DealFiles(QString fileNameRead)
{
    QFile fileRead(pathA + "/" + fileNameRead);

    if(fileRead.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(ui->rbtnContinuousLine->isChecked())
        {
            if((endLine >= startLine) && (startLine > 0) \
               && (endLine <= MaxLineNum))
            {
                for(int i=0; i<startLine-1; i++)
                    codec->toUnicode((QByteArray)fileRead.readLine().trimmed());
                for(int i=0; i<endLine+1-startLine; i++)
                {
                    lineStr[i] = codec->toUnicode((QByteArray)fileRead.readLine().trimmed());
                    lineDeal.append(lineStr[i]);
                    if(i != endLine-startLine)
                        lineDeal.append(delimiter);
                }
                lineDeal.append('\n');
            }
            else if((endLine < startLine) && (endLine > 0) \
                    && (startLine <= MaxLineNum))
            {
                for(int i=0; i<endLine-1; i++)
                    codec->toUnicode((QByteArray)fileRead.readLine().trimmed());
                for(int i=0; i<startLine+1-endLine; i++)
                {
                    lineStr[i] = codec->toUnicode((QByteArray)fileRead.readLine()).trimmed();
                    lineDeal.append(lineStr[i]);
                    if(i != startLine-endLine)
                        lineDeal.append(delimiter);
                }
                lineDeal.append('\n');
            }
            else
            {
                ui->statusBar->showMessage("Wrong Line Number!", 5000);
                return 0;
            }
        }
        else
        {
            fileRead.close();
            for(int i=0; i<specifiedLine; i++)
            {
                lineDeal.append(readLineDeal(&fileRead, sl[i], slStart[i], slEnd[i]));
                if(i+1 != specifiedLine)
                    lineDeal.append(delimiter);
            }
            lineDeal.append('\n');
        }
//        else
//        {
//            lineStr[0] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[0] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[1] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[2] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[3] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[3] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[3] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[3] = codec->toUnicode((QByteArray)fileRead.readLine());
//            lineStr[3] = codec->toUnicode((QByteArray)fileRead.readLine());

//            lineDeal = lineStr[0].mid(dataDealPosition_0, lineStr[0].length() - dataDealPosition_0 - 1);
//            lineDeal.append(delimiter);
//            lineDeal.append(lineStr[1].mid(dataDealPosition_1, lineStr[1].length() - dataDealPosition_1 - 1));
//            lineDeal.append(delimiter);
//            lineDeal.append(lineStr[2].mid(dataDealPosition_2, lineStr[2].length() - dataDealPosition_2 - 1));
//            lineDeal.append(delimiter);
//            lineDeal.append(lineStr[3].mid(dataDealPosition_3, lineStr[3].length() - dataDealPosition_3 - 1));
//            lineDeal.append('\n');
//        }
        qDebug() << lineDeal;
    }
    else
    {
        ui->statusBar->showMessage("Open Read File Fault!", 5000);
//        qDebug()<<"Open Read File Fault!";
    }
    fileRead.close();


    QFile fileWrite(pathA + "/" + "_0_Data.txt");
    QTextStream fileWriteText(&fileWrite);
    if(fileWrite.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
//        ui->statusBar->showMessage("Open '" + fileWrite.fileName() + "' Success!", 5000);
//        qDebug()<<"Open '" + fileWrite.fileName() + "' Success!";

        fileWriteText << lineDeal;
        lineDeal = "";
    }
    else
    {
        ui->statusBar->showMessage("Open Write File Fault!", 5000);
//        qDebug()<<"Open Write File Fault!";
    }
    fileWrite.close();

    return 1;
}

QString MainWindow::readLineDeal(QFile *file, int line, int startNmu, int endNum)
{
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    //qDebug()<<line<<startNmu<<endNum;
    if(!line)
    {
        ui->statusBar->showMessage("Wrong Line Number!", 5000);
        line = 1;
    }
    QString strReturn;
    for(int i=0; i<line; i++)
        strReturn = codec->toUnicode((QByteArray)file->readLine().trimmed());
    strReturn = strReturn.mid(startNmu, strReturn.length() - startNmu - endNum);
    file->close();
    return strReturn;
}


void MainWindow::on_rbtnContinuousLine_clicked()
{
    rbtnCheck();
}

void MainWindow::on_rbtnSpecifiedLine_clicked()
{
    rbtnCheck();
}

void MainWindow::rbtnCheck()
{
    ui->gbContinuousLine->setEnabled(false);
    ui->gbSpecifiedLine->setEnabled(false);
    if(ui->rbtnContinuousLine->isChecked())
    {
        ui->gbContinuousLine->setEnabled(true);
        //qDebug()<<"rbtnContinuousLine";
    }
    else
        ui->gbContinuousLine->setEnabled(false);
    if(ui->rbtnSpecifiedLine->isChecked())
    {
        ui->gbSpecifiedLine->setEnabled(true);
        //qDebug()<<"rbtnSpecifiedLine";
    }
    else
        ui->gbSpecifiedLine->setEnabled(false);
}

void MainWindow::on_cbDelimiter_currentTextChanged(const QString &arg1)
{
    //qDebug()<<arg1;

    ui->leDelimiter->clear();
    ui->leDelimiter->setEnabled(false);
    if(arg1 == "Custom...")
    {
        ui->leDelimiter->setEnabled(true);
    }
    else if(arg1 == "Tab")
        delimiter = "\t";
    else
        delimiter = arg1;
}

void MainWindow::on_leDelimiter_textChanged(const QString &arg1)
{
    delimiter = arg1;
}

void MainWindow::on_leStartLine_textChanged(const QString &arg1)
{
    startLine = arg1.toInt();
    //qDebug()<<startLine;
}

void MainWindow::on_leEndLine_textChanged(const QString &arg1)
{
    endLine = arg1.toInt();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
//    qDebug()<<arg1;
    if(arg1 > 12)
        ui->spinBox->setValue(12);
    specifiedLine = arg1;

    for(int i=0; i<MaxLineNum; i++)
    {
        slLE[i]->setEnabled(false);
        slStartLE[i]->setEnabled(false);
        slEndLE[i]->setEnabled(false);
    }
    for(int i=0; i<specifiedLine; i++)
    {
        slLE[i]->setEnabled(true);
        slStartLE[i]->setEnabled(true);
        slEndLE[i]->setEnabled(true);
    }
}

void MainWindow::on_leSL1_textChanged(const QString &arg1){
    sl[0] = arg1.toInt();}
void MainWindow::on_leSLs1_textChanged(const QString &arg1){
    slStart[0] = arg1.toInt();}
void MainWindow::on_leSLe1_textChanged(const QString &arg1){
    slEnd[0] = arg1.toInt();}
void MainWindow::on_leSL2_textChanged(const QString &arg1){
    sl[1] = arg1.toInt();}
void MainWindow::on_leSLs2_textChanged(const QString &arg1){
    slStart[1] = arg1.toInt();}
void MainWindow::on_leSLe2_textChanged(const QString &arg1){
    slEnd[1] = arg1.toInt();}
void MainWindow::on_leSL3_textChanged(const QString &arg1){
    sl[2] = arg1.toInt();}
void MainWindow::on_leSLs3_textChanged(const QString &arg1){
    slStart[2] = arg1.toInt();}
void MainWindow::on_leSLe3_textChanged(const QString &arg1){
    slEnd[2] = arg1.toInt();}
void MainWindow::on_leSL4_textChanged(const QString &arg1){
    sl[3] = arg1.toInt();}
void MainWindow::on_leSLs4_textChanged(const QString &arg1){
    slStart[3] = arg1.toInt();}
void MainWindow::on_leSLe4_textChanged(const QString &arg1){
    slEnd[3] = arg1.toInt();}
void MainWindow::on_leSL5_textChanged(const QString &arg1){
    sl[4] = arg1.toInt();}
void MainWindow::on_leSLs5_textChanged(const QString &arg1){
    slStart[4] = arg1.toInt();}
void MainWindow::on_leSLe5_textChanged(const QString &arg1){
    slEnd[4] = arg1.toInt();}
void MainWindow::on_leSL6_textChanged(const QString &arg1){
    sl[5] = arg1.toInt();}
void MainWindow::on_leSLs6_textChanged(const QString &arg1){
    slStart[5] = arg1.toInt();}
void MainWindow::on_leSLe6_textChanged(const QString &arg1){
    slEnd[5] = arg1.toInt();}
void MainWindow::on_leSL7_textChanged(const QString &arg1){
    sl[6] = arg1.toInt();}
void MainWindow::on_leSLs7_textChanged(const QString &arg1){
    slStart[6] = arg1.toInt();}
void MainWindow::on_leSLe7_textChanged(const QString &arg1){
    slEnd[6] = arg1.toInt();}
void MainWindow::on_leSL8_textChanged(const QString &arg1){
    sl[7] = arg1.toInt();}
void MainWindow::on_leSLs8_textChanged(const QString &arg1){
    slStart[7] = arg1.toInt();}
void MainWindow::on_leSLe8_textChanged(const QString &arg1){
    slEnd[7] = arg1.toInt();}
void MainWindow::on_leSL9_textChanged(const QString &arg1){
    sl[8] = arg1.toInt();}
void MainWindow::on_leSLs9_textChanged(const QString &arg1){
    slStart[8] = arg1.toInt();}
void MainWindow::on_leSLe9_textChanged(const QString &arg1){
    slEnd[8] = arg1.toInt();}
void MainWindow::on_leSL10_textChanged(const QString &arg1){
    sl[9] = arg1.toInt();}
void MainWindow::on_leSLs10_textChanged(const QString &arg1){
    slStart[9] = arg1.toInt();}
void MainWindow::on_leSLe10_textChanged(const QString &arg1){
    slEnd[9] = arg1.toInt();}
void MainWindow::on_leSL11_textChanged(const QString &arg1){
    sl[10] = arg1.toInt();}
void MainWindow::on_leSLs11_textChanged(const QString &arg1){
    slStart[10] = arg1.toInt();}
void MainWindow::on_leSLe11_textChanged(const QString &arg1){
    slEnd[10] = arg1.toInt();}
void MainWindow::on_leSL12_textChanged(const QString &arg1){
    sl[11] = arg1.toInt();}
void MainWindow::on_leSLs12_textChanged(const QString &arg1){
    slStart[11] = arg1.toInt();}
void MainWindow::on_leSLe12_textChanged(const QString &arg1){
    slEnd[11] = arg1.toInt();}

void MainWindow::archiveDeal(bool saveAload)
{
    //1:Default Path
    //2:Mod
    //3:Delimiter
    //4:Custom Delimiter or Empty

    //5C:Start Line
    //6C:End Line

    //5S:Specified Line
    //6->S:Line & slStart & endLine

    archiveFile.close();
    if(saveAload == Load)
    {
        if(archiveFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->statusBar->showMessage("Open Archive File Success!", 5000);

            //Line 1
            pathA = archiveFileText.readLine();
            //qDebug()<<pathA;
            if((pathA == "") || pathA == "\n")
            {
                //qDebug()<<"PathA Is Empty!";
                pathA = pathDefault;
            }
            //Line 2
            if(archiveFileText.readLine() == "0")
            {
                ui->rbtnContinuousLine->setChecked(true);
                ui->rbtnSpecifiedLine->setChecked(false);
            }
            else
            {
                ui->rbtnContinuousLine->setChecked(false);
                ui->rbtnSpecifiedLine->setChecked(true);
            }
            rbtnCheck();
            //Line 3
            int customDelimiterValue = archiveFileText.readLine().toInt();
            ui->cbDelimiter->setCurrentIndex(customDelimiterValue);
            on_cbDelimiter_currentTextChanged(QString(customDelimiterValue));
            delimiter = ui->cbDelimiter->currentText();
            //Line 4
            if(customDelimiterValue == 12)
            {
                delimiter = archiveFileText.readLine();
                ui->leDelimiter->setText(delimiter);
            }
            else
                archiveFileText.readLine();

            if(ui->rbtnContinuousLine->isChecked())
            {
                //Line 5C
                ui->leStartLine->setText(archiveFileText.readLine());
                startLine = ui->leStartLine->text().toInt();
                //Line 6C
                ui->leEndLine->setText(archiveFileText.readLine());
                endLine = ui->leEndLine->text().toInt();
            }
            else
            {
                //Line 5S
                specifiedLine = archiveFileText.readLine().toInt();
                //qDebug()<<specifiedLine;
                ui->spinBox->setValue(specifiedLine);
                on_spinBox_valueChanged(specifiedLine);
                //Line 6-> S
                for(int i=0; i<MaxLineNum; i++)
                {
                    slLE[i]->setText(archiveFileText.readLine());
                    slStartLE[i]->setText(archiveFileText.readLine());
                    slEndLE[i]->setText(archiveFileText.readLine());
                    sl[i] = slLE[i]->text().toInt();
                    slStart[i] = slStartLE[i]->text().toInt();
                    slEnd[i] = slEndLE[i]->text().toInt();
                }
            }
        }
        else
            ui->statusBar->showMessage("Open Archive File Fault!", 5000);
        archiveFile.close();
    }
    else
    {
        if(archiveFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->statusBar->showMessage("Open Archive File Success!", 5000);

            //Line 1
            archiveFileText << pathA << '\n';
            //Line 2
            if(ui->rbtnContinuousLine->isChecked())
                archiveFileText << 0 << '\n';
            else
                archiveFileText << 1 << '\n';
            //Line 3
            archiveFileText << ui->cbDelimiter->currentIndex() << '\n';
            //Line 4
            archiveFileText << delimiter << '\n';

            if(ui->rbtnContinuousLine->isChecked())
            {
                //Line 5C
                archiveFileText << startLine << '\n';
                //Line 6C
                archiveFileText << endLine << '\n';
            }
            else
            {
                //Line 5S
                archiveFileText << specifiedLine << '\n';
                //Line 6->S
                for(int i=0; i<MaxLineNum; i++)
                {
                    archiveFileText << sl[i] << '\n';
                    archiveFileText << slStart[i] << '\n';
                    archiveFileText << slEnd[i] << '\n';
                }
            }
        }
        else
            ui->statusBar->showMessage("Open Archive File Fault!", 5000);
        archiveFile.close();
    }
}

void MainWindow::on_btnSaveSetting_clicked()
{
    archiveDeal(Save);
}
