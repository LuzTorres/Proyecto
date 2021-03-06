#include<conio.h> // para el uso de getch
#include <iostream>
using namespace std; // lectura cout
struct dato {
	int i;
	dato *s;
}
*a, *i, *p, *e;
int da;
int buscar(int d);
void insertar(int dat); 
void mostrar(void);
void borrar(void);
void menu(void);
void guardar(void);
void cargar(void);
main() {
	menu();
}
void menu(void) {
	int opc,da;
			cout<<"\n\t***Programa para almacenar datos y guardar en archivo***\n";
	
   time_t now = time(0);  
   char* dt = ctime(&now);
   cout << "\nLa fecha y hora local es:\t" << dt << endl;
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   
   	  do { //mostrar opciones
	    cout<<"\nQue desea hacer?:";
		cout<<"\n\t1 - Buscar datos";
		cout<<"\n\t2 - Insertar datos";
		cout<<"\n\t3 - Mostrar todos los datos";
		cout<<"\n\t4 - Borrar un dato";
		cout<<"\n\t5 - Guardar datos a Archivo";
		cout<<"\n\t6 - Cargar datos de Archivo";
		cout<<"\n\t0 - Finalizar";
		cout<<"\n\nSeleccione opcion: ";
		cin>>opc;
		switch(opc) {  //para los casos
		
			case 0: cout<<"\n\nFinaliza el programa";
			getch();// borrar
			p=i;
			while(p) {
				a=p;
				p=p->s;
				delete(a);
			}
			exit(0); // casos para los opciones
			case 1: cout<<"\n\nIngrese dato a buscar: ";
			cin>>da;
			if(buscar(da))
			 cout<<"\n\nDato existe"; else
			 cout<<"\n\nDato NO EXISTE";
			getch();
			break;
			case 2: cout<<"Ingrese dato: ";
			cin>>da;
			insertar(da);
			break;
			case 3: mostrar();
			break;
			case 4: borrar();
			break;
			case 5: guardar();
			break;
			case 6: cargar();
			break;
			default: cout<<"\n\tOPCION NO VALIDA!!!"; // si no es ninguna de las opcciones
			getch();
		}
	}
	while(opc);
	system("pause");
    }
void mostrar(void) { // muestra dato
	int cont=1;
	if(!i) {
		cout<<"\n\tNO HAY LISTA PARA MOSTRAR";
		getch();
		return;
	}
	p=i;
	cout<<endl<<endl;
	while(p) {
		cout<<cont++<<" - Valor = "<<p->i<<endl;
		p=p->s;
	}
	cout<<"\n\tEso es todo";
	getch();
}
int buscar(int d) { // buscar dato si es que existe y si es que se repete
	if (!i) {
		cout<<"No hay datos en la lista!!!\n";
		getch();
		return(0);
	}
	p=i;
	a=NULL;
	while(p->s && p->i<d) {
		a=p;
		p=p->s;
	}
	return(p->i==d?1:0);
}
void insertar(int dat) { //inserta
	if(!i) {
		i=new(dato);
		i->s=NULL;
		i->i=dat;
		return;
	}
	if(buscar(dat)) { // si hay algo igual
		cout<<"\n\nDato existente";
		getch();
		return;
	}
	e=new(dato);
	e->i=dat;
	if(p==i && p->s) {
		e->s=p;
		i=e;
		return;
	}
	if(p==i && !p->s) {
		if(p->i < e->i) {
			p->s=e;
			e->s=NULL;
		} else {
			e->s=p;
			i=e;
		}
		return;
	}
	if(p->s) {
		a->s=e;
		e->s=p;
		return;
	}
	if(e->i > p->i) {
		e->s=NULL;
		p->s=e;
	} else {
		a->s=e;
		e->s=p;
	}
}
void borrar(void) { // borrar
	cout<<"\n\nIngrese dato a eliminar: ";
	cin>>da;
	if(buscar(da)) {
		if(a)
		 a->s=p->s; else
		 i=p->s;
		delete(p);
		cout<<"\n\nDato eliminado";
	} else
	 cout<<"\n\nDato no se encuentra";
	getch();
}
void guardar(void) { //guardar dato
	FILE *arch;
	arch=fopen("DATOS.TXT","w");
	if(!i) {
		cout<<"\n\nNO HAY LISTA PARA GUARDAR";
		getch();
		return;
	}
	p=i;
	while(p) {
		fprintf(arch,"%i\n",p->i);
		p=p->s;
	}
	cout<<"\n\nArchivo Guardado";
	fclose(arch);
	getch();
}
void cargar(void) { // para la parte del archivo
	int c,x;
	FILE *arch;
	arch=fopen("DATOS.TXT","r");
	if(!arch) {
		cout<<"\nNO EXISTE EL ARCHIVO";
		getch();
		return;
	}
	do {
		c=fscanf(arch,"%i\n",&x);
		if(c!=EOF) {
			insertar(x);
		}
	}
	while (c!=EOF);
	cout<<"\nArchivo Cargado";
	fclose(arch);
	getch();
}
