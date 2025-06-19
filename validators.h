#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <QObject>
#include <QValidator>


class HexIntegerValidator : public QValidator
{
    Q_OBJECT
public:
    explicit HexIntegerValidator(QObject *parent = nullptr);

    QValidator::State validate(QString &input, int &) const;

    void setMaxID(qint64 maxID=0x1FFFFFFFF);

private:
    qint64 m_maximum = 0x1FFFFFFFF;
};

class HexStringValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HexStringValidator(QObject *parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const;

    void setMaxLength(int maxLength);

private:
    int m_maxLength = 0;
};

class DecIntegerValidator : public QValidator
{
    Q_OBJECT
public:
    explicit DecIntegerValidator(QObject *parent = nullptr);

    QValidator::State validate(QString &input, int &) const;

    void setMaxTime(qint64 max=10000);

private:
    qint64 m_maximum = 10000;
};

#endif // VALIDATORS_H
