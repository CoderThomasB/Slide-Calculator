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

enum Parse_Stuff {
	Digit, Symbol, Number, Operator, Equation, Full,
	Plus, Minus, Times, Divide
};

static const char Digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// if you change the I also suggest doing a search and replas Just in case ;)
static const char plus_str[] = "+\0";
static const char minus_str[] = "−\0";
static const char times_str[] = "×\0";
static const char divide_str[] = "÷\0";

struct Token_Node { 
	const char *Token_start;
	int Token_lenth;
	struct Token_Node *next; 
}; 


int Lexical_Analyzers_Number(const char *To_Parse)
{
	int Token_lenth = 0;
	bool Is = false;
	do {
		Is = false;
		for ( int i = 0; i < 10 ; i++ )
		{
			Is = (To_Parse[Token_lenth] == Digits[i]) || Is;
		}
		if(Is)
		{
			Token_lenth = Token_lenth + 1;
		}
	} while( Is && (To_Parse[Token_lenth] != '\000'));
	
	return Token_lenth;
}
int Lexical_Analyzers_Operator(const char *To_Parse)
{
	int Token_lenth = 0;
	bool Is;
  Is = true;
  while ((To_Parse[Token_lenth] == plus_str[Token_lenth])&&To_Parse[Token_lenth] != '\000' )
    {
      Token_lenth = Token_lenth + 1;
    }
  while ((To_Parse[Token_lenth] == minus_str[Token_lenth])&&To_Parse[Token_lenth] != '\000' )
    {
      Token_lenth = Token_lenth + 1;
    }
  while ((To_Parse[Token_lenth] == times_str[Token_lenth])&&To_Parse[Token_lenth] != '\000' )
    {
      Token_lenth = Token_lenth + 1;
    }
  while ((To_Parse[Token_lenth] == divide_str[Token_lenth])&&To_Parse[Token_lenth] != '\000' )
    {
      Token_lenth = Token_lenth + 1;
    }

	return Token_lenth;
}
struct Token_Node* Lexical_Analyzers(const char *To_Parse){
	int change = 0;
	struct Token_Node *Head = NULL;
	struct Token_Node *Now = NULL;

	Head = malloc (sizeof (struct Token_Node));
	(Head -> next) = NULL;
	(Head -> Token_start) = 0;
	(Head -> Token_lenth) = 0;

	Now = Head;
	// UNFINISHED
	do {
		printf("To_Parse:%s\n", To_Parse);
		printf("%p\n", Now);
		if((Now -> Token_start) != 0){
			(Now -> next) = malloc (sizeof (struct Token_Node));
			Now = (Now -> next);
			(Now -> next) = NULL;
			(Now -> Token_start) = 0;
			(Now -> Token_lenth) = 0;
		}
		//Now.next = malloc (sizeof (struct Token_Node))
		change = 0;
		change = change + Lexical_Analyzers_Number(To_Parse);
		if(change == 0){
			change = change + Lexical_Analyzers_Operator(To_Parse);
		}
		(Now -> Token_lenth) = change;
		(Now -> Token_start) = To_Parse;

		printf("%s\n", (Now -> Token_start));

		if(change != 0){
			To_Parse = To_Parse + change;
		}

	} while (change != 0);

	printf("%p\n", Head);
	return Head;
}





bool Parse(enum Parse_Stuff To_Parse, const char *The_char)
{
	bool Is = false;
	int i = 0;
	switch (To_Parse)
		{
			
			case Number:
				
				Is = (Lexical_Analyzers_Number(The_char) >= 1);
				
			break;
			
			case Operator:
				
				if (Parse (Symbol, The_char))
				{
					if(Parse (Number, The_char))
					{
						Is = true;
					}
				}
				
			break;
			
			case Digit:
				for ( int i = 0; i < 10 ; i++ )
				{
					Is = (The_char[0] == Digits[i]) || Is;
				}
			break;
			
			case Symbol:
				
				Is = Parse (Plus, The_char) || Is;
				if(Is == false){Is = Parse (Minus, The_char);}
				if(Is == false){Is = Parse (Times, The_char);}
				if(Is == false){Is = Parse (Divide, The_char);}
				
			break;
			
			case Plus:
				printf("%s\n","Plus");
				for ( int i = 0; i < strlen(plus_str) ; i++ )
				{
					Is = (The_char[i] == plus_str[i]);
					
				}
				if(Is){printf("Symbol Lenth:%lu\n", strlen(times_str));}
			break;
			
			case Minus:
				printf("%s\n","Minus");
				for ( int i = 0; i < strlen(minus_str) ; i++ )
				{
					Is = (The_char[i] == minus_str[i]);
					
				}
				if(Is){printf("Symbol Lenth:%lu\n", strlen(times_str));}
			break;
			
			case Times:
				printf("%s\n","Times");
				for ( int i = 0; i < strlen(times_str) ; i++ )
				{
					Is = (The_char[i] == times_str[i]);
					
				}
				if(Is){printf("Symbol Lenth:%lu\n", strlen(times_str));}
			break;
			
			case Divide:
				printf("%s\n","Divide");
				for ( int i = 0; i < strlen(divide_str) ; i++ )
				{
					Is = (The_char[i] == divide_str[i]);
					
				}
				if(Is){printf("Symbol Lenth:%lu\n", strlen(times_str));}
			break;


		}
	return Is;
}


char *python_command = "python3\0";

//const int Max_Size = 100; "error: variable-sized object may not be initialized"


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
	//	reads the charters of the Screen
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

const char * Calculate_Resolt(){
	const char *Screen_Text = gtk_entry_get_text(GTK_ENTRY(Screen));
	
	struct Token_Node *Head = Lexical_Analyzers (Screen_Text);
	struct Token_Node *Now = Head;
	
	printf("%p\n", Head);
	printf("%p\n", Now);
	//printf("%i\n", (Head -> Token_lenth));
	//printf("%i\n", (Now -> Token_lenth));

	while ((Now -> next) != 0)
	{
		for (int x = 0; x < (Now -> Token_lenth); x++)
		printf("%c", *((Now -> Token_start)+x));

		printf("\n");
		Now = (Now -> next);
	}

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
