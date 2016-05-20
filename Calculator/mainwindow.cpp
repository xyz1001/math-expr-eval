#encoding="GBK"
#include "mainwindow.h"
#include <exception>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Quit=new QAction(QIcon(":image/quit"),tr("Quit"),this);
    Quit->setShortcut(QKeySequence::Quit);
    connect(Quit,&QAction::triggered,this,&MainWindow::close);

    File=menuBar()->addMenu(tr("&File"));
    File->addAction(Quit);

    CentralWidget=new QWidget(this);
    setCentralWidget(CentralWidget);
    setWindowTitle(tr("Calculator"));
    NumberLayout=new QGridLayout();
    NumberButton0=new QPushButton(tr("0"));
    NumberButton1=new QPushButton(tr("1"));
    NumberButton2=new QPushButton(tr("2"));
    NumberButton3=new QPushButton(tr("3"));
    NumberButton4=new QPushButton(tr("4"));
    NumberButton5=new QPushButton(tr("5"));
    NumberButton6=new QPushButton(tr("6"));
    NumberButton7=new QPushButton(tr("7"));
    NumberButton8=new QPushButton(tr("8"));
    NumberButton9=new QPushButton(tr("9"));
    OperatorButtonPoint=new QPushButton(tr("."));
    OperatorButtonEqual=new QPushButton(tr("="));
    connect(NumberButton0,&QPushButton::clicked,this,&MainWindow::setResultText0);
    connect(NumberButton1,&QPushButton::clicked,this,&MainWindow::setResultText1);
    connect(NumberButton2,&QPushButton::clicked,this,&MainWindow::setResultText2);
    connect(NumberButton3,&QPushButton::clicked,this,&MainWindow::setResultText3);
    connect(NumberButton4,&QPushButton::clicked,this,&MainWindow::setResultText4);
    connect(NumberButton5,&QPushButton::clicked,this,&MainWindow::setResultText5);
    connect(NumberButton6,&QPushButton::clicked,this,&MainWindow::setResultText6);
    connect(NumberButton7,&QPushButton::clicked,this,&MainWindow::setResultText7);
    connect(NumberButton8,&QPushButton::clicked,this,&MainWindow::setResultText8);
    connect(NumberButton9,&QPushButton::clicked,this,&MainWindow::setResultText9);
    connect(OperatorButtonPoint,&QPushButton::clicked,this,&MainWindow::setResultTextPoint);
    connect(OperatorButtonEqual,&QPushButton::clicked,this,&MainWindow::setResultTextEqual);

    NumberLayout->addWidget(OperatorButtonEqual,3,2);
    NumberLayout->addWidget(OperatorButtonPoint,3,1);
    NumberLayout->addWidget(NumberButton0,3,0);
    NumberLayout->addWidget(NumberButton1,2,0);
    NumberLayout->addWidget(NumberButton2,2,1);
    NumberLayout->addWidget(NumberButton3,2,2);
    NumberLayout->addWidget(NumberButton4,1,0);
    NumberLayout->addWidget(NumberButton5,1,1);
    NumberLayout->addWidget(NumberButton6,1,2);
    NumberLayout->addWidget(NumberButton7,0,0);
    NumberLayout->addWidget(NumberButton8,0,1);
    NumberLayout->addWidget(NumberButton9,0,2);

    OperatorLayout=new QVBoxLayout();
    OperatorButtonAdd=new QPushButton(tr("+"));
    OperatorButtonSub=new QPushButton(tr("-"));
    OperatorButtonMul=new QPushButton(tr("*"));
    OperatorButtonDiv=new QPushButton(tr("/"));
    connect(OperatorButtonAdd,&QPushButton::clicked,this,&MainWindow::setResultTextAdd);
    connect(OperatorButtonSub,&QPushButton::clicked,this,&MainWindow::setResultTextSub);
    connect(OperatorButtonMul,&QPushButton::clicked,this,&MainWindow::setResultTextMul);
    connect(OperatorButtonDiv,&QPushButton::clicked,this,&MainWindow::setResultTextDiv);
    OperatorLayout->addWidget(OperatorButtonAdd);
    OperatorLayout->addWidget(OperatorButtonSub);
    OperatorLayout->addWidget(OperatorButtonMul);
    OperatorLayout->addWidget(OperatorButtonDiv);

    FunctionKeyLayout=new QVBoxLayout();
    FunctionKeyButtonCE=new QPushButton(tr("CE"));
    FunctionKeyButtonDelete=new QPushButton(tr("Delete"));
    FunctionKeyButtonAns=new QPushButton(tr("Ans"));
    FunctionKeyButtonQuit=new QPushButton(tr("Quit"));
    FunctionKeyLayout->addWidget(FunctionKeyButtonDelete);
    FunctionKeyLayout->addWidget(FunctionKeyButtonCE);
    FunctionKeyLayout->addWidget(FunctionKeyButtonAns);
    FunctionKeyLayout->addWidget(FunctionKeyButtonQuit);
    connect(FunctionKeyButtonDelete,&QPushButton::clicked,this,&MainWindow::setResultTextDelete);
    connect(FunctionKeyButtonCE,&QPushButton::clicked,this,&MainWindow::setResultTextCE);
    connect(FunctionKeyButtonAns,&QPushButton::clicked,this,&MainWindow::setResultTextAns);
    connect(FunctionKeyButtonQuit,&QPushButton::clicked,this,&MainWindow::close);

    ButtonLayout=new QHBoxLayout();
    ButtonLayout->addLayout(NumberLayout);
    ButtonLayout->addLayout(OperatorLayout);
    ButtonLayout->addLayout(FunctionKeyLayout);

    MainLayout=new QVBoxLayout(CentralWidget);
    ResultText=new QLineEdit(tr("0"));
    ResultText->setAlignment(Qt::AlignRight);
    MainLayout->addWidget(ResultText);
    MainLayout->addLayout(ButtonLayout);
    MainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setOperatorBtnEnable(bool ok)
{
    OperatorButtonAdd->setEnabled(ok);
    OperatorButtonDiv->setEnabled(ok);
    OperatorButtonEqual->setEnabled(ok);
    OperatorButtonMul->setEnabled(ok);
    OperatorButtonPoint->setEnabled(ok);
    OperatorButtonSub->setEnabled(ok);
}

