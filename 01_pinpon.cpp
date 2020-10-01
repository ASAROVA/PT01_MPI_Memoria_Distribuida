#include <iostream>
#include <mpi.h>
#include <sstream>

using namespace std;
#define SL cout<<endl

int main(int argc, char** argv) {
    SL;

    MPI_Init(NULL, NULL);

    int TP;
    MPI_Comm_size(MPI_COMM_WORLD, &TP);

    int NP;
    MPI_Comm_rank(MPI_COMM_WORLD, &NP);

    char NomP[MPI_MAX_PROCESSOR_NAME];
    int NomP_long;
    MPI_Get_processor_name(NomP, &NomP_long);

    
    // Para este pinpon solo permitiremos 2 procesos
    if (TP != 2) 
    {
	    fprintf(stderr, "Solo 2 procesos para %s.\n", argv[0]);
	    MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int LIMITE_PINPON = 10;
    int cuenta_pinpon = 0;
    int NP_colega = (NP + 1) % 2;

    const char* pinpon[] = { (char*)("pon"),
	    					 (char*)("pin"), };

    ostringstream ssalida;
    string salida;

    while (cuenta_pinpon < LIMITE_PINPON) 
    {
        if (NP == cuenta_pinpon % 2) 
        {
            cuenta_pinpon++;

            MPI_Send ( &cuenta_pinpon, 1, 
            		   MPI_INT, NP_colega, 0, MPI_COMM_WORLD );
            
            printf( "%s: \t\t%s %d \n",
                 	NomP, pinpon[cuenta_pinpon%2], cuenta_pinpon );

        } 
        else 
        {
            MPI_Recv ( &cuenta_pinpon, 1, 
            		   MPI_INT, NP_colega, 0, MPI_COMM_WORLD,
                   	   MPI_STATUS_IGNORE					  );
        }
    }

    MPI_Finalize();
}
