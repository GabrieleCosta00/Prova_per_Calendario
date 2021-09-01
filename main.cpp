#include <iostream>

#define n_giorno 5
#define n_slot 6
#define n_aula 4
#define n_esame 10
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

int main()
{
    int giorno=0, slot=0, aula=0;
    date m[n_giorno][n_slot][n_aula];
    exam esame[n_esame];
    bool mettibile = true;
    bool prof_libero = true;

    // inizializzazioni

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

    // Stampa dell'elenco degli esami

    /*for(int i=0; i<n_giorno; i++)
    {
        for(int j=0; j<n_slot; j++)
        {
            for(int k=0; k<n_aula; k++)
            {
                cout<<"\t"<<m[i][j][k];
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }*/

    cout<<endl;
    for(int i=0; i<n_esame; i++)
    {
        cout<<"Esame id: "<<esame[i].id<<"\tStato: ";
        for (int j=0; j<n_max_parall; j++)
        {
            cout<<esame[esame[i].id_parall[j]].piazzato<<" ";
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

    // Procedura di inserimento degli esami nel calendario

    for (int i=0; i<n_esame; i++)
    {
        for (int n=0; n<esame[i].n_parall; n++)
        {
            esame[i].parall_piazzato = true;
            for (int m=0; m<esame[i].n_parall; m++)
            {
                if (!esame[esame[i].id_parall[m]-1].piazzato)
                {
                    esame[i].parall_piazzato = false;
                }
            }
            while((giorno<n_giorno) && !esame[esame[i].id_parall[n]-1].piazzato)
            {
                while(((slot + esame[esame[i].id_parall[n]-1].durata - 1)<n_slot) && !esame[esame[i].id_parall[n]-1].piazzato)
                {
                    while ((aula<n_aula) && !esame[esame[i].id_parall[n]-1].piazzato)
                    {
                        for(int j=0; j<esame[esame[i].id_parall[n]-1].durata; j++)
                        {
                            for (int k=0; k<n_aula; k++)
                            {
                                if(m[giorno][slot+j][k].prof_esame==esame[esame[i].id_parall[n]-1].prof && aula!=k)
                                    prof_libero = false;
                            }
                            if (m[giorno][slot+j][aula].id_esame!=0)
                                mettibile = false;
                        }
                        if(mettibile && prof_libero)
                        {
                            esame[esame[i].id_parall[n]-1].piazzato=true;
                            for(int j=0; j<esame[esame[i].id_parall[n]-1].durata; j++)
                            {
                                m[giorno][slot+j][aula].id_esame = esame[esame[i].id_parall[n]-1].id;
                                m[giorno][slot+j][aula].durata_esame = esame[esame[i].id_parall[n]-1].durata;
                                m[giorno][slot+j][aula].prof_esame = esame[esame[i].id_parall[n]-1].prof;
                            }
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