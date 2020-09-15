/*  COPYRIGT Thomas booker 2020
 *  All Rigtes rezered
 */
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h> 
#include <math.h>

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
GtkWidget	*Button_Back;
GtkWidget	*Button_CE;
GtkWidget	*Button_Dot;


GtkBuilder	*Builder;


enum Token_types {
	Number, Plus, Minus, Times, Divide, Mod, Error
};
enum sucses_types {
	maths_sucses, maths_invalid, maths_Error
};

int Digits_Loop = 11;
static const char Digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

// if you change the I also suggest doing a search and replas Just in case ;)
static const char plus_str[] = "+\0";
static const char minus_str[] = "−\0";
static const char times_str[] = "×\0";
static const char divide_str[] = "÷\0";
static const char mod_str[] = "%\0";

struct To_return {
	float number;
	enum sucses_types sucses;
};

struct Token_Node {
  // null termernatedm string
	char *Token_start;
	enum Token_types Token_type;
	struct Token_Node *next;
};

struct Token_atrbutes {
  int Token_lenth;
  enum Token_types Token_type;
};

struct Token_Return {
	enum Token_types Token_type;
	int Token_lenth;
}; 

const char* Get_Name_Of_Token_type(enum Token_types Token_type);
struct To_return Canclate_Reolt_From_Token(struct Token_Node Number1,struct Token_Node Number2,struct Token_Node The_Operator);
const char* Get_Name_Of_Token_type(enum Token_types Token_type);

struct Token_atrbutes Lexical_Analyzers_Number(const char *To_Parse){
	struct Token_atrbutes atrbutes;
	atrbutes.Token_lenth = 0;
	atrbutes.Token_type = Number;
	bool Is = false;
	do {
		Is = false;
		for ( int i = 0; i < Digits_Loop; i++ )
		{
			Is = (To_Parse[atrbutes.Token_lenth] == Digits[i]) || Is;
		}
		if(Is)
		{
			atrbutes.Token_lenth = atrbutes.Token_lenth + 1;
		}
	} while( Is && (To_Parse[atrbutes.Token_lenth] != '\000'));

	return atrbutes;
}

struct Token_atrbutes Lexical_Analyzers_Operator(const char *To_Parse)
{
	struct Token_atrbutes atrbutes;
	atrbutes.Token_lenth = 0;
	bool Is;
	Is = true;
	while ((To_Parse[atrbutes.Token_lenth] == plus_str[atrbutes.Token_lenth])&&To_Parse[atrbutes.Token_lenth] != '\000' )
	{
		atrbutes.Token_lenth = atrbutes.Token_lenth + 1;
		atrbutes.Token_type = Plus;
	}
	while ((To_Parse[atrbutes.Token_lenth] == minus_str[atrbutes.Token_lenth])&&To_Parse[atrbutes.Token_lenth] != '\000' )
	{
		atrbutes.Token_lenth = atrbutes.Token_lenth + 1;
		atrbutes.Token_type = Minus;
	}
	while ((To_Parse[atrbutes.Token_lenth] == times_str[atrbutes.Token_lenth])&&To_Parse[atrbutes.Token_lenth] != '\000' )
	{
		atrbutes.Token_lenth = atrbutes.Token_lenth + 1;
		atrbutes.Token_type = Times;
	}
	while ((To_Parse[atrbutes.Token_lenth] == divide_str[atrbutes.Token_lenth])&&To_Parse[atrbutes.Token_lenth] != '\000' )
	{
		atrbutes.Token_lenth = atrbutes.Token_lenth + 1;
		atrbutes.Token_type = Divide;
	}
	while ((To_Parse[atrbutes.Token_lenth] == mod_str[atrbutes.Token_lenth])&&To_Parse[atrbutes.Token_lenth] != '\000' )
	{
		atrbutes.Token_lenth = atrbutes.Token_lenth + 1;
		atrbutes.Token_type = Mod;
	}

	return atrbutes;
}

struct To_return Canclate_Reolt_From_Token(struct Token_Node Number1,struct Token_Node Number2,struct Token_Node The_Operator){
	struct To_return the_return;

	// NOT FINISHED
	if(Number1.Token_type != Number){
		//printf("Number1 not Number\n");
		//printf("Number1 is a %s\n", Get_Name_Of_Token_type (Number1.Token_type));
		the_return.sucses = maths_invalid;
		return the_return;
	}
	if(Number2.Token_type != Number){
		//printf("Number2 not Number\n");
		//printf("Number2 is a %s\n", Get_Name_Of_Token_type (Number2.Token_type));
		the_return.sucses = maths_invalid;
		return the_return;
	}
	if(The_Operator.Token_type == Number){
		//printf("The_Operator is Number\n");
		//printf("The_Operator is a %s\n", Get_Name_Of_Token_type (The_Operator.Token_type));
		the_return.sucses = maths_invalid;
		return the_return;
	}


