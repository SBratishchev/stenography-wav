#include "music.h"


music::music()
{
    for(int i = 0; i < maskSize; i++)
    {
        double second = i;
        mask[i] = pow(2.0, second);
    }
}


void music::Write(fstream &audio, ifstream &text)
{
    int position = 44; // отступаем заголов
    char letter; // симфол, который будем записывать в аудио файл
    int textLen; // длина текстового файла

    // находим длину текстового файла
    text.seekg(0, ios_base::end);
    textLen = text.tellg() - 1;
    text.seekg(0);

    // длинна текста не должна привышать 1 байта или 255 символов
    textLen &= 255;
    letter = textLen;

    // записываем длину текста
    position = WriteByte(position, letter, audio);

    // в цикле записываем текст
    for(int i = 0; i < textLen; i++)
    {
        if(audio.eof())
        {
            cout << "Audio file is less than the required!" << endl;
            cout << i+1 << "symbols written" << endl;

            letter = i+1;
            WriteByte(44, letter, audio);
        }
        else
        {
            text.get(letter); // читаем символ
            position = WriteByte(position, letter, audio); // передаем символ
        }
    }
}


int music::WriteByte(int position, unsigned char text, fstream &audio)
{
    // указываем позицию куда писать
    audio.seekg(position, ios_base::beg);

    char buf;
    char fileBuf;

    // в цикле записываем 1 БИТ символа в 1 БАЙТ аудио файла
    for(int i = 0; i < maskSize; i++)
    {
        // находим i бит символа
        buf = text & mask[i];
        for(int j = 0; j < i; j++)
        {
            buf >>= 1;
        }

        audio.read(&fileBuf, 1); // читаем 1 БАЙТ аудио файла
        fileBuf &= maskByte; // обнуляем младший бит
        fileBuf |= buf; // в младший бит аудио файла записываем бит символа
        audio.seekg(-1, ios_base::cur); // перемещаемся на 1 позицию назад
        audio.write(&fileBuf, 1); // записываем измененый байт
    }

    return audio.tellg();
}


void music::Read(ifstream &audio, ofstream &text)
{
    int position = 44; // пропускаем WAV заголовок
    unsigned char letter; // буфер символа
    int textLen = 0; // длинна текста

    letter = ReadByte(position, audio); // читаем длинну текста
    textLen |= letter; // преобразуем в целочисленный тип

    // в цикле достаем символ из аудио файла, и записываем символ в файл вывода
    for(int i = 0; i < textLen; i++)
    {
        position += 8; // смешаемся на 1 символ
        letter = ReadByte(position, audio); // читаем 1 симво
        text << letter; // записываем 1 символ в файл вывода
    }
}


unsigned char music::ReadByte(int position, ifstream &audio)
{
    audio.seekg(position, ios_base::beg); // указываем на место откуда читать

    unsigned char returnValue = 0; // переменная для результата
    char buf; // буфферная переменная
    char fileBuf; // переменная для данных аудио файла

    // в цикле находи i бит символа
    for(int i = 0; i < maskSize; i++)
    {
        audio.read(&fileBuf, 1); // читаем 1 байт из аудио файла

        // собственно вчленяем i бит
        buf = fileBuf & 1;
        for(int j = 0; j < i; j++)
        {
            buf <<= 1;
        }
        // записываем в сумматор
        returnValue |= buf;
    }

    return returnValue;
}
