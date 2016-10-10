#include "pushbutton.h"

PushButton::PushButton(const QString &text, QWidget *parent)
    :QPushButton(text, parent)
{
    connect(this, &QPushButton::clicked, this, &PushButton::onClicked);
}

void PushButton::onClicked()
{
    emit clicked(this);
}