	//printf("Number1.Token_start: %s\n", Number1.Token_start);
	//printf("Number2.Token_start: %s\n", Number2.Token_start);


	float int_Number1 = atof(Number1.Token_start);


	float int_Number2 = atof(Number2.Token_start);

	//printf("Number1: %i\n", int_Number1);
	//printf("Number2: %i\n", int_Number2);

	switch (The_Operator.Token_type)
		{
		case Number:
			//printf("The_Operator is not Number\n");
			the_return.sucses = maths_invalid;
			return the_return;
			break;
		case Times:
			the_return.sucses = maths_sucses;
			the_return.number = int_Number1 * int_Number2;
			return the_return;
			break;
		case Divide:
			if(int_Number2 == 0){
				the_return.sucses = maths_Error;
				return the_return;
			}
			the_return.sucses = maths_sucses;
			the_return.number = int_Number1 / int_Number2;
			return the_return;
			break;
		case Plus:
			the_return.sucses = maths_sucses;
			the_return.number = int_Number1 + int_Number2;
			return the_return;
			break;
		case Minus:
			the_return.sucses = maths_sucses;
			the_return.number = int_Number1 - int_Number2;
			return the_return;
			break;
		case Mod:
			the_return.sucses = maths_sucses;
			the_return.number = ((int)int_Number1) % ((int)int_Number2);
			return the_return;
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
  struct Token_atrbutes atrbutes;
  atrbutes.Token_lenth = 0;
  atrbutes.Token_type = Number;
	enum Token_types Type;
	struct Token_Return _;

	Head = malloc (sizeof (struct Token_Node));
	Set_Token_Node_To_Zero(Head);

	Now = Head;


	// UNFINISHED
	do {
		if((Now -> Token_start) != NULL){
			(Now -> next) = malloc (sizeof (struct Token_Node));
			Now = (Now -> next);
			Set_Token_Node_To_Zero(Now);
		}
		//Now.next = malloc (sizeof (struct Token_Node))
		change = 0;
		atrbutes = Lexical_Analyzers_Number(To_Parse);
		change = change + atrbutes.Token_lenth;
		Type = atrbutes.Token_type;
		if(change == 0){
			atrbutes = Lexical_Analyzers_Operator(To_Parse);
			change = change + atrbutes.Token_lenth;
			Type = atrbutes.Token_type;
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





struct Token_Node *Parse(struct Token_Node * Token_Start)
{
	struct Token_Node *Token_Now = Token_Start; // this is away one behind because we need to know the first nubber



	while (((Token_Now -> next)) != NULL)
	{
		if(((Token_Now -> next) -> next) == NULL){
			Token_Now = Token_Now -> next;
			continue;
		}
		struct To_return Reolt = Canclate_Reolt_From_Token(*Token_Now, *((Token_Now -> next) -> next), *(Token_Now -> next));
		if(Reolt.sucses == maths_sucses){
			//printf("%f\n", Reolt.number);
			struct Token_Node *_ = ((Token_Now -> next) -> next) -> next;
			//printf("((Token_Now -> next) -> next) -> Token_start\n");
			free(((Token_Now -> next) -> next) -> Token_start);
			//printf("((Token_Now -> next) -> next)\n");
			free(((Token_Now -> next) -> next));
			//printf("(Token_Now -> next) -> Token_start\n");
			free((Token_Now -> next) -> Token_start);
			//printf("(Token_Now -> next)\n");
			free((Token_Now -> next));
			//printf("Token_Now -> Token_start\n");
			free(Token_Now -> Token_start);
			//printf("Done\n");

			(Token_Now -> next) = _;
			(Token_Now -> Token_type) = Number;
			(Token_Now -> Token_start) = malloc(sizeof (char) * 1000);
			//printf("Done2\n");


			sprintf((Token_Now -> Token_start), "%.3f", Reolt.number);
			//itoa(Reolt, (Token_Now -> Token_start), 10);
		}else if(Reolt.sucses == maths_invalid){
			Token_Now = Token_Now -> next;
		}else if(Reolt.sucses == maths_Error){
			free(Token_Now -> Token_start);
			(Token_Now -> Token_start) = malloc (sizeof(char)*5);
			(Token_Now -> Token_start) = "Error";
			(Token_Now -> Token_type) = Error;

			Token_Now = Token_Now -> next;
		}
	}

	Token_Now = Token_Start;
	while ((Token_Now -> next) != NULL)
	{
		//printf("%s\n", Token_Now -> Token_start);
		Token_Now = Token_Now -> next;
	}
  return Token_Start;
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
	Button_Back = GTK_WIDGET(gtk_builder_get_object(Builder, "Button Back"));
	Button_CE = GTK_WIDGET(gtk_builder_get_object(Builder, "Button CE"));
	Button_Dot = GTK_WIDGET(gtk_builder_get_object(Builder, "Button ."));

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

void button_pressed(){
	gtk_entry_grab_focus_without_selecting(GTK_ENTRY(Screen));
}

void add_text_to_Screen(const gchar *input)
{
	int i = gtk_editable_get_position( GTK_EDITABLE(Screen) );
	gtk_editable_insert_text(GTK_EDITABLE(Screen), input, sizeof (input), &i);
	gtk_editable_set_position(GTK_EDITABLE(Screen), i);

	/*int position = gtk_editable_get_position( GTK_EDITABLE(Screen) );
	//printf("position: %i\n", position);
	gtk_editable_set_position(GTK_EDITABLE(Screen), position+1);
	// reads the charters of the Screen
	const char *Screen_Text = gtk_entry_get_text(GTK_ENTRY(Screen));
	
	// Gets the lenth of the exseted output
	int Output_Size = strlen(gtk_entry_get_text(GTK_ENTRY(Screen))) + strlen(input) + 10;


	// Crats a Bufer
	 
	// this code is not dynamic
	// char text[100] = "";
	char *text = (char *) malloc(Output_Size * sizeof(char));

	// a test for success!
	if (text == NULL) {
		//printf("Memory not allocated.\n");
		return;
	}
	
	// set it to zero
	memset(text, 0, Output_Size);
	
	// appends the pre edter Screen_Text
	strncat(text, Screen_Text, position);

	// appends the input
	strcat(text, input);

	// adds the afder editer Screen_Text
	strcat(text, Screen_Text + position + sizeof (input));

	//printf("OutPut:%s\n", text);

	gtk_editable_set_position(GTK_EDITABLE(Screen), position+2);

	// writs the Buffer / output to the screen
	gtk_entry_set_text(GTK_ENTRY(Screen), text);
	
	// frees the memory cativerty in our programe
	free(text);

	// We Are Done !!!!
	return;*/
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

char * Calculate_Resolt(){
	const char *Screen_Text = gtk_entry_get_text(GTK_ENTRY(Screen));

	struct Token_Node *Head = Lexical_Analyzers (Screen_Text);
	struct Token_Node *Now = Head;

	struct Token_Node *Output = Parse(Head);

	return (Output->Token_start);
}

void show_Answer(char *The_Answer){
	gtk_widget_show_all(Top);
	gtk_label_set_text(GTK_LABEL(Answer), The_Answer);
}


//                                   ||
// is thare a beter way to do this ? \/
void on_Button_equals_clicked();
void on_Screen_changed(){
	const char *Screen_Text = gtk_entry_get_text(GTK_ENTRY(Screen));
	int lenth = strlen(Screen_Text);
	//printf("lenth:%i\n", lenth);
	char *output = malloc (sizeof (char) * (lenth + 100)); // +100 for some more spase
	bool maches = false;
	int output_i = 0;
	int Screen_Text_i = 0;
	struct Token_atrbutes _;
	bool will_clear = false;
	bool will_show_ans = false;


	while (Screen_Text_i <= lenth)
	{
		//printf("Screen_Text_i:%i\n", Screen_Text_i);
		maches = false;
		if(strncmp(Screen_Text + Screen_Text_i, "=", sizeof ("=") -1 ) == 0){
			//printf("plus not\n");
			strcpy(output + output_i, plus_str);
			output_i += sizeof(plus_str) - 1;
			Screen_Text_i += sizeof ("*") - 1;
      //printf("size of:%i\n", sizeof ("*") - 1);
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, " ", sizeof (" ") -1 ) == 0){
			//printf("space\n");
			output_i += 0;
			Screen_Text_i += 1;
			maches = true;
		}
    if(strncmp(Screen_Text + Screen_Text_i, "a", sizeof ("a") -1 ) == 0){
			//printf("space\n");
			output_i += 0;
			Screen_Text_i += 1;
			will_show_ans = true;
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, "c", sizeof ("c") -1 ) == 0){
			//printf("space\n");
			output_i += 0;
			Screen_Text_i += 1;
			will_clear = true;
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, "*", sizeof ("*") -1 ) == 0){
			//printf("times\n");
			strcpy(output + output_i, times_str);
			output_i += sizeof(times_str) - 1;
			Screen_Text_i += sizeof ("*") - 1;
      //printf("size of:%i\n", sizeof ("*") - 1);
			//printf("strlen(times_str) is :%i\n", strlen(times_str));
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, "/", sizeof ("/")) == 0){
			//printf("minus\n");
			strcpy(output + output_i, divide_str);
			output_i += sizeof(divide_str) -1 ;
			Screen_Text_i += 1;
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, "-", sizeof ("-")) == 0){
			//printf("minus\n");
			strcpy(output + output_i, minus_str);
			output_i += sizeof(minus_str) -1 ;
			Screen_Text_i += 1;
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, "%", sizeof ("%")) == 0){
			//printf("minus\n");
			strcpy(output + output_i, mod_str);
			output_i += sizeof(mod_str) -1 ;
			Screen_Text_i += 1;
			maches = true;
		}
		if(strncmp(Screen_Text + Screen_Text_i, "_", sizeof ("_")) == 0){
			//printf("minus not\n");
			strcpy(output + output_i, minus_str);
			output_i += sizeof(minus_str) -1 ;
			Screen_Text_i += 1;
			maches = true;
		}

		if(maches == false){
			//printf("to:%s\n", Screen_Text + Screen_Text_i);
			strncpy(output + output_i, Screen_Text + Screen_Text_i, 1);
			output_i += 1;
			Screen_Text_i += 1;
			maches = true;
		}
	}
	//printf("will_clear: %i\n", will_clear);
	//printf("will_show_ans: %i\n", will_show_ans);
	if((lenth < 1) || will_clear){
		gtk_widget_hide(Label_Equals);
		gtk_widget_hide(Answer);
	}else{
		on_Button_equals_clicked();
	}

