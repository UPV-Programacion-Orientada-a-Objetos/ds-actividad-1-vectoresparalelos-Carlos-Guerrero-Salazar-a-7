#include <iostream>
#include <string.h>

void registrar(int posicion,std::string a[],std::string valor){
  a[posicion]=valor;
}

int buscar_nombre(const std::string& nombre, std::string a[], int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        if (nombre == a[i]) {
            std::cout<<"si existe"<<std::endl;
            return i;
        }
    }
    return -1;
}

int contar_medallas(const std::string& nombre_pais, std::string pais[], std::string medallas[], int tamaño) {
int cantidad_medallas=0;
for(int i=0;i<tamaño;i++){
  if(pais[i]==nombre_pais){
    int numero_medallas=0;
    numero_medallas= std::stoi(medallas[i]);
    cantidad_medallas+=numero_medallas;
  }
  }
  return cantidad_medallas;
}
int main() { 
    //comando que permite al sistema agarrar un archivo externo para lectura "r",puedes
    //utilizarlo tambien para escritura "w"
    FILE* csv = fopen("lista.csv","r");
    char linea[300];//valor que lee cada linea
    int contador_registros=0;//numero de registros en tamaño de las arrays
    //evita que se rompa el programa por falta de archivo
    if(csv==NULL){
      std::cout<<"error no se encontro el csv"<<std::endl;
      return 0;
    }
    //por cada linea en el csv busca que siga el texto cuando no la ultima vez que pase por la condicion es el tamaño de los paralelos
    while(fgets(linea,sizeof(linea),csv)){
      if(strlen(linea) > 1){
        std::cout<<"atletas detectados"<<contador_registros+1<<std::endl;
        contador_registros++;
      }
    }
    rewind(csv);
    //creacion de los paralelos con tamaños ya definidos
    std::string nombres[contador_registros]={};
    std::string pais[contador_registros]={};
    std::string disciplina[contador_registros]={};
    std::string genero[contador_registros]={};
    std::string medallas[contador_registros]={};
    contador_registros=0;//se vuelve a cero para colocar los datos
    while(fgets(linea,sizeof(linea),csv)){
      char *token = strtok(linea, ",");//crea un char que utiliza la linea actual y nulifica con \0 los caracteres indicados
      int lugar=1;
        while (token != NULL) {//mientras no dejen de existir los saltos de lineas o espacios
            switch (lugar){
            case 1:
            registrar(contador_registros,nombres,std::string(token));
            break;
            case 2:
            registrar(contador_registros,pais,std::string(token));
            break;
            case 3:
            registrar(contador_registros,disciplina,std::string(token));
            break;
            case 4:
            registrar(contador_registros,genero,std::string(token));
            break;
            case 5:
            registrar(contador_registros,medallas,std::string(token));
            break;
            }
            token = strtok(NULL, ",");
            lugar++;
        }
        contador_registros++;
    }
    for(int i = 0; i < contador_registros; i++){
        std::cout << "nombre" << ": " << nombres[i] << std::endl;
        std::cout << "pais" << ": " << pais[i] << std::endl;
        std::cout << "disciplina" << ": " << disciplina[i] << std::endl;
        std::cout << "genero" << ": " << genero[i] << std::endl;
        std::cout << "medallas" << ": " << medallas[i] << std::endl;
    }
    fclose(csv);
    int opcion=1;
    while(opcion!=0){
      std::cout << "selecciona una acción: "<< std::endl;
      std::cout << "1/buscar atletas "<< std::endl;
      std::cout << "2/calcular total de medallas de los participantes"<< std::endl;
      std::cout << "3/buscar al atleta con más medallas de los registrados "<< std::endl;
      std::cin>> opcion;
      if(opcion==1){
          int posicion=0;
          std::string nombre_buscar="";
          std::cout<<"escribe el nombre: ";
          std::cin>>nombre_buscar;
          posicion=buscar_nombre(nombre_buscar,nombres,contador_registros);
          if(posicion!=-1){
              std::cout << "pais" << ": " << pais[posicion] << std::endl;
              std::cout << "medallas" << ": " << medallas[posicion] << std::endl;
          }else{
            std::cout<<"error, volviendo"<<std::endl;
          }
      }
      //caso de medallas por pais
      if(opcion==2){
        std::string paises_unicos[contador_registros];
        int num_paises = 0;
        
        //en el registro
        for(int i = 0; i < contador_registros; i++){
            bool existe = false;
            //si el pais ya existe se evita
            for(int j = 0; j < num_paises; j++){
                if(pais[i] == paises_unicos[j]){
                    existe = true;
                    break;
                }
            }
            //si no existe se guarda
            if(!existe){
                paises_unicos[num_paises] = pais[i];
                num_paises++;//contador para delimitar valores
            }
        }
        std::cout<<"Medallas de los paises"<<std::endl;
        for(int i=0;i<num_paises;i++){
          int medallas_totales=contar_medallas(paises_unicos[i],pais,medallas,contador_registros);
          std::cout<<paises_unicos[i]<<":"<<medallas_totales<<std::endl;
        }
      }
      //caso del jugador con más medallas
      if(opcion==3){
      int persona_medallista=0;
      int cantidad=0;
      int empate=0;
        for(int i=0;i<contador_registros;i++){
          int medallas_actuales=std::stoi(medallas[i]);
          if(cantidad<=medallas_actuales){
            if(cantidad==medallas_actuales){
                empate=1;
            }else{
              empate=0;
            }
            cantidad=medallas_actuales;
            persona_medallista=i;
          }
        }
        if(empate){
          std::cout<<"tenemos un empate entre"<<std::endl;
          for(int i=0;i<=persona_medallista;i++){
            int medallas_actuales=std::stoi(medallas[i]);
            if(cantidad==medallas_actuales){
              std::cout<<nombres[i]<<std::endl;
            }
          }
          std::cout<<"con: "<<cantidad<<" medallas"<<std::endl;
        }else{
          std::cout<<"persona con más medallas"<<nombres[persona_medallista]<<" con: "<<cantidad<<std::endl;
        }
      }
    }
    
    return 0;
}

