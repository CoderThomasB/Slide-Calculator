#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h> 

GtkWidget	*Main_Window;
GtkWidget	*Main_Top;
GtkWidget	*Screen;
GtkWidget	*Answer;
GtkWidget	*Buttons;
GtkWidget	*Top;

GtkWidget	*Label_Equals;

GtkWidget	*Button_0;
GtkWidget	*Button_1;
GtkWidget	*Button_2;
GtkWidget	*Button_3;
GtkWidget	*Button_4;
GtkWidget	*Button_5;
GtkWidget	*Button_6;
GtkWidget	*Button_7;
GtkWidget	*Button_8;
GtkWidget	*Button_9;
GtkWidget	*Button_divide;
GtkWidget	*Button_time;
GtkWidget	*Button_equals;
GtkWidget	*Button_minus;
GtkWidget	*Button_plus;

GtkBuilder	*Builder;


enum Token_types {
	Number, Plus, Minus, Times, Divide
};

static const char Digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// if you change the I also suggest doing a search and replas Just in case ;)
static const char plus_str[] = "+\0";
static const char minus_str[] = "−\0";
static const char times_str[] = "×\0";
static const char divide_str[] = "÷\0";

struct Token_Node { 
	char *Token_start;
	enum Token_types Token_type;
	struct Token_Node *next;
};

struct Token_Return {
	enum Token_types Token_type;
	int Token_lenth;
}; 

const char* Get_Name_Of_Token_type(enum Token_types Token_type);
int Canclate_Reolt_From_Token(struct Token_Node Number1,struct Token_Node Number2,struct Token_Node The_Operator);
const char* Get_Name_Of_Token_type(enum Token_types Token_type);

struct Token_Return Lexical_Analyzers_Number(const char *To_Parse)
{
	struct Token_Return T_Return;
	T_Return.Token_lenth = 0;
	bool Is = false;
	do {
		Is = false;
		for ( int i = 0; i < 10 ; i++ )
		{
			Is = (To_Parse[T_Return.Token_lenth] == Digits[i]) || Is;
		}
		if(Is)
		{
			T_Return.Token_lenth = T_Return.Token_lenth + 1;
		}
	} while( Is && (To_Parse[T_Return.Token_lenth] != '\000'));
	
	return T_Return;
}

struct Token_Return Lexical_Analyzers_Operator(const char *To_Parse)
{
	struct Token_Return T_Return;
	T_Return.Token_lenth = 0;
	bool Is;
	Is = true;
	while ((To_Parse[T_Return.Token_lenth] == plus_str[T_Return.Token_lenth])&&To_Parse[T_Return.Token_lenth] != '\000' )
	{
		T_Return.Token_lenth = T_Return.Token_lenth + 1;
		T_Return.Token_type = Plus;
	}
	while ((To_Parse[T_Return.Token_lenth] == minus_str[T_Return.Token_lenth])&&To_Parse[T_Return.Token_lenth] != '\000' )
	{
		T_Return.Token_lenth = T_Return.Token_lenth + 1;
		T_Return.Token_type = Minus;
	}
	while ((To_Parse[T_Return.Token_lenth] == times_str[T_Return.Token_lenth])&&To_Parse[T_Return.Token_lenth] != '\000' )
	{
		T_Return.Token_lenth = T_Return.Token_lenth + 1;
		T_Return.Token_type = Times;
	}
	while ((To_Parse[T_Return.Token_lenth] == divide_str[T_Return.Token_lenth])&&To_Parse[T_Return.Token_lenth] != '\000' )
	{
		T_Return.Token_lenth = T_Return.Token_lenth + 1;
		T_Return.Token_type = Divide;
	}

	return T_Return;
}

