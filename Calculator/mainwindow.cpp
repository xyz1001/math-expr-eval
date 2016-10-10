#include "mainwindow.h"
#include <exception>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setWindowFlags(Qt::CustomizeWindowHint);
    menuBar()->close();

    setStyleSheet("QPushButton{"
                  "background-color:gray;"
                  "color: white;"
                  "width:55px;"
                  "height:55px;"
                  "font-size: 15px;"
                  "border-radius: 10px;"
                  "border: 2px groove gray;"
                  "border-style: outset;}"

                  "QPushButton:hover{"
                  "background-color:white;"
                  "color: black;}"

                  "QPushButton:pressed,QPushButton:disabled{"
                  "color: white;"
                  "background-color:rgb(0, 0, 0);"
                  "border-style: inset; }");

    CentralWidget=new QWidget(this);
    setCentralWidget(CentralWidget);
    setWindowTitle(tr("Calculator"));
    buttonsLayout = new QGridLayout();
    /*
     * 根据BUTTONS表添加,设置按钮
     */
    for(int i=0; i<BUTTONS.size(); ++i)
    {
        QVector<string> row = BUTTONS.at(i);    //一行按钮
        for(int j=0; j<row.size(); ++j)
        {
            const string &symbol = row.at(j);   //按钮上显示的字符
            if(!(symbol.empty()))
            {
                PushButton *pushButton = new PushButton(QString::fromStdString(symbol));
                buttons.push_back(pushButton);  //保存至按钮数组
                connect(pushButton,&PushButton::clicked,this,&MainWindow::setInputText);
                buttonsLayout->addWidget(pushButton, i, j);
            }
        }
    }

    /*
     * 功能键
     */
    functionKeyButtonClear=new QPushButton(QString::fromStdString(CLEAR));
    functionKeyButtonBackspace=new QPushButton(QString::fromStdString(BACKSPACE));
    functionKeyButtonAns=new QPushButton(QString::fromStdString(ANS));
    functionKeyButtonShift=new QPushButton(QString::fromStdString(SHIFT));
    equalButton = new QPushButton(QString::fromStdString(EQUAL));

    connect(functionKeyButtonBackspace,&QPushButton::clicked,this,&MainWindow::onBackspaceClicked);
    connect(functionKeyButtonClear,&QPushButton::clicked,this,&MainWindow::onClearClicked);
    connect(functionKeyButtonAns,&QPushButton::clicked,this,&MainWindow::onAnsClicked);
    connect(functionKeyButtonShift,&QPushButton::clicked,this,&MainWindow::onShiftClicked);
    connect(equalButton, &QPushButton::clicked, this, &MainWindow::onEqualClicked);

    buttonsLayout->addWidget(functionKeyButtonBackspace, 1, 0);
    buttonsLayout->addWidget(functionKeyButtonClear, 1, 1);
    buttonsLayout->addWidget(functionKeyButtonAns, 1, 2);
    buttonsLayout->addWidget(functionKeyButtonShift, 0, 4);
    //将等号添加至最后一行最后两格位置
    buttonsLayout->addWidget(equalButton, BUTTONS.size(), BUTTONS.at(BUTTONS.size()-1).size()-2, 1, 2);


    MainLayout=new QGridLayout(CentralWidget);
    //设置表达式输入框
    inputText=new QLineEdit("0");
    inputText->setAlignment(Qt::AlignRight);
    inputText->setReadOnly(true);
    inputText->setStyleSheet("QLineEdit{height: 50px;"
                             "border-style: plain;"
                             "border-radius: 10px;"
                             "font-size: 30px}");
    //设置等于符号
    equalLabel = new QLabel("=");
    equalLabel->setStyleSheet("width:55px;"
                              "height:55px;"
                              "font-size: 30px;");
    //设置结果显示框
    resultText = new QLineEdit("0");
    resultText->setReadOnly(true);
    resultText->setStyleSheet("QLineEdit{height: 50px;"
                             "border-style: plain;"
                             "border-radius: 10px;"
                             "font-size: 30px}");
    MainLayout->addWidget(inputText, 0, 0, 1, 5);
    MainLayout->addWidget(equalLabel, 1, 1);
    MainLayout->addWidget(resultText, 1, 2, 1, 3);
    MainLayout->addLayout(buttonsLayout, 2, 0, 7, 5);
    MainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setFixedSize(MainLayout->sizeHint());
}

MainWindow::~MainWindow()
{

}

QString MainWindow::cal(QString s)
{
    QString temp;
    expression = new Expression(transformStdExpression(s));
    try
    {
        temp=QString::fromStdString(expression->getResult());
    }catch(runtime_error e){
        QMessageBox messagebox(QMessageBox::Warning,"错误",QString::fromStdString(e.what()));
        messagebox.exec();
        temp = "Error";
    }

    calcFinished = true;
    delete expression;
    return temp;
}

