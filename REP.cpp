#include "REP.h"
REP::REP()
{
    memset(ruta_disco, 0, 255);
    memset(ruta_reporte, 0, 255);
    memset(nombre_disco, 0, 255);
    memset(ruta_archivo, 0, 255);
    par_ra = false;
}
void REP::limpiar(){
    memset(ruta_disco, 0, 255);
    memset(ruta_reporte, 0, 255);
    memset(nombre_disco, 0, 255);
    memset(ruta_archivo, 0, 255);
    par_ra = false;
}
void REP::ejecutar_REP(lista::list * lista, objetos::REP rep){
    int letra = rep.id[3];
    MOUNT * nuevo;
    lista::nodoC * temp = nuevo->buscarLetra(letra, lista->first);
    if(temp != NULL){
        lista::nodoP * particion = nuevo->buscar_id(rep, lista->first);
        if(particion!= NULL){
            if(rep.f_mbr == 1){
                graficar_MBR(temp->path, rep);
            }else if(rep.f_disk ==1){
                graficar_Disk(temp->path, rep);
            }else{
                // revisar la variable para reportes de la fase 2
                if(rep.f_rep==1){ //reporte sb
                    getRuta(temp->path);
                    rep_sb(temp->path,particion);
                }else if(rep.f_rep==2){ // -> reporte file
                    getRuta(temp->path);
                    rep_file(temp->path,particion);
                }else if(rep.f_rep==3){ //-> reporte bitmap de inodos
                    getRuta(temp->path);
                    rep_bm_inodes(temp->path,particion);
                }else if(rep.f_rep==4){ //-> reporte bitmap de blokes
                    getRuta(temp->path);
                    rep_bm_blockes(temp->path,particion);
                }else if(rep.f_rep==5){ // -> reporte de inodos
                    getRuta(temp->path);
                    rep_inodos(temp->path,particion);
                }else if(rep.f_rep==6){ // -> reporte tree
                    ofstream outfile(ruta_reporte);
                    outfile.close();
                    getRuta(temp->path);
                    rep_arbol(temp->path,particion);
                }else if(rep.f_rep==7){ // -> reporte de bloques
                    getRuta(temp->path);
                    rep_bloques(temp->path,particion);
                }else if(rep.f_rep==8){ // -> reporte journal
                    getRuta(temp->path);
                    rep_journal(temp->path,particion);
                }else if(rep.f_rep==9){ // -> reporte ls
                    getRuta(temp->path);
                    rep_ls(temp->path,particion);
                }
            }
            limpiar();
        }else{
            cout << "Error, la particion no esta montada" << endl;
        }
    }
}
char* REP::get_Fecha(time_t time)
{
    char* fecha_hora = (char*) malloc(sizeof (char)*128);
    struct tm *tiempo_local = localtime(&time);
    strftime(fecha_hora, 128, "%d/%m/%y %H:%M", tiempo_local);
    return fecha_hora;
}
void REP::graficar_MBR(char path[255], objetos::REP rep){
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    objetos::EBR ebr;
    ebr.part_next =-1;
    getRuta(path);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
        if(mkdir(ruta_disco, 0777) != -1){
            existe_dir++;
        }
    }
    int pos_extendida = 0;
    if(existe_dir!=0){
        double size_patition = 0.0;
        FILE *doc;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        if(archivo_mbr !=NULL){
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        for(int i = 0; i<4; i++){
            if(mbr.mbr_partitions[i].part_type == 'E'){
                pos_extendida = i;
            }
        }
        fclose(archivo_mbr);
        char * fecchita = get_Fecha(mbr.mbr_fecha_creacion);
        int size = mbr.mbr_tamano;
        int sig = mbr.mbr_disk_signature;
        char fit = mbr.mbr_disk_fit;
        doc = fopen("/home/archivos/reportesreporte_mbr.dot","w");
        fprintf(doc,"digraph reporte{ \n");
        fprintf(doc,"tbl [ shape=plaintext \n");
        fprintf(doc,"   label=< \n");
        fprintf(doc,"   <table border= \"0\" cellborder=\"1\" color=\"#9121B0\" cellspacing=\"0\"> \n");
        fprintf(doc,"       <tr><td colspan=\"2\"> %s </td></tr>\n",rep.id);
        fprintf(doc,"       <tr><td cellpadding=\"4\"><b> Nombre </b></td> <td cellpadding=\"4\"><b>Valor </b></td></tr> \n");
        fprintf(doc,"       <tr> \n");
        fprintf(doc,"           <td cellpadding=\"4\"><b> mbr_tamaño</b> </td> \n");
        fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", size);
        fprintf(doc,"       </tr> \n");
        fprintf(doc,"       <tr> \n");
        fprintf(doc,"           <td cellpadding=\"4\"><b> fecha de creacion</b> </td> \n");
        fprintf(doc,"           <td cellpadding=\"4\"> %s </td> \n", fecchita);
        fprintf(doc,"       </tr> \n");
        fprintf(doc,"       <tr> \n");
        fprintf(doc,"           <td cellpadding=\"4\"><b> mbr_mbr_disk_signature</b> </td> \n");
        fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", sig);
        fprintf(doc,"       </tr> \n");
        fprintf(doc,"       <tr> \n");
        fprintf(doc,"           <td cellpadding=\"4\"><b> mbr_disk_fit</b> </td> \n");
        char letra ;
        if(fit == 0){
            letra = 'B';
        }else if(fit == 1){
            letra = 'F';
        }else{
            letra = 'W';
        }
        fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n", letra);
        fprintf(doc,"       </tr> \n");
        int cont = 1;
        int ext = 0;
        for(int i = 0; i<4; i++){
            if(mbr.mbr_partitions[i].part_status == '1'){
                fprintf(doc,"       <tr> \n");
                fprintf(doc,"           <td cellpadding=\"4\"><b> part_status_%d</b> </td> \n",cont);
                fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n", mbr.mbr_partitions[i].part_status);
                fprintf(doc,"       </tr> \n");
                fprintf(doc,"       <tr> \n");
                fprintf(doc,"           <td cellpadding=\"4\"><b> part_type_%d</b> </td> \n",cont);
                fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n", mbr.mbr_partitions[i].part_type);
                fprintf(doc,"       </tr> \n");
                fprintf(doc,"       <tr> \n");
                fprintf(doc,"           <td cellpadding=\"4\"><b> part_fit_%d</b> </td> \n",cont);
                fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n", mbr.mbr_partitions[i].part_fit);
                fprintf(doc,"       </tr> \n");
                fprintf(doc,"       <tr> \n");
                fprintf(doc,"           <td cellpadding=\"4\"><b> part_star_%d</b> </td> \n",cont);
                fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", mbr.mbr_partitions[i].part_start);
                fprintf(doc,"       </tr> \n");
                fprintf(doc,"       <tr> \n");
                fprintf(doc,"           <td cellpadding=\"4\"><b> part_size_%d</b> </td> \n",cont);
                fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", mbr.mbr_partitions[i].part_size);
                fprintf(doc,"       </tr> \n");
                fprintf(doc,"       <tr> \n");
                fprintf(doc,"           <td cellpadding=\"4\"><b> part_name_%d</b> </td> \n",cont);
                fprintf(doc,"           <td cellpadding=\"4\"> %s </td> \n", mbr.mbr_partitions[i].part_name);
                fprintf(doc,"       </tr> \n");
                cont++;
                if(mbr.mbr_partitions[i].part_type == 'E'){
                    pos_extendida = i;
                    ext++;
                }
            }
        }
        fprintf(doc,"   </table> \n");
        fprintf(doc," >]; \n");
        archivo_mbr = fopen(path, "rb+");
        int inicio_part = mbr.mbr_partitions[pos_extendida].part_start;
        fseek(archivo_mbr, inicio_part, SEEK_SET);
        fread(&ebr,sizeof(objetos::EBR), 1, archivo_mbr);
        objetos::EBR temp = ebr;
        if(ext==0){
            temp.part_next=-1;
        }
        int contador_ebr=0;
        while(temp.part_next != -1){
            contador_ebr++;
            fprintf(doc,"      tbl%d [ shape=plaintext \n",contador_ebr);
            fprintf(doc,"   label=< \n");
            fprintf(doc,"   <table border= \"0\" cellborder=\"1\" color=\"#9121B0\" cellspacing=\"0\"> \n");
            fprintf(doc,"       <tr><td colspan=\"2\"> EBR_%d </td></tr>\n",contador_ebr);
            fprintf(doc,"       <tr><td cellpadding=\"4\"><b> Nombre </b></td> <td cellpadding=\"4\"><b>Valor </b></td></tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_status_1</b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n", temp.part_status);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_fit_1</b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n",temp.part_fit);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_start_1</b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", temp.part_start);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_size_1 </b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", temp.part_size);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_next_1 </b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", temp.part_next);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_name_1 </b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %s </td> \n", temp.part_name);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"   </table> \n");
            fprintf(doc," >]; \n");
            fseek(archivo_mbr, temp.part_next, SEEK_SET);
            fread(&temp,sizeof(objetos::EBR),1, archivo_mbr);
        }
        contador_ebr++;
        if(temp.part_next == -1 && ext !=0){
            fprintf(doc,"      tbl%d [ shape=plaintext \n",contador_ebr);
            fprintf(doc,"   label=< \n");
            fprintf(doc,"   <table border= \"0\" cellborder=\"1\" color=\"#9121B0\" cellspacing=\"0\"> \n");
            fprintf(doc,"       <tr><td colspan=\"2\"> EBR_%d </td></tr>\n",contador_ebr);
            fprintf(doc,"       <tr><td cellpadding=\"4\"><b> Nombre </b></td> <td cellpadding=\"4\"><b>Valor </b></td></tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_status_1</b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n", temp.part_status);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_fit_1</b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %c </td> \n",temp.part_fit);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_start_1</b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", temp.part_start);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_size_1 </b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", temp.part_size);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_next_1 </b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %d </td> \n", temp.part_next);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"       <tr> \n");
            fprintf(doc,"           <td cellpadding=\"4\"><b> part_name_1 </b> </td> \n");
            fprintf(doc,"           <td cellpadding=\"4\"> %s </td> \n", temp.part_name);
            fprintf(doc,"       </tr> \n");
            fprintf(doc,"   </table> \n");
            fprintf(doc," >]; \n");
        }
        fclose(archivo_mbr);
        fprintf(doc,"} \n");
        fclose(doc);
        strcpy(ejecutarDot, "dot -Tpng /home/archivos/reportesreporte_mbr.dot -o");
        strcat(ejecutarDot, " ");
        strcat(ejecutarDot, ruta_reporte);
        system(ejecutarDot);
        strcat(ruta, "xdg-open");
        strcat(ruta, " ");
        strcat(ruta, ruta_reporte);
        system(ruta);
        }else{
             printf("** ERROR: No se pudo cargar el archivo del mbr ** \n");
         }
    }
}
void REP::getRuta(char * path){
    int i=0;
    char caracter[2] = {0};
    char temp_path[500]={0};
    memset(caracter, 0, 2);
    memset(temp_path, 0, 500);
    while(path[i] != 0){
        caracter[0] = path[i];
        if(strcmp(caracter,"/")==0){
            strcat(temp_path, "/");
            strcat(ruta_disco, temp_path);
            memset(temp_path, 0, 500);
        }else if(strcmp(caracter,".")==0){
            strcat(nombre_disco, temp_path);
            memset(temp_path, 0, 500);
        }else{
            strcat(temp_path,caracter);
        }
        i++;
    }
}
void REP::graficar_Disk(char path[255], objetos::REP rep){
    char ejecutarDot_disk[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot_disk[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    MKDISK nuevo;
    objetos::MBR mbr;
    objetos::EBR ebr;
    getRuta(path);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
        if(mkdir(ruta_disco, 0777) != -1){
            existe_dir++;
        }
    }
    int pos_extendida = 0;
    int todo_libre =0;
    if(existe_dir!=0){
        double porcentaje_usado = 0.0;
        double porcentaje_total = 0.0;
        double porcentaje_usado_ex = 0.0;
        double porcentaje_total_ex = 0.0;
        double libre = 100.0;
        double part_libres = 0.0;
        FILE *archivo_disco = fopen(path, "rb+");
        if(archivo_disco !=NULL){
            fseek(archivo_disco, 0, SEEK_SET);
            fread(&mbr, sizeof (objetos::MBR), 1, archivo_disco);
            fclose(archivo_disco);
            for(int i=0; i<4;i++){
                if(mbr.mbr_partitions[i].part_type != 'P' && mbr.mbr_partitions[i].part_type != 'E' ){
                    part_libres++;
                }
                if(mbr.mbr_partitions[i].part_type == 'E'){
                    pos_extendida = i;
                }
            }
            FILE *doc_disk;
            doc_disk = fopen("/home/archivos/reportesreporte_disk.dot","w");
            fprintf(doc_disk,"digraph reporte{ \n");
            fprintf(doc_disk,"label= %s \n",rep.id);
            fprintf(doc_disk,"tbl [ shape=plaintext \n");
            fprintf(doc_disk,"   label=< \n");
            fprintf(doc_disk,"   <table border= \"0\" cellborder=\"1\" color=\"#5597DD\" cellspacing=\"0\"> \n");
            fprintf(doc_disk,"      <tr> \n");
            fprintf(doc_disk,"        <td> <b>MBR</b></td> \n");
            for(int i = 0; i<4; i++){
                if(mbr.mbr_partitions[i].part_type == 'P'){
                    porcentaje_usado = obtenerPorcentaje((double)mbr.mbr_partitions[i].part_start, (double)mbr.mbr_partitions[i].part_size, (double)mbr.mbr_tamano);
                    porcentaje_total = porcentaje_usado + porcentaje_total;
                   fprintf(doc_disk,"        <td>  <b>Primaria</b> <br/>  %s <br/><font color=\"#5A6571\" >%.2f  del disco  </font></td> \n",mbr.mbr_partitions[i].part_name,porcentaje_usado);
                }else if(mbr.mbr_partitions[i].part_type == 'E'){
                    porcentaje_usado = obtenerPorcentaje((double)mbr.mbr_partitions[i].part_start, (double)mbr.mbr_partitions[i].part_size, (double)mbr.mbr_tamano);
                    porcentaje_total = porcentaje_usado + porcentaje_total;
                    archivo_disco = fopen(path, "rb+");
                    int inicio_part = mbr.mbr_partitions[pos_extendida].part_start;
                    fseek(archivo_disco, inicio_part, SEEK_SET);
                    fread(&ebr,sizeof(objetos::EBR), 1, archivo_disco); //este seria el primer ebr
                    objetos::EBR temp = ebr;
                    fprintf(doc_disk,"       <td> \n");
                    fprintf(doc_disk,"         <table color=\"#5597DD\" border=\"0\" cellborder=\"1\" cellpadding=\"10\" cellspacing=\"0\"> \n",libre);
                    fprintf(doc_disk,"               <tr><td  colspan=\"50\"><b>Extendida</b></td></tr> \n");
                    fprintf(doc_disk,"               <tr> \n");
                    if(ebr.part_status == '4'){
                        fprintf(doc_disk,"                   <td>EBR</td> \n");
                        fprintf(doc_disk,"                   <td>Libre<br/><font color=\"#5A6571\" >100% del disco</font></td> \n");
                    }else{
                        //Es una logica
                        while(temp.part_next != -1 && temp.part_next != 0 ){
                            if(temp.part_status == '0'){
                                porcentaje_usado_ex = obtenerPorcentaje((double)temp.part_start, (double)temp.part_size, (double)mbr.mbr_tamano);
                                porcentaje_total_ex = porcentaje_usado_ex + porcentaje_total_ex;
                                fprintf(doc_disk,"                   <td>EBR</td> \n");
                                fprintf(doc_disk,"                   <td>  Libre <br/><font color=\"#5A6571\" > </font></td> \n");
                                fseek(archivo_disco, temp.part_next, SEEK_SET);
                                fread(&temp,sizeof(objetos::EBR),1, archivo_disco);
                            }else{
                                porcentaje_usado_ex = obtenerPorcentaje((double)temp.part_start, (double)temp.part_size, (double)mbr.mbr_tamano);
                                porcentaje_total_ex = porcentaje_usado_ex + porcentaje_total_ex;
                                fprintf(doc_disk,"                   <td>EBR</td> \n");
                                fprintf(doc_disk,"                   <td>Logica<br/> %s <br/><font color=\"#5A6571\" > %.2f  del disco</font></td> \n",temp.part_name ,porcentaje_usado_ex);
                                fseek(archivo_disco, temp.part_next, SEEK_SET);
                                fread(&temp,sizeof(objetos::EBR),1, archivo_disco);
                            }
                        }
                        if(porcentaje_total_ex < 100){
                            double total = 100- porcentaje_total_ex;
                            fprintf(doc_disk,"                   <td>Libre<br/><font color=\"#5A6571\" > %.2f  del disco</font></td> \n",total);
                        }
                    }
                    fprintf(doc_disk,"               </tr> \n");
                    fprintf(doc_disk,"         </table> \n");
                    fprintf(doc_disk,"       </td> \n");
                    fclose(archivo_disco);
                }else{
                    fprintf(doc_disk,"        <td>  <b>Libre</b> <font color=\"#5A6571\" >   </font></td> \n");
                    todo_libre++;
                }
                if(i == 3){
                    if(porcentaje_total < 100){
                        double total = 100- porcentaje_total;
                        fprintf(doc_disk,"                   <td>Libre<br/><font color=\"#5A6571\" > %.2f  del disco</font></td> \n",total);
                    }
                }
            }
            fprintf(doc_disk,"      </tr> \n");
            fprintf(doc_disk,"   </table> \n");
            fprintf(doc_disk," >]; \n");
            fprintf(doc_disk,"} \n");
            fseek(archivo_disco, 0, SEEK_SET);
            fclose(doc_disk);
            strcpy(ejecutarDot_disk, "dot -Tpng /home/archivos/reportesreporte_disk.dot -o");
            strcat(ejecutarDot_disk, " ");
            strcat(ejecutarDot_disk, ruta_reporte);
            system(ejecutarDot_disk);
            strcat(ruta, "xdg-open");
            strcat(ruta, " ");
            strcat(ruta, ruta_reporte);
            system(ruta);
            limpiar();
        }
    }
}
double REP::obtenerPorcentaje(double posicion_inicio, double posicion_fin, double tamanio_mbr) {
    int resultado = (int) ((posicion_fin * 100) / tamanio_mbr);
    return resultado;
}
void REP::rep_ls(char path[255],lista::nodoP * particion){
    char ejecutarDot[1024];
    char ruta[255];
    memset(ejecutarDot,'\0',1024);
    memset(ruta,'\0',255);
    //Verificar si es archivo
    MKDIR * mkd = new MKDIR();
    FILE *fp1;
    fp1 = fopen(path, "rb+");
    if (!fp1) {
        printf("Error: No se encontro el disco");
        return;
    }
    //RECUPERO MBR
    objetos::MBR *masterBoot = (objetos::MBR*) malloc(sizeof (objetos::MBR));
    fseek(fp1, 0, SEEK_SET);
    fread(masterBoot, sizeof (objetos::MBR), 1, fp1);
    //BUSCANDO PARTICION
    int i;
    for (i = 0; i < 4; i++) {
        if (strcmp(masterBoot->mbr_partitions[i].part_name, particion->name) == 0) {
            break;
        }
    }
    //RECUPERANDO SUPER BLOQUE DE PARTICIÓN
    objetos::superBloque super ;
    fseek(fp1, masterBoot->mbr_partitions[i].part_start, SEEK_SET);
    fread(&super, sizeof ( objetos::superBloque), 1, fp1);
    objetos::inodo *father = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    int inode_position;
    int n = mkd->ContadorBarras(ruta_archivo);
    if (n == 1) {
        //Recuperar inodo padre
        inode_position = super.s_inode_start;
        fseek(fp1, inode_position, SEEK_SET);
        fread(father, sizeof (objetos::inodo), 1, fp1);
    } else {
        MKDIR::Lista ruta2[n - 1];
        //Limpiar
        for (int i = 0; i < n - 1; i++) {
            memset(ruta2[i].carpeta, 0, sizeof (ruta2[i].carpeta));
        }
        int longPath = strlen(ruta_archivo);
        int k = -1;
        int contador = 0;
        for (int i = 0; i < longPath; i++) {
            if (ruta_archivo[i] == '/') {
                contador++;
                k++;
                if (contador == n) {
                    break;
                }
            } else {
                strcpy(ruta2[k].carpeta, mkd->Concatenar(ruta2[k].carpeta, ruta_archivo[i]));
            }
        }
        //Busqueda de la ruta
        inode_position = mkd->BusquedaCarpeta(fp1,super , super.s_inode_start, ruta2, n - 1, 0);
        if (inode_position == 0) {
            printf("Error: La ruta no existe.\n");
            return;
        } else {
            //Recuperar inodo padre
            fseek(fp1, inode_position, SEEK_SET);
            fread(father, sizeof (objetos::inodo), 1, fp1);
        }
    }
    //Obtener el inodo del archivo
    char ts1[300];
    memset(ts1, 0, sizeof (ts1));
    strcpy(ts1, strdup(ruta_archivo)); //Copiando ruta
    char filename[50];
    memset(filename, 0, sizeof (filename));
    strcpy(filename, basename(ts1)); //Obteniendo nombre de archivo o carpeta
    fs * sis = new fs();
    int pos_object = sis->ExisteInodo( super, inode_position, filename,fp1);
    char foldername[50];
    memset(foldername, 0, sizeof (foldername));
    strcpy(foldername, basename(ruta_archivo));
    if (pos_object != -1) {
        //inodo de archivo
        objetos::inodo inodoArchivo;
        fseek(fp1, pos_object, SEEK_SET);
        fread(&inodoArchivo, sizeof (objetos::inodo), 1, fp1);
        FILE *doc;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        doc = fopen("/home/archivos/reportesreporte_ls.dot","w");
        fprintf(doc,"digraph reporte{ \n");
        fprintf(doc,"  reporte [ shape=plaintext  \n");
        fprintf(doc,"  label=<  \n");
        fprintf(doc, "<table border='2' cellborder='1'> \n");
        fprintf(doc, " <tr> \n <td>Permisos</td><td>Owner</td><td>Grupo</td><td>Size</td><td>Fecha-Hora-Creacion</td><td>Tipo</td><td>Name</td></tr>\n");
        fprintf(doc, " <tr><td>");
        //************** para los permisos
            permisos(inodoArchivo.i_perm,doc);
            fprintf(doc, "</td> \n");
        //*********  usuario
            fprintf(doc, "<td>");
             obtener_Nuser(super,inodoArchivo.i_uid,archivo_mbr,doc);
            fprintf(doc, "</td> \n");
        //****** grupo
            fprintf(doc, "<td>");
             obtener_Ngrupo(super,inodoArchivo.i_gid,archivo_mbr,doc);
            fprintf(doc, "</td> \n");
        //************* size
            fprintf(doc, "<td>");
            fprintf(doc,"%d",inodoArchivo.i_size);
            fprintf(doc, "</td> \n");
        //************* fecha
            MKDISK * nuevo = new MKDISK();
            objetos::MBR mbr = nuevo->crearMBR(0);
            fprintf(doc, "<td>");
            fprintf(doc,"%s",get_Fecha(inodoArchivo.i_ctime));
            fprintf(doc, "</td> \n");
        //************ tipo
            fprintf(doc, "<td>");
            if(inodoArchivo.i_type == '0'){
                fprintf(doc,"Carpeta");
            }else if(inodoArchivo.i_type == '1'){
                fprintf(doc,"Archivo");
            }
            fprintf(doc, "</td> \n");
        //*********** nombre
            fprintf(doc, "<td>");
            fprintf(doc,"%s",foldername);
            fprintf(doc, "</td> \n");
        fprintf(doc, " </tr> \n");
        fprintf(doc," </table> \n");
        fprintf(doc," >]; }\n");
        fclose(doc);
        strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportesreporte_ls.dot -o");
        strcat(ejecutarDot, " ");
        strcat(ejecutarDot, ruta_reporte);
        system(ejecutarDot);
        strcat(ruta, " xdg-open");
        strcat(ruta, " ");
        strcat(ruta, ruta_reporte);
        system(ruta);
    } else {
        printf("Error: El archivo no existe.\n");
    }
    fclose(fp1);
}
void REP::rep_file(char path[255],lista::nodoP * particion){
    char ejecutarDot[1024];
    char ruta[255];
        for (int i = 0; i < 1024; i++) {
            ejecutarDot[i] = '\0';
        }
        for (int i = 0; i < 255; i++) {
            ruta[i] = '\0';
        }
    MKFILE * mkf = new MKFILE();
    MKDIR * mkd = new MKDIR();
    int tipo = mkf->VerificarPath(ruta_archivo);
    if (tipo != 1) {
        printf("Error: La ruta no contiene un archivo.\n");
        return;
    }
    //DISCO
    FILE *fp1;
    fp1 = fopen(path, "rb+");
    if (!fp1) {
        printf("Error: No se encontro el disco");
        return;
    }
    //RECUPERO MBR
    objetos::MBR *masterBoot = (objetos::MBR*) malloc(sizeof (objetos::MBR));
    fseek(fp1, 0, SEEK_SET);
    fread(masterBoot, sizeof (objetos::MBR), 1, fp1);
    //BUSCANDO PARTICION
    int i;
    for (i = 0; i < 4; i++) {
        if (strcmp(masterBoot->mbr_partitions[i].part_name, particion->name) == 0) {
            break;
        }
    }
    //RECUPERANDO SUPER BLOQUE DE PARTICIÓN
    objetos::superBloque super ;
    fseek(fp1, masterBoot->mbr_partitions[i].part_start, SEEK_SET);
    fread(&super, sizeof ( objetos::superBloque), 1, fp1);
    objetos::inodo *father = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    int inode_position;
    int n = mkd->ContadorBarras(ruta_archivo);
    if (n == 1) {
        //Recuperar inodo padre
        inode_position = super.s_inode_start;
        fseek(fp1, inode_position, SEEK_SET);
        fread(father, sizeof (objetos::inodo), 1, fp1);
    } else {
        MKDIR::Lista ruta2[n - 1];
        //Limpiar
        for (int i = 0; i < n - 1; i++) {
            memset(ruta2[i].carpeta, 0, sizeof (ruta2[i].carpeta));
        }
        int longPath = strlen(ruta_archivo);
        int k = -1;
        int contador = 0;
        for (int i = 0; i < longPath; i++) {
            if (ruta_archivo[i] == '/') {
                contador++;
                k++;
                if (contador == n) {
                    break;
                }
            } else {
                strcpy(ruta2[k].carpeta, mkd->Concatenar(ruta2[k].carpeta, ruta_archivo[i]));
            }
        }
        //Busqueda de la ruta
        inode_position = mkd->BusquedaCarpeta(fp1,super , super.s_inode_start, ruta2, n - 1, 0);
        if (inode_position == 0) {
            printf("Error: La ruta no existe.\n");
            return;
        } else {
            //Recuperar inodo padre
            fseek(fp1, inode_position, SEEK_SET);
            fread(father, sizeof (objetos::inodo), 1, fp1);
        }
    }
    //Obtener el inodo del archivo
    char ts1[300];
    memset(ts1, 0, sizeof (ts1));
    strcpy(ts1, strdup(ruta_archivo)); //Copiando ruta
    char filename[50];
    memset(filename, 0, sizeof (filename));
    strcpy(filename, basename(ts1)); //Obteniendo nombre de archivo o carpeta
    fs * sis = new fs();
    int pos_object = sis->ExisteInodo( super, inode_position, filename,fp1);
    if (pos_object != -1) {
        //inodo de archivo
        objetos::inodo inodoArchivo;
        fseek(fp1, pos_object, SEEK_SET);
        fread(&inodoArchivo, sizeof (objetos::inodo), 1, fp1);
        cout<<"Nombre de archivo: "<<filename<<endl;
        printf("%s\n", sis->ObtenerTexto(fp1, super, inodoArchivo));
        FILE *doc_sb;
        doc_sb = fopen("/home/archivos/reportesfile.dot","w");
        fprintf(doc_sb,"digraph reporte{ \n");
        fprintf(doc_sb,"Nombre-> Contenido \n");
        fprintf(doc_sb," Nombre [label=\"%s\",shape=Mdiamond]; \n",filename);
        fprintf(doc_sb," Contenido[label=\"%s\",shape=Mdiamond]; \n",sis->ObtenerTexto(fp1, super, inodoArchivo));
        fprintf(doc_sb,"}\n");
        fclose(doc_sb);
        strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportesfile.dot -o");
        strcat(ejecutarDot, " ");
        strcat(ejecutarDot, ruta_reporte);
        system(ejecutarDot);
        strcat(ruta, "xdg-open");
        strcat(ruta, " ");
        strcat(ruta, ruta_reporte);
        system(ruta);
        fclose(fp1);
    } else {
        printf("Error: El archivo no existe.\n");
    }
}
void REP::rep_sb( char path[255],lista::nodoP * particion ){
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
       printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
        //buscar la particion donde esta el sistema de archivos
        int num_particion=-1;
        for(int i=0; i<4;i++){
            if(mbr.mbr_partitions[i].part_status!='0'){
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion = i;
                }
            }
        }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion != -1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
        //crear el reporte
            FILE *doc_sb;
            doc_sb = fopen("/home/archivos/reportessuper.s_dot","w");
            fprintf(doc_sb,"digraph reporte{ \n");
            fprintf(doc_sb,"tbl [ shape=plaintext \n");
            fprintf(doc_sb,"   label=< \n");
            fprintf(doc_sb,"   <table border= \"0\" cellborder=\"1\"  cellspacing=\"0\"> \n");
            fprintf(doc_sb,"       <tr><td colspan=\"2\"> Super Bloque -  %s - %s.disk</td></tr>\n",particion->name, nombre_disco);
            fprintf(doc_sb,"       <tr><td cellpadding=\"4\"><b> Nombre </b></td> <td cellpadding=\"4\"><b>Valor </b></td></tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_inodes_count</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_inodes_count);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_blocks_count</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_blocks_count);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_free_inodes_count</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_free_inodes_count);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_free_blocks_count_count</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_free_blocks_count);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_mtime</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %s </td> \n", get_Fecha(super_bloque.s_mtime));
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_umtime</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %s </td> \n", get_Fecha(super_bloque.s_umtime));
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_mnt_count</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_mnt_count);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_magic</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_magic);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_inode_size</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_inode_size);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_bloc_size</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_block_size);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_first:ino</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_first_ino);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_first_block</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_first_blo);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_bm_inode_start</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_bm_inode_start);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_bm_block_start</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_bm_block_start);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_inode_start</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_inode_start);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"       <tr> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"><b> s_block_start</b> </td> \n");
            fprintf(doc_sb,"           <td cellpadding=\"4\"> %d </td> \n", super_bloque.s_block_start);
            fprintf(doc_sb,"       </tr> \n");
            fprintf(doc_sb,"   </table> \n");
            fprintf(doc_sb," >]; \n");
            fclose(archivo_mbr);
            fprintf(doc_sb,"} \n");
            fclose(doc_sb);
            strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportessuper.s_dot -o");
            strcat(ejecutarDot, " ");
            strcat(ejecutarDot, ruta_reporte);
            system(ejecutarDot);
            strcat(ruta, "xdg-open");
            strcat(ruta, " ");
            strcat(ruta, ruta_reporte);
            system(ruta);
        }else{
            cout << super_bloque.s_magic << endl;
            cout <<"Error, no se pudo recuperar la informacion del formato de la particion" <<endl;
            return;
        }
    }
}
void REP::rep_bm_inodes(char path[255], lista::nodoP*particion){
    //variables para escribir el dot y la ruta donde se generara
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
       printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            printf("entre al archivo \n");
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
         //buscar la particion donde esta el sistema de archivos
         int num_particion=-1;
         for(int i=0; i<4;i++){
             if(mbr.mbr_partitions[i].part_status!='0'){
                 if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                     num_particion = i;
                 }
             }
         }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion!=-1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
            //crear archivo del reporte
            ofstream archivo_reporte;
            archivo_reporte.open(ruta_reporte,ios::out);
            if(archivo_reporte.fail()){
                cout<<"NO ES POSIBLE ABRIR EL ARCHIVO"<<endl;
                return;
            }
            int inicio_bloques = super_bloque.s_bm_inode_start;
            int numero_bloques = super_bloque.s_inodes_count;
            fseek(archivo_mbr,inicio_bloques,SEEK_SET);
            objetos::bitmap *bip = (objetos::bitmap*) malloc(sizeof (objetos::bitmap));
            int contador=0;
            for(int i=0; i < numero_bloques; i++){
                fread(bip, sizeof (objetos::bitmap), 1, archivo_mbr);
                if (contador < 20) {
                    if (bip->state == '0') {
                            archivo_reporte<<bip->state;
                    } else if(bip->state == '1'){
                        archivo_reporte<<bip->state;
                    }else{
                        archivo_reporte<<bip->state;
                    }
                    archivo_reporte<<" ";
                } else {
                    archivo_reporte<<"\n";
                    if (bip->state == '1') {
                        archivo_reporte<<bip->state;
                    } else if(bip->state == '0'){
                        archivo_reporte<<bip->state;
                    }else{
                        archivo_reporte<<bip->state;
                    }
                    archivo_reporte<<" ";
                    contador = 0;
                }
                contador++;
            }
            archivo_reporte.close();
        }else{
            cout<<" **ERROR: no se pudo recuperar la informacion del formato de la particion"<<endl;
            return;
        }
    }
}
void REP::rep_bm_blockes(char path[255], lista::nodoP*particion){
    //variables para escribir el dot y la ruta donde se generara
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
        printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        double size_patition = 0.0;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            printf("entre al archivo \n");
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
        //buscar la particion donde esta el sistema de archivos
        int num_particion=-1;
        for(int i=0; i<4;i++){
            if(mbr.mbr_partitions[i].part_status!='0'){
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion = i;
                }
            }
        }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion!=-1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
            //crear archivo del reporte
            FILE *archivo_reporte;
            archivo_reporte = fopen(ruta_reporte, "w");
            int inicio_bloques = super_bloque.s_bm_block_start;
            int numero_bloques = super_bloque.s_blocks_count;
            fseek(archivo_mbr,inicio_bloques,SEEK_SET);
            fseek(archivo_reporte,0,SEEK_SET);
            objetos::bitmap *bip = (objetos::bitmap*) malloc(sizeof (objetos::bitmap));
            int contador=0;
            for(int i=0; i < numero_bloques; i++){
                fread(bip, sizeof (objetos::bitmap), 1, archivo_mbr);
                if (contador < 20) {
                    if (bip->state != 'C' && bip->state != 'A' && bip->state != 'P') {
                      fprintf(archivo_reporte, "%c", '0');
                    } else {
                        fprintf(archivo_reporte, "%c", '1');
                    }
                    fprintf(archivo_reporte, " ");
                } else {
                    fprintf(archivo_reporte, "\n");
                    if (bip->state != 'C') {
                        fprintf(archivo_reporte, "%c", '0');
                    } else {
                        fprintf(archivo_reporte, "%c", '1');
                    }
                    fprintf(archivo_reporte, " ");
                    contador = 0;
                }
                contador++;
            }
            cout<<" **se creo el reporte de bitmap de bloques de la particion - "<<particion->name<<endl;
        }else{
            cout<<" **ERROR: no se pudo recuperar la informacion del formato de la particion"<<endl;
            return;
        }
     }
}
void REP::rep_inodos( char path[255],lista::nodoP * particion ){
    //variables para escribir el dot y la ruta donde se generara
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
       printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        double size_patition = 0.0;
        FILE *doc;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            printf("entre al archivo \n");
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
        //buscar la particion donde esta el sistema de archivos
        int num_particion=-1;
        for(int i=0; i<4;i++){
            if(mbr.mbr_partitions[i].part_status!='0'){
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion = i;
                }
            }
        }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion!=-1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
            //crear el reporte
            doc = fopen("/home/archivos/reportesreporte_inodos.dot","w");
             //** contenido del reporte
            fprintf(doc, "digraph Reporte{\n");
            fprintf(doc, "rankdir = \"LR\";\n");
            fprintf(doc, "    node[\n");
            fprintf(doc, "        fontname = \"Bitstream Vera Sans\"\n");
            fprintf(doc, "        fontsize = 8\n");
            fprintf(doc, "        style= filled\n");
            fprintf(doc, "        shape = box\n");
            fprintf(doc, "    ]\n");
            CuerpoInodos(super_bloque, 0, super_bloque.s_inode_start , archivo_mbr,doc);
            flechas_inodos(super_bloque, doc);
            fprintf(doc, "}\n");
            fclose(doc);
            strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportesreporte_inodos.dot -o");
            strcat(ejecutarDot, " ");
            strcat(ejecutarDot, ruta_reporte);
            system(ejecutarDot);
            strcat(ruta, "xdg-open");
            strcat(ruta, " ");
            strcat(ruta, ruta_reporte);
            system(ruta);
            limpiar();
        }else{
            cout<<" **ERROR: no se pudo recuperar la informacion del formato de la particion"<<endl;
            return;
        }
    }
}
void REP::CuerpoInodos(objetos::superBloque super, int noinodo, int pos_inode, FILE *archivo, FILE * fp) {
    //Obtener el inodo
    objetos::inodo *node = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    fseek(archivo, pos_inode, SEEK_SET);
    fread(node, sizeof (objetos::inodo), 1, archivo);
    char tipo[10];
    memset(tipo, 0, sizeof (tipo));
    int contador = 0;
    //DIBUJO DEL inodo
    fprintf(fp, "inodo%d[label=\"<f%d>inodo %d\n", noinodo, contador, noinodo);
    contador++;
    fprintf(fp, "|<f%d>UID :         %d\n", contador, node->i_uid);
    contador++;
    fprintf(fp, "|<f%d>GID :         %d\n", contador, node->i_gid);
    contador++;
    fprintf(fp, "|<f%d>SIZE :        %d\n", contador, node->i_size);
    contador++;
    fprintf(fp, "|<f%d>ATIME : %s\n", contador, ctime(&node->i_atime));
    contador++;
    fprintf(fp, "|<f%d>CTIME : %s\n", contador, ctime(&node->i_ctime));
    contador++;
    fprintf(fp, "|<f%d>MTIME : %s\n", contador, ctime(&node->i_mtime));
    contador++;
    if (node->i_type == '0') {
        strcpy(tipo, "carpeta");
    } else {
        strcpy(tipo, "archivo");
    }
    fprintf(fp, "|<f%d>TIPO :    %s\n", contador, tipo);
    contador++;
    fprintf(fp, "|<f%d>PERMISOS :    %d\n", contador, node->i_perm);
    contador++;
    /*Apuntadores directos*/
    for (int i = 0; i < 12; i++) {
        fprintf(fp, "|<f%d>APD%d :  %d\n", contador, i, node->block[i]);
        contador++;
    }
    /*Apuntadores indirectos*/
    fprintf(fp, "|<f%d>APIS%d :          %d\n", contador, 12, node->block[12]);
    contador++;
    fprintf(fp, "|<f%d>APID%d :          %d\n", contador, 13, node->block[13]);
    contador++;
    fprintf(fp, "|<f%d>APIT%d :          %d\n", contador, 14, node->block[14]);
    contador++;
    fprintf(fp, "\" shape = \"Mrecord\" ];\n");
    //Recursividad
    if (node->i_type == '0') { //CARPETA
        /*Recorrer apuntadores directos*/
        int inicio;
        for (int i = 0; i < 12; i++) {
            if (node->block[i] != -1) {
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                if (i == 0) {
                    inicio = 2;
                } else {
                    inicio = 0;
                }
                for (int j = inicio; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                        CuerpoInodos(super, folder_block->b_content[j].b_inodo, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                    }
                }
            }
        }
    //** apuntadores indirectos
        if(node->block[12]!= -1){
            objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(archivo, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, archivo); //Recupero el bloque de Carpeta
            for(int i =0; i<16; i++){
                if(pointer_block->b_pointers[i]!=-1){
                    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                    fseek(archivo, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                    fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                     int cont_int=0;
                    for (int j = 0; j < 4; j++) {
                        if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                            CuerpoInodos(super, folder_block->b_content[j].b_inodo, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                        }
                    }
                }
            }
        }
    }
}
void REP::flechas_inodos(objetos::superBloque super, FILE * fp){
    int num_inodo= super.s_inode_start;
    int total_inodos = super.s_inodes_count - super.s_free_inodes_count;
    int contador = 0;
    for(contador=0; contador<total_inodos;contador++){
        //Obtener el inodo
        fprintf(fp, "inodo%d -> inodo%d \n",contador,contador+1 );
    }
}
void REP::rep_arbol( char path[255],lista::nodoP * particion ){
   //variables para escribir el dot y la ruta donde se generara
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
       printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        double size_patition = 0.0;
        FILE *doc;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            printf("entre al archivo \n");
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
        //buscar la particion donde esta el sistema de archivos
        int num_particion=-1;
        for(int i=0; i<4;i++){
            if(mbr.mbr_partitions[i].part_status!='0'){
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion = i;
                }
            }
        }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion!=-1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
            //crear el reporte
            doc = fopen("/home/archivos/reportesreporte_arbol.dot","w");
            //** contenido del reporte
            fprintf(doc, "digraph Reporte{\n");
            fprintf(doc, "rankdir = \"LR\"\n");
            fprintf(doc, "    node[\n");
            fprintf(doc, "        fontname = \"Bitstream Vera Sans\"\n");
            fprintf(doc, "        fontsize = 8\n");
            fprintf(doc, "        style= filled\n");
            fprintf(doc, "        fillcolor=white\n");
            fprintf(doc, "        shape = box\n");
            fprintf(doc, "    ]\n");
            CuerpoArbol(super_bloque, 0, super_bloque.s_inode_start, archivo_mbr, doc);
            ApuntadoresArbol(super_bloque, 0, super_bloque.s_inode_start, archivo_mbr, doc);
            fprintf(doc, "}\n");
            fclose(doc);
            strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportesreporte_arbol.dot -o");
            strcat(ejecutarDot, " ");
            strcat(ejecutarDot, ruta_reporte);
            system(ejecutarDot);
            strcat(ruta, "xdg-open");
            strcat(ruta, " ");
            strcat(ruta, ruta_reporte);
            system(ruta);
        }else{
            cout<<" **ERROR: no se pudo recuperar la informacion del formato de la particion"<<endl;
            return;
        }
    }
}
void REP::CuerpoArbol(objetos::superBloque super, int noinodo, int pos_inode, FILE *archivo, FILE * fp) {
    //Obtener el inodo
    objetos::inodo *node = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    fseek(archivo, pos_inode, SEEK_SET);
    fread(node, sizeof (objetos::inodo), 1, archivo);
    char tipo[10];
    memset(tipo, 0, sizeof (tipo));
    int contador = 0;
    //DIBUJO DEL inodo
    fprintf(fp, "inodo%d[label=\"<f%d>inodo %d\n", noinodo, contador, noinodo);
    contador++;
    fprintf(fp, "|<f%d>UID :   %d\n", contador, node->i_uid);
    contador++;
    fprintf(fp, "|<f%d>GID :   %d\n", contador, node->i_gid);
    contador++;
    fprintf(fp, "|<f%d>SIZE :  %d\n", contador, node->i_size);
    contador++;
    fprintf(fp, "|<f%d>ATIME : %s\n", contador, ctime(&node->i_atime));
    contador++;
    fprintf(fp, "|<f%d>CTIME : %s\n", contador, ctime(&node->i_ctime));
    contador++;
    fprintf(fp, "|<f%d>MTIME : %s\n", contador, ctime(&node->i_mtime));
    contador++;
    if (node->i_type == '0') {
        strcpy(tipo, "carpeta");
    } else {
        strcpy(tipo, "archivo");
    }
    fprintf(fp, "|<f%d>TIPO :  %s\n", contador, tipo);
    contador++;
    fprintf(fp, "|<f%d>PERMISOS :  %d\n", contador, node->i_perm);
    contador++;
    /*Apuntadores directos*/
    for (int i = 0; i < 12; i++) {
        if (node->block[i] != -1) {
            fprintf(fp, "|<f%d>APD%d :  %d\n", contador, i, node->block[i]);
            contador++;
        }
    }
    /*Apuntadores indirectos*/
    if (node->block[12] != -1) {
        fprintf(fp, "|<f%d>APIS%d :  %d\n", contador, 12, node->block[12]);
        contador++;
    }
    if (node->block[13] != -1) {
        fprintf(fp, "|<f%d>APID%d :  %d\n", contador, 13, node->block[13]);
        contador++;
    }
    if (node->block[14] != -1) {
        fprintf(fp, "|<f%d>APIT%d :  %d\n", contador, 14, node->block[14]);
        contador++;
    }
    fprintf(fp, "\" shape = \"Mrecord\" color=cyan4];\n");
    if (node->i_type == '0') { //CARPETA
        //DIBUJAR BLOQUES DE CARPETA
        /*Apuntadores directos*/
        for (int i = 0; i < 12; i++) {
            contador = 0;
            if (node->block[i] != -1) {
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                fprintf(fp, "Folder%d[label=\"<f%d>Bloque Carpeta %d\n", node->block[i], contador, node->block[i]);
                contador++;
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        fprintf(fp, "|<f%d>%s    %d\n", contador, folder_block->b_content[j].b_name, folder_block->b_content[j].b_inodo);
                        contador++;
                    }
                }
                fprintf(fp, "\"shape = \"Mrecord\" color = orange style = filled];\n");
            }
        }
        //** apuntador indirecto
        if(node->block[12]!=-1){
            //recuperar el bloque
            objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(archivo, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, archivo); //Recupero el bloque de Carpeta

            fprintf(fp, "Apuntadores%d[label=\"<f%d>Bloque Apuntadores %d\n", node->block[12], contador, node->block[12]);
            int cont2=0;
            for(int i =0; i<16; i++){
                    if(pointer_block->b_pointers[i]!=-1){
                        fprintf(fp, "|<f%d>  %d\n", cont2, pointer_block->b_pointers[i]);
                        cont2++;
                    }
                }
            fprintf(fp, "\"shape = \"Mrecord\" color = yellow style = filled];\n");
            for(int i =0; i<16; i++){
                if(pointer_block->b_pointers[i]!=-1){
                    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                    fseek(archivo, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                    fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta

                    fprintf(fp, "Folder%d[label=\"<f%d>Bloque Carpeta %d\n", pointer_block->b_pointers[i], contador, pointer_block->b_pointers[i]);
                    int cont_int=0;
                    for (int j = 0; j < 4; j++) {
                        if (folder_block->b_content[j].b_inodo != -1) {
                            fprintf(fp, "|<f%d>%s    %d\n", cont_int, folder_block->b_content[j].b_name, folder_block->b_content[j].b_inodo);
                            cont_int++;
                        }
                    }
                    fprintf(fp, "\"shape = \"Mrecord\" color = orange style = filled];\n");
                }
            }
        }
    } else if (node->i_type == '1') { //ARCHIVO
        //DIBUJAR BLOQUES DE ARCHIVO
        /*Apuntadores directos*/
        for (int i = 0; i < 12; i++) {
            contador = 0;
            if (node->block[i] != -1) {
                objetos::bloqueArchivo *file_block = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
                fread(file_block, sizeof (objetos::bloqueArchivo), 1, archivo); //Recupero el bloque de Archivo
                fprintf(fp, "Archivo%d[label=\"<f%d>Bloque Archivo %d\n", node->block[i], contador, node->block[i]);
                contador++;
                char delimitador[] = "\n";
                //delimitador[]= "\n";
                char *grupo = strtok(file_block->b_content, delimitador);
                if (grupo != NULL) {
                    while (grupo != NULL) {
                        // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
                        //printf("Token: %s\n", token);
                        fprintf(fp, "|<f%d> %s\n", contador, grupo);
                        grupo = strtok(NULL, delimitador);
                    }
                }
                //fprintf(fp, "|<f%d> %s\n", contador, file_block->b_content);
                contador++;
                fprintf(fp, "\"shape = \"Mrecord\" color = limegreen];\n");
            }
        }

    }
    //Recursividad
    if (node->i_type == '0') { //CARPETA
        /*Recorrer apuntadores directos*/
        int inicio;
        for (int i = 0; i < 12; i++) {
            if (node->block[i] != -1) {
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                if (i == 0) {
                    inicio = 2;
                } else {
                    inicio = 0;
                }
                for (int j = inicio; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                        CuerpoArbol(super, folder_block->b_content[j].b_inodo, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                    }
                }
            }
        }
        //** Recorrer apntadores indirectos de primer nivel
        if(node->block[12] != -1 ){
            objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(archivo, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, archivo); //Recupero el bloque de Carpeta

            for(int i =0; i<16; i++){
                if(pointer_block->b_pointers[i] != -1){
                    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                    fseek(archivo, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                    fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta

                    for (int j = inicio; j < 4; j++) {
                        if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                            CuerpoArbol(super, folder_block->b_content[j].b_inodo, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                        }
                    }
                }
            }
        }
    }
}
void REP::ApuntadoresArbol(objetos::superBloque super, int noinodo, int pos_inode, FILE *archivo, FILE * fp) {
    //Obtener el inodo
    objetos::inodo *node = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    fseek(archivo, pos_inode, SEEK_SET);
    fread(node, sizeof (objetos::inodo), 1, archivo);
    int contador = 9;
    if (node->i_type == '0') { //CARPETA
        /*Apuntadores directos*/
        int inicio;
        for (int i = 0; i < 12; i++) {
            if (node->block[i] != -1) {
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                fprintf(fp, "inodo%d:f%d->Folder%d:f0;\n", noinodo, contador, node->block[i]);
                int contador2;
                if (i == 0) {
                    inicio = 2;
                    contador2 = 3;
                } else {
                    inicio = 0;
                    contador2 = 1;
                }
                for (int j = inicio; j < 4; j++) { //Apuntadores de bloque de carpeta a inodos
                    if (folder_block->b_content[j].b_inodo != -1) {

                        fprintf(fp, "Folder%d:f%d->inodo%d:f0;\n", node->block[i], contador2, folder_block->b_content[j].b_inodo);
                    }
                    contador2++;
                }
            }
            contador++;
        }
        //** apuntadores indirectos
        if(node->block[12]!= -1){
            //recuperar el bloque
            objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(archivo, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, archivo); //Recupero el bloque de Carpeta
             fprintf(fp, "inodo%d:f%d->Apuntadores%d;\n", noinodo, contador, node->block[12]);

             int cont2=0;
             for(int i=0; i<16; i++){
                 if(pointer_block->b_pointers[i] !=-1){
                     objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                     fseek(archivo, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                     fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta

                     fprintf(fp, "Apuntadores%d:f%d->Folder%d;\n", node->block[12], cont2, pointer_block->b_pointers[i]);
                     cont2++;
                 }
             }
            contador ++;
             for(int i=0;i<16;i++){  //*** apuntar carpetas a inodos
                 if(pointer_block->b_pointers[i] !=-1){
                     objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                     fseek(archivo, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                     fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta

                     int cont_int=0;
                     for(int j=0;j<4;j++){
                         if(folder_block->b_content[j].b_inodo != -1){
                            fprintf(fp, "Folder%d:f%d->inodo%d:f0;\n", pointer_block->b_pointers[i], cont_int, folder_block->b_content[j].b_inodo);
                            cont_int++;
                         }
                     }
                 }
             }
        }
    } else if (node->i_type == '1') { //ARCHIVO
        /*Apuntadores directos*/
        for (int i = 0; i < 12; i++) {
            if (node->block[i] != -1) {
                objetos::bloqueArchivo *file_block = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
                fread(file_block, sizeof (objetos::bloqueArchivo), 1, archivo); //Recupero el bloque de Archivo
                fprintf(fp, "inodo%d:f%d->Archivo%d:f0;\n", noinodo, contador, node->block[i]);
                contador++;
            }
        }
        contador++;
    }
    //RECURSIVIDAD
    if (node->i_type == '0') { //CARPETA
        /*Recorrer apuntadores directos*/
        int inicio;
        for (int i = 0; i < 12; i++) {
            if (node->block[i] != -1) {
               objetos:: bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                if (i == 0) {
                    inicio = 2;
                } else {
                    inicio = 0;
                }
                for (int j = inicio; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                        ApuntadoresArbol(super, folder_block->b_content[j].b_inodo, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                    }
                }
            }
        }
        //** apuntadores indirectos
        if(node->block[12] != -1 ){
            objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(archivo, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, archivo); //Recupero el bloque de Carpeta
            for(int i =0; i<16; i++){
                if(pointer_block->b_pointers[i] != -1){
                    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                    fseek(archivo, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                    fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta

                    for (int j = inicio; j < 4; j++) {
                        if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                            ApuntadoresArbol(super, folder_block->b_content[j].b_inodo, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                        }
                    }
                }
            }
        }
    }
}
void REP::rep_bloques( char path[255],lista::nodoP * particion ){
   //variables para escribir el dot y la ruta donde se generara
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
       printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        double size_patition = 0.0;
        FILE *doc;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            printf("entre al archivo \n");
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
        //buscar la particion donde esta el sistema de archivos
        int num_particion=-1;
        for(int i=0; i<4;i++){
            if(mbr.mbr_partitions[i].part_status!='0'){
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion = i;
                }
            }
        }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion!=-1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
            //crear el reporte
            doc = fopen("/home/archivos/reportesbloques.dot","w");
            //** contenido del reporte
            fprintf(doc, "digraph Reporte{\n");
            fprintf(doc, "rankdir = \"LR\";\n");
            fprintf(doc, "    node[\n");
            fprintf(doc, "        fontname = \"Bitstream Vera Sans\"\n");
            fprintf(doc, "        fontsize = 8\n");
            fprintf(doc, "        style= filled\n");
            fprintf(doc, "        shape = box\n");
            fprintf(doc, "    ]\n");
            CuerpoBloques(super_bloque, super_bloque.s_inode_start, archivo_mbr, doc);
            fprintf(doc, "}\n");
            fclose(doc);
            cout<<"MORI"<<endl;
            strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportesbloques.dot -o");
            strcat(ejecutarDot, " ");
            strcat(ejecutarDot, ruta_reporte);
            system(ejecutarDot);
            strcat(ruta, "xdg-open");
            strcat(ruta, " ");
            strcat(ruta, ruta_reporte);
            system(ruta);
        }else{
            cout<<" **ERROR: no se pudo recuperar la informacion del formato de la particion"<<endl;
            return;
        }
    }
}
void REP::CuerpoBloques(objetos::superBloque super, int pos_inode, FILE *archivo, FILE * fp) {
    //Obtener el inodo
    objetos::inodo *node = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    fseek(archivo, pos_inode, SEEK_SET);
    fread(node, sizeof (objetos::inodo), 1, archivo);
    if (node->i_type == '0') { //CARPETA
        /******************************           Recorrer apuntadores directos         ***************************/
        for (int i = 0; i < 12; i++) {
            int contador = 0;
            if (node->block[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                fprintf(fp, "Folder%d[label=\"<f%d>Bloque Carpeta %d\n", node->block[i], contador, node->block[i]);
                contador++;
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        fprintf(fp, "|<f%d>%s    %d\n", contador, folder_block->b_content[j].b_name, folder_block->b_content[j].b_inodo);
                    }
                }
                fprintf(fp, "\"shape = \"Mrecord\" color=coral style=filled];\n");
            }
        }
        /*****************************       Recorrer apuntador Indirecto Simple        **************************/
        if (node->block[12] != -1) {
            //Obtener el bloque de apuntadores
            objetos::bloqueApuntadores *pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(fp, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, fp);
            fprintf(fp, "Folder%d[label=\"Bloque Apuntadores %d\n", node->block[12], node->block[12]);
            int contador = 0;
            for (int i = 0; i < 16; i++) {
                fprintf(fp, "%d,", pointer_block->b_pointers[i]);
                contador++;
                if (contador == 4) {
                    contador = 0;
                    fprintf(fp, "\\n");
                }
            }
            fprintf(fp, "\"shape = \"Mrecord\" color= peru  style=filled];\n");
            for (int i = 0; i < 16; i++) {
                if (pointer_block->b_pointers[i] != -1) {
                    //Obtener el bloque de carpeta
                    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                    fseek(fp, super.s_block_start + (pointer_block->b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                    fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, fp);
                    fprintf(fp, "Folder%d[label=\"Bloque Carpeta\n", pointer_block->b_pointers[i]);
                    for (int j = 0; j < 4; j++) {
                        if (folder_block->b_content[j].b_inodo != -1) {
                            fprintf(fp, "%s    %d\n", folder_block->b_content[j].b_name, folder_block->b_content[j].b_inodo);
                        }
                    }
                    fprintf(fp, "\"shape = \"Mrecord\" color=firebrick2 style=filled];\n");
                }
            }
        }
    }
    if (node->i_type == '1') { //ARCHIVO
        /*****************************           Recorrer apuntadores directos         **************************/
        for (int i = 0; i < 12; i++) {
            int contador = 0;
            if (node->block[i] != -1) {
                //Obtener el bloque de archivo
                objetos::bloqueArchivo *file_block = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
                fread(file_block, sizeof (objetos::bloqueArchivo), 1, archivo); //Recupero el bloque de Archivo
                fprintf(fp, "Archivo%d[label=\"<f%d>Bloque Archivo %d\n", node->block[i], contador, node->block[i]);
                contador++;
                //ciclo para separar
                char delimitador[] = "\n";
                char *grupo = strtok(file_block->b_content, delimitador);
                if (grupo != NULL) {
                    while (grupo != NULL) {
                        // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
                        fprintf(fp, "|<f%d> %s\n", contador, grupo);
                        grupo = strtok(NULL, delimitador);
                    }
                }
                fprintf(fp, "\"shape = \"Mrecord\" color = limegreen];\n");
            }
        }
        /*****************************       Recorrer apuntador Indirecto Simple        **************************/
        if (node->block[12] != -1) {
            //Obtener el bloque de apuntadores
            objetos::bloqueApuntadores *pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
            fseek(fp, node->block[12], SEEK_SET);
            fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, fp);
            fprintf(fp, "Folder%d[label=\"Bloque Apuntadores\n", node->block[12]);
            int contador = 0;
            for (int i = 0; i < 16; i++) {
                fprintf(fp, "%d,", pointer_block->b_pointers[i]);
                contador++;
                if (contador == 4) {
                    contador = 0;
                    fprintf(fp, "\\n");
                }
            }
            fprintf(fp, "\"shape = \"Mrecord\" color= peru  style=filled];\n");

            for (int i = 0; i < 16; i++) {
                if (pointer_block->b_pointers[i] != -1) {
                    //Obtener el bloque de archivo
                    objetos::bloqueArchivo *file_block = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
                    fseek(archivo, pointer_block->b_pointers[i], SEEK_SET); //Me muevo al bloque de Archivo
                    fread(file_block, sizeof (objetos::bloqueArchivo), 1, archivo); //Recupero el bloque de Archivo
                    fprintf(fp, "Archivo%d[label=\"Bloque Archivo\n", pointer_block->b_pointers[i]);
                    char delimitador[] = "\n";
                    char *grupo = strtok(file_block->b_content, delimitador);
                    if (grupo != NULL) {
                        while (grupo != NULL) {
                            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
                            fprintf(fp, "|<f%d> %s\n", contador, grupo);
                            grupo = strtok(NULL, delimitador);
                        }
                    }
                    fprintf(fp, "\"shape = \"Mrecord\" color = limegreen];\n");
                }
            }
        }
    }
    //Recursividad
    if (node->i_type == '0') { //CARPETA
        /*Recorrer apuntadores directos*/
        int inicio;
        for (int i = 0; i < 12; i++) {
            if (node->block[i] != -1) {
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                if (i == 0) {
                    inicio = 2;
                } else {
                    inicio = 0;
                }
                for (int j = inicio; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                        CuerpoBloques(super, super.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)), archivo, fp);
                    }
                }
            }
        }
    }
    //** apuntadores indirectos
    if(node->block[12]!= -1){
        objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
        fseek(archivo, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
        fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, archivo); //Recupero el bloque de Carpeta
        for(int i =0; i<16; i++){
            if(pointer_block->b_pointers[i]!=-1){
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(archivo, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, archivo); //Recupero el bloque de Carpeta
                 int cont_int=0;
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) { //Que apunta a un inodo
                    }
                }
            }
        }
    }
}
void REP::rep_journal( char path[255],lista::nodoP * particion ){
   //variables para escribir el dot y la ruta donde se generara
    char ejecutarDot[1024];
    char ruta[255];
    for (int i = 0; i < 1024; i++) {
        ejecutarDot[i] = '\0';
    }
    for (int i = 0; i < 255; i++) {
        ruta[i] = '\0';
    }
    // creo el mbr donde guardare los datos del mbr del disco
    MKDISK * nuevo = new MKDISK();
    objetos::MBR mbr = nuevo->crearMBR(0);
    DIR* directorio = opendir(ruta_disco);
    int existe_dir =0;
    if (directorio) {
        existe_dir++;
    }else if (ENOENT == errno) {
       printf("**LAS CARPETAS DEL DISCO NO EXISTEN ** %s \n", path);
    }
    if(existe_dir!=0){
        double size_patition = 0.0;
        FILE *doc;
        FILE *archivo_mbr;
        archivo_mbr = fopen(path, "rb+");
        //leer mbr
        if(archivo_mbr !=NULL){
            printf("entre al archivo \n");
            fseek(archivo_mbr,0,SEEK_SET); //para escribir en el archivo me coloco al inicio.
            fread(&mbr,sizeof(objetos::MBR),1,archivo_mbr); //leo el mbr del disco
        }
        //buscar la particion donde esta el sistema de archivos
        int num_particion=-1;
        for(int i=0; i<4;i++){
            if(mbr.mbr_partitions[i].part_status!='0'){
                //cout<<"particion "<<mbr.mbr_partitions[i].part_name<<endl;
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion = i;
                }
            }
        }
        //si se encontro la particion en el mbr del disco se prosede a ubicarse en el inicio de la particion y se lee el super bloque
        objetos::superBloque super_bloque;
        if(num_particion!=-1){
            fseek(archivo_mbr,mbr.mbr_partitions[num_particion].part_start,SEEK_SET);
            fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_mbr);
        }else{
            cout<<" **ERROR: no se encontro la particion en el disco"<<endl;
            return;
        }
        //comprobando que el superbloque este bien
        if(super_bloque.s_magic == 61267){
            //crear el reporte
            doc = fopen("/home/archivos/reportesreporte_journal.dot","w");
            //** contenido del reporte
            fprintf(doc, "digraph Reporte{\n");
            fprintf(doc, "rankdir = \"LR\";\n");
            fprintf(doc, "    node[\n");
            fprintf(doc, "        fontname = \"Bitstream Vera Sans\"\n");
            fprintf(doc, "        fontsize = 10\n");
            fprintf(doc, "        style= filled\n");
            fprintf(doc, "        shape = box\n");
            fprintf(doc, "        fillcolor=gainsboro\n");
            fprintf(doc, "        color =orange\n");
            fprintf(doc, "    ]\n");
            CuerpoJournaling(mbr.mbr_partitions[num_particion].part_start, super_bloque.s_bm_inode_start, archivo_mbr, doc, mbr.mbr_partitions[num_particion].part_name);
            flechas_journal(mbr.mbr_partitions[num_particion].part_start, super_bloque.s_bm_inode_start, archivo_mbr, doc, mbr.mbr_partitions[num_particion].part_name);
            fprintf(doc, "}\n");
            fclose(doc);
            fclose(archivo_mbr);
            strcpy(ejecutarDot, "dot -Tpdf /home/archivos/reportesreporte_journal.dot -o");
            strcat(ejecutarDot, " ");
            strcat(ejecutarDot, ruta_reporte);
            system(ejecutarDot);
            strcat(ruta, "xdg-open");
            strcat(ruta, " ");
            strcat(ruta, ruta_reporte);
            system(ruta);
        }else{
            cout<<" **ERROR: no se pudo recuperar la informacion del formato de la particion"<<endl;
            return;
        }
    }
}
void REP::CuerpoJournaling(int inicioParticion, int inicioBitmapinodo, FILE *archivo, FILE * fp, char particion[]){
    int posicion = inicioParticion + sizeof (objetos::superBloque);
    for(int i = posicion; i < inicioBitmapinodo; i = i + sizeof (objetos::journal)) {
        objetos::journal *j = (objetos::journal*) malloc(sizeof (objetos::journal));
        fseek(archivo, i, SEEK_SET);
        fread(j, sizeof (objetos::journal), 1, archivo);
        int contador = 0;
        if (j->estado=='1') {
            //DIBUJO DEL inodo
            fprintf(fp, "Journal%d[label=\"<f%d>Journal\n", i, contador);
            contador++;
            fprintf(fp, "|<f%d>OPERACION :     %s\n", contador, j->operacion);
            contador++;
            fprintf(fp, "|<f%d>TIME : %s\n", contador, ctime(&j->hora));
            contador++;
            fprintf(fp, "|<f%d>PROPIETARIO :   %s\n", contador, j->user);
            contador++;
            fprintf(fp, "|<f%d>PARTICION :    %s\n", contador, particion);
            contador++;
            fprintf(fp, "|<f%d>FS :    %d\n", contador, 3);
            contador++;
            fprintf(fp, "\" shape = \"Mrecord\" ];\n");
        } else {
            break;
        }
    }
}
void REP::flechas_journal(int inicioParticion, int inicioBitmapinodo, FILE *archivo, FILE * fp, char particion[]){
    int posicion = inicioParticion + sizeof (objetos::superBloque);
    for(int i = posicion; i < inicioBitmapinodo; i = i + sizeof (objetos::journal)) {
        objetos::journal *j = (objetos::journal*) malloc(sizeof (objetos::journal));
        fseek(archivo, i, SEEK_SET);
        fread(j, sizeof (objetos::journal), 1, archivo);
        objetos::journal *j2 = (objetos::journal*) malloc(sizeof (objetos::journal));
        fseek(archivo, i+ sizeof (objetos::journal), SEEK_SET);
        fread(j2, sizeof (objetos::journal), 1, archivo);
        int contador = 0;
        if (j->estado=='1' && j2->estado=='1') {
            //DIBUJO DEL inodo
            fprintf(fp, "Journal%d -> Journal%d \n", i,i + sizeof (objetos::journal) );

        } else {
            break;
        }
    }
}
void REP::permisos(int num,FILE * doc){
    char permisos[3];
    sprintf(permisos, "%d", num);
    switch (permisos[0]) {
        case '0':// 000
            fprintf(doc, "---");
            break;
        case '1'://001
            fprintf(doc, "--x");
            break;
        case '2'://010
            fprintf(doc, "-w-");
            break;
        case '3'://011
            fprintf(doc, "-wx");
            break;
        case '4'://100
            fprintf(doc, "r--");
            break;
        case '5'://101
            fprintf(doc, "r-x");
            break;
        case '6'://110
            fprintf(doc, "rw-");
            break;
        case '7'://
            fprintf(doc, "rwx");
            break;
    }
    fprintf(doc, " ");
    switch (permisos[1]) {//grupo logueado
        case '0':// 000
            fprintf(doc, "---");
            break;
        case '1'://001
            fprintf(doc, "--x");
            break;
        case '2'://010
            fprintf(doc, "-w-");
            break;
        case '3'://011
            fprintf(doc, "-wx");
            break;
        case '4'://100
            fprintf(doc, "r--");
            break;
        case '5'://101
            fprintf(doc, "r-x");
            break;
        case '6'://110
            fprintf(doc, "rw-");
            break;
        case '7'://
            fprintf(doc, "rwx");
            break;
    }
    fprintf(doc, " ");
    switch (permisos[2]) {//otros
        case '0':// 000
            fprintf(doc, "---");
            break;
        case '1'://001
            fprintf(doc, "--x");
            break;
        case '2'://010
            fprintf(doc, "-w-");
            break;
        case '3'://011
            fprintf(doc, "-wx");
            break;
        case '4'://100
            fprintf(doc, "r--");
            break;
        case '5'://101
            fprintf(doc, "r-x");
            break;
        case '6'://110
            fprintf(doc, "rw-");
            break;
        case '7'://
            fprintf(doc, "rwx");
            break;
    }
}
void REP::obtener_Nuser(objetos::superBloque super_bloque, int n_usuario, FILE * archivo_disco,FILE* doc){
    //OBTENIENDO inodo DEL ARCHIVO USERS
    objetos::inodo *users = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    int posUser = super_bloque.s_inode_start + sizeof (objetos::inodo);
    fseek(archivo_disco, posUser, SEEK_SET);
    fread(users, sizeof (objetos::inodo), 1, archivo_disco);
    //OBTENIENDO TExTO DEL ARCHIVO
    char Texto[14000];
    LOGIN * sis = new LOGIN();
    strcpy(Texto,sis->ObtenerTexto(archivo_disco, super_bloque, users));
    char Text[14000];
    strcpy(Text, strdup(Texto));
    //ANALIZANDO  **********************************************************
    int id = 0;
    char tipo = 'A';
    char nameGroup[11];
    char nameUser[11];
    char password[11];
    char *end_str;
    char *line = strtok_r(Text, "\n", &end_str);
    int cont1=0;
    int cont2=0;
    int contador_usuarios=0;
    while (line != NULL) {
        cont1++;
        char *end_token;
        char *token = strtok_r(line, ",", &end_token);
        while (token != NULL) {
           // cout<<"  llego aqui wile interno  ***";
           // cout<<cont2<<endl;
            cont2++;
            //Limpiando variables
            id = 0;
            tipo = 'A';
            memset(nameGroup, 0, sizeof (nameGroup));
            memset(nameUser, 0, sizeof (nameUser));
            memset(password, 0, sizeof (password));
            //Almacenando datos
            id = atoi(token);
            token = strtok_r(NULL, ",", &end_token);
            tipo = token[0];
            token = strtok_r(NULL, ",", &end_token);
            strcpy(nameGroup, token);
            token = strtok_r(NULL, ",", &end_token);
            if (tipo == 'U') {
                contador_usuarios++;
                strcpy(nameUser, token);
                token = strtok_r(NULL, ",", &end_token);
                strcpy(password, token);
                if(id == n_usuario){
                    fprintf(doc,"%s",nameUser);
                    return;
                }
                token = strtok_r(NULL, ",", &end_token);
            }
       }
   line = strtok_r(NULL, "\n", &end_str);
   }
}
void REP::obtener_Ngrupo(objetos::superBloque super_bloque, int n_grupo, FILE * archivo_disco,FILE* doc){
    //OBTENIENDO inodo DEL ARCHIVO USERS
    objetos::inodo *users = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    int posUser = super_bloque.s_inode_start + sizeof (objetos::inodo);
    fseek(archivo_disco, posUser, SEEK_SET);
    fread(users, sizeof (objetos::inodo), 1, archivo_disco);
    //OBTENIENDO TExTO DEL ARCHIVO
    char Texto[14000];
    LOGIN * sis = new LOGIN();
    strcpy(Texto,sis->ObtenerTexto(archivo_disco, super_bloque, users));
    char Text[14000];
    strcpy(Text, strdup(Texto));
    //ANALIZANDO  **********************************************************
    int id = 0;
    char tipo = 'A';
    char nameGroup[11];
    char *end_str;
    char *line = strtok_r(Text, "\n", &end_str);
    while (line != NULL) {
        char *end_token;
        char *token = strtok_r(line, ",", &end_token);
        while (token != NULL) {
            //Limpiando variables
            id = 0;
            tipo = 'A';
            memset(nameGroup, 0, sizeof (nameGroup));
            //Almacenando datos
            id = atoi(token);
            token = strtok_r(NULL, ",", &end_token);
            tipo = token[0];
            token = strtok_r(NULL, ",", &end_token);
            strcpy(nameGroup, token);
            token = strtok_r(NULL, ",", &end_token);
            if (tipo == 'U') {
                token = strtok_r(NULL, ",", &end_token);
                token = strtok_r(NULL, ",", &end_token);
            } else if (tipo == 'G') {
                if(id == n_grupo){
                    fprintf(doc,"%s",nameGroup);
                    return;
                }
            }
        }
        line = strtok_r(NULL, "\n", &end_str);
    }
}
