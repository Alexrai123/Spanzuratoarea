#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
using namespace std;

class Game
{
private:
    const int nr_incercari;
    string cuvant;
    string cuvinte[10];
    string nume_jucator;
private:
    int schimbaLitera(char guess, string& cuv_ghicit)
    {
        int potriviri = 0;
        int lungime = cuvant.length();
        for (int i = 0; i < lungime; i++)
        {
            //litera a fost deja ghicita
            if (guess == cuv_ghicit[i])
                return 0;
            if (guess == cuvant[i])
            {
                cuv_ghicit[i] = guess;
                potriviri++;
            }
        }
        return potriviri;
    }
    void UpdateScorFinal(int scor_curent)
    {
        //salvam primele top 10 cele mai mari scoruri
        ifstream in("scor.txt");
        priority_queue<pair<int, string>> pq;
        string nume;
        int scor;
        in >> nume;
        while (!in.eof())
        {
            in >> scor;
            pq.push({ scor,nume });
            in >> nume;
        }
        pq.push({ scor_curent,nume_jucator });
        in.close();
        ofstream out("scor.txt");
        for (int i = 0; !pq.empty() && i < 5; i++)
        {
            out << pq.top().second << " " << pq.top().first << endl;
            pq.pop();
        }
        out.close();
    }
public:
    void AfiseazaTopScoruri()
    {
        ifstream in("scor.txt");
        system("cls");
        cout << "TOP SCORURI" << endl;
        string n;
        int scor;
        in >> n;
        int i = 1;
        while (!in.eof())
        {
            in >> scor;
            cout << i << ". " << n << "  " << scor << endl;
            in >> n;
            i++;
        }
        if (i == 1)
            cout << "Fii primul de pe lista!!" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << endl << "Apasa orice tasta pentru a continua." << endl;
        cin.ignore();
        cin.get();
    }
    Game() :nr_incercari(6)
    {
        cuvinte[0] = "romania";
        cuvinte[1] = "mamaliga";
        cuvinte[2] = "varcolac";
        cuvinte[3] = "castel";
        cuvinte[4] = "strigoi";
        cuvinte[5] = "transilvania";
        cuvinte[6] = "vlad";
        cuvinte[7] = "tepes";
        cuvinte[8] = "dracula";
        cuvinte[9] = "usturoi";
        nume_jucator = "necunoscut";
        ifstream in("scor.txt");
        if (!in)
        {
            //fisierul nu exista
            system("mkdir data");
            ofstream out("scor.txt");
            out.close();
        }
        in.close();
    }
    void Afiseaza_titlu()
    {
        cout << "===============================================================================================\n\n";
        cout << "\t *    *      **      **    *   *****    **   **      **      **    *" << endl;
        cout << "\t *    *     *  *     * *   *  *         * * * *     *  *     * *   *" << endl;
        cout << "\t ******    ******    *  *  *  *  *****  *  *  *    ******    *  *  *" << endl;
        cout << "\t *    *   *      *   *   * *  *      *  *     *   *      *   *   * *" << endl;
        cout << "\t *    *  *        *  *    **   ******   *     *  *        *  *    **\n" << endl;
        cout << "===============================================================================================\n";
    }
    void Afiseaza_reguli()
    {
        cout << endl;
        cout <<"\t\t\t REGULI\n" << endl;
        cout << "1.Ghiceste cuvantul introducand cate o litera pe rand.\n";
        cout << "2.Fiecare litera este reprezentata de o stea.\n";
        cout << "3.Ai " << nr_incercari << " incercari sa ghicesti cuvantul.\n";
        cout << "---------------------------------------------------------------\n" << endl << endl;
        cout << "Apasa orice tasta pentru a continua." << endl;
        cin.ignore();
        cin.get();
    }
    void Incepe_Jocul()
    {
        int alegeri_gresite = 0, scor_curent = 100;
        srand(time(NULL));
        int n = rand() % 10;
        cuvant = cuvinte[n];
        string necunoscut = string(cuvant.length(), '*');
        //repeta pana cand nr de incercari e 0
        system("cls");
        while (alegeri_gresite < nr_incercari)
        {
            system("cls");
            starePersoana(alegeri_gresite);
            cout << endl << necunoscut << endl;
            cout << "Mai ai " << nr_incercari - alegeri_gresite << " incercari." << endl;
            cout << "Ghiceste o litera: ";
            char alegere;
            cin >> alegere;
            cout << endl;
            if (schimbaLitera(alegere, necunoscut) == 0)
            {
                cout << "Gresit! Litera nu se afla acolo!" << endl;
                alegeri_gresite++;
                scor_curent -= 10;
                cin.get();
            }
            else {
                cout << "Corect!" << endl;
                cin.get();
            }
            cout << "Mai ai " << nr_incercari - alegeri_gresite << " incercari." << endl;
            if (cuvant == necunoscut)
            {
                system("cls");
                cout << cuvant << endl;
                cout << "Felicitari!"<<endl;
                cin.get();
                break;
            }
        }
        if (alegeri_gresite == nr_incercari)
        {
            system("cls");
            starePersoana(alegeri_gresite);
            cout << "\nAi pierdut..." << endl;
            cout << "Cuvantul era " << cuvant << endl;
            scor_curent -= 100;
            cin.get();
            starePersoana(alegeri_gresite);
        }
        if (scor_curent < 0)
            scor_curent = 0;
        cout << "Scorul tau este: " << scor_curent << endl << endl;
        UpdateScorFinal(scor_curent);
    }
    void getNumeJucator()
    {
        cout << "Introdu numele tau: ";
        cin >> nume_jucator;
    }
    void starePersoana(int nr_incercare_gresita)
    {
        switch (nr_incercare_gresita)
        {
        case 0:
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |          " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << "_|______________" << endl;
            break;
        case 1:
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |          0 " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << "_|______________" << endl;
            break;
        case 2:       
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |       \\ 0 " << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << "_|______________" << endl;
            break;
        case 3:
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |       \\ 0 /" << endl;
            cout << " |         " << endl;
            cout << " |         " << endl;
            cout << "_|______________" << endl;
            break;
        case 4:
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |       \\ 0 /" << endl;
            cout << " |         |" << endl;
            cout << " |         " << endl;
            cout << "_|______________" << endl;
            break;
        case 5:
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |       \\ 0 /" << endl;
            cout << " |         |" << endl;
            cout << " |        /  " << endl;
            cout << "_|______________" << endl;
            break;
        case 6:
            cout << " ___________" << endl;
            cout << " |         }" << endl;
            cout << " |       \\ 0 /" << endl;
            cout << " |         |" << endl;
            cout << " |        / \\ " << endl;
            cout << "_|______________" << endl;
        }
    }
};

int main()
{
    Game Hangman;
    int alegere;
    do
    {
        system("cls");
        Hangman.Afiseaza_titlu();
        cout << "\t1.Start joc\n";
        cout << "\t2.Afiseaza scoruri\n";
        cout << "\t3.Reguli\n";
        cout << "\t4.Paraseste jocul\n";
        cout << "Introdu alegerea ta: ";
        cin >> alegere;
        string c;
        switch (alegere)
        {
            case 1:
                Hangman.getNumeJucator();
                Hangman.Incepe_Jocul();
                do
                {
                    Hangman.Incepe_Jocul();
                    cout << "Vrei sa incerci din nou ? (Y/N): ";
                    cin >> c;
                } while (c == "da" || c == "Da" || c == "DA");
                break;
            case 2:
                Hangman.AfiseazaTopScoruri();
                break;
            case 3:
                Hangman.Afiseaza_reguli();
                break;
            case 4:
                cout << "Jocul a fost incheiat cu succes!";
                break;
            default:
                cout << "Alegeti o optiune valida!";
                break;
        }
    } while (alegere != 4);
    return 0;
}