string MainWindow::transformStdExpression(QString expression)
{
    expression = expression.replace("×", "*").replace("÷", "/").replace("√", "#").replace("°", "`");
    return expression.toStdString();
}

void MainWindow::setInputText(PushButton *pushButton)
{
    QString symbol = pushButton->text();
    /*
     * 未计算完成,还在输入中,将输入的字符直接添加至表达式输入框文本后
     */
    if(calcFinished==false)
    {
        inputText->setText(inputText->text()+pushButton->text());
    }
    /*
     * 已经计算完成,准备开始下一次计算
     * 根据输入的内容,若为数字/括号/前置运算符/可省略第一个操作数的中置运算符,则直接将输入显示在输入框中
     */
    else
    {
        Metacharacter m = METACHARACTERS.at(transformStdExpression(symbol));
        if(m.type == 0 || m.type == 2 || (m.type==1 && (m.position == 1 || m.e == "#" || m.e == "-")))
        {
            //如果输入的是小数点,则在其前面添加小数点
            if(symbol == ".")
            {
                inputText->setText(QString("0."));
            }
            else
            {
                inputText->setText(pushButton->text());
            }
        }
        else if(m.type == 1)
        {
            inputText->setText(Ans + pushButton->text());
        }
        historySize.clear();    //清空上次输入的历史记录
        calcFinished=false; //表示正在输入过程中
    }
    historySize.push(pushButton->text().size());    //记录输入的操作词大小
}

void MainWindow::onEqualClicked()
{
    QString temp;
    temp=cal(inputText->text());
    if(temp=="Error")   //如果计算出错
    {
        resultText->setText(tr("Error"));
        Ans = "0";
        return;
    }

    /*
     * 由于返回值为double转换的QString,字符串小数位会有一串0,需要去除,并在小数位全为0时去除小数点
     */
    while(temp.right(1)=="0")
        temp=temp.left(temp.size()-1);
    if(temp.right(1)==".")
        temp=temp.left(temp.size()-1);
    resultText->setText(temp);
    /*
     * 如果计算结果为负数,为Ans加上括号便于下次计算使用
     */
    if(temp.at(0) == '-')
        Ans=QString("%1%2%3").arg("(").arg(temp).arg(")");
    else
        Ans = temp;
}

void MainWindow::onClearClicked()
{
    inputText->setText("0");
    historySize.clear();
    calcFinished=true;
}

void MainWindow::onAnsClicked()
{
    if(inputText->text()=="0"||calcFinished==true)
    {
        inputText->setText(Ans);
        calcFinished=false;
    }
    else
        inputText->setText(inputText->text()+Ans);
    int length = Ans.size();
    while(length--)
        historySize.push(1);
}

void MainWindow::onShiftClicked()
{
    /*
     * 根据shift按下状态转换sin,cos,tan和lg四个按钮
     */
    if(isShifting)
    {
        isShifting = false;
        for(int i=0; i<4; ++i)
        {
            buttons[i]->setText(QString::fromStdString(BUTTONS.at(0).at(i)));
        }
        functionKeyButtonShift->setStyleSheet("QPushButton{background-color:gray;"
                                              "font-size: 15px;"
                                              "border-style: outset;}"
                                              "QPushButton:hover{"
                                              "background-color:white;"
                                              "color: black;}"
                                              "QPushButton:pressed{"
                                              "background-color:rgb(0, 0, 0);"
                                              "border-style: inset;}");
    }
    else
    {
        isShifting = true;
        for(int i=0; i<4; ++i)
        {
            buttons[i]->setText(QString::fromStdString(SHIFT_TABLE[buttons[i]->text().toStdString()]));
        }
        functionKeyButtonShift->setStyleSheet("QPushButton:pressed{background-color:gray;"
                                              "border-style: outset;}"
                                              "QPushButton:hover{"
                                              "background-color:white;"
                                              "color: black;}"
                                              "QPushButton{"
                                              "font-size: 40px;"
                                              "font-style: bold;"
                                              "background-color:rgb(0, 0, 0);"
                                              "border-style: inset;}");
    }
}

void MainWindow::onBackspaceClicked()
{
    QString result=inputText->text();
    calcFinished = false;   //计算完成时若按下删除键,重新将计算完成标记置为正在输入中
    if(result.size()==1)    //输入框只剩一个字符
    {
        historySize.clear();
        inputText->setText("0");
        calcFinished = true;
    }
    else
    {
        int length = historySize.empty() ? 1:historySize.pop(); //兼容手动输入字符情况
        inputText->setText(result.left(result.size()-length));
    }
}