int Canclate_Reolt_From_Token(struct Token_Node Number1,struct Token_Node Number2,struct Token_Node The_Operator){

	// NOT FINISHED
	if(Number1.Token_type != Number){
		printf("Number1 not Number\n");
		printf("Number1 is a %s\n", Get_Name_Of_Token_type (Number1.Token_type));
		return -1;
	}
	if(Number2.Token_type != Number){
		printf("Number2 not Number\n");
		printf("Number2 is a %s\n", Get_Name_Of_Token_type (Number2.Token_type));
		return -1;
	}
	if(The_Operator.Token_type == Number){
		printf("The_Operator is Number\n");
		printf("The_Operator is a %s\n", Get_Name_Of_Token_type (The_Operator.Token_type));
		return -1;
	}


	printf("Number1.Token_start: %s\n", Number1.Token_start);
	printf("Number2.Token_start: %s\n", Number2.Token_start);


	int int_Number1 = atoi(Number1.Token_start);


	int int_Number2 = atoi(Number2.Token_start);

	printf("Number1: %i\n", int_Number1);
	printf("Number2: %i\n", int_Number2);

	switch (The_Operator.Token_type)
		{
		case Number:
			printf("The_Operator is not Number\n");
			return -1;
			break;
		case Times:
			return int_Number1 * int_Number2;
			break;
		case Divide:
			return int_Number1 / int_Number2;
			break;
		case Plus:
			return int_Number1 + int_Number2;
			break;
		case Minus:
			return int_Number1 - int_Number2;
			break;

	}
}

struct Token_Node* Set_Token_Node_To_Zero(struct Token_Node *The_Token_Node){
	(The_Token_Node -> next) = NULL;
	(The_Token_Node -> Token_start) = 0;
}


struct Token_Node* Lexical_Analyzers(const char *To_Parse){
	//(char *) malloc(Output_Size * sizeof(char));

	int change = 0;
	struct Token_Node *Head = NULL;
	struct Token_Node *Now = NULL;
	enum Token_types Type;
	struct Token_Return _;

	Head = malloc (sizeof (struct Token_Node));
	Set_Token_Node_To_Zero(Head);

	Now = Head;


	// UNFINISHED
	do {
		if((Now -> Token_start) != 0){
			(Now -> next) = malloc (sizeof (struct Token_Node));
			Now = (Now -> next);
			Set_Token_Node_To_Zero(Now);
		}
		//Now.next = malloc (sizeof (struct Token_Node))
		change = 0;
		_ = Lexical_Analyzers_Number(To_Parse);
		change = change + _.Token_lenth;
		Type = _.Token_type;
		Type = Number;
		if(change == 0){
			_ = Lexical_Analyzers_Operator(To_Parse);
			change = change + _.Token_lenth;
			Type = _.Token_type;
		}


		(Now -> Token_start) = malloc (sizeof (char) * (change + 1));
		memset((Now -> Token_start), '\000', change + 1);
		strncpy((Now -> Token_start), To_Parse, change);

		(Now -> Token_type) = Type;

		if(change != 0){
			To_Parse = To_Parse + change;
		}

	} while (change != 0);

	return Head;
}





int Parse(struct Token_Node * Token_Start)
{
	struct Token_Node *Token_Now = Token_Start; // this is away one behind because we need to know the first nubber



	while (((Token_Now -> next) -> next) != NULL)
	{
		int Reolt = Canclate_Reolt_From_Token(*Token_Now, *((Token_Now -> next) -> next), *(Token_Now -> next));
		if(Reolt != -1){
			printf("%i\n", Reolt);
		}
	}



}


int main (int argc, char **argv){
	
	
	// We are just geting started!
	gtk_init(&argc, &argv);

	// read the glade file
	Builder = gtk_builder_new_from_file("glade/Main.glade");
	
	// some More Init stuff. You know
	Main_Window = GTK_WIDGET(gtk_builder_get_object(Builder, "Main Window"));
	Main_Top = GTK_WIDGET(gtk_builder_get_object(Builder, "Main Top"));
	Screen = GTK_WIDGET(gtk_builder_get_object(Builder, "Screen"));
	Answer = GTK_WIDGET(gtk_builder_get_object(Builder, "Answer"));
	Buttons = GTK_WIDGET(gtk_builder_get_object(Builder, "Buttons"));
	Label_Equals = GTK_WIDGET(gtk_builder_get_object(Builder, "Label Equals"));
	Top = GTK_WIDGET(gtk_builder_get_object(Builder, "Top"));

	//                                   ||
	// is thare a beter way to do this ? \/
	//
	Button_0 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 0"));
	Button_1 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 1"));
	Button_2 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 2"));
	Button_3 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 3"));
	Button_4 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 4"));
	Button_5 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 5"));
	Button_6 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 6"));
	Button_7 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 7"));
	Button_8 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 8"));
	Button_9 = GTK_WIDGET(gtk_builder_get_object(Builder, "Button 9"));
	Button_divide = GTK_WIDGET(gtk_builder_get_object(Builder, "Button ÷"));
	Button_time = GTK_WIDGET(gtk_builder_get_object(Builder, "Button ×"));
	Button_equals = GTK_WIDGET(gtk_builder_get_object(Builder, "Button ="));
	Button_minus = GTK_WIDGET(gtk_builder_get_object(Builder, "Button −"));
	Button_plus = GTK_WIDGET(gtk_builder_get_object(Builder, "Button +"));

	// connects the signals
	gtk_builder_connect_signals(Builder, NULL);
	// I Don't know what this is ???
	g_object_unref(Builder);

	// We need to See what bug We have crated!
	gtk_widget_show(Main_Window);

	// A BIG LOOOOOOOOP ???
	gtk_main();

	return 0;
}