	if(!will_clear){
		gtk_entry_set_text(GTK_ENTRY(Screen), output);
	}else
	{
		gtk_entry_set_text(GTK_ENTRY(Screen), "");
	}

	if(will_show_ans){
		//printf("");
		const char *Answer_Text = gtk_label_get_text(GTK_LABEL(Answer));
		gtk_entry_set_text (GTK_ENTRY (Screen), Answer_Text);
	}

}
/*
void on_Screen_activate(){
	//on_Screen_changed ();
	on_Button_equals_clicked();
}
*/
void on_Button_Dot_clicked(){
	button_pressed();
	add_text_to_Screen(".");
}

void on_Button_Ans_clicked()
{
	button_pressed();
	const gchar *Answer_Text = gtk_label_get_text(GTK_LABEL(Answer));
	gtk_entry_set_text (GTK_ENTRY (Screen), Answer_Text);
	gtk_editable_set_position(GTK_EDITABLE(Screen), -1);
}

void on_Button_equals_clicked()
{
	button_pressed();
	char *Resolt = Calculate_Resolt();
	show_Answer(Resolt);
}

void on_Button_mod_clicked(){
	button_pressed();
	add_text_to_Screen(mod_str);
}

void on_Button_Back_clicked()
{
	button_pressed();
	int posishon = gtk_editable_get_position(GTK_EDITABLE(Screen));
	gtk_editable_delete_text(GTK_EDITABLE(Screen), posishon-1, posishon);
}

