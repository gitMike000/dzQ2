#include "parsetext.h"

#define MIN(a, b) (a < b) ? a : b

ParseText::ParseText()
{
    text = "";
    preText = "";
    pos = 0;
}

//"©‰€₽" #@COP@ - © #@PRO@ - ‰ #@EUR@ - € #@RUB@ - ₽

bool ParseText::change(QString istr)
{
    qint32 length = MIN(MIN(text.length(), istr.length()), pos);
    preText = "";
    for (qint32 i = 0; i < length; i++)
    {
        if (text[i] != istr[i])
        {
            pos = i;
            break;
        }
    }
    const QChar *arStr = istr.constData();
    qint32 ppos = 0, lastp = -1; // курсор на начало символа, с которого будет осуществлять происк метки #@
    bool chg = false; // есть изменения текста?
    for (qint32 fnd = istr.indexOf("#@", pos); // поиск первого примера в тексте
        fnd != -1 && lastp != pos; // -1 - означает, что в строке нет (больше) примеров
        fnd = istr.indexOf("#@", pos))
    {
        preText.insert(preText.length(), &arStr[ppos], fnd); // копируем текст до примера
        lastp = pos;
        pos = fnd+2;

        int r = istr.indexOf('@', (fnd+2));//если есть равенство, то пример завершен
        int space = istr.indexOf(' ', (fnd+2));
        if ((r < space || space == -1) && r != -1) // проверяем, что равно для текущего примера, а не следующего
        {
            QString exampl = "";
            exampl.insert(0, &arStr[fnd + 2], r - fnd - 1);
            //QString rez="#@"+exampl;
            QString rez;
            if ("COP@" == exampl) rez = "©";
            if ("PRO@" == exampl) rez = "‰";
            if ("EUR@" == exampl) rez = "€";
            if ("RUB@" == exampl) rez = "₽";
            if (rez.isEmpty()) continue;
            preText += rez;
            pos = r + 1;
            chg = true;
        }
        preText.insert(preText.length(), &arStr[pos], istr.length() - pos); // дописываем оставшийся текст
        pos -=4;
    }
    return chg;
}

QString ParseText::getText()
{
    text = preText;
    return text;
}
