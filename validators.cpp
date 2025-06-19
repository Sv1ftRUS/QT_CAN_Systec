#include "validators.h"

HexIntegerValidator::HexIntegerValidator(QObject *parent) :
    QValidator(parent)
{
}
/*
QValidator::State HexIntegerValidator::validate(QString &input, int &) const
{
    bool ok;
    uint value = input.toUInt(&ok, 16);

    if (input.isEmpty())
        return Intermediate;

    //if (!ok || ( value > VALIDATORMAXID ))
    if (!ok || ( value > ((MainWindow::ui->comboBox_IDlen->currentIndex() == 0)?0x7FF : 0x3FFFFFFF))
        return Invalid;

    return Acceptable;
}
*/

QValidator::State HexIntegerValidator::validate(QString &input, int &) const
{
    bool ok;
    uint value = input.toUInt(&ok, 16);

    if (input.isEmpty())
        return Intermediate;

    //if (!ok || ( value > VALIDATORMAXID ))
    if (!ok || ( value > m_maximum))
        return Invalid;

    return Acceptable;
}

void HexIntegerValidator::setMaxID(qint64 maxID)
{
    m_maximum=maxID;
    return;
}

HexStringValidator::HexStringValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State HexStringValidator::validate(QString &input, int &pos) const
{
    const int maxSize = 16;//2 * m_maxLength;
    const QChar space = QLatin1Char(' ');
    QString data = input;
    data.remove(space);

    if (data.isEmpty())
        return Intermediate;

    // limit maximum size and forbid trailing spaces
    if ((data.size() > maxSize) || (data.size() == maxSize && input.endsWith(space)))
        return Invalid;

    // check if all input is valid
    const QRegularExpression re(QStringLiteral("^[[:xdigit:]]*$"));
    if (!re.match(data).hasMatch())
        return Invalid;

    // insert a space after every two hex nibbles
    const QRegularExpression insertSpace(QStringLiteral("(?:[[:xdigit:]]{2} )*[[:xdigit:]]{3}"));
    if (insertSpace.match(input).hasMatch()) {
        input.insert(input.size() - 1, space);
        pos = input.size();
    }
    return Acceptable;
}

DecIntegerValidator::DecIntegerValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State DecIntegerValidator::validate(QString &input, int &) const
{
    bool ok;
    uint value = input.toUInt(&ok, 10);

    if (input.isEmpty())
        return Intermediate;

    //if (!ok || ( value > VALIDATORMAXID ))
    if (!ok || ( value > m_maximum))
        return Invalid;

    return Acceptable;
}

void DecIntegerValidator::setMaxTime(qint64 max)
{
    m_maximum=max;
    return;
}