QString MainWindow::cal(QString s)
{
    QString temp;
    expression = new Expression(s.toStdString());
    try
    {
        temp=QString::fromStdString(expression->getResult());
    }catch(runtime_error e){
        QMessageBox messagebox(QMessageBox::Warning,tr("Error"),QString::fromStdString(e.what()));
        messagebox.exec();
        ResultText->clear();
    }
    delete expression;
    return temp;
}

void MainWindow::setResultText0()
{
    if(isCalc==true)
    {
        ResultText->setText("0");
        isCalc=false;
    }
    else
        if(ResultText->text()!="0")
            ResultText->setText(ResultText->text()+"0");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText1()
{
    if(ResultText->text()=="0"||isCalc==true)
    {
        ResultText->setText("1");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"1");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText2()
{
    if(ResultText->text()=="0"||isCalc==true)
    {
        ResultText->setText("2");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"2");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText3()
{
    if(ResultText->text()=="0"||isCalc==true)
    {
        ResultText->setText("3");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"3");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText4()
{
    if(ResultText->text()=="4"||isCalc==true)
    {
        ResultText->setText("1");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"4");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText5()
{
    if(ResultText->text()=="5"||isCalc==true)
    {
        ResultText->setText("1");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"5");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText6()
{
    if(ResultText->text()=="6"||isCalc==true)
    {
        ResultText->setText("1");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"6");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText7()
{
    if(ResultText->text()=="0"||isCalc==true)
    {
        ResultText->setText("7");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"7");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText8()
{
    if(ResultText->text()=="8"||isCalc==true)
    {
        ResultText->setText("1");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"8");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultText9()
{
    if(ResultText->text()=="9"||isCalc==true)
    {
        ResultText->setText("9");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"9");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultTextPoint()
{
    if(isCalc==true)
    {
        ResultText->setText("0.");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+".");
    setOperatorBtnEnable(false);
}

void MainWindow::setResultTextEqual()
{
    QString temp;
    temp=cal(ResultText->text());
    ResultText->setText(ResultText->text()+"=");
    if(temp=="Error")
    {
        ResultText->setText(tr("Error"));
        return;
    }
    while(temp.right(1)=="0")
        temp=temp.left(temp.size()-1);
    if(temp.right(1)==".")
        temp=temp.left(temp.size()-1);
    ResultText->setText(ResultText->text()+temp);
    Ans=temp;
    setOperatorBtnEnable(true);
    isCalc=true;
}

void MainWindow::setResultTextAdd()
{
    if(isCalc==true)
    {
        ResultText->setText("Ans+");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"+");
    setOperatorBtnEnable(false);
}

void MainWindow::setResultTextSub()
{
    if(isCalc==true)
    {
        ResultText->setText("Ans-");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"-");
    setOperatorBtnEnable(false);
}

void MainWindow::setResultTextMul()
{
    if(isCalc==true)
    {
        ResultText->setText("Ans*");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"*");
    setOperatorBtnEnable(false);
}

void MainWindow::setResultTextDiv()
{
    if(isCalc==true)
    {
        ResultText->setText("Ans/");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"/");
    setOperatorBtnEnable(false);
}

void MainWindow::setResultTextCE()
{
    ResultText->setText("0");
    setOperatorBtnEnable(true);
    isCalc=false;
}

void MainWindow::setResultTextAns()
{
    if(ResultText->text()=="0"||isCalc==true)
    {
        ResultText->setText("Ans");
        isCalc=false;
    }
    else
        ResultText->setText(ResultText->text()+"Ans");
    setOperatorBtnEnable(true);
}

void MainWindow::setResultTextDelete()
{
    QString result=ResultText->text();
    if(isCalc==true)
    {
        setOperatorBtnEnable(false);
        if(ResultText->text().right(1)=="=")
        {
            setOperatorBtnEnable(true);
            isCalc=false;
        }
    }
    if(result.size()==1)
        ResultText->setText("0");
    else if(result.right(3)=="Ans")
        ResultText->setText(result.left(result.size()-3));
    else
        ResultText->setText(result.left(result.size()-1));
    if(ResultText->text().right(1)=="+"
            ||ResultText->text().right(1)=="-"
            ||ResultText->text().right(1)=="*"
            ||ResultText->text().right(1)=="/"
            ||ResultText->text().right(1)=="."
            ||isCalc==true)
        setOperatorBtnEnable(false);
    else
        setOperatorBtnEnable(true);
}

/*
void MainWindow::setResultText(const QString & Button)
{
    QString result=ResultText->text();
    switch (signal)
    {
    case "0":
        if(result!="0")
            ResultText->setText(result+"0");
        break;
    case "1":
        if(result=="0")
            ResultText->setText("1");
        else
            ResultText->setText(result+"1");
        break;
    case "2":
        if(result=="0")
            ResultText->setText("2");
        else
            ResultText->setText(result+"2");
        break;
    case "3":
        if(result=="0")
            ResultText->setText("3");
        else
            ResultText->setText(result+"3");
        break;
    case "4":
        if(result=="0")
            ResultText->setText("4");
        else
            ResultText->setText(result+"4");
        break;
    case "5":
        if(result=="0")
            ResultText->setText("5");
        else
            ResultText->setText(result+"5");
        break;
    case "6":
        if(result=="0")
            ResultText->setText("6");
        else
            ResultText->setText(result+"6");
        break;
    case "7":
        if(result=="0")
            ResultText->setText("7");
        else
            ResultText->setText(result+"7");
        break;
    case "8":
        if(result=="0")
            ResultText->setText("8");
        else
            ResultText->setText(result+"8");
        break;
    case "9":
        if(result=="0")
            ResultText->setText("9");
        else
            ResultText->setText(result+"9");
        break;
    case "delete":
        if(result.size()==1)
            ResultText->setText("0");
        else
            result=result.left(result.size()-1);
    case "CE":
        ResultText->setText("0");
    default:
        break;
    }
}
*/