void on_Button_CE_clicked()
{
	button_pressed();
	gtk_entry_set_text(GTK_ENTRY(Screen), "");
}

void on_Button_divide_clicked()
{
	button_pressed();
	add_text_to_Screen(divide_str);
}

void on_Button_time_clicked()
{
	button_pressed();
	add_text_to_Screen(times_str);
}

void on_Button_minus_clicked()
{
	button_pressed();
	add_text_to_Screen(minus_str);
}

void on_Button_plus_clicked()
{
	button_pressed();
	add_text_to_Screen(plus_str);
}


void on_Button_0_clicked()
{
	button_pressed();
	add_text_to_Screen("0");
}

void on_Button_1_clicked()
{
	button_pressed();
	add_text_to_Screen("1");
}

void on_Button_2_clicked()
{
	button_pressed();
	add_text_to_Screen("2");
}

void on_Button_3_clicked()
{
	button_pressed();
	add_text_to_Screen("3");
}

void on_Button_4_clicked()
{
	button_pressed();
	add_text_to_Screen("4");
}

void on_Button_5_clicked()
{
	button_pressed();
	add_text_to_Screen("5");
}

void on_Button_6_clicked()
{
	button_pressed();
	add_text_to_Screen("6");
}

void on_Button_7_clicked()
{
	// Can You See ME!
	button_pressed();
	add_text_to_Screen("7");
}

void on_Button_8_clicked()
{
	button_pressed();
	add_text_to_Screen("8");
}

void on_Button_9_clicked()
{
	button_pressed();
	add_text_to_Screen("9");
}