// Exits if the window is closed or DESTROYED!
// DESTROYED is better that closed in english
void on_window_main_destroy()
{
	gtk_main_quit();
}


void add_text_to_Screen(const gchar *input)
{
	// reads the charters of the Screen
	const char *Screen_Text = gtk_entry_get_text(GTK_ENTRY(Screen));
	
	// Gets the lenth of the exseted output
	int Output_Size = strlen(gtk_entry_get_text(GTK_ENTRY(Screen))) + strlen(input) + 1;


	// Crats a Bufer
	 
	// this code is not dynamic
	// char text[100] = "";
	char *text = (char *) malloc(Output_Size * sizeof(char));

	// a test for success!
	if (text == NULL) {
		printf("Memory not allocated.\n");
		return;
	}
	
	memset(text, 0, Output_Size);
	
	// appends the Screen_Text
	strcat(text, Screen_Text);

	// appends the input
	strcat(text, input);

	printf("OutPut:%s\n", text);

	// writs the Buffer / output to the screen
	gtk_entry_set_text(GTK_ENTRY(Screen), text);
	
	// frees the memory cativerty in our programe
	free(text);

	// We Are Done !!!!
	return;
}
const char* Get_Name_Of_Token_type(enum Token_types Token_type){
	switch (Token_type)
		{
		case Plus: return "Plus";
		case Minus: return "Minus";
		case Times: return "Times";
		case Divide: return "Divide";
		case Number: return "Number";
		default: return "";
		}
}

const char * Calculate_Resolt(){
	const char *Screen_Text = gtk_entry_get_text(GTK_ENTRY(Screen));

	struct Token_Node *Head = Lexical_Analyzers (Screen_Text);
	struct Token_Node *Now = Head;


	/*int i = 1;
	while ((Now -> next) != 0)
	{
		printf("Token %i %s :", i, Get_Name_Of_Token_type(Now -> Token_type));
		for (int x = 0; x < (Now -> Token_lenth); x++)
		printf("%c", *((Now -> Token_start)+x));

		printf("\n");
		Now = (Now -> next);
		i++;
	}*/

	Parse(Head);

	//system("python3 -c \"print(1+1)\"");
	//execlp(python_command, python_command, "-c", "print('hi')", NULL);

	return Screen_Text;
}



void show_Answer(const gchar *The_Answer){
	gtk_widget_show_all(Top);
	gtk_label_set_text(GTK_LABEL(Answer), The_Answer);
}

//                                   ||
// is thare a beter way to do this ? \/
void on_Button_equals_clicked()
{
	const char *Resolt = Calculate_Resolt();
	show_Answer(Resolt);
}

void on_Button_divide_clicked()
{
	add_text_to_Screen("÷");
}

void on_Button_time_clicked()
{
	add_text_to_Screen("×");
}

void on_Button_minus_clicked()
{
	add_text_to_Screen("−");
}

void on_Button_plus_clicked()
{
	add_text_to_Screen("+");
}


void on_Button_0_clicked()
{
	add_text_to_Screen("0");
}

void on_Button_1_clicked()
{
	add_text_to_Screen("1");
}

void on_Button_2_clicked()
{
	add_text_to_Screen("2");
}

void on_Button_3_clicked()
{
	add_text_to_Screen("3");
}

void on_Button_4_clicked()
{
	add_text_to_Screen("4");
}

void on_Button_5_clicked()
{
	add_text_to_Screen("5");
}

void on_Button_6_clicked()
{
	add_text_to_Screen("6");
}

void on_Button_7_clicked()
{
	// Can You See ME!
	add_text_to_Screen("7");
}

void on_Button_8_clicked()
{
	add_text_to_Screen("8");
}

void on_Button_9_clicked()
{
	add_text_to_Screen("9");
}
