#include <iostream>

#define n_giorno 5
#define n_slot 6
#define n_aula 4
#define n_esame 20
#define n_max_parall 5

using namespace std;

struct exam {
    int id;
    bool piazzato;
    bool parall_piazzato;
    int durata;
    int prof;
    int n_parall;
    int id_parall[n_max_parall];
};

struct date {
    int id_esame;
    int durata_esame;
    int prof_esame;
};

// Procedure

void print_esami(const exam* esame){
    cout<<endl;
    for(int i=0; i<n_esame; i++)
    {
        cout<<"Esame id: "<<esame[i].id<<"\tStato: ";
        for (int j=0; j<n_max_parall; j++)
        {
            if(esame[i].id_parall[j]!=0)
            {
                cout<<esame[esame[i].id_parall[j]-1].piazzato<<" ";
            }
            else
            {
                cout<<"0 ";
            }
        }
        cout<<"\tDurata: "<<esame[i].durata<<
            "\t Prof: "<<esame[i].prof<<"\tPrall: ";
        for (int j=0; j<n_max_parall; j++)
        {
            cout<<esame[i].id_parall[j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

void print_calendario(date m[][n_slot][n_aula]){
    cout<<"Calendario: "<<endl<<endl;
    cout<<"Id esame - Durata - Prof     > Aule"<<endl<<endl<<"             v"<<endl<<"      Slot e Giorni"<<endl<<endl<<endl;

    for(int i=0; i<n_giorno; i++)
    {
        for(int j=0; j<n_slot; j++)
        {
            for(int k=0; k<n_aula; k++)
            {
                cout<<"\t"<<m[i][j][k].id_esame<<" - "<<m[i][j][k].durata_esame<<" - "<<m[i][j][k].prof_esame;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
}

void Mettibile(exam* esame, date m[][n_slot][n_aula],
               int cont_esami, int cont_parall, int giorno, int slot, int aula, bool* mettibile){
    for(int j=0; j<esame[esame[cont_esami].id_parall[cont_parall]-1].durata; j++)
    {
        if (m[giorno][slot+j][aula].id_esame!=0)
            *mettibile = false;
    }
}

void Prof_libero(exam* esame, date m[][n_slot][n_aula],
                 int cont_esami, int cont_parall, int giorno, int slot, int aula, bool* prof_libero){
    for(int j=0; j<esame[esame[cont_esami].id_parall[cont_parall]-1].durata; j++)
    {
        for (int k=0; k<n_aula; k++)
        {
            if(m[giorno][slot+j][k].prof_esame==esame[esame[cont_esami].id_parall[cont_parall]-1].prof && aula!=k)
                *prof_libero = false;
        }
    }
}

void Inizializza_date(date m[][n_slot][n_aula]){
    for(int i=0; i<n_giorno; i++)
    {
        for(int j=0; j<n_slot; j++)
        {
            for(int k=0; k<n_aula; k++)
            {
                m[i][j][k].id_esame=0;
                m[i][j][k].durata_esame=0;
                m[i][j][k].prof_esame=0;
            }
        }
    }
}

void Inizializza_exam_default(exam* esame){
    for(int i=0; i<n_esame; i++)
    {
        esame[i].id=i+1;
        esame[i].piazzato=false;
        esame[i].parall_piazzato=false;
        esame[i].durata=1;
        esame[i].prof=1001+i;
        esame[i].n_parall=1;
        for (int j=0; j<n_max_parall; j++)
        {
            esame[i].id_parall[j]=0;
        }
        esame[i].id_parall[0]=esame[i].id;
    }
}

void Personalizza_exam(exam* esame){
    for(int i=1; i<n_esame; i=i+2)
    {
        esame[i].piazzato=false;
        esame[i].durata=2;
    }

    for(int i=0; i<n_esame; i=i+3)
    {
        esame[i].piazzato=false;
        esame[i].durata=4;
    }

    for(int i=0; i<n_esame; i=i+4)
    {
        esame[i].piazzato=false;
        esame[i].durata=3;
    }

    for(int i=0; i<n_esame-5; i=i+5)
    {
        esame[i].prof = esame[i+2].prof = esame[i+5].prof;
    }

    esame[0].n_parall=2;
    esame[0].id_parall[1]=esame[8].id;
    esame[8].n_parall=2;
    esame[8].id_parall[1]=esame[0].id;
}

void Inserisci_esame(exam* esame, date m[][n_slot][n_aula],
                     int cont_esami, int cont_parall, int giorno, int slot, int aula){
    esame[esame[cont_esami].id_parall[cont_parall]-1].piazzato=true;
    for(int j=0; j<esame[esame[cont_esami].id_parall[cont_parall]-1].durata; j++)
    {
        m[giorno][slot+j][aula].id_esame = esame[esame[cont_esami].id_parall[cont_parall]-1].id;
        m[giorno][slot+j][aula].durata_esame = esame[esame[cont_esami].id_parall[cont_parall]-1].durata;
        m[giorno][slot+j][aula].prof_esame = esame[esame[cont_esami].id_parall[cont_parall]-1].prof;
    }
}

int main()
{
    int giorno=0, slot=0, aula=0;
    date m[n_giorno][n_slot][n_aula];
    exam esame[n_esame];
    bool mettibile = true;
    bool prof_libero = true;

    // inizializzazioni

    Inizializza_date(m);
    Inizializza_exam_default(esame);
    Personalizza_exam(esame);

    // Stampa dell'elenco degli esami

    print_esami(esame);

    // Procedura di inserimento degli esami nel calendario

    for (int cont_esami=0; cont_esami<n_esame; cont_esami++)
    {
        for (int cont_parall=0; cont_parall<esame[cont_esami].n_parall; cont_parall++)
        {
            esame[cont_esami].parall_piazzato = true;
            for (int cont_parall_interno=0; cont_parall_interno<esame[cont_esami].n_parall; cont_parall_interno++)
            {
                if (!esame[esame[cont_esami].id_parall[cont_parall_interno]-1].piazzato)
                {
                    esame[cont_esami].parall_piazzato = false;
                }
            }
            while((giorno<n_giorno) && !esame[esame[cont_esami].id_parall[cont_parall]-1].piazzato)
            {
                while(((slot + esame[esame[cont_esami].id_parall[cont_parall]-1].durata - 1)<n_slot) &&
                !esame[esame[cont_esami].id_parall[cont_parall]-1].piazzato)
                {
                    while ((aula<n_aula) && !esame[esame[cont_esami].id_parall[cont_parall]-1].piazzato)
                    {
                        Mettibile(esame, m, cont_esami, cont_parall, giorno, slot, aula, &mettibile);
                        Prof_libero(esame, m, cont_esami, cont_parall, giorno, slot, aula, &prof_libero);

                        if(mettibile && prof_libero)
                        {
                            Inserisci_esame(esame, m, cont_esami, cont_parall, giorno, slot, aula);
                        }
                        else
                        {
                            aula++;
                            mettibile = true;
                        }
                    }
                    aula=0;
                    slot++;
                    prof_libero = true;
                }
                slot=0;
                giorno++;
            }
            giorno=0;
        }
    }

    cout<<"\t----------------------------------------------------------------------"<<endl<<endl<<endl;

    // Stampa del calendario compilato e dell'elenco degli esami per sapere quali sono rimasti eventualmente non messi

    print_calendario(m);
    print_esami(esame);
}