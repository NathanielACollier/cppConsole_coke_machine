/*
Nathaniel Collier
4/21/2006 12:10:08 PM
Coke Machine Simulation
*/

#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <cstdlib>

using namespace std;


#define DRINK_AMNT 6
#define COIN_TYPE_COUNT 3

struct drink_type
{
 string name;
 double cost;
 int count;
};




// quarter dime nickel
int cash_register[COIN_TYPE_COUNT]=
{
     5,5,5
};



struct user_type
{
 double current_credit;
 int quarters;
 int nickels;
 int dimes;
};

////////////////////////////////// Global Variables //////////////////////////////////////////////
list<char> credit;
user_type user;
bool credit_good = false;
drink_type drink_list[DRINK_AMNT];

///////////////////////////////// Global Functions  /////////////////////////////////////////////////

// stack operations
// pop
template< class object >
object pop(list<object>& stack)
{
  //if (stack.empty()) { throw  "Stack underflow."; }
  object result = stack.back();
  stack.pop_back();
  return result;
}//end pop


// dequeue
template< class object>
object dequeue(list<object>& stack)
{
 //if( stack.empty()) { throw "Queue underflow.";}
 object result = stack.front();
 stack.pop_front();
 return result;
}




void process_input();
char print_drink_list();
void user_clear();
void setup_drinklist();

int main()
{
  // Functions
  
  void user_input();
  // Variables
  

  // Initialize User
  user_clear();
  
  setup_drinklist();
  user_input();

system("pause");
return 0;
}


void setup_drinklist()
{

  drink_list[0].name = "Regular Coke";
  drink_list[0].cost = 0.55;
  drink_list[0].count = 6;
  
  drink_list[1].name = "Diet Coke";
  drink_list[1].cost = 0.55;
  drink_list[1].count = 6;
  
  drink_list[2].name = "Minute Maid Orange";
  drink_list[2].cost = 0.55;
  drink_list[2].count = 6;

  drink_list[3].name = "Dr. Pepper";
  drink_list[3].cost = 0.55;
  drink_list[3].count = 6;

  drink_list[4].name = "Sprite";
  drink_list[4].cost = 0.55;
  drink_list[4].count = 6;

  drink_list[5].name = "Diet Dr. Pepper";
  drink_list[5].cost = 0.55;
  drink_list[5].count = 6;

}



void user_clear()
{
 user.current_credit = 0;
  user.dimes = 0;
  user.nickels = 0;
  user.quarters = 0;
}



char print_drink_list()
{
 char coin = 0;
 cout << "\n"
      << " +----------------------+                                        \n"
      << " |Q - Quarter =25 Cents |     -=<The Coke Machine>=-             \n"
      << " |D - Dime    =10 Cents |     Written By: Nathaniel Collier      \n"
      << " |N - Nickel  = 5 Cents |     4/21/2006 12:10:08 PM              \n"
      << " |R - Return Change     |                                        \n"
      << " |----------------------+                                        \n";
 cout << " [Credit: " << setprecision(2) << fixed << user.current_credit <<  setprecision(0) <<  " ] [Quarters: " << user.quarters << " ] [Dimes: " << user.dimes << " ] [Nickels: " << user.nickels << " ]\n";
 cout << " +- Inventory List ---------------------------------------------+\n";
 for( int i=0; i < DRINK_AMNT; ++i )
 {
   cout << "   " << i << ". " << setw( 20 ) << left << drink_list[i].name << " - "  << setw( 15 ) << ((drink_list[i].count > 0) ? "Available" :"Not Available" )  << "Price: $"  << setw(4) << setprecision(2) << drink_list[i].cost << " Stock: " << setw(3) << setprecision(0) << drink_list[i].count <<  "\n";                                         
 } 
 cout << " +--------------------------------------------------------------+\n";   
 cout << "\nPlease Input Correct Change: \nInput (x=quit)> ";
 cin>> coin;
 return coin;
}


