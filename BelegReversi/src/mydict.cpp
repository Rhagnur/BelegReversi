#include "mydict.h"

MyDict::MyDict()
{
    deutsch[0] = "aktiviert";
    deutsch[1] = "Anzeigefilter";
    deutsch[2] = "Credits";
    deutsch[3] = "Design";
    deutsch[4] = "Eigene Musik";
    deutsch[5] = "Export";
    deutsch[6] = "hat gewonnen!";
    deutsch[7] = "Highscore";
    deutsch[8] = "ist an der Reihe.";
    deutsch[9] = "ist wieder an der Reihe.";
    deutsch[10] = "konnte nicht ziehen.";
    deutsch[11] = "Lautstärke einstellen";
    deutsch[12] = "Mögliche Züge anzeigen";
    deutsch[13] = "Musik laden";
    deutsch[14] = "Musik stumm";
    deutsch[15] = "Name Spieler 1";
    deutsch[16] = "Name Spieler 2";
    deutsch[17] = "Optionen";
    deutsch[18] = "Spieler gegen Computer";
    deutsch[19] = "Spieler gegen Spieler";
    deutsch[20] = "Spielfeldgröße";
    deutsch[21] = "Spielmodus";
    deutsch[22] = "Spiel starten";
    deutsch[23] = "Sprache";
    deutsch[24] = "stumm";
    deutsch[25] = "Unentschieden!!!";
    deutsch[26] = "Zug aussetzen";
    deutsch[27] = "Zurück";
    deutsch[28] = "Sekunden übrig";

    english[0] = "activated";
    english[1] = "Filter output";
    english[2] = "Credits";
    english[3] = "Design";
    english[4] = "My Music";
    english[5] = "Export";
    english[6] = "won!";
    english[7] = "Highscore";
    english[8] = "'s turn.";
    english[9] = "'s turn, again.";
    english[10] = "skipped a turn.";
    english[11] = "Adjust volume";
    english[12] = "Show possible turns";
    english[13] = "Load music";
    english[14] = "Mute music";
    english[15] = "Player 1 name";
    english[16] = "Player 2 name";
    english[17] = "Options";
    english[18] = "Player vs Computer";
    english[19] = "Player vs Player";
    english[20] = "Fieldsize";
    english[21] = "Gamemode";
    english[22] = "Start game";
    english[23] = "Language";
    english[24] = "mute";
    english[25] = "Draw!!!";
    english[26] = "Skip turn";
    english[27] = "Back";
    english[28] = "seconds left";

    dict["deu"] = deutsch;
    dict["eng"] = english;

}

QString* MyDict::getDict(QString sprache)
{
    return dict[sprache];
}

