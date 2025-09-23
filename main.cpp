#include <iostream>
#include <string.h>

void aumentar(int &contador,std::string *&original,std::string valor){
    std::string *aux;
    aux=new std::string[contador+1];
    for(int i=0;i<contador;i++){
      aux[i]=original[i];
    }
    aux[contador]=valor;
    delete[] original;
    original=aux;
    aux=nullptr;
    contador++;
}
int main() { 
    //comando que permite al sistema agarrar un archivo externo para lectura "r",puedes
    //utilizarlo tambien para escritura "w"
    FILE* csv = fopen("lista.csv","r");
    char linea[300];//linea que lee cada linea
    int contador=1;//contador de tamaño de las arrays
    std::string *a= nullptr;
    a=new std::string[contador];
    
    if(csv==NULL){
      std::cout<<"error"<<std::endl;
      return 0;
    }
    
    while(fgets(linea,sizeof(linea),csv)){
      char *token = strtok(linea, ",");//crea un char que utiliza la linea actual y nulifica con \0 los caracteres indicados
        while (token != NULL) {//mientras no dejen de existir los saltos de lineas o espacios
            std::cout<<token;
            aumentar(contador,a,std::string(token));
            token = strtok(NULL, ",");
        }
        std::cout << std::endl;
    }
    for(int i = 0; i < contador; i++){
        std::cout << i << ": " << a[i] << std::endl;
    }
    delete[] a;
    fclose(csv);
    return 0;
}
