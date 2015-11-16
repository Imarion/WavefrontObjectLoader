
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QDoubleValidator>
#include <QLocale>

#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_about.h"

const QString MainWindow::configFileName = "config.xml";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);
    uiMainWindow->scaleStepLineEdit->setValidator(new QDoubleValidator(uiMainWindow->scaleXSpinBox->minimum(), uiMainWindow->scaleXSpinBox->maximum(), uiMainWindow->scaleXSpinBox->decimals(), this));

    defaultDataDir = "";

    MyGlWindow = new GlWindow();
    if (MyGlWindow) MyGlWindow->show();        

    checkConfigfile();
    readDefaultDataDir();    
}

MainWindow::~MainWindow()
{
    saveConfigFile();

    delete uiMainWindow;
}

void MainWindow::on_MenuFileLoad_triggered()
{
    QString file;
    QLocale dloc;

    file = QFileDialog::getOpenFileName(this, "Open File", defaultDataDir, "Files(*.obj)");
    if (file != "")
    {
        defaultDataDir = QFileInfo(file).absolutePath();

        MyGlWindow->setObjFile(file);
        MyGlWindow->displayObj();        
        uiMainWindow->autoScaleEdit->setText(dloc.toString(MyGlWindow->getAutoScale()));

        setManualScaletoAuto();
        setGlWindowScale();
        setScaleStep();
    }
}

void MainWindow::closeEvent (QCloseEvent * event)
{
    Q_UNUSED(event)

    if (MyGlWindow)
    {
        MyGlWindow->close();
        delete MyGlWindow;
    }
}

void MainWindow::checkConfigfile()
{
    QFile configFile(configFileName);

    if (!configFile.exists())
    {
        saveConfigFile();
    }

}

void MainWindow::readDefaultDataDir()
{
    QDomDocument configDoc;
    QFile configFile(configFileName);

    if (configFile.open(QIODevice::ReadOnly))
    {
        configDoc.setContent(&configFile);
        QDomNodeList nl = configDoc.elementsByTagName("DefaultDataDir");
        QDomNode     n  = nl.item(0);
        QDomElement  e  = n.toElement();

        defaultDataDir=e.text();
        configFile.close();
    }
    else
    {
        qDebug() << "La y a vraiment un stuut pour ouvrir l'xml";
    }
}

bool MainWindow::saveConfigFile()
{
    QFile configFile(configFileName);

    if (configFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QDomDocument configDoc;

        QDomElement UserSettings = configDoc.createElement("UserSettings");

        QDomElement DefaultDataDir = configDoc.createElement("DefaultDataDir");
        DefaultDataDir.appendChild(configDoc.createTextNode(defaultDataDir));
        UserSettings.appendChild(DefaultDataDir);

        configDoc.appendChild(UserSettings);

        QTextStream out(&configFile);
        out << configDoc.toString();

        configFile.close();
        return true;
    }
    return false;
}

double MainWindow::calculateStep(double val)
{
    return pow(10, floor(log10(val)));
}

void MainWindow::setScaleStep()
{
    QLocale dloc;

    uiMainWindow->scaleStepLineEdit->setText(dloc.toString(calculateStep(dloc.toDouble(uiMainWindow->autoScaleEdit->text()))/10.0f));
}

void MainWindow::setManualScaletoAuto()
{
    QLocale dLoc;

    uiMainWindow->scaleXSpinBox->setValue(dLoc.toDouble(uiMainWindow->autoScaleEdit->text()));
    uiMainWindow->scaleYSpinBox->setValue(dLoc.toDouble(uiMainWindow->autoScaleEdit->text()));
    uiMainWindow->scaleZSpinBox->setValue(dLoc.toDouble(uiMainWindow->autoScaleEdit->text()));
}

void MainWindow::on_scaleXSpinBox_valueChanged(double arg1)
{
    MyGlWindow->setScaleX(arg1);
}

void MainWindow::on_scaleYSpinBox_valueChanged(double arg1)
{
    MyGlWindow->setScaleY(arg1);
}

void MainWindow::on_scaleZSpinBox_valueChanged(double arg1)
{
    MyGlWindow->setScaleZ(arg1);
}

void MainWindow::on_scaleManual_clicked()
{
    QLocale dLoc;

    uiMainWindow->scaleXSpinBox->setEnabled(true);
    uiMainWindow->scaleYSpinBox->setEnabled(true);
    uiMainWindow->scaleZSpinBox->setEnabled(true);

    uiMainWindow->scaleXSpinBox->setSingleStep(dLoc.toDouble(uiMainWindow->scaleStepLineEdit->text()));
    uiMainWindow->scaleYSpinBox->setSingleStep(dLoc.toDouble(uiMainWindow->scaleStepLineEdit->text()));
    uiMainWindow->scaleZSpinBox->setSingleStep(dLoc.toDouble(uiMainWindow->scaleStepLineEdit->text()));

    setGlWindowScale();
}

void MainWindow::on_scaleAuto_clicked()
{

    uiMainWindow->scaleXSpinBox->setDisabled(true);
    uiMainWindow->scaleYSpinBox->setDisabled(true);
    uiMainWindow->scaleZSpinBox->setDisabled(true);

    //MyGlWindow->setAutoScale();
    setGlWindowScale();
}

void MainWindow::setGlWindowScale()
{
    if (uiMainWindow->scaleManual->isChecked())
    {
        MyGlWindow->setScaleX(uiMainWindow->scaleXSpinBox->value());
        MyGlWindow->setScaleY(uiMainWindow->scaleYSpinBox->value());
        MyGlWindow->setScaleZ(uiMainWindow->scaleZSpinBox->value());
    } else if (uiMainWindow->scaleAuto->isChecked())
    {
        MyGlWindow->setAutoScale();
    }
}

void MainWindow::on_scaleStepLineEdit_textChanged(const QString &arg1)
{
    QLocale dLoc;

    uiMainWindow->scaleXSpinBox->setSingleStep(dLoc.toDouble(uiMainWindow->scaleStepLineEdit->text()));
    uiMainWindow->scaleYSpinBox->setSingleStep(dLoc.toDouble(uiMainWindow->scaleStepLineEdit->text()));
    uiMainWindow->scaleZSpinBox->setSingleStep(dLoc.toDouble(uiMainWindow->scaleStepLineEdit->text()));
}

void MainWindow::on_manualRotateRadioButton_clicked()
{
    MyGlWindow->setRotAuto(false);
}

void MainWindow::on_autoRotateRadioButton_clicked()
{
    MyGlWindow->setRotAuto(true);
}

void MainWindow::on_actionAbout_triggered()
{
    Ui::About uiAboutDlg;
    QDialog d;
    uiAboutDlg.setupUi(&d);
    d.exec();
}
