/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	LargeNumber.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Provide a memory effecient number system that can hold an infinitly large
 |				number, and functions that can manipulate it.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		January 6th 2013
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Dependancy:	stdio.h,	stdlib.h,	inttypes.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
#include "LargeNumber.h"

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	init_segment
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise function for a segment in a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		value_segment		The value the head segment will be set to.
 |	@return:	segment_making,		The initialisation was a success.
 |				NULL,				Allocation of memory failed, intialisation unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
segment* init_segment(unsigned int value_segment){
	segment* making_segment;
	
	/// Allocates memory for segment and sets it to the given value.
	if( (making_segment = malloc(sizeof(segment))) == NULL){
		return NULL;						//Allocation failed, return error value.
	}
	making_segment->value = value_segment % MAXVALUE;
	making_segment->next = NULL;					//Set the default to having no next.
	making_segment->prev = NULL;					//Set by default to having no previous.
	
	return making_segment;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	free_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	To free all allocated memory used in a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		deleting_largenumber	The large number which will be deleted.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void free_largenumber(large_number* deleting_largenumber){
	segment* conductor = NULL, *todelete;
	
	///If the large number has any segments, they are all freed.
	if( (todelete = deleting_largenumber->head) != NULL){
		///Starting from the head, every segment in the large number is visited, and the
		///previous one is stored, then freed. Once the end is reached the last element is
		///freed.
		conductor = todelete->next;
		
		while( conductor != NULL){
			free(todelete);
			todelete = conductor;
			
			conductor = conductor->next;
		}
		free(todelete);						//Last element otherwise would not be freed.
		todelete = NULL;
	}
	//Memory allocated for large number itself is freed and set to null.
	free(deleting_largenumber);
	deleting_largenumber = NULL;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	init_largenumber
 -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise function for a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		value_number		The value the number will be set to.
 |	@return:	largenumber_making	The initialisation was a success.
 |				NULL,				Allocation of memory failed, intialisation unsuccessful.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* init_largenumber(long long value_number){
	large_number* making_largenumber;
	segment* setting_segment, *conductor;
	
	///Allocates memory for the entire number, then allocates memory for the first
	if( (making_largenumber = malloc(sizeof(large_number))) == NULL){
		return NULL;						//Allocation failed, return error value
	}
	
	if( value_number >= POSITIVE){
		making_largenumber->sign = POSITIVE;
	}
	else{
		making_largenumber->sign = NEGATIVE;
		value_number = -value_number;
	}
	
	if( (setting_segment = init_segment(value_number % MAXVALUE)) == NULL){
		///Allocation failed, free all allocated values and return error value.
		free(making_largenumber);
		making_largenumber = NULL;
		return NULL;
	}
	making_largenumber->head = setting_segment;
	making_largenumber->tail = making_largenumber->head;
	
	conductor = making_largenumber->head;
	
	while( ( (unsigned long long) (value_number /= MAXVALUE)) > 0){
		if( (setting_segment = init_segment(value_number % MAXVALUE)) == NULL){
			///Allocation failed, free all allocated values and return error value.
			free_largenumber(making_largenumber);
			making_largenumber = NULL;
			return NULL;
		}
		conductor->next = setting_segment;
		setting_segment->prev = conductor;
		
		making_largenumber->tail = setting_segment;
	}
	
	making_largenumber->max_dec_places = 0;	//No decimals are allowed by default.
	
	return making_largenumber;
}


/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	fprint_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise print the contents of a large number to a stream in base ten.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		toprint_number,		The large number to be displayed to the given stream.
 |				stream,				Where the number will be displayed to.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void fprint_largenumber(FILE* stream, large_number *toprint_number){
	segment* conductor = toprint_number->tail;
	int counter = 1;
	unsigned int toprint_digit, sigfig;
	
	if(conductor != NULL){
		fprintf(stream, "\n");
		if( toprint_number-> sign == NEGATIVE){
			fprintf(stream, "-");
		}
		fprintf(stream, "%u", conductor->value);
		conductor = conductor->prev;
	}
	
	while( conductor != NULL){
		if(counter == toprint_number->decimal_position){
			fprintf(stream, ".");
		}
		for( sigfig = MAXVALUE/10; sigfig > 0; sigfig /= 10){
			toprint_digit = (conductor->value / sigfig)%10;
			fprintf(stream, "%u", toprint_digit);
		}
		
		conductor = conductor->prev;
	}
	
	fprintf(stream, "\n");
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	print_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise print the contents of a large number to screen in base ten,
 |				shorthand for the fprint_largenumber function.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		toprint_number		The large number to be displayed to the given stream.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
void print_largenumber(large_number *toprint_number){
	fprint_largenumber(stdout, toprint_number);
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	copy_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise print the contents of a large number to screen in base ten.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		tocopy			The number whos values will be copied into another number.
 |	@return:	copied,			The copied number.
 |				NULL,			An error had occured.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* copy_largenumber(large_number* tocopy){
	large_number* copied;
	segment* made_segment, *cond;
	
	if( (copied = init_largenumber(tocopy->head->value)) == NULL){
		return NULL;
	}
	///Every node in the given number is visited. A new segment is created with its value, 
	///and added to the end of the copied number.
	for(cond = tocopy->head->next; cond != NULL; cond = cond->next){
		if( (made_segment = init_segment(cond->value)) == NULL){
			//Allocation unsuccessful, return error value.
			free_largenumber(copied);
			copied = NULL;
			return NULL;
		}
		copied->tail->next = made_segment;
		made_segment->prev = copied->tail;
		copied->tail = made_segment;
	}
	copied->sign = tocopy->sign;
	copied->decimal_position = tocopy->decimal_position;
	copied->max_dec_places = tocopy->max_dec_places;
	
	return copied;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	stolargenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Initialise print the contents of a large number to screen in base ten.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number_string		The character representation of the large number.
 |	@return:	number,				The characters converted into a large number.
 |				NULL,				An error had occured.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
extern large_number* stolargenumber(char* number_string){
	large_number* number;					//Return value.
	segment* made_segment;					//Used to add segments to the large number.
	int number_pointer, char_pointer;
	char* holding;
	unsigned int converting;
	int i;									//loop control.
	
	if( (holding = calloc(10, sizeof(char))) == NULL){
		return NULL;
	}
	
	if( (number = init_largenumber(0)) == NULL){
		free(holding);
		holding = NULL;
		return NULL;						//Allocation failed, return error value.
	}
	number_pointer = 8;
	
	///Goes through all the characters from the end. If they are a number value, they
	///are added to 
	for(char_pointer = strlen(number_string) - 1; char_pointer >= 0; char_pointer--){
		if( number_string[char_pointer] <= '9' || number_string[char_pointer] >= '0'){
			holding[number_pointer] = number_string[char_pointer];
			number_pointer--;
		}
		
		///Updates the number pointer, and if the holding string is full, it will produce a
		///new segment and add it to the end of the large number, then clear the array.
		if( number_pointer < 0){
			converting = 0;
			for( i = 0; i <= 8; i++){
				converting *= 10;
				converting += holding[i] - '0';
			}
			number->tail->value = converting;
			if(char_pointer != 0){			
				if( (made_segment = init_segment(0)) == NULL){
					///Allocation failed, free all allocated memory and return error value.
					free(holding);
					holding = NULL;
					free_largenumber(number);
					number = NULL;
					return NULL;
				}
				number->tail->next = made_segment;
				made_segment->prev = number->tail;
				number->tail = made_segment;
				
			}
			memset(holding, '\0',strlen(holding));
			number_pointer = 8;
		}
	}
	
	///Under the case that a partial number is held after all characters are read, a number
	///is produced and added to the end of the list.
	if( number_pointer != 8){
		converting = 0;
		for( i = number_pointer+1; i <= 8; i++){
			converting *= 10;
			converting += holding[i] - '0';
		}
		number->tail->value = converting;
	}
	print_largenumber(number);
	free(holding);
	holding = NULL;
	return number;
}

/*
 === === === === === === === === === === === === === === === === === === === === === === ===
 *	MATH FUNCTIONS FOR LARGE NUMBERS
 === === === === === === === === === === === === === === === === === === === === === === ===
 */

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	add_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Add a single value to a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				The number that will be added to.
 |				value_adding,		The value that will be added to the number.
 |	@return:	sum,				The number of the value and large number added together.
 |				0,					An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* add_largenumber(large_number* number, int value_adding){
	large_number* sum;						//Return value.
	segment* conductor, *made_segment;
	unsigned long long carry;
	
	if( (sum = init_largenumber(0)) == NULL){
		return NULL;						//Allocation failed, return error value.
	}
	sum->sign = number->sign;
	
	///Does a subtraction operation if more appripriate based on the signs.
	if( sum->sign == POSITIVE && value_adding < 0){
		free_largenumber(sum);
		sum = NULL;
		return sub_largenumber(number, -value_adding);
	}
	else if( sum->sign == NEGATIVE){
		if( value_adding > 0){
			free_largenumber(sum);
			sum = NULL;
			return sub_largenumber(number,value_adding);
		}
		else{
			value_adding = -value_adding;
		}
	}
	carry = (unsigned long long) value_adding;
	conductor = number->head;
	while(1){
		if( conductor != NULL){
			carry += conductor->value;
			conductor = conductor->next;
		}
		//Sets the last value of the sum to hold the maximum allowed value of adding value.
		sum->tail->value = carry % MAXVALUE;
		carry /= MAXVALUE;
		
		if( carry > 0 || conductor != NULL){
			///Adds a new blank segment to the end of the large number.
			if( (made_segment = init_segment(0)) == NULL){
				//Allocation failed, free allocated memory and return error value.
				free_largenumber(sum);
				number = NULL;
				return NULL;
			}
			sum->tail->next = made_segment;
			made_segment->prev = sum->tail;
			sum->tail = made_segment;

			continue;
		}
		else break;
	}
	
	return sum;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	add_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Add a single value to a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number_one,			The first part of the addition.
 |				number_two,			The second part of the addition.
 |	@return:	sum,				The value of the two large numbers added.
 |				NULL,				An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* add_two_largenumbers(large_number* number_one,large_number* number_two){
	large_number* sum;						//Return value.
	segment* conductor_one, *conductor_two, *made_segment;
	unsigned long long value_adding = 0;
	
	///Checks if a subtraction operation would be more appropriate given the signs.
	if( number_one->sign != number_two->sign){
		//sub_two_largenumbers(number_one, number_two);
	}
	
	///Sets the head of the sum to the sum of the first two segments in the given numbers.
	conductor_one = number_one->head;
	conductor_two = number_two->head;
	
	if( conductor_one != NULL){
		value_adding += (unsigned long long) conductor_one->value;
		conductor_one = conductor_one->next;
	}
	if( conductor_two != NULL){
		value_adding += (unsigned long long) conductor_two->value;
		conductor_two = conductor_two->next;
	}
	if( (sum = init_largenumber(value_adding % MAXVALUE)) == NULL){
		return NULL;
	}
	value_adding /= MAXVALUE;
	
	//Until all the segments in both numbers are visited, and all values to be carried are
	//Added to the large number, a new segment is created and added to the sum, and it takes
	//the value of the two large numbers added, plus the carry, modded by one billion.
	while(conductor_one != NULL || conductor_two != NULL || value_adding > 0){
		//Creates a blank segment and adds it to the end of the large number.
		if((made_segment = init_segment(0)) == NULL){
			free_largenumber(sum);
			sum = NULL;
			return NULL;
		}
		sum->tail->next = made_segment;
		made_segment->prev = sum->tail;
		sum->tail = made_segment;
		
		//The value the the current section will be is calculated by adding the prevous
		//carry value, and the two current segments (if valid).
		if( conductor_one != NULL){
			value_adding += (unsigned long long) conductor_one->value;
			conductor_one = conductor_one->next;
		}
		if( conductor_two != NULL){
			value_adding += (unsigned long long) conductor_two->value;
			conductor_two = conductor_two->next;
		}
		//Tail value is set, and the carry value is produced.
		sum->tail->value = value_adding % MAXVALUE;
		
		value_adding /= MAXVALUE;
	}
	
	return sum;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	sub_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Subtracts a value from a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				The number that will be minused from.
 |				value_negate,		The value that will be negated from the large number.
 |	@return:	negated,			The negated value.
 |				NULL,				An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* sub_largenumber(large_number* number, int value_negate){
	large_number* negated;					//Return value;
	segment* cond, *made_segment;
	char satisfied = 0;
	
	if( (negated = init_largenumber(0)) == NULL){
		return NULL;						//Allocation failed, return error value.
	}
	//Sets the sign to the correct value.
	negated->sign = number->sign;
	
	//Chooses an addition operation if more appropriate.
	if( (number->sign == POSITIVE)&&(value_negate < 0)){
		free_largenumber(negated);
		negated = NULL;
		return add_largenumber(number, (long) -1 * value_negate);
	}
	if(number->sign == NEGATIVE){
		if( value_negate > 0){
			free_largenumber(negated);
			negated = NULL;
			return add_largenumber(number, -value_negate);
		}
		value_negate = -value_negate;
	}
	cond = number->head;
	if( cond->value >= value_negate){
		negated->head->value = cond->value - value_negate;
		
		for(cond = cond->next; cond != NULL; cond = cond->next){
			if( (made_segment = init_segment(cond->value)) == NULL){
				///Allocation failed, free allocated variables and return error value.
				free_largenumber(negated);
				negated = NULL;
				return NULL;
			}
			negated->tail->next = made_segment;
			made_segment->prev = negated->tail;
			negated->tail = made_segment;
		}
	}
	
	else{
		value_negate -= number->head->value;
		negated->head->value = 	MAXVALUE - value_negate;

		if(cond->next == NULL){
			if(negated->sign == NEGATIVE){
				negated->sign = POSITIVE;
			}
			else{
				negated->sign = NEGATIVE;
			}
		}
		else{
			for(cond = cond->next; cond != NULL; cond = cond->next){
				if( (made_segment = init_segment(0)) == NULL){
					///Allocation failed, free allocated variables and return error value.
					free_largenumber(negated);
					negated = NULL;
					return NULL;
				}
				negated->tail->next = made_segment;
				made_segment->prev = negated->tail;
				negated->tail = made_segment;
			
				if(satisfied){
					negated->tail->value = cond->value;
				}
				else{
					if( cond->value > 0){
						negated->tail->value = cond->value - 1;
						satisfied = 1;
					}
					else{
						negated->tail->value = MAXVALUE - 1;
					}
				}
			}
		}
	}
	
	return negated;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	sub_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Gets the value of a number negated by another negated number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		value_number,		The number that will be minused from.
 |				value_negate,		The value that will be negated from the large number.
 |	@return:	negated,			The negated value.
 |				NULL,				An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* sub_two_largenumbers(large_number* value_number, large_number* value_negate){
	large_number* negated;					//Return value.
	
	//Used for the basic operations of the subtraction.
	segment* cond_i, *cond_j, *cond_k;		//Conductors to traverse the numbers.
	segment* todelete;						//Used to delete segments for removing zeros.
	int offset, off_count;
	unsigned long long minus_value;
	
	unsigned char is_larger;
	
	if( (negated = copy_largenumber(value_number)) == NULL){
		return NULL;						//Error occured, return error value.
	}
	///If an add operation is more appropriate, it is done in place.
	if( value_number->sign != value_number->sign){
		free(negated);
		negated = NULL;
		return add_two_largenumbers(value_number, value_negate);
	}
	
	/*
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	 |	It is checked to see if the negated value is larger than the base number.
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	*/
	is_larger = 0;							//Determines if the base is larger than negate.
	cond_i = value_number->head;
	cond_j = value_negate->head;
	
	///The two numbers are traversed to check which one ends first to determine which one is
	///larger. If they both end first, the values are checked to see which is larger.
	while(1){
		//Case one, the negated value ends first, the base is automatically larger, continue.
		if( cond_j == NULL && cond_i != NULL){
			is_larger = 1;
			break;
		}
		
		//Case two, the base value ends first, the negated is automatically larger, call
		// a minus operation with the values switched and the sign of the current negate
		//reverse.
		if( cond_i == NULL && cond_j != NULL){
			is_larger = 0;
			break;
		}
		 
		//Case three, they both end at the same time, further checking is required
		if( cond_i == NULL && cond_j == NULL){
			///The first number to have a larger value is larger.
			///If both are equal, zero value is returned.
			for(cond_i = value_number->tail, cond_j = value_negate->tail;
				cond_i != NULL && cond_j != NULL;
				cond_i = cond_i->prev, cond_j = cond_j->prev){
				
				if(cond_i->value > cond_j->value){
					is_larger = 1;			//The base number is larger.
					break;
				}
				if(cond_i->value < cond_j->value){
					is_larger = 0;			//The base number is smaller.
					break;
				}
				else{
					is_larger = 3;			//The value is the same, continue checking.
					continue;
				}
			}
			//If it takes the value of three, the two values are equal, return zero number.
			if( is_larger == 3){
				free_largenumber(negated);
				negated = init_largenumber(0);
				return negated;
			}
			break;
		}
		
		cond_i = cond_i->next;
		cond_j = cond_j->next;
	}
	///Based on the outcome, the appropriate option is selected:
	if( is_larger == 0){
		//If the negated number is larger than the current number, then a minus is
		//performed by calling this function again with the operators in reverse,
		//and the sign reversed on the current negate number.
		
		free(negated);
		if( (negated = sub_two_largenumbers(value_negate, value_number)) == NULL){
			return NULL;					//Error occured, return error value.
		}
		
		if( negated->sign == POSITIVE){
			negated->sign = NEGATIVE;
		}
		else{
			negated->sign = POSITIVE;
		}
		return negated;
	}
	
	
	/*
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	 |	The negation operation:
	 |	Assumptions: based on previous check, the negate value is smaller than the base.
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	*/
	offset = 0;
	for(cond_i = value_negate->head; cond_i != NULL; cond_i = cond_i->next){
		
		//The value is moved by an offset equal to the negated values conductor. This is
		//garaunteed to be initialised, based on the larger/smaller than checking.
		cond_j = negated->head;
		for( off_count = offset; off_count > 0; off_count--){
			cond_j = cond_j->next;
		}
		///A negate is attempted between the two current segments. There are two cases.
		///The first is the negating segment is smaller or equal than the base. In which
		///case thevalue of the current base segment is reduced. The other case is the
		///negated segment is larger than the base segment. In which case it will take a
		///value And the next avaliable nonzero segment is reduced by one.
		
		//Case one: The current negating segment is smaller than the current base segment:
		if( cond_i->value <= cond_j->value){
			cond_j->value -= cond_i->value;	//Value is reduced.
		}
		
		//Case two: The current negating segment is larger than the current base segment:
		else if( cond_i->value > cond_j->value){
			//To make sure overflow does not occur, it is required to do 2 operations.
			minus_value = (unsigned long long) MAXVALUE - cond_i->value;
			minus_value += (unsigned long long) cond_j->value;
			cond_j->value = minus_value;
			//The first non-zero segment is found and reduced by one. Note that based on 
			//previous checking it is garaunteed one exists.
			for( cond_k = cond_j->next;;cond_k = cond_k->next){
				if( cond_k->value > 0){
					cond_k->value--;		//Non zero value found and reduced.
					break;
				}
				else continue;
			}
		}
		
		offset++;
	}
	///Now that the subtraction is complete, it is essential to remove all leading zeros.
	///Note, based on previous checks, it is garaunteed that at least one nonzero value
	///exists:
	for( cond_j = negated->tail->prev; cond_j != NULL;cond_j = cond_j->prev){
		if( cond_j->next->value == 0){
			todelete = cond_j->next;
			cond_j->next = NULL;
			negated->tail = cond_j;
			free(todelete);
			continue;
		}
		else break;
	}
	
	return negated;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	div_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Gets the value of a number negated by another negated number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				The number that will be minused from.
 |				value_negate,		The value that will be negated from the large number.
 |	@return:	negated,			The negated value.
 |				NULL,				An error occured whilst adding a segment.
 |				0,					A divide by zero was attempted.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Note:		This operation has a long runtime. If it is possible to complete it using
 |				conventional means, it will do it in place.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* div_two_largenumbers(large_number* value_number, 
									large_number* value_negate){
	large_number* negated;					//Return value.
	segment* made_segment;					//Used to add segments to the end of the number.
	
	unsigned long long alt_i, alt_j, alt_result;//Used if alternative operation can be done.
	
	//Variables used in division operation
	large_number* base_number, *partial_div;
	segment* cond_i, *cond_j, *swapper, *todelete;
	int div_len, inflation;
	
	/*
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	 |	Initialisation based on parameters:
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	*/
	
	if( (negated = init_largenumber(0)) == NULL){
		return NULL;						//Allocation failed, return error value.
	}
	//The appropriate sign is set based on the two numbers.
	if( value_number->sign == value_negate->sign){
		negated->sign = POSITIVE;
	}
	else{
		negated->sign = NEGATIVE;
	}
	
	/*
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	 |	Case checking for alternative means:
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	*/
	
	///If a divide by zero is attempted, a zero value is returned:
	if(value_negate->head->next == NULL && value_negate->head->value == 0){
		return negated;
	}
	
	//If the two numbers can be represented by a unsigned long long, then a convential 
	//division operation is done in place.
	if(   (value_number->head->next == NULL || value_number->head->next->next == NULL ) 
	   && (value_negate->head->next == NULL || value_negate->head->next->next == NULL ))  {
		//The first unsigned long long is set based on the numbers value.
		alt_i = 0;
		if( value_number->head->next != NULL){
			alt_i += (unsigned long long) value_number->head->next->value * MAXVALUE;
		}
		alt_i += (unsigned long long) value_number->head->value;
		//The second unsigned long long is set based on the negate numbers value.
		alt_j = 0;
		if( value_negate->head->next != NULL){
			alt_j += (unsigned long long) value_negate->head->next->value * MAXVALUE;
		}
		alt_j += (unsigned long long) value_negate->head->value;
		
		alt_result = alt_i/alt_j;
		negated->head->value = alt_result % MAXVALUE;
		
		//If another segment is required to contain the result, it is added to the end
		//of the largenumber
		if( alt_result >= MAXVALUE){
			alt_result /= MAXVALUE;
			if( (made_segment = init_segment(alt_result)) == NULL){
				//Allocation failed, free allocated variables and return error value.
				free_largenumber(negated);
				negated = NULL;
				return NULL;
			}
			negated->tail->next = made_segment;
			made_segment->prev = negated->tail;
			negated->tail = made_segment;
		}
		//The conventional result is returned.
		return negated;
	}
	
	/*
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	 |	The long run-time algorithm:
	 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
	*/
	///The base number will allow a reference to what happened before a partial subtraction
	///took place.
	if( (base_number = init_largenumber(0)) == NULL){
		//Allocation failed, free all allocated memory and return error value.
		free_largenumber(negated);
		negated = NULL;
		return NULL;
	}
	base_number->sign = value_negate->sign;
	
	///Every segment in the main numerator is visited. With every segment visited, the
	///current value is pushed onto the front of the base number. Subtractions take
	///place until there is a change in sign. For every successful subtraction, the
	///negated current section is increased by one and the base number is changed
	///to represent the subtraction result. If unsuccessful, the next value in the
	///main numerator is visited.
	for( cond_i = value_number->tail; cond_i != NULL; cond_i = cond_i->prev){
		if( (made_segment = init_segment(cond_i->value)) == NULL){
			//Allocation failed, release all allocated memory and return error value.
			free_largenumber(negated);
			negated = NULL;
			free_largenumber(base_number);
			base_number = NULL;
			return NULL;
		}
		made_segment->next = base_number->head;
		base_number->head->prev = made_segment;
		base_number->head = made_segment;
		//To improve run time, any leading zero values are removed from the base number.
		for( cond_j = base_number->tail; cond_j != NULL; cond_j = cond_j->prev){
			
		}
		
		partial_div = copy_largenumber(base_number);
	
	}
	
	
	return negated;
}


/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	multiply_largenumber
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Multiplies a single value to a large number.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				The number that will be multiplied.
 |				value_multiplying,	The value that will be multiplied to the number.
 |	@return:	product,			The value of the large number multiplied by given value.
 |				NULL,				An error occured whilst allocating
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* multiply_largenumber(large_number* number, int value_multiplying){
	large_number* product;					//Return value.
	segment* cond_i, *cond_j, *made_segment;
	unsigned long long value_adding;
	
	if( (product = init_largenumber(0)) == NULL){
		return NULL;						//Allocation unsuccessful, return error value.
	}

	///If the signs are different, then the numbers sign is changed.
	if(number->sign == POSITIVE && value_multiplying < 0){
		value_multiplying = -value_multiplying;
		product->sign = NEGATIVE;
	}
	else if(number->sign == NEGATIVE && value_multiplying >= 0){
		product->sign = POSITIVE;
	}
	//Does not need to do computation if value is zero.
	if(value_multiplying == 0){
		return product;
	}
	
	///Goes through every segment in the number, multiplies if, and carries the values
	///through.
	for( cond_i = number->tail; cond_i != NULL; cond_i = cond_i->prev){
		value_adding = (unsigned long long) cond_i->value * value_multiplying;
		
		cond_j = product->head;
		//The value is added until no value is left to carry over to the next segment.
		while(1){
			value_adding += cond_j->value;
			cond_j->value = value_adding % MAXVALUE;
			
			//Checks if there is any value that carries over to next segment.
			if( value_adding /= MAXVALUE){
				///Checks if there is a segment the value can be added to.
				if(cond_j->next == NULL){
					//Segment needed, one is added to the end of the product.
					if( (made_segment = init_segment(0)) == NULL){
						free_largenumber(product);
						product = NULL;
						return NULL;
					}
					cond_j->next = made_segment;
					made_segment->prev = cond_j;
					cond_j = made_segment;
					product->tail = made_segment;
				}
				continue;
			}
			else break;
		}
		
		if(cond_i->prev != NULL){
			//A segment is required to be added to the head of the product.
			if( (made_segment = init_segment(0)) == NULL){
				free_largenumber(product);
				product = NULL;
				return NULL;
			}
			product->head->prev = made_segment;
			made_segment->next = product->head;
			product->head = made_segment;
		}
	}
	
	return product;
}

/*
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	multiply_two_largenumbers
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Multiplies two large numbers together.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		number,				The number that will be multiplied.
 |				value_multiplying,	The value that will be multiplied to the number.
 |	@return:	product,			The value of the two numbers multiplied together.
 |				NULL,				An error occured whilst adding a segment.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 */
large_number* multiply_two_largenumbers(large_number* mult_one, large_number* mult_two){
	large_number* product, *partial_prod, *todelete_number;
	segment *cond, *made_segment;
	int offset, counter;					//Used to track the offset for partial products.
	
	if( (product = init_largenumber(0)) == NULL){
		return NULL;
	}
	
	if( mult_one->sign == mult_two->sign){
		product->sign = POSITIVE;
	}
	else{
		product->sign = NEGATIVE;
	}
	
	offset = 0;
	for( cond = mult_one->head; cond != NULL; cond = cond->next){
		partial_prod = multiply_largenumber(mult_two, cond->value);
		
		//Adds padding to the start of the partial product equal to the current offset - 1.
		for( counter = offset; counter > 0; counter--){
			///Blank segment is added to the front of the partial product.
			if( (made_segment = init_segment(0)) == NULL){
				///Allocation failed, free all allocated memory and return error value.
				free_largenumber(partial_prod);
				partial_prod = NULL;
				free_largenumber(product);
				product = NULL;
				return NULL;
			}
			partial_prod->head->prev = made_segment;
			made_segment->next = partial_prod->head;
			partial_prod->head = made_segment;
		}
		///Adds the partial product to the full product.
		todelete_number = product;			//Required to free after.
		product = add_two_largenumbers(product, partial_prod);
		
		//Frees the allocated numbers that will or have been reassigned values.
		free_largenumber(todelete_number);
		todelete_number = NULL;
		free_largenumber(partial_prod);
		partial_prod = NULL;
		
		offset++;
	}
	
	return product;
}

int main(){
	large_number* one, *two, *three;
	char* buffer = "";
	
	one = init_largenumber(-30);
	two = init_largenumber(-400);
	
	print_largenumber(one);
	print_largenumber(two);
	
	three = sub_two_largenumbers(two, one);
	
	print_largenumber(three);
	
	
	
	
	return 0;
}
