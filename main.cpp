#include "music.h"

int main(int argc, char* argv[])
{
    cout << "*Max length of message 255 symbols!" << endl
         << "*Audio file must be .wav format!" << endl << endl;

    if (argc != 4)
    {
        cout << "Incorrect command line!" << endl
             << "Waited: command <audio_file> <text_file> <key('w' or 'r')>" << endl
             << "'w' for hide message, 'r' for read massage!" << endl;

        return 1;
    }

    music lab;

    if(argv[3][0] == 'w')
    {
        fstream audio(argv[1], ios_base::binary | ios_base::out | ios_base::in);
        ifstream text(argv[2], ios_base::in);
        lab.Write(audio, text);
        audio.close();
        text.close();
    }
    else if(argv[3][0] == 'r')
    {
        ifstream audio(argv[1], ios_base::binary | ios_base::in);
        ofstream text(argv[2], ios_base::out);
        lab.Read(audio, text);
        audio.close();
        text.close();
    }
    else
    {
        cout << "Incorrect command line!" << endl
             << "Waited: command <audio_file> <text_file> <key('w' or 'r')>" << endl
             << "'w' for hide message, 'r' for read massage!" << endl;

        return 1;
    }

    return 0;
}