void user_input()
{
  char coin = 0;
  
  do
  {
    system("cls");
    coin = print_drink_list();
    switch( coin )
    {
		case '0':
	 case '1':
	 case '2':
	 case '3':
	 case '4':
	 case '5':
          // purchase a coke
		 if( drink_list[coin-48].count <= 0 )
		 {
           cout << "\n" << drink_list[coin-48].name << " is currently unavailable.\n";
		   system("pause");
		   continue;
		 }
         if( credit_good != true )
		 {
           cout << "\nYou do not have enough credit to purchase a " << drink_list[coin - 48].name << ".\nIt cost " << setprecision(2) << fixed << drink_list[coin - 48].cost << ".\n";
		   system("pause");
		   continue;
		 }
		 else
		 {
          cout << "\nYou have purchased a " << drink_list[coin - 48].name << ".\n" << setprecision(2) << fixed << drink_list[coin - 48].cost << " will now be subtracted from your credit.\n";
		  char coin = 0;
		  int qc=0,dc=0,nc=0;
		  do{
		    if( credit.empty() )
			{
              cout << "\nYou did not put in correct change.\nYour coins have been returned please try again.\n";
			  credit.clear();
		      user_clear();
              system("pause");
			  continue;
			}
			coin = pop( credit );
			switch( coin )
			{
              case 'Q': qc++;   break;
              case 'D': dc++;   break;
              case 'N': nc++;   break;
			}
		    } while( ((qc*.25) + ( dc *.1) + (nc*.05)) != .55 );
		   --(drink_list[coin-48].count);
		  
		   // reset user credit
		     qc=dc=nc=0;
		     for( list<char>::iterator current = credit.begin(); current != credit.end(); ++current )
		     {
              switch( *current )
			  {
               case 'Q': qc++;  break;
               case 'D': dc++;  break;
               case 'N': nc++;  break; 
			  }
		     }
			 user.dimes = dc;
		     user.quarters = qc;
		     user.nickels = nc;
		     user.current_credit = ((qc*.25) + ( dc *.1) + (nc*.05));
		 }
		 system("pause");
		 break;
	 
      case 'R': case 'r' : 
         credit.push_back('R');
      break;
      case 'Q': case 'q' : 
         credit.push_back('Q');
      break;
      case 'D': case 'd' : 
         credit.push_back('D');
      break;
      case 'N': case 'n' : 
         credit.push_back('N');
      break;
	  case 'X': case 'x' :
		  cout << "\nCoke Machine Simulation will now end.\n";
		  exit(0);
      default:
      
      break;     
    } // end switch
	process_input();
  }while( coin != 'X' || coin != 'x'  ); // end while
 // if( credit_check() != true )
  
}


void process_input()
{
 
  int qc=0,dc=0,nc=0;
  
  if( credit.size() <= 0 ) return;
  
    switch( credit.back() )
    {
	 
     case 'R':
		 cout << "\n [Change: ";
        credit.pop_back(); // gets rid of the R
		for( list<char>::iterator current = credit.begin(); current != credit.end(); ++current )
		{
          switch( *current )
		  {
            case 'Q': qc++;   break;
            case 'D': dc++;   break;
            case 'N': nc++;   break;
		  }
		}
        cout << setprecision(2) << fixed << ((qc*.25) + ( dc *.1) + (nc*.05)) << " ] [Quarters: " << qc << " ] [Nickels: " << nc << " ] [Dimes: " << dc << " ]\n";
        credit.clear();
		user_clear();
      system("pause");
		break;
      default:
		  // Run through the linked list counting up coins
		  for( list<char>::iterator current = credit.begin(); current != credit.end(); ++current )
		  {
            switch( *current )
			{
             case 'Q': qc++;  break;
             case 'D': dc++;  break;
             case 'N': nc++;  break; 
			}
		  }
        
	    user.dimes = dc;
		user.quarters = qc;
		user.nickels = nc;
		user.current_credit = ((qc*.25) + ( dc *.1) + (nc*.05));
        if( user.current_credit >= 0.55)
         credit_good = true;
        
    }


}









