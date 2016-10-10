/**
  * QPushButton子类,捕获原不带参数的clicked信号并重新发射clicked(PushButton*)信号,
  * 便于槽函数得知发射信号按钮.
  */
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    PushButton(const QString &text, QWidget *parent = 0);
    /*
     * 不允许拷贝和赋值
     */
    PushButton(const PushButton&) = delete;
    PushButton& operator=(const PushButton&) = delete;

signals:
    void clicked(PushButton *pushButton);

private slots:
    void onClicked();
};

#endif // PUSHBUTTON_H
